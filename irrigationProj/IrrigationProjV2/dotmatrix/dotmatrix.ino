#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define DATA_PIN 11     
#define CLK_PIN 12      
#define CS_PIN 10       
#define MAX_DEVICES 4

#define SOFT_RX 2
#define SOFT_TX 3

bool textChanState = true;
String serialValue;
char myChar[20];

SoftwareSerial mySoftSerial(SOFT_RX, SOFT_TX); 

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  Serial.begin(9600);
  mySoftSerial.begin(9600);

  display.begin();
  display.setIntensity(5);
  display.displayClear();

  display.displayText("HELLO WORLD", PA_CENTER, 100, 0, PA_PRINT, PA_NO_EFFECT);
}

void loop() {
  if (textChanState == true) {
    textChange("hi");
    textChanState = false;
    Serial.println("기본 메시지 출력됨");
  }

  if (display.displayAnimate()) {
    display.displayReset();
  }

  if (Serial.available()) {
    serialValue = Serial.readStringUntil('\n');
    serialValue.trim();  
    serialValue.toCharArray(myChar, sizeof(myChar));
    textChange(myChar);
    Serial.print("Serial 수신: ");
    Serial.println(myChar);
  }

  if (mySoftSerial.available()) {
    serialValue = mySoftSerial.readStringUntil('\n');
    serialValue.trim();  
    serialValue.toCharArray(myChar, sizeof(myChar));
    textChange(myChar);
    Serial.print("SoftSerial 수신: ");
    Serial.println(myChar);
  }
}

void textChange(char str[]) {
  display.displayClear();
  display.displayText(str, PA_CENTER, 100, 0, PA_PRINT, PA_NO_EFFECT);
  display.displayReset();
}
