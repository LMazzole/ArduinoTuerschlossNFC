#include "KeyPad.h"

KeyPad::KeyPad()
{
 }

//===============================================================

 bool KeyPad::buttonPressed(int button)
 /** @brief Check if Button is pressed
  *
  * Check if Button switch from High to Low and Back to High
  * @param button scanned Button
  * @return True if Pressed
  *         False if not*/
 {
   if (digitalRead(button) == LOW)
   {
     while (1)
     {
       if (digitalRead(button) == HIGH)
         return true;
     }
   }
   return false;
 }

 //===============================================================

 void KeyPad::accesgranted()
 /** @brief Open the Door
  *
  *  Set the Green Led to HIGH and open the Door for 2 Sec.
  *  @return Void
  */
 {
   DEBUG_PRINTLN("Access granted");
   delay(1);
   digitalWrite(ledOpen, HIGH);
   analogWrite(doorPin, 255);
   delay(2000); //2sec
   digitalWrite(ledOpen, LOW);
   analogWrite(doorPin, 0);
 }

 //===============================================================

 void KeyPad::accesdenied()
   /** @brief Leave the Door closed
    *
    * Set the Red LED to HIGH for 1 Sec.
    * @return Void.
    */
   {
     DEBUG_PRINTLN("Access denied");
     digitalWrite(ledClose, HIGH);
     delay(1000);  //1sec
     digitalWrite(ledClose, LOW);
   }

 //===============================================================

   void KeyPad::reset()
   /** @brief Reset Input-Array
    *
    * Reset InputCode-array by filling with Zeros
    * @return Void
    */
   {
     DEBUG_PRINTLN("Reset");
     int r;  //VarReset
     for (r = 0; r < (maxIN); ++r)
     {
       inputCode[r] = '0';
     }
   }

 //===============================================================

   void KeyPad::checkCode(int p)
   /** @brief Check if Code is correct
    *
    * Check if input code is the same as the secret code
    * @param p Count of pressed Buttons
    * @return Void
    */
   {
     Serial.println("Function checkCode");
     int i;              //VarInputCode
     int correct = 0;    //VarCountPW
     for (i = 0; i < (k); i++)
     {
       if (inputCode[i] == secretCode[i])
       {
 	       correct++;
       }
     }
     KeyPad::reset(); //reset code-vector
     if ((correct == k) && (p == k))
     {
       accesgranted();
     }
     else
     {
       accesdenied();
     }
   }

   void KeyPad::monitoring(unsigned int timeout)
   {
      unsigned long callTime = 0;
      unsigned long runTime = 0;
      int breakFlag = 0;
      int p = 0;          //VarCountlenghtIN

     if (buttonPressed(buttonStar))
       {
         DEBUG_PRINTLN("--*--");
         digitalWrite(ledClose, HIGH); /**TODO:Fix Hardware Issue->switch to ledOpen when fixed*/
         delay(20);
         digitalWrite(ledClose, LOW);
         reset();
         callTime = millis(); //Set time of function-call
         while (1)
         {
           runTime=millis();
           if (runTime - callTime >= timeout) //Check for Timeout
           {
             DEBUG_PRINTLN("Keypad Timeout");
             breakFlag = 1;
           }
           if (breakFlag)
             break;

           //Reset rows and cols var for loop
           int n = 0;
           int m = 0;

           for (n = 0; n < 4; n++)  //Check cols
           {
             for (m = 0; m < 3; m++) //Check rows
             {
               if (buttonPressed(buttonHash) || (p >= maxIN))
               {
                 checkCode(p);
                 breakFlag = 1;
               }
               else if (buttonPressed(Zahlenfeld[n][m]))
               {
                 inputCode[p] = (Zahlenfeld[n][m]);
                 Serial.println(ZahlenfeldPrint[n][m]);
                 delay(1);
                 ++p;
               }
             }
           }
         }
       }
   }
