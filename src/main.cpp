#include <Arduino.h>
#include <string.h>
#include "soundmanager.cpp"
#include "inputmanager.cpp"

SoundManager soundManager;
InputManager inputManager;
volatile int64_t lastCheckTime = 0;

void setup()
{
  Serial.begin(9600);
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