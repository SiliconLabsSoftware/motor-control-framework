#!/usr/bin/env bash

set -euo pipefail

if [[ "$#" -ne 2 ]]; then
  echo "Usage: $0 <compile_commands.json> <workspace>"
  exit 2
fi

compilation_database=$1
workspace=$2

if [[ ! -s "$compilation_database" ]]; then
  echo "Compilation database is missing or empty: $compilation_database"
  exit 1
fi

workspace=$(realpath "$workspace")
project_root="$workspace/motor_control_framework_extension"
filtered_database="$(dirname "$compilation_database")/project_compile_commands.json"

source_roots=(
  "$project_root/examples"
  "$project_root/motor_control_framework/common/arduino_layer/arduino_layer_init.cpp"
  "$project_root/motor_control_framework/common/ble_stream_adapter"
  "$project_root/motor_control_framework/common/simple_foc_platform_specific/current_sense"
  "$project_root/motor_control_framework/common/simple_foc_platform_specific/driver"
  "$project_root/motor_control_framework/config"
  "$project_root/motor_control_framework/overlays"
)

for source_root in "${source_roots[@]}"; do
  if [[ ! -e "$source_root" ]]; then
    echo "Configured Sonar source does not exist: $source_root"
    exit 1
  fi

  if [[ -d "$source_root" ]]; then
    source_link=$(find "$source_root" -type l -print -quit)
    if [[ -n "$source_link" ]]; then
      echo "Refusing to analyze a source tree containing a symbolic link: $source_link"
      exit 1
    fi
  elif [[ -L "$source_root" ]]; then
    echo "Refusing to analyze a symbolic link: $source_root"
    exit 1
  fi
done

examples_root="$project_root/examples/"
arduino_init="$project_root/motor_control_framework/common/arduino_layer/arduino_layer_init.cpp"
ble_root="$project_root/motor_control_framework/common/ble_stream_adapter/"
current_sense_root="$project_root/motor_control_framework/common/simple_foc_platform_specific/current_sense/"
driver_root="$project_root/motor_control_framework/common/simple_foc_platform_specific/driver/"

jq \
  --arg examples_root "$examples_root" \
  --arg arduino_init "$arduino_init" \
  --arg ble_root "$ble_root" \
  --arg current_sense_root "$current_sense_root" \
  --arg driver_root "$driver_root" \
  '
    [
      .[]
      | select(
          (.file | startswith($examples_root))
          or .file == $arduino_init
          or (.file | startswith($ble_root))
          or (.file | startswith($current_sense_root))
          or (.file | startswith($driver_root))
        )
      | select(
          .file
          | test("/examples/mc_anomaly_voice_example/(imu/lsm6dsm_reg\\.[ch]$|model/|recognize_commands\\.(cc|h)$|tflite/)")
          | not
        )
    ]
  ' "$compilation_database" > "$filtered_database.tmp"

command_count=$(jq length "$filtered_database.tmp")
if [[ "$command_count" -eq 0 ]]; then
  echo "No project-owned compiler commands remain after filtering."
  exit 1
fi

while IFS= read -r source_file; do
  if [[ ! -f "$source_file" ]]; then
    echo "A project source referenced by the compilation database is missing: $source_file"
    exit 1
  fi

  canonical_source=$(realpath "$source_file")
  if [[ "$canonical_source" != "$workspace/"* ]]; then
    echo "A project source resolves outside the workspace: $source_file"
    exit 1
  fi
done < <(jq -r '.[].file' "$filtered_database.tmp" | sort -u)

while IFS= read -r compiler; do
  if [[ ! -x "$compiler" ]]; then
    echo "Compiler from the build environment is unavailable: $compiler"
    exit 1
  fi
done < <(jq -r '.[].arguments[0]' "$filtered_database.tmp" | sort -u)

while IFS= read -r include_directory; do
  if [[ ! -d "$include_directory" ]]; then
    echo "Include directory from the build environment is unavailable: $include_directory"
    exit 1
  fi
done < <(
  jq -r '.[] | .arguments[] | select(startswith("-I/")) | ltrimstr("-I")' \
    "$filtered_database.tmp" | sort -u
)

mv "$filtered_database.tmp" "$filtered_database"
echo "Prepared $command_count project-owned compiler commands for SonarCloud."
