/**
 * @file TuerschlossNFC.ino
 * @author Luca Mazzoleni
 *
 * @brief  Doorlock with Keypad and NFC
 *
 *  Board: Arduino Leonardo \n
 *  Library: \link{https://github.com/adafruit/Adafruit-PN532\endlink \n
 *
 */

/* Includes */
// #define MYDEBUG
#include "debug.h"

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

#include "global.h"
#include "access.h"
#include "KeyPad.h"
#include "NfcPad.h"


//SPI connection
/**Check Adafruit library for more Information \link{https://github.com/adafruit/Adafruit-PN532\endlink
 * @param PN532_SCK Serial Clock
 * @param PN532_MISO Master Input, Slave Outpu
 * @param PN532_MOSI Master Output, Slave Input
 * @param PN532_SS Slave Select
 * */
NfcPad nfcpad(PN532_SCK,
                   PN532_MISO,
                   PN532_MOSI,
                   PN532_SS);

KeyPad keypad;

#if defined(ARDUINO_ARCH_SAMD)
/** for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
 *also change #define in Adafruit_PN532.cpp library file
 */
#define Serial SerialUSB
#endif

//=============================================================================================================
void setup()
{
  Serial.begin(115200); //115200
  DEBUG_PRINTLN("===ARDUINO INIT===");

  pinMode(ledOpen, OUTPUT);
  pinMode(ledClose, OUTPUT);
  pinMode(doorPin, INPUT);
  pinMode(button0, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
  pinMode(button8, INPUT);
  pinMode(button9, INPUT);
  pinMode(buttonStar, INPUT);
  pinMode(buttonHash, INPUT);
  digitalWrite(ledOpen, LOW);
  digitalWrite(ledClose, LOW);
  analogWrite(doorPin, 0);
  digitalWrite(button0, HIGH);
  digitalWrite(button1, HIGH);
  digitalWrite(button2, HIGH);
  digitalWrite(button3, HIGH);
  digitalWrite(button4, HIGH);
  digitalWrite(button5, HIGH);
  digitalWrite(button6, HIGH);
  digitalWrite(button7, HIGH);
  digitalWrite(button8, HIGH);
  digitalWrite(button9, HIGH);
  digitalWrite(buttonStar, HIGH);
  digitalWrite(buttonHash, HIGH);

//==========================================================================================
 nfcpad.SAMConfig();   // configure board to read RFID tags
}

//=========================================================================================
void loop()
{


//=====================================================================================================
//ABFRAGE NFC
  DEBUG_PRINTLN("Abfrage NFC");
  nfcpad.monitoring(100);


//=====================================================================================================
//Check Keypad-Input
  DEBUG_PRINTLN("Check for Input on Keypad");
  keypad.monitoring(8000);
}
