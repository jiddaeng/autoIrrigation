#define pinBUZZER 8
#define pinSTART 10
#define START_KEY   (pinMode(pinSTART, INPUT_PULLUP), delay(1), (digitalRead(10)==0))

#include <pitches.h>

#define startPin 10
#define stopPin A3
#define buzPin 8
#define setBtn A0
#define upBtn A1
#define downBtn A2
#define entBtn A3



int nowMode = 0;
 
bool currentsetBtnState = 0;
bool lastsetBtnState = 0;

bool currentupBtnState = 0;
bool currentdownBtnState = 0;

bool lastupBtnState = 0;
bool lastdownBtnState = 0;

bool currententBtnState = 0;
bool lastentBtnState = 0;

bool currentStartState = 0;
bool currentStopState = 0;
bool lastStartState = 0;

 

int interval[] = {1, 1, 1, 1, 1};
int ledPin[] = {4,5,6,7};

LiquidCrystal_I2C lcd(0x3F, 16, 2);
SoftwareSerial softSerial(12, 11);


bool playFlag = true;
int nowTime = 0;

char timeMS = 's';
int intTimeMS = 1;

 

int pumpPin = 9;
bool pumpState = false;
 

void _boot_melody(int count);
void _start(int);


void _boot_melody(int count) {
  for (int j=0; j<count; j++) {
    for (int i=1500; i<2500; i=i+50) {
      tone(pinBUZZER, i, 20);
      delay(10);
    }
  }
  noTone(pinBUZZER);
}
void _start_melody() {
  int melody[]={NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7,0};

  for (int thisNote = 0; thisNote < 9; thisNote++) {
      
    tone(pinBUZZER, melody[thisNote], 100);
    delay(100);
    noTone(pinBUZZER);
  }
}

void _end_melody() {
  int melody[]={NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7,0};

  for (int thisNote = 9; thisNote > 0; thisNote--) {
      
    tone(pinBUZZER, melody[thisNote], 100);
    delay(100);
    noTone(pinBUZZER);
  }
}

void _start(int no) {
  pinMode(pinBUZZER, OUTPUT);
  pinMode(pinSTART, INPUT_PULLUP);

  _boot_melody(1);

  while (!START_KEY) {
    pinMode(pinSTART, OUTPUT);
    digitalWrite(pinSTART, LOW); delay(100);
    digitalWrite(pinSTART, HIGH); delay(50);

    if (no==0) break;
  }
  _boot_melody(2);
}
