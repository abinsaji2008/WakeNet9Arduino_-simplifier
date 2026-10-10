# WakeNet9Arduino

Version **2.2.0**

An Arduino-style wrapper for Espressif ESP-SR WakeNet wake-word detection on supported ESP32 devices, designed for the ESP32-S3 and the `wn9_hiesp` (“Hi ESP”) model.

## Important requirements

- A compatible ESP32 Arduino core / ESP-SR integration is required.
- The selected wake-word model must be available in the ESP-SR model partition named `model` (for example, `wn9_hiesp`).
- This library does not include the proprietary/model binary itself, and installing it does not automatically flash the model partition.
- Hardware and Arduino-core compatibility must be tested on the specific ESP32-S3 board and ESP-SR version.

## Configurable INMP441 microphone pins

Choose the pins in your main sketch. Example for an ESP32-S3 with an INMP441:

```cpp
#include <WakeNet9Arduino.h>

#define MIC_SD_PIN   16  // INMP441 SD -> ESP32 data-in
#define MIC_SCK_PIN  17  // INMP441 SCK/BCLK
#define MIC_WS_PIN   15  // INMP441 WS/LRCLK
#define MIC_USE_LEFT_CHANNEL true  // L/R wired to GND means left slot

WakeNet9Arduino wakeNet;

void onWakeWord() {
  Serial.println("Hi ESP detected");
}

void setup() {
  Serial.begin(115200);

  WakeNet9Arduino::Config config;
  config.dataPin = MIC_SD_PIN;
  config.bclkPin = MIC_SCK_PIN;
  config.wsPin = MIC_WS_PIN;
  config.sampleRate = 16000;
  config.use32BitInput = true;
  config.useLeftChannel = MIC_USE_LEFT_CHANNEL;
  config.wakeWordLabel = "Hi ESP";

  wakeNet.setWakeWordCallback(onWakeWord);
  if (!wakeNet.begin(config)) {
    Serial.println("WakeNet start failed");
  }
}

void loop() {
  wakeNet.handleSerial();
}
```

The example shows the intended API. Confirm that the current library source matches these member names and functions before compiling; the repository must contain the actual implementation files as well as this metadata.

## Pin configuration

- `bclkPin`: INMP441 SCK/BCLK
- `wsPin`: INMP441 WS/LRCLK
- `dataPin`: INMP441 SD connected to ESP32 I2S input
- `useLeftChannel`: choose the slot matching the INMP441 L/R connection
- `sampleRate`: normally 16000 Hz for WakeNet models

## Installation

Arduino IDE → Sketch → Include Library → Add .ZIP Library… and select the release ZIP, or search for `WakeNet9Arduino` in Library Manager after its registry entry has been accepted and indexed.

## Release notes

### 2.2.0
- Documents main-sketch configurable INMP441 pin assignments.
- Declares the expected ESP32 architecture and the separate model-partition requirement.
