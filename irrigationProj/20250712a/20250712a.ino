#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "valueAndMelody.h"
#include "lcdAndSerial.h"
#include "buttonCheck.h"
#include "aboutLed.h"

void setup() {

  _start(1);

  pinMode(setBtn, INPUT_PULLUP);
  pinMode(upBtn, INPUT_PULLUP);
  pinMode(downBtn, INPUT_PULLUP);
  pinMode(entBtn, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(startPin, INPUT);
  pinMode(buzPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);

  for (int i = 0; i<4; i++) {
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], 0);
  }

 

  interval[0] = EEPROM.read(0);
  interval[1] = EEPROM.read(1);
  interval[2] = EEPROM.read(2);
  interval[3] = EEPROM.read(3);
  interval[4] = EEPROM.read(4);
  timeMS = EEPROM.read(5);

  lcd.begin();
  lcd.backlight();
  allLcdPrint(1);
  Serial.begin(9600);
  softSerial.begin(9600);

}


void loop() {
  serialDebug();
  modeTurnRead();
  intvUpDownRead();
  startRead();

  if (playFlag==true) {
    ledPrint();
    stopRead();
    playFlag = false;
  }
}
