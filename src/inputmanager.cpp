#include <Arduino.h>
#include <SPI.h>
#include <mfrc522/MFRC522.h>
#include <NfcAdapter.h>
#include <string.h>

using namespace std;

#define HSPI_CS 15
#define HSPI_MOSI 13
#define HSPI_MISO 12
#define HSPI_SCK 14

#define RST_PIN 0

class InputManager
{
private:
    MFRC522 *reader = new MFRC522(HSPI_CS, RST_PIN);
    NfcAdapter *nfc = new NfcAdapter(reader);
    SPIClass *hspi;

    String lastCardContent = "";

    String readCard()
    {
        String result = "";

        for (byte i = 0; i < reader->uid.size; i++)
            result += String(reader->uid.uidByte[i], HEX);

        result.toUpperCase();

        return result;
    }

public:
    void setup()
    {
        Serial.println("Initializing Input Manager ...");

        hspi = new SPIClass(HSPI);
        hspi->begin(HSPI_SCK, HSPI_MISO, HSPI_MOSI, HSPI_CS);

        reader->PCD_Init(*hspi);
        nfc->begin();

        Serial.println("Input Manager is READY.");
    }

    String getNfcString()
    {
        if (!nfc->tagPresent())
            return "";

        NfcTag tag = nfc->read();

        // String uid = tag.getUidString();
        // Serial.println(uid);

        if (!tag.hasNdefMessage())
        {
            // Serial.println("no ndef message");
            return "";
        }

        NdefMessage message = tag.getNdefMessage();
        int recordCount = message.getRecordCount();
        // Serial.println("Record count : " + String(recordCount));
        if (recordCount == 0)
        {
            // Serial.println("no record");
            return "";
        }

        NdefRecord record = message.getRecord(0);
        if (record.getTypeLength() < 1 || record.getType()[0] != NdefRecord::RTD_TEXT)
        {
            Serial.println("wrong record type");
            return "";
        }

        String text(record.getPayload(), record.getPayloadLength());

        if (text.length() > 3)
            text = text.substring(3);

        if (text == lastCardContent)
            return "";

        lastCardContent = text;

        return text;
    }
};
