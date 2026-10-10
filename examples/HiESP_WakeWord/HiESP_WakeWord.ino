/*
  HiESP_WakeWord
  Example for WakeNet9Simplifier on ESP32-S3.

  Requirements:
  - A compatible ESP32 Arduino core and ESP-SR integration.
  - A model partition named "model" containing the wn9_hiesp model.
  - An INMP441 (or compatible) I2S microphone.
*/

#include <WakeNet9Arduino.h>

// Example ESP32-S3 GPIO assignments. Change these to match your wiring.
constexpr int MIC_BCLK_PIN = 17;
constexpr int MIC_WS_PIN   = 18;
constexpr int MIC_DATA_PIN = 16;

WakeNet9Arduino wakeNet;

void onWakeWordDetected() {
  Serial.println("Wake word detected: Hi ESP");
}

void setup() {
  Serial.begin(115200);
  delay(500);

  WakeNet9Arduino::Config config;
  config.bclkPin = MIC_BCLK_PIN;
  config.wsPin = MIC_WS_PIN;
  config.dataPin = MIC_DATA_PIN;
  config.sampleRate = 16000;
  config.use32BitInput = true;
  config.useLeftChannel = true;
  config.wakeWordLabel = "Hi ESP";

  wakeNet.setSerialOutput(true);
  wakeNet.setWakeWordCallback(onWakeWordDetected);

  if (!wakeNet.begin(config)) {
    Serial.println("WakeNet initialization failed.");
    Serial.println("Check ESP-SR support, microphone wiring, and the 'model' partition.");
    return;
  }

  Serial.println("WakeNet is ready. Say: Hi ESP");
  Serial.println("Serial commands: ON, OFF, LOG ON, LOG OFF, STATUS, HELP");
}

void loop() {
  wakeNet.handleSerial();
}
