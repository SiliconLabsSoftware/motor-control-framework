/***************************************************************************//**
 * @file
 * @brief Audio classifier application
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "FreeRTOS.h"
#include "task.h"
#include "sl_power_manager.h"
#include "sl_status.h"
#include "audio_classifier.h"
#include "recognize_commands.h"
#include "config/audio_classifier_config.h"
#include "ml_common.h"
#include "sl_tflite_micro_model_audio.h"
#include "sl_tflite_micro_config.h"
#include "sl_tflite_micro_init.h"
#include "sl_tflite_micro_opcode_resolver.h"
#include "sl_ml_audio_feature_generation.h"
#include "sl_sleeptimer.h"
#include "Arduino.h"
#include <cmath>
#include "tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "motor_control.h"
#include "sl_mic.h"

#define POS(x) ((x) < 0 ? -(x) : (x))
#define NEG(x) ((x) > 0 ? -(x) : (x))

// Pointer to RecognizeCommands object for handling recognitions.
static RecognizeCommands *command_recognizer = nullptr;

// FreeRTOS Task variables
static StaticTask_t xAudioTaskBuffer;
static StackType_t xAudioStack[TASK_STACK_SIZE];
static TaskHandle_t audio_task_handle = NULL;
static tflite::MicroInterpreter *sl_tflite_interpreter = nullptr;
static bool power_manager_em1_added = false;
static volatile bool deinit_requested = false;

// Global audio feature generation state (initialized once, runs continuously)
static bool audio_feature_gen_global_initialized = false;

// Variables for detection/activity
static int32_t detected_timeout = 0;
static int32_t activity_timestamp = 0;
static int32_t activity_toggle_timestamp = 0;
static uint8_t previous_score = 0;
static int32_t previous_score_timestamp = 0;
static int previous_result = 0;
static float target_speed = 15.0f;

// Category label variables
int category_count = 0;
const char* category_labels[] = CATEGORY_LABELS;
static int category_label_count = sizeof(category_labels) / sizeof(category_labels[0]);

static void audio_classifier_task(void *arg);
static void handle_result(int32_t current_time, int result, uint8_t score, bool is_new_command);

/***************************************************************************//**
 * Run model inference
 *
 * Copies the currently available data from the feature_buffer into the input
 * tensor and runs inference, updating the global output tensor.
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 ******************************************************************************/
static sl_status_t run_inference()
{
  // Update model input tensor
  sl_status_t status = sl_ml_audio_feature_generation_fill_tensor(sl_tflite_interpreter->input(0));
  if (status != SL_STATUS_OK) {
    return SL_STATUS_FAIL;
  }
  // Run the model on the spectrogram input and make sure it succeeds.
  TfLiteStatus invoke_status = sl_tflite_interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Processes the output from the output tensor
 *
 * @return
 *   SL_STATUS_OK on success, other value on failure.
 ******************************************************************************/
static sl_status_t process_output()
{
  // Determine whether a command was recognized based on the output of inference
  uint8_t result = 0;
  uint8_t score = 0;
  bool is_new_command = false;
  uint32_t current_time_stamp;
  sl_status_t status = SL_STATUS_OK;

  // Get current time stamp needed by CommandRecognizer
  current_time_stamp = sl_sleeptimer_tick_to_ms(sl_sleeptimer_get_tick_count());

  // Process the latest result from the model output
  TfLiteStatus process_status = command_recognizer->ProcessLatestResults(
    sl_tflite_interpreter->output(0), current_time_stamp, &result, &score, &is_new_command);

  if (process_status == kTfLiteOk) {
    // Take an action based on the new result/score
    handle_result(current_time_stamp, result, score, is_new_command);
  } else {
    status = SL_STATUS_FAIL;
  }

  return status;
}

/***************************************************************************//**
 * Initialize audio feature generation globally (called once at boot)
 ******************************************************************************/
void audio_feature_generation_global_init(void)
{
  if (!audio_feature_gen_global_initialized) {
    Serial.println("Audio: Initializing feature generation globally (one-time)");
    sl_status_t status = sl_ml_audio_feature_generation_init();
    if (status == SL_STATUS_OK) {
      audio_feature_gen_global_initialized = true;
      Serial.println("Audio: Feature generation initialized successfully");
      Serial.println("Audio: Microphone DMA running continuously");
    } else {
      Serial.print("Audio: ERROR - Feature generation init failed: ");
      Serial.println(status);
    }
  }
}

/***************************************************************************//**
 * Initialize audio classifier application.
 ******************************************************************************/
void audio_classifier_init(void)
{
  // Initialize feature generation globally on first call
  audio_feature_generation_global_init();

  deinit_requested = false;
  audio_task_handle = xTaskCreateStatic(audio_classifier_task,
                                        "audio classifier task",
                                        TASK_STACK_SIZE,
                                        (void *) NULL,
                                        TASK_PRIORITY,
                                        xAudioStack,
                                        &xAudioTaskBuffer);
  Serial.begin(0);
  EFM_ASSERT(audio_task_handle != NULL);
}

void audio_classifier_deinit(void)
{
  if (audio_task_handle == NULL) {
    Serial.println("Audio deinit: task already NULL");
    return;
  }

  Serial.println("Audio deinit: requesting shutdown");
  deinit_requested = true;

  const uint32_t MAX_DEINIT_RETRIES = 10;
  const uint32_t DEINIT_RETRY_DELAY_MS = 50;

  for (uint32_t retry = 0; retry < MAX_DEINIT_RETRIES; retry++) {
    if (audio_task_handle != NULL) {
      vTaskDelay(pdMS_TO_TICKS(DEINIT_RETRY_DELAY_MS));
    } else {
      Serial.println("Audio deinit: task exited gracefully");
      break;
    }
  }

  if (audio_task_handle != NULL) {
    Serial.println("Audio deinit: force deleting task");
    vTaskDelete(audio_task_handle);
    audio_task_handle = NULL;
  }

  if (power_manager_em1_added) {
    sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
    power_manager_em1_added = false;
  }

  Serial.println("Audio deinit: keeping microphone running (DMA continues in background)");

  sl_tflite_interpreter = nullptr;
  command_recognizer = nullptr;

  ml_model_release(ML_MODEL_AUDIO);

  detected_timeout = 0;
  activity_timestamp = 0;
  activity_toggle_timestamp = 0;
  previous_score = 0;
  previous_score_timestamp = 0;
  previous_result = 0;
  target_speed = 15.0f;

  Serial.println("Audio deinit: complete");
}

/***************************************************************************//**
 * Audio classifier task function
 *
 * This function is executed by a FreeRTOS task and does not return.
 *
 * @param arg ignored
 ******************************************************************************/
static void audio_classifier_task(void *arg)
{
  (void)arg;

  Serial.println("Audio Classifier\r\n");
  Serial.println("Audio: Starting microphone (feature gen already initialized globally)");

  // Instantiate model from char array.
  // The array may have been created in autogen/sl_ml_model.h or elsewhere.
  const tflite::Model* model = tflite::GetModel(sl_tflite_model_audio_array);
  // Check model schema version
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Error: Invalid model version");
    audio_task_handle = NULL;
    vTaskDelete(NULL);
    return;
  }

  // Create op resolver (local instance for audio model)
  static tflite::MicroMutableOpResolver < 7 > opcode_resolver;
  static bool resolver_initialized = false;
  if (!resolver_initialized) {
    opcode_resolver.AddConv2D();
    opcode_resolver.AddDepthwiseConv2D();
    opcode_resolver.AddAdd();
    #if SL_TFLITE_MICRO_MODEL_TYPE == SL_TFLITE_MICRO_MODEL_AUDIO_ENHANCED
    opcode_resolver.AddAveragePool2D();
    #elif SL_TFLITE_MICRO_MODEL_TYPE == SL_TFLITE_MICRO_MODEL_AUDIO_BASE
    opcode_resolver.AddMaxPool2D();
    #endif
    opcode_resolver.AddReshape();
    opcode_resolver.AddFullyConnected();
    opcode_resolver.AddSoftmax();
    resolver_initialized = true;
  }

  ml_model_context_t model_ctx = { nullptr, nullptr, nullptr };
  if (ml_model_acquire(ML_MODEL_AUDIO,
                       model,
                       opcode_resolver,
                       SL_TFLITE_MICRO_ARENA_SIZE,
                       &model_ctx) != SL_STATUS_OK) {
    Serial.println("ERROR: Failed to initialize audio model");
    audio_task_handle = NULL;
    vTaskDelete(NULL);
    return;
  }
  sl_tflite_interpreter = model_ctx.interpreter;

  // Instantiate CommandRecognizer
  static RecognizeCommands static_recognizer(sl_tflite_micro_get_error_reporter(), SMOOTHING_WINDOW_DURATION_MS,
                                             DETECTION_THRESHOLD, SUPPRESSION_TIME_MS, MINIMUM_DETECTION_COUNT, IGNORE_UNDERSCORE_LABELS);
  command_recognizer = &static_recognizer;

  const TfLiteTensor* input = sl_tflite_interpreter->input(0);
  const TfLiteTensor* output = sl_tflite_interpreter->output(0);

  // Validate model tensors
  if ((output->dims->size == 2) && (output->dims->data[0] == 1)) {
    category_count = output->dims->data[1];
  } else {
    Serial.println("ERROR: Invalid output tensor shape");
    Serial.println("expecting an output tensor of shape [1,x]");
    Serial.println("where x is the number of classification results");
  }

  if (category_count != category_label_count) {
    Serial.println("WARNING: Number of categories(%d) is not equal to the number of labels(%d).\n");
    Serial.println("Make sure that CATEGORY_LABELS is configured correctly for the model in use.\n");
    Serial.print("category_count:");
    Serial.print(category_count);
    Serial.print(", category_label_count:");
    Serial.println(category_label_count);
  }

  // Validate input/output type of the tflite model
  if ((input->type != kTfLiteInt8) || (output->type != kTfLiteInt8)) {
    Serial.println("ERROR: Invalid input/output tensor type.\n");
    Serial.println("Application requires input and output tensors to be of type int8.\n");
    audio_task_handle = NULL;
    vTaskDelete(NULL);
    return;
  }

  // Add EM1 requirement to allow microphone sampling
  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
  power_manager_em1_added = true;

  while (1) {
    if (deinit_requested) {
      break;
    }

    // Delay task in order to do periodic inference
    #if SL_TFLITE_MICRO_MODEL_TYPE == SL_TFLITE_MICRO_MODEL_AUDIO_ENHANCED
    vTaskDelay(pdMS_TO_TICKS(SL_TFLITE_MODEL_LATENCY_MS / 2));
    #elif SL_TFLITE_MICRO_MODEL_TYPE == SL_TFLITE_MICRO_MODEL_AUDIO_BASE
    vTaskDelay(pdMS_TO_TICKS(100));
    #endif

    if (deinit_requested) {
      break;
    }

    // Perform a word detection
    sl_ml_audio_feature_generation_update_features();
    sl_status_t inference_status = run_inference();
    if (inference_status == SL_STATUS_OK) {
      process_output();
    }
  }

  audio_task_handle = NULL;
  vTaskDelete(NULL);
}

/***************************************************************************//**
 * Handle inference result
 *
 * This function is called whenever we have a successful inference result.
 *
 * @param current_time timestamp of the inference result.
 * @param result classification result, this is number >= 0.
 * @param score the score of the result. This is number represents the confidence
 *   of the result classification.
 * @param is_new_command true if the result is a new command, false otherwise.
 ******************************************************************************/
static void handle_result(int32_t current_time, int result, uint8_t score, bool is_new_command)
{
  const char *label = get_category_label(result);

  if (is_new_command) {
    Serial.print("Detected class=");
    Serial.print(result);
    Serial.print(" label=");
    Serial.print(label);
    Serial.print(" score=");
    Serial.print(score);
    Serial.print(" @");
    Serial.print(current_time);
    Serial.println("ms");
    if (motor_p) {
#if SL_TFLITE_MICRO_MODEL_TYPE == SL_TFLITE_MICRO_MODEL_AUDIO_BASE
      switch (result) {
        case 1:  // Stop motor
          motor_p->target = 0.0f;  // Stop motor
          break;
        case 0: // Start motor
          motor_p->target = 15.0f;  // Set to target speed
          break;
        default:
          break;
      }
#elif SL_TFLITE_MICRO_MODEL_TYPE == SL_TFLITE_MICRO_MODEL_AUDIO_ENHANCED
      switch (result) {
        case 4:  // Stop motor
          motor_p->target = 0.0f;  // Stop motor
          break;
        case 5: // Start motor
          if (target_speed == 0.0f) {
            target_speed = 15.0f;
          }
          motor_p->target = target_speed;  // Set to target speed
          break;
        case 3: // Decrease speed, and if running, set to target speed
          if (target_speed > 0.0f) {
            target_speed -= target_speed >= 5.0f ? 5.0f : 0;  // Decrease speed
          } else {
            target_speed += target_speed <= -5.0f ? 5.0f : 0;  // Increase speed
          }
          if (motor_p->target != 0.0f) {
            motor_p->target = target_speed;
          }
          break;
        case 2: // Increase speed, and if running, set to target speed
          if (target_speed > 0.0f) {
            target_speed += target_speed < 25.0f ? 5.0f : 0;  // Increase speed
          } else {
            target_speed -= target_speed >= -25.0f ? 5.0f : 0;  // Decrease speed
          }
          if (motor_p->target != 0.0f) {
            motor_p->target = target_speed;
          }
          break;
        case 1: // Turn right
          target_speed = POS(target_speed);
          if (motor_p->target != 0.0f) {
            motor_p->target = target_speed;
          }
          break;
        case 0: // Turn left
          target_speed = NEG(target_speed);
          if (motor_p->target != 0.0f) {
            motor_p->target = target_speed;
          }
          break;
        default:
          break;
      }
#endif
    }
    detected_timeout = current_time + SUPPRESSION_TIME_MS;
  } else if (detected_timeout != 0 && current_time >= detected_timeout) {
    detected_timeout = 0;
    previous_score = score;
    previous_result = result;
    previous_score_timestamp = current_time;
  }

  // When detection timeout has passed we start to check for activity, which is
  // signaled by a change in the score value.
  if (detected_timeout == 0) {
    if (previous_score == 0) {
      previous_result = result;
      previous_score = score;
      previous_score_timestamp = current_time;
      return;
    }

    // Calculate the rate of difference in score between the two last results
    const int32_t time_delta = current_time - previous_score_timestamp;
    const int8_t score_delta = (int8_t)(score - previous_score);
    const float diff = (time_delta > 0) ? std::fabs(score_delta) / time_delta : 0.0f;

    previous_score = score;
    previous_score_timestamp = current_time;

    if (diff >= SENSITIVITY || (previous_result != result)) {
      previous_result = result;
      activity_timestamp = current_time + 500;
    } else if (current_time >= activity_timestamp) {
      activity_timestamp = 0;
    }

    if (activity_timestamp != 0) {
      if (current_time - activity_toggle_timestamp >= 100) {
        activity_toggle_timestamp = current_time;
      }
    }
  }
}

/***************************************************************************//**
 * Get the label for a certain category/class
 *
 * @param index
 *   index of the category/class
 *
 * @return
 *   pointer to the label string. The label is "?" if no corresponding label
 *   was found.
 ******************************************************************************/
const char * get_category_label(int index)
{
  if ((index >= 0) && (index < category_label_count)) {
    return category_labels[index];
  } else {
    return "?";
  }
}
