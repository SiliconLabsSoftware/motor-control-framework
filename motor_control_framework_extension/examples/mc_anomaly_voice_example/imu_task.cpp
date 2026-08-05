/***************************************************************************//**
 * @file
 * @brief IMU task functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

 #include "sl_status.h"
 #include "imu_task.h"
 #include "FreeRTOS.h"
 #include "task.h"
 #include "Arduino.h"
 #include "imu/sl_lsm6dsm.h"
 #include "sl_sleeptimer.h"
 #include "sl_spidrv_instances.h"
 #include "sl_tflite_micro_model.h"
 #include "sl_tflite_micro_init.h"
 #include "sl_tflite_micro_opcode_resolver.h"
 #include "sl_tflite_micro_config.h"
 #include "ml_common.h"
 #include "constants.h"
/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
 #ifndef LSM6DSM_ID
 #define LSM6DSM_ID            0x6AU
 #endif

 #define ABS(x) ((x) < 0 ? -(x) : (x))

 #ifndef IMU_TASK_STACK_SIZE
 #define IMU_TASK_STACK_SIZE      512
 #endif

 #ifndef IMU_TASK_PRIO
 #define IMU_TASK_PRIO            29
 #endif
/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static TfLiteTensor* model_input;
static tflite::MicroInterpreter* interpreter;
static TaskHandle_t xImuTaskHandle = NULL;
static sl_sleeptimer_timer_handle_t inference_timer;
static int16_t head_ptr = -1;
static bool data_ready = false;
static volatile bool inference_timeout = false;
static sl_lsm6dsm_data_t imu_data[SEQUENCE_LENGTH];
static sl_lsm6dsm_data_t imu_data_prev;
static float latestAnomalyScore;
static bool imu_hw_initialized = false;
static volatile bool deinit_requested = false;
/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static void imu_task(void *arg);
static void imu_init(void);
static void model_init(void);
static sl_status_t accelerometer_read(sl_lsm6dsm_data_t * dst);
static float mae(float* output);
/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
float getAnomaly(void)
{
  return latestAnomalyScore;
}

/***************************************************************************//**
 * Initialize blink example.
 ******************************************************************************/
// Triggered by the inference_timer
static void on_timeout_inference(sl_sleeptimer_timer_handle_t *handle, void* data)
{
  (void)handle;  // unused
  (void)data;  // unused
  inference_timeout = true;
}

void imu_task_init(void)
{
  static StaticTask_t xImuTaskBuffer;
  static StackType_t  xImuStack[IMU_TASK_STACK_SIZE];

  deinit_requested = false;
  xImuTaskHandle = xTaskCreateStatic(imu_task,
                                     "imu task",
                                     IMU_TASK_STACK_SIZE,
                                     ( void * ) NULL,
                                     IMU_TASK_PRIO,
                                     xImuStack,
                                     &xImuTaskBuffer);

  EFM_ASSERT(xImuTaskHandle != NULL);
  Serial.begin(0);
  Serial.println("IMU task initialized");
  inference_timeout = false;
}

void imu_task_deinit(void)
{
  if (xImuTaskHandle == NULL) {
    Serial.println("IMU deinit: task already NULL");
    return;
  }

  Serial.println("IMU deinit: requesting shutdown");
  deinit_requested = true;

  const uint32_t MAX_DEINIT_RETRIES = 10;
  const uint32_t DEINIT_RETRY_DELAY_MS = 50;

  for (uint32_t retry = 0; retry < MAX_DEINIT_RETRIES; retry++) {
    if (xImuTaskHandle != NULL) {
      vTaskDelay(pdMS_TO_TICKS(DEINIT_RETRY_DELAY_MS));
    } else {
      Serial.println("IMU deinit: task exited gracefully");
      break;
    }
  }

  if (xImuTaskHandle != NULL) {
    Serial.println("IMU deinit: force deleting task");
    vTaskDelete(xImuTaskHandle);
    xImuTaskHandle = NULL;
  }

  sl_sleeptimer_stop_timer(&inference_timer);

  if (imu_hw_initialized) {
    Serial.println("IMU deinit: deinitializing hardware");
    sl_lsm6dsm_deinit();
    imu_hw_initialized = false;
  }

  head_ptr = -1;
  data_ready = false;
  inference_timeout = false;
  latestAnomalyScore = 0.0f;
  model_input = nullptr;
  interpreter = nullptr;

  ml_model_release(ML_MODEL_IMU);

  Serial.println("IMU deinit: complete");
}

/*******************************************************************************
 * Torque Sensor Velocity 6PWM task.
 ******************************************************************************/
static void imu_task(void *arg)
{
  (void)&arg;
  sl_status_t status;

  model_init();
  imu_init();

  if (model_input == nullptr || interpreter == nullptr) {
    Serial.println("ERROR: Model initialization failed");
    xImuTaskHandle = NULL;
    vTaskDelete(NULL);
    return;
  }

  sl_lsm6dsm_data_t *dst = (sl_lsm6dsm_data_t *) model_input->data.f;
  sl_sleeptimer_start_periodic_timer_ms(&inference_timer, INFERENCE_PERIOD_MS, on_timeout_inference, NULL, 0, 0);

  while (1) {
    if (deinit_requested) {
      break;
    }

    while (!sl_lsm6dsm_is_accel_data_ready() && !deinit_requested) {
      vTaskDelay(pdMS_TO_TICKS(1));
    }

    if (deinit_requested) {
      break;
    }

    status = accelerometer_read(dst);
    if (status != SL_STATUS_OK) {
      Serial.println("ERROR: Failed to get acceleration");
    }

    if (inference_timeout && data_ready) {
      inference_timeout = false;
      data_ready = false;
      TfLiteStatus invoke_status = interpreter->Invoke();

      if (invoke_status != kTfLiteOk) {
        Serial.println("error: inference failed");
        break;
      }

      float *output = interpreter->output(0)->data.f;
      latestAnomalyScore = SIGMOID(mae(output));
      Serial.print("Anomaly: ");
      Serial.println((uint32_t)(latestAnomalyScore * 100.0));
    }
    vTaskDelay(pdMS_TO_TICKS(1));
  }

  xImuTaskHandle = NULL;
  vTaskDelete(NULL);
}

static float mae(float* output)
{
  float mae_value = 0.0;
  sl_lsm6dsm_data_t* pred_output = (sl_lsm6dsm_data_t*)output;
  for (int i = 0; i < SEQUENCE_LENGTH; i++) {
    mae_value += ABS(pred_output[i].x - imu_data[i].x) + ABS(pred_output[i].y - imu_data[i].y) + ABS(pred_output[i].z - imu_data[i].z);
  }
  return mae_value / (SEQUENCE_LENGTH * ACCELEROMETER_CHANNELS);
}

static void imu_init(void)
{
  sl_status_t status;
  uint8_t device_id;
  sl_lsm6dsm_config_t config = {
    .spi_handle = sl_spidrv_eusart_exp_handle,
    .cs_port = gpioPortA,
    .cs_pin = 6,
  };

  Serial.println("Initializing LSM6DSM IMU...");

  status = sl_lsm6dsm_init(&config);
  if (status != SL_STATUS_OK) {
    Serial.println("ERROR: Initialization failed");
    Serial.println(status);
    return;
  }
  imu_hw_initialized = true;

  status = sl_lsm6dsm_get_device_id(&device_id);
  Serial.println("Device ID: ");
  Serial.println(device_id);
  Serial.println(" (expected 0x6A)");

  Serial.print("\r\nConfiguring accelerometer...\r\n");

  status = sl_lsm6dsm_set_sample_rate(SL_LSM6DSM_ODR_104HZ, SL_LSM6DSM_ODR_104HZ);
  if (status != SL_STATUS_OK) {
    Serial.println("ERROR: Failed to set sample rate");
    Serial.println(status);
    return;
  }

  status = sl_lsm6dsm_set_accel_full_scale(SL_LSM6DSM_ACCEL_FS_2G);
  if (status != SL_STATUS_OK) {
    Serial.println("ERROR: Failed to set accel full scale");
    Serial.println(status);
    return;
  }

  status = sl_lsm6dsm_set_gyro_full_scale(SL_LSM6DSM_GYRO_FS_250DPS);
  if (status != SL_STATUS_OK) {
    Serial.println("ERROR: Failed to set gyro full scale");
    Serial.println(status);
    return;
  }
}

static void model_init(void)
{
  const tflite::Model* model = tflite::GetModel(sl_tflite_model_array);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("ERROR: Invalid IMU model version");
    return;
  }

  // Create op resolver (local instance for IMU model)
  static tflite::MicroMutableOpResolver < 7 > opcode_resolver;
  static bool resolver_initialized = false;
  if (!resolver_initialized) {
    opcode_resolver.AddQuantize();
    opcode_resolver.AddReshape();
    opcode_resolver.AddFullyConnected();
    opcode_resolver.AddShape();
    opcode_resolver.AddStridedSlice();
    opcode_resolver.AddPack();
    opcode_resolver.AddDequantize();
    resolver_initialized = true;
  }
  ml_model_context_t model_ctx = { nullptr, nullptr, nullptr };
  if (ml_model_acquire(ML_MODEL_IMU,
                       model,
                       opcode_resolver,
                       SL_TFLITE_MICRO_ARENA_SIZE,
                       &model_ctx) != SL_STATUS_OK) {
    Serial.println("ERROR: Failed to initialize IMU model");
    return;
  }

  interpreter = model_ctx.interpreter;
  model_input = model_ctx.input_tensor;
  if ((model_input->dims->size != 3) || (model_input->dims->data[0] != 1)
      || (model_input->dims->data[1] != SEQUENCE_LENGTH)
      || (model_input->dims->data[2] != ACCELEROMETER_CHANNELS)
      || (model_input->type != kTfLiteFloat32)) {
    Serial.println("ERROR: Bad input tensor parameters in model");
    return;
  }
}

static sl_status_t accelerometer_read(sl_lsm6dsm_data_t *dst)
{
  sl_status_t status;
  sl_lsm6dsm_data_t imu_acc;
  status = sl_lsm6dsm_get_acceleration(&imu_acc);
  if (status != SL_STATUS_OK) {
    Serial.println("ERROR: Failed to get acceleration");
    return SL_STATUS_FAIL;
  }
  if (!data_ready) {
    if (head_ptr >= 0) {
      imu_data[head_ptr].x = (imu_acc.x - imu_data_prev.x - MEAN_X) / STD_X;
      imu_data[head_ptr].y = (imu_acc.y - imu_data_prev.y - MEAN_Y) / STD_Y;
      imu_data[head_ptr].z = (imu_acc.z - imu_data_prev.z - MEAN_Z) / STD_Z;
      dst[head_ptr].x = imu_data[head_ptr].x;
      dst[head_ptr].y = imu_data[head_ptr].y;
      dst[head_ptr].z = imu_data[head_ptr].z;
    }
    imu_data_prev.x = imu_acc.x;
    imu_data_prev.y = imu_acc.y;
    imu_data_prev.z = imu_acc.z;
    head_ptr++;
  }
  if (head_ptr >= SEQUENCE_LENGTH ) {
    head_ptr = -1;
    data_ready = true;
  }
  return SL_STATUS_OK;
}
