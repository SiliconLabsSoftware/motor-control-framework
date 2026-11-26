#!/usr/bin/env bash

set -euo pipefail

: "${SISDK_DIR:?SISDK_DIR must point to the installed Simplicity SDK}"
: "${AIML_DIR:?AIML_DIR must point to the installed AI/ML extension}"
: "${BUILD_OUTPUT_DIR:?BUILD_OUTPUT_DIR must be set}"

repository_root=$(git rev-parse --show-toplevel)
extension_dir="$repository_root/motor_control_framework_extension"
examples_dir="$extension_dir/examples"

# Build every example at least once. The additional BRD4401C build ensures that
# each board-specific framework overlay is represented in the compilation data.
build_variants=(
  "mc_open_loop_example:brd4186c"
  "mc_open_loop_example:brd4401c"
  "mc_hall_sensor_example:brd4186c"
  "mc_sensorless_example:brd4186c"
  "mc_current_control_example:brd4186c"
  "mc_anomaly_voice_example:brd4120a"
)

mkdir -p "$BUILD_OUTPUT_DIR"

for build_variant in "${build_variants[@]}"; do
  application=${build_variant%%:*}
  board=${build_variant##*:}
  project_file="$examples_dir/$application/$application.slcp"
  generated_dir="$BUILD_OUTPUT_DIR/$application-$board"

  echo "Generating $application for $board"
  slc generate \
    -p "$project_file" \
    -d "$generated_dir" \
    --with "$board" \
    --sdk-package-path "$SISDK_DIR" \
    --sdk-package-path "$AIML_DIR" \
    --sdk-package-path "$extension_dir" \
    --output-type cmake \
    --toolchain gcc

  echo "Building $application for $board"
  (
    cd "$generated_dir/cmake_gcc"
    cmake --workflow --preset project
  )
done
