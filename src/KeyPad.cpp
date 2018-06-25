#define MYDEBUG

#include "KeyPad.h"
#include "access.h"

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
   DEBUG_PRINTLN("KeyPad::buttonPressed(int button)");
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

   void KeyPad::reset()
   /** @brief Reset Input-Array
    *
    * Reset InputCode-array by filling with Zeros
    * @return Void
    */
   {
     DEBUG_PRINTLN("KeyPad::reset");
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
     DEBUG_PRINTLN("KeyPad::checkCode(int p)");
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
       accessgranted();
     }
     else
     {
       accessdenied();
     }
   }

   void KeyPad::monitoring(unsigned int timeout)
   {
     DEBUG_PRINTLN("KeyPad::monitoring(unsigned int timeout)");
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
                 DEBUG_PRINTLN(ZahlenfeldPrint[n][m]);
                 delay(1);
                 ++p;
               }
             }
           }
         }
       }
   }
