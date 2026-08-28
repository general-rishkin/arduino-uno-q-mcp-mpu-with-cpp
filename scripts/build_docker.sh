#!/usr/bin/env bash

# Build a Docker image for the Arduino Uno Q1 MPU with all binaries of this repo.
set -euo pipefail

PROJECT_ROOT="."
INSTALL_DIR="build/install"
IMAGE_NAME="learning-arduino-q"
TAR_FILE="${INSTALL_DIR}/${IMAGE_NAME}.tar.gz"

mkdir -p "${INSTALL_DIR}"

docker build -t "${IMAGE_NAME}" --target runtime -f "${PROJECT_ROOT}/.devcontainer/Dockerfile" "${PROJECT_ROOT}"
docker save "${IMAGE_NAME}" | gzip > "${TAR_FILE}"

echo "==> Successfully saved ${TAR_FILE}"
