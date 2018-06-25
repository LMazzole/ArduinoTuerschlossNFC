#ifndef KEYPAD_H_
#define KEYPAD_H_

#define MYDEBUG
#include "debug.h"

#include "Arduino.h"
#include "global.h"

class KeyPad
{
private:
  int Zahlenfeld[4][3] = {  {button1, button2, button3},
                            {button4, button5, button6},
                            {button7, button8, button9},
                            {buttonStar, button0, buttonHash}};

const char* ZahlenfeldPrint[4][3] = { {"--1--", "--2--", "--3--"},
                                  {"--4--","--5--", "--6--"},
                                  {"--7--", "--8--", "--9--"},
                                  {"--*--", "--0--", "--#--"}};

  /**Initialize a Array for the Inputs*/
  char inputCode[maxIN];

  /**Set a Timeout for the Keypad */
  // const long keypadTimeout = 8000;

public:
    KeyPad();
    void init();
    bool buttonPressed(int button);
    void checkCode(int p);
    void reset();
    void monitoring(unsigned int timeout);
};

#endif //KEYPAD_H_
