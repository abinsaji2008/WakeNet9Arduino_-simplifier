# WakeNet9Arduino

Version **2.2.0**

An Arduino-style wrapper for Espressif ESP-SR WakeNet detection, targeting ESP32-S3 and the `wn9_hiesp` wake word “Hi ESP”.

## Requirements

- Compatible ESP32 Arduino core and ESP-SR headers/libraries.
- ESP-SR model partition named `model` containing the `wn9_hiesp` model. This library does not include the model binary or automatically flash model partitions.
- 16 kHz audio. This implementation expects 32-bit I2S capture transformed to 16-bit samples by `ESP_I2S`.

## Configure INMP441 pins in your main sketch

```cpp
#include <WakeNet9Arduino.h>

#define MIC_SD_PIN   16
#define MIC_SCK_PIN  17
#define MIC_WS_PIN   15
#define MIC_USE_LEFT_CHANNEL true

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
    Serial.println("WakeNet initialization failed");
  }
}

void loop() {
  wakeNet.handleSerial();
}
```

Pin definitions are examples: choose GPIOs appropriate for your board. The same constants can be shared with a streaming library so wake-word and transcription capture use the same microphone pins.

## API

- `WakeNet9Arduino::Config`
- `begin(config)`, `end()`
- `setWakeWordCallback(callback)`
- `setSerialOutput(enabled)`
- `handleSerial()`

Serial Monitor commands: `ON`, `OFF`, `LOG ON`, `LOG OFF`, `STATUS`, `HELP`.

## Installation

Arduino IDE → Sketch → Include Library → Add .ZIP Library… and select a release ZIP. After the Arduino Library Registry accepts and indexes this repository, install through Library Manager by searching for `WakeNet9Arduino`.

## Release notes

### 2.2.0
- Exposes INMP441 BCLK, WS, SD and channel selection through a configuration struct in the main sketch.
- Wraps ESP-SR's native WakeNet interface.
- Requires the external `model` partition with `wn9_hiesp`.
