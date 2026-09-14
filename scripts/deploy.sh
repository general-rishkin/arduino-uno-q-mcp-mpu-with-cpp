#!/usr/bin/env bash
set -euo pipefail

# Upload firmware to Arduino Uno Q1 MCU

USER=arduino
IP=192.168.0.103

# Deploy Application

ssh $USER@$IP mkdir -p /tmp/firmware/
scp -r build/install/. $USER@$IP:/tmp/firmware/

# Once deployed, call `arduino-cli upload -b arduino:zephyr:unoq -i ino_hello/` to flash the MCU firmware.