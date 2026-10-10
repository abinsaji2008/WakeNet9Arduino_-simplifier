#pragma once

#include <Arduino.h>
#include <ESP_I2S.h>

class WakeNet9Arduino {
public:
  struct Config {
    int bclkPin = 17;
    int wsPin = 15;
    int dataPin = 16;
    int sampleRate = 16000;
    bool use32BitInput = true;
    bool useLeftChannel = true;
    uint32_t i2sTimeoutMs = 100;
    const char *wakeWordLabel = "Hi ESP";
  };
  using WakeWordCallback = void (*)();

  WakeNet9Arduino();
  ~WakeNet9Arduino();
  bool begin(const Config &config);
  bool end();
  void handleSerial();
  void setSerialOutput(bool enabled);
  void setWakeWordCallback(WakeWordCallback callback);

private:
  bool beginAudio();
  void processSerialCommand(String command);
  I2SClass i2s_;
  void *models_;
  void *wakeData_;
  const void *wakeInterface_;
  char *wakeModelName_;
  int chunkSize_;
  bool active_;
  bool enabled_;
  bool serialOutput_;
  bool i2sStarted_;
  int sampleRate_;
  int bclkPin_;
  int wsPin_;
  int dataPin_;
  bool useLeftChannel_;
  uint32_t i2sTimeoutMs_;
  String serialLine_;
  int16_t audioBuffer_[1024];
  WakeWordCallback callback_;
};
