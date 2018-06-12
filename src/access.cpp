#include "access.h"
#include "global.h"
#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>

void accessgranted()
/** @brief Open the Door
 *
 *  Set the Green Led to HIGH and open the Door for 2 Sec.
 *  @return Void
 */
{
  DEBUG_PRINTLN("Access granted");
  digitalWrite(ledOpen, HIGH);
  analogWrite(doorPin, 255);
  delay(2000); //2sec
  digitalWrite(ledOpen, LOW);
  analogWrite(doorPin, 0);
}

//===============================================================

void accessdenied()
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
