#define MYDEBUG

// #include "KeyPad.h"
#include "NfcPad.h"
#include "access.h"
#include "global.h"

NfcPad::NfcPad(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t ss) : Adafruit_PN532(clk, miso, mosi, ss){

}
NfcPad::NfcPad(uint8_t irq, uint8_t reset) : Adafruit_PN532(irq, reset){

}
NfcPad::NfcPad(uint8_t ss) : Adafruit_PN532(ss){

}


  void NfcPad::monitoring(int timeout)
  {
    // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
     // 'uid' will be populated with the UID, and uidLength will indicate
     // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
      DEBUG_PRINTLN("NfcPad::monitoring(int timeout)");
     success = Adafruit_PN532::readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength
                                       ,timeout);

     if (success)
     {
       // Display some basic information about the card
       DEBUG_PRINTLN("Found an ISO14443A card");
       DEBUG_PRINT("  UID Length: ");
       DEBUG_PRINTDEC(uidLength);
       DEBUG_PRINTLN(" bytes");
       DEBUG_PRINT("  UID Value: ");
       Adafruit_PN532::PrintHex(uid, uidLength);

       if (uidLength == 4 || uidLength == 7)
       {
         // We probably have a Mifare Classic card ...
         uint32_t cardid = uid[0];
         cardid <<= 8;
         cardid |= uid[1];
         cardid <<= 8;
         cardid |= uid[2];
         cardid <<= 8;
         cardid |= uid[3];
         Serial.print("Seems to be a Mifare Classic card #");
         Serial.println(cardid);

         if (checkid(cardid))
         {
           accessgranted();
         }
         else
         {
           accessdenied();
         }
       }
       DEBUG_PRINTLN("");

   //    if (uidLength == 7) //first 4 hex should be enough
   //    {
   //      uint32_t cardidl = uid[0];
   //      cardidl <<= 8;
   //      cardidl |= uid[1];
   //      cardidl <<= 8;
   //      cardidl |= uid[2];
   //      cardidl <<= 8;
   //      cardidl |= uid[3];
   //
   //    }

     }

  }

  bool NfcPad::checkid(double idcard)
  /** @brief Check if ID is authorized
   *
   * If the NFC ID from the scanned Card is saved in the authorized List \n
   * You need to Edit here, if you like to add your Card!
   * @param idcard NFC ID from the scanned Card
   * @return True if Authorized \n
   *         False if not*/
  {
    DEBUG_PRINTLN("NfcPad::checkid(double idcard)");
      for(int iterator = 0; iterator < authorizedCardsSize; iterator++)
      {
      	  DEBUG_PRINTLN(authorizedCards[iterator]);
          if (idcard == authorizedCards[iterator])
          {
  	         DEBUG_PRINTLN(authorizedCardsName[iterator]);
              return true;
          }
      }
      DEBUG_PRINTLN("NoAccess with this Card");
      return false;
  }
