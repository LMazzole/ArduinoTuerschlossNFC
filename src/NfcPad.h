#ifndef NFCPAD_H_
#define NFCPAD_H_

class NfcPad
{
private:
    uint8_t success;
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};  /* Buffer to store the returned UID */
    uint8_t uidLength; /* Length of the UID (4 or 7 bytes depending on ISO14443A card type)*/

public:
    NfcPad NfcPad();
    void monitoring();
    bool checkid(double idcard);

};


#endif //NFCPAD_H_
