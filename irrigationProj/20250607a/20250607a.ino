#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <SoftwareSerial.h>

// MAX7219 설정
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

// 핀 설정
#define DATA_PIN 11     // DIN
#define CLK_PIN 12      // CLK
#define CS_PIN 10       // CS or LOAD

#define MAX_DEVICES 4

// 소프트웨어 시리얼 핀 설정
#define SOFT_RX 2
#define SOFT_TX 3

bool textChanState = true;
String serialValue;
char myChar[20];

// 소프트웨어 시리얼 인스턴스
SoftwareSerial mySoftSerial(SOFT_RX, SOFT_TX); // RX, TX 순서!

// MD_Parola 인스턴스 생성
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

  // USB 시리얼 입력 처리
  if (Serial.available()) {
    serialValue = Serial.readStringUntil('\n');
    serialValue.trim();  // 앞뒤 공백, 줄바꿈 제거
    serialValue.toCharArray(myChar, sizeof(myChar));
    textChange(myChar);
    Serial.print("Serial 수신: ");
    Serial.println(myChar);
  }

  // 소프트 시리얼 입력 처리
  if (mySoftSerial.available()) {
    serialValue = mySoftSerial.readStringUntil('\n');
    serialValue.trim();  // 앞뒤 공백, 줄바꿈 제거
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
