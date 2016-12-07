#include "KeyPad.h"
#include "NfcPad.h"

NfcPad::NfcPad()
{

}

  void NfcPad::monitoring()
  {
    // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
     // 'uid' will be populated with the UID, and uidLength will indicate
     // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
     success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength
                                       ,500); // Timeout is 150ms

     if (success)
     {
       // Display some basic information about the card
       Serial.println("Found an ISO14443A card");
       Serial.print("  UID Length: ");
       Serial.print(uidLength, DEC);
       Serial.println(" bytes");
       Serial.print("  UID Value: ");
       nfc.PrintHex(uid, uidLength);

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
           accesgranted();
         }
         else
         {
           accesdenied();
         }
       }
       Serial.println("");

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
  //	Serial.println(authorizedCardsSize);
  //	Serial.println(authorizedCards[0][0]);
  //	Serial.println(String(authorizedCards[0][1]));
  //	Serial.println(authorizedCards[1][0]);

      for(int iterator = 0; iterator < authorizedCardsSize; iterator++)
      {
  //    	Serial.println("ForLoop");
  //    	Serial.println(iterator);
  //    	Serial.println(authorizedCardsSize);
      	Serial.println(authorizedCards[iterator]);
          if (idcard == authorizedCards[iterator])
          {
  	    Serial.println(authorizedCardsName[iterator]);
              return true;
          }
      }
      Serial.println("NoAccess with this Card");
      return false;
  }
