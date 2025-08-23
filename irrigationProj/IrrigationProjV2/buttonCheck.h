void buzSound(int cnt) {
  for (int i = 0; i<cnt; i++) {
    tone(buzPin, 1000, 50);
    delay(100);
  }
  
}

void intvCheck(int intv[]) {
  for (int i=0; i<5; i++) {
    if (intv[i] <0){intv[i]=0; buzSound(2);}
    if (intv[i] > 60){intv[i]=60; buzSound(2);}
  }

}

void modeTurnRead() {

  currentsetBtnState = digitalRead(setBtn);

  if (currentsetBtnState == LOW && lastsetBtnState==HIGH) {
    nowMode += 1;
    buzSound(1);
    if (nowMode > 5) {
      nowMode = 0;
    }

    partLcdPrint(nowMode);
    delay(500);
    allLcdPrint(1);
  }

  lastsetBtnState = currentsetBtnState;
}

 

void intvUpDownRead() {

  currentupBtnState = digitalRead(upBtn);
  currentdownBtnState = digitalRead(downBtn);

  if (currentupBtnState == LOW) {
    if(nowMode<5) {
      interval[nowMode] += 1;
      intvCheck(interval);
      EEPROM.write(nowMode, interval[nowMode]);
      buzSound(1);

    } else if(nowMode==5) {
      
      if(timeMS=='m')
        timeMS='s';
      else
        timeMS = 'm';

      EEPROM.write(nowMode, timeMS); 
      buzSound(1);
    }
    allLcdPrint(0);
  }

  if (currentdownBtnState == LOW) {
    if(nowMode<5) {
      interval[nowMode] -= 1;
      intvCheck(interval);
      allLcdPrint(1);
      EEPROM.write(nowMode, interval[nowMode]);
      buzSound(1);
    }
  }  

  lastupBtnState = currentupBtnState;
  lastdownBtnState = currentdownBtnState;
}

 

 

 

void startRead() {
  currentStartState = digitalRead(startPin);
  if (currentStartState==LOW) {playFlag = true; _start_melody();}
}

void stopRead() {
  currentStopState = digitalRead(stopPin);
  if (currentStopState==LOW) playFlag=false;
}
