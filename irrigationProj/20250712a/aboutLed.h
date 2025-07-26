void ledPrint() {
  lcd.clear();
  pumpState = true;
  if(timeMS=='m')
    intTimeMS = 60;
  else
    intTimeMS = 1;

  for (int i=0; i<4; i++) {
    if(playFlag==true) {
      digitalWrite(ledPin[i], 1);

      for (int j =0; j<(interval[i]*intTimeMS*100); j++) {
        delay(10);
        
        if(j%100<50){
          digitalWrite(ledPin[i], 1);
          digitalWrite(pumpPin, 1);
        } else {
          digitalWrite(ledPin[i], 0);
          digitalWrite(pumpPin, 0);
        }

        nowTime = j/100;

        if ((j%100)==0) {
          ledLcdPrint(i, (int)nowTime);
          char data[10];
          sprintf(data, "%d : %02d", i+1, (interval[i]-(int)nowTime));
          dotmat(data);
        }

        modeTurnRead();
        intvUpDownRead();
        stopRead();
      }
    }

    digitalWrite(ledPin[i], 0);
  }

  delay(interval[4]*intTimeMS*1000);
  _end_melody();
  pumpState = false;

  allLcdPrint(1);
  char data[10] = "READY";
  dotmat(data);

}
