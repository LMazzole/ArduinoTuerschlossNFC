#ifndef NFCPAD_H_
#define NFCPAD_H_

// #define MYDEBUG

#include "debug.h"
#include "Adafruit_PN532.h"

class NfcPad : public Adafruit_PN532
{
private:
    uint8_t success;
    uint8_t uid[7] = {0, 0, 0, 0, 0, 0, 0};  /* Buffer to store the returned UID */
    uint8_t uidLength; /* Length of the UID (4 or 7 bytes depending on ISO14443A card type)*/

public:
    NfcPad(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t ss);  // Software SPI
    NfcPad(uint8_t irq, uint8_t reset);  // Hardware I2C
    NfcPad(uint8_t ss);  // Hardware SPI
    void monitoring(int timeout);
    bool checkid(double idcard);

};


#endif //NFCPAD_H_
