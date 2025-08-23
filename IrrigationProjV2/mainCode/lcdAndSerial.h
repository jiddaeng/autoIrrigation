void partLcdPrint(int mode) {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (mode>=0 && mode<4) {
    lcd.print("LED"); lcd.print(mode+1); lcd.print(" time set");
  }
  else if(mode==4)
    lcd.print("waiting time");
  else if(mode==5)
    lcd.print("minute or second");
}

void ledLcdPrint(int nowLed, int nowTime) {
  lcd.setCursor(0, 0);
  lcd.print("set: ");

  for (int i=0; i<4; i++) {
    char t[10];
    sprintf(t, "%02d",((int)interval[i]));
    lcd.print(t);
    lcd.print(' ');
  }

  lcd.setCursor(0, 1);

  lcd.print("now: ");

  for (int i=0;i<4;i++) {
    if (i==nowLed) {
      char tt[10];
      sprintf(tt, "%02d", (int)(interval[i]-nowTime));
      lcd.print(tt);
      
    } else if(i>nowLed) {
      char ttt[10];
      sprintf(ttt,"%02d",(int)interval[i]);
      lcd.print(ttt);
      
    } else{
      lcd.print("--");
    }

    lcd.print(' ');
  }
}

void allLcdPrint(bool clearFlag) {
  if (clearFlag==1) 
    lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Mode: ");
  lcd.print(nowMode+1);
  lcd.print(' ');
  lcd.print("ms: ");
  lcd.print(timeMS);

  
  lcd.setCursor(0, 1);
  lcd.print("TM: ");
  lcd.print(interval[0]);lcd.print(" ");
  lcd.print(interval[1]);lcd.print(" ");
  lcd.print(interval[2]);lcd.print(" ");
  lcd.print(interval[3]);lcd.print(" ");
  lcd.print(interval[4]);
 
  lcd.setCursor(15, 0);
  if(pumpState==true)
    lcd.print('P');
  else 
    lcd.print('-');
}

void serialDebug() {
  Serial.print("nowMode : ");
  Serial.println(nowMode);
  Serial.print("timeMS : ");
  Serial.println(timeMS);
  Serial.print("intv : ");
  Serial.print(interval[0]);Serial.print(" ");
  Serial.print(interval[1]);Serial.print(" ");
  Serial.print(interval[2]);Serial.print(" ");
  Serial.print(interval[3]);Serial.print(" ");
  Serial.print(interval[4]);Serial.println();
}

void dotmat(char data[10]) {
  
  softSerial.println(data);
}
