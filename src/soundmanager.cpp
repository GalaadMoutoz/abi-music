#include <Arduino.h>
#include "Audio.h"
#include <string.h>

using namespace std;

// microSD Card Reader connections
#define SD_CS 5
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_SCK 18

// I2S Connections
#define I2S_DOUT 22
#define I2S_BCLK 26
#define I2S_LRC 25

class SoundManager
{
private:
    Audio audio;

public:
    void setup()
    {
        pinMode(SD_CS, OUTPUT);
        digitalWrite(SD_CS, HIGH);

        SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

        if (!SD.begin(SD_CS))
        {
            Serial.println("Error accessing microSD card!");
            while (true)
                ;
        }

        audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
        audio.setVolume(5);
    }

    void play(String path)
    {
        audio.connecttoFS(SD, path.c_str());
    }

    void loop()
    {
        audio.loop();
    }
};
