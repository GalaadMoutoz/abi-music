#include <Arduino.h>
#include <string.h>
#include "soc/soc.h"
#include "soc/rtc.h"
#include "soundmanager.cpp"
#include "inputmanager.cpp"

SoundManager soundManager;
InputManager inputManager;
int64_t lastCheckTime = 0;

void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  soundManager.setup();
  inputManager.setup();

  Serial.println("Systems are online. Ready to play.");
  soundManager.play("boot.mp3");
}

void loop()
{
  soundManager.loop();

  if (esp_timer_get_time() < lastCheckTime + 1000000)
    return;

  lastCheckTime = esp_timer_get_time();

  String filePath = inputManager.getNfcString();
  if (filePath != "")
  {
    Serial.println(filePath);
    soundManager.play(filePath);
  }
}