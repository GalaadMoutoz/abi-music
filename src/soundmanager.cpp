#include <Arduino.h>
#include "Audio.h"
#include <string.h>

using namespace std;

// microSD Card Reader connections
#define VSPI_CS 5
#define VSPI_MOSI 23
#define VSPI_MISO 19
#define VSPI_SCK 18

// I2S Connections
#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC 26

class SoundManager
{
private:
    Audio audio;
    SPIClass *vspi = NULL;

public:
    void setup()
    {
        Serial.println("Initializing Sound Manager ...");

        pinMode(VSPI_CS, OUTPUT);
        digitalWrite(VSPI_CS, HIGH);

        vspi = new SPIClass(VSPI);
        vspi->begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, VSPI_CS);

        if (!SD.begin(VSPI_CS, *vspi))
        {
            Serial.println("Error accessing microSD card!");
            while (true)
                ;
        }

        audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
        audio.setVolume(10);

        Serial.println("Sound Manager is READY.");
    }

    void play(String path)
    {
        audio.stopSong();
        audio.connecttoFS(SD, path.c_str());
    }

    void loop()
    {
        audio.loop();
    }
};
