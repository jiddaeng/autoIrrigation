#define buzPin 8
#define startPin 10
#define START_KEY   (pinMode(startPin, INPUT_PULLUP), delay(1), (digitalRead(startPin)==0))

#include <pitches.h>

#define stopPin A3
#define setBtn A0
#define upBtn A1
#define downBtn A2
#define entBtn A3
#define maxLed 50



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
int neoPin = 3;
Adafruit_NeoPixel pixels(maxLed, neoPin, NEO_GRB + NEO_KHZ800);


bool playFlag = true;
int nowTime = 0;

char timeMS = 's';
int intTimeMS = 1;

 

int pumpPin = 9;
bool pumpState = false;

bool againFlag = false;
 

void _boot_melody(int count);
void _start(int);

void buzSound(int cnt) {
  for (int i = 0; i<cnt; i++) {
    tone(buzPin, 1000, 50);
    delay(30);
  }
}


void _boot_melody(int count) {
  for (int j=0; j<count; j++) {
    for (int i=1500; i<2500; i=i+50) {
      tone(buzPin, i, 20);
      delay(10);
    }
  }
  noTone(buzPin);
}
void _start_melody() {
  int melody[]={NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7,0};

  for (int thisNote = 0; thisNote < 9; thisNote++) {
      
    tone(buzPin, melody[thisNote], 100);
    delay(100);
    noTone(buzPin);
  }
}

void _end_melody() {
  int melody[]={NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7,0};

  for (int thisNote = 9; thisNote > 0; thisNote--) {
      
    tone(buzPin, melody[thisNote], 100);
    delay(100);
    noTone(buzPin);
  }
}

void _start(int breaking) {
  pinMode(buzPin, OUTPUT);
  pinMode(startPin, INPUT_PULLUP);

  _boot_melody(1);
  while (!START_KEY) {
    pinMode(startPin, OUTPUT);
    digitalWrite(startPin, LOW); delay(100);
    digitalWrite(startPin, HIGH); delay(50);

    if (breaking==0) break;
    Serial.println("여기니?");
  }
  _boot_melody(2);
}
