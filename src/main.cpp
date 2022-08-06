#include <Arduino.h>
#include <string.h>
#include "soundmanager.cpp"
#include "inputmanager.cpp"

SoundManager soundManager;
InputManager inputManager;

void setup()
{
  Serial.begin(9600);
  soundManager.setup();
  soundManager.play("/test.mp3");
}

void loop()
{
  soundManager.loop();

  String filePath = inputManager.getNfcString();
  if (filePath != "")
    soundManager.play("/" + filePath);
}
