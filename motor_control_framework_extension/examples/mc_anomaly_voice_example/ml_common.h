#ifndef ML_COMMON_H
#define ML_COMMON_H

#include "sl_tflite_micro_config.h"
#include "sl_status.h"

#ifdef __cplusplus
#include "sl_memory_manager.h"
#include <cstddef>
#include <cstdint>
#include <new>
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

typedef enum {
  ML_MODEL_NONE = 0,
  ML_MODEL_AUDIO = 1,
  ML_MODEL_IMU = 2,
} ml_model_id_t;

typedef struct {
  tflite::MicroInterpreter *interpreter;
  TfLiteTensor *input_tensor;
  TfLiteTensor *output_tensor;
} ml_model_context_t;

typedef struct {
  ml_model_id_t active_model;
  void *arena_allocation;
  uint8_t *arena_aligned;
  size_t arena_size;
  tflite::MicroInterpreter *interpreter;
} ml_runtime_state_t;

inline ml_runtime_state_t& ml_runtime_state()
{
  static ml_runtime_state_t state = {
    ML_MODEL_NONE,
    nullptr,
    nullptr,
    0U,
    nullptr
  };
  return state;
}

inline sl_status_t ml_model_acquire(ml_model_id_t model_id,
                                    const tflite::Model *model,
                                    tflite::MicroOpResolver &opcode_resolver,
                                    size_t arena_size,
                                    ml_model_context_t *ctx)
{
  if ((model == nullptr) || (ctx == nullptr) || (arena_size == 0U)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  ml_runtime_state_t &state = ml_runtime_state();

  if ((state.active_model != ML_MODEL_NONE) && (state.active_model != model_id)) {
    if (state.interpreter != nullptr) {
      delete state.interpreter;
      state.interpreter = nullptr;
    }
    state.active_model = ML_MODEL_NONE;
  }

  if (state.arena_size < arena_size) {
    if (state.interpreter != nullptr) {
      delete state.interpreter;
      state.interpreter = nullptr;
    }
    if (state.arena_allocation != nullptr) {
      sl_free(state.arena_allocation);
      state.arena_allocation = nullptr;
      state.arena_aligned = nullptr;
      state.arena_size = 0U;
    }
    state.arena_allocation = sl_malloc(arena_size + 15U);
    if (state.arena_allocation == nullptr) {
      return SL_STATUS_ALLOCATION_FAILED;
    }
    uintptr_t aligned_addr = ((uintptr_t)state.arena_allocation + 15U) & ~(uintptr_t)0x0FU;
    state.arena_aligned = reinterpret_cast<uint8_t *>(aligned_addr);
    state.arena_size = arena_size;
  }

  if (state.interpreter == nullptr) {
    state.interpreter = new tflite::MicroInterpreter(
      model,
      opcode_resolver,
      state.arena_aligned,
      state.arena_size
      );
    if (state.interpreter == nullptr) {
      return SL_STATUS_ALLOCATION_FAILED;
    }
    if (state.interpreter->AllocateTensors() != kTfLiteOk) {
      delete state.interpreter;
      state.interpreter = nullptr;
      return SL_STATUS_FAIL;
    }
  }

  state.active_model = model_id;
  ctx->interpreter = state.interpreter;
  ctx->input_tensor = state.interpreter->input(0);
  ctx->output_tensor = state.interpreter->output(0);

  return SL_STATUS_OK;
}

inline void ml_model_release(ml_model_id_t model_id)
{
  ml_runtime_state_t &state = ml_runtime_state();

  if (state.active_model != model_id) {
    return;
  }
  if (state.interpreter != nullptr) {
    delete state.interpreter;
    state.interpreter = nullptr;
  }
  state.active_model = ML_MODEL_NONE;
}

#endif // __cplusplus

#endif
