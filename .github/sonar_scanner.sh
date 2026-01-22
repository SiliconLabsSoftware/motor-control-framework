#!/bin/bash
# This script prepares and runs the sonar-scanner.

set -euo pipefail

echo ">>> [sonar_scanner.sh] Preparing SonarQube analysis..."

# Determine Branch Name for non-PR analysis
# Priority:
# 1. INPUT_SONAR_BRANCH (Manual override for Sonar project branch)
# 2. INPUT_BRANCH (Manual override for Git branch)
# 3. SONAR_BRANCH_NAME (GitHub ref_name)
# 4. git rev-parse (Local fallback)
BRANCH_NAME=${INPUT_SONAR_BRANCH:-${INPUT_BRANCH:-${SONAR_BRANCH_NAME:-$(git rev-parse --abbrev-ref HEAD)}}}

SONAR_HOST_URL=${SONAR_HOST_URL:-""}
SONAR_TOKEN=${SONAR_TOKEN:-""}

PR_KEY=${SONAR_PR_KEY:-""}
PR_SOURCE=${SONAR_PR_BRANCH:-""}
PR_TARGET=${SONAR_PR_BASE:-""}

COMPONENTS=${COMPONENTS:-"simplefoc-port-mg24"}
GITHUB_EVENT_NAME=${GITHUB_EVENT_NAME:-"push"}
PROJECT_BASE_DIR=${PROJECT_BASE_DIR:-$(pwd)}
GITHUB_SHA=${GITHUB_SHA:-$(git rev-parse HEAD)}

if [ -z "$SONAR_HOST_URL" ] || [ -z "$SONAR_TOKEN" ]; then
    echo "Error: SONAR_HOST_URL and SONAR_TOKEN environment variables must be set."
    exit 1
fi

COMPONENTS_CSV=$(echo "$COMPONENTS" | tr ' ' ',')

ARGS=(
    "-Dsonar.token=${SONAR_TOKEN}"
    "-Dsonar.host.url=${SONAR_HOST_URL}"
    "-Dsonar.projectBaseDir=${PROJECT_BASE_DIR}"
    "-Dproject.settings=${PROJECT_BASE_DIR}/.github/sonar-project.properties"
    "-Dsonar.cfamily.variants.names=${COMPONENTS_CSV}"
    "-Dsonar.scm.revision=${GITHUB_SHA}"
)
if [ "$GITHUB_EVENT_NAME" == "pull_request" ]; then
    echo ">>> [sonar_scanner.sh] Mode: Pull Request #$PR_KEY"
    ARGS+=(
        "-Dsonar.pullrequest.key=${PR_KEY}"
        "-Dsonar.pullrequest.branch=${PR_SOURCE}"
        "-Dsonar.pullrequest.base=${PR_TARGET}"
    )
else
    echo ">>> [sonar_scanner.sh] Mode: Branch Analysis ($BRANCH_NAME)"
    echo ">>> [sonar_scanner.sh] Event type: $GITHUB_EVENT_NAME"
    ARGS+=(
        "-Dsonar.branch.name=${BRANCH_NAME}"
    )
fi

echo ">>> [sonar_scanner.sh] Running sonar-scanner..."
sonar-scanner "${ARGS[@]}"

echo ">>> [sonar_scanner.sh] Analysis submitted."
