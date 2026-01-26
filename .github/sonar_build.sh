#!/bin/bash

# This script builds the project components and collects coverage data for SonarQube analysis.
# It is designed to be used inside Docker containers set up for SonarQube scanning.
# Usage: ./sonar_build.sh [target]
# where [target] can be "all" or a space-separated list of components/variants to build.

set -euo pipefail

# --- Configuration ---
COMPONENTS=${COMPONENTS}
PYTHON_VARIANTS=${PYTHON_VARIANTS}

BW_PATH="/opt/build-wrapper-linux-x86/build-wrapper-linux-x86-64"

TARGET=${1:-"all"}

echo ">>> [sonar_build.sh] Starting build process for target: $TARGET"

#This is for Python variants. IT IS  EXPERIMENTAL USE WITH CAUTION
if [ -n "$PYTHON_VARIANTS" ]; then
    for variant in $PYTHON_VARIANTS; do
        if [[ "$TARGET" == "all" ]] || [[ " $TARGET " =~ " $variant " ]]; then
            echo ">>> [sonar_build.sh] Processing Python variant: $variant"
            PROJECT_DIR="projects/$variant"

            if [ -d "$PROJECT_DIR" ]; then
                pushd "$PROJECT_DIR" > /dev/null

                if [ ! -d ".venv" ]; then
                    echo "Creating virtual environment for $variant..."
                    make venv
                fi

                source .venv/bin/activate

                echo "Installing coverage..."
                python3 -m pip install coverage

                echo "Running tests for $variant..."
                python3 -m coverage run --branch -m unittest discover -s tests/unit

                echo "Generating XML report: coverage.xml"
                python3 -m coverage xml -o "coverage.xml"

                if [ ! -f "coverage.xml" ]; then
                    echo "Error: coverage.xml was not generated for $variant"
                    exit 1
                fi
                if [ ! -s "coverage.xml" ]; then
                    echo "Error: coverage.xml is empty for $variant"
                    exit 1
                fi

                deactivate
                popd > /dev/null
            else
                echo "Warning: $PROJECT_DIR directory not found. Skipping."
            fi
        fi
    done
fi

if [ -n "$COMPONENTS" ]; then
    BW_CHECKED=false

    for comp in $COMPONENTS; do
        if [[ "$TARGET" == "all" ]] || [[ " $TARGET " =~ " $comp " ]]; then

            if [ "$BW_CHECKED" = false ]; then
                echo ">>> [sonar_build.sh] Building C/C++ components with build-wrapper..."

                if [ ! -f "$BW_PATH" ]; then
                    echo "Warning: build-wrapper not found at $BW_PATH. Checking PATH..."
                    if command -v build-wrapper-linux-x86-64 &> /dev/null; then
                        BW_PATH="build-wrapper-linux-x86-64"
                    else
                        echo "Error: build-wrapper-linux-x86-64 not found. Cannot proceed with CFamily analysis."
                        exit 1
                    fi
                fi

                mkdir -p sonar-bw
                BW_CHECKED=true
            fi

            echo ">>> [sonar_build.sh] Building component: $comp"

            OUT_DIR="sonar-bw/$comp"
            ########################
            # Make sure the make command is updated here to match your project's build system!
            ########################
            $BW_PATH --out-dir "$OUT_DIR" make $comp

            echo ">>> [sonar_build.sh] Finished building $comp"
        fi
    done
fi

echo ">>> [sonar_build.sh] Build process complete."
