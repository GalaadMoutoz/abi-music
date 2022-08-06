#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <string.h>

using namespace std;

#define SS_PIN 5
#define RST_PIN 27

class InputManager
{
private:
    MFRC522 *reader = new MFRC522(SS_PIN, RST_PIN);

    String readCard()
    {
        String result = "";
        for (byte i = 0; i < reader->uid.size; i++)
            result += String(reader->uid.uidByte[i], HEX);

        result.toUpperCase();
        Serial.println(result);

        return result;
    }

public:
    void setup()
    {
        SPI.begin();
        reader->PCD_Init();

        Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
    }

    String getNfcString()
    {
        if (!reader->PICC_IsNewCardPresent())
            return "";
        if (!reader->PICC_ReadCardSerial())
            return "";

        return readCard();
    }
};
