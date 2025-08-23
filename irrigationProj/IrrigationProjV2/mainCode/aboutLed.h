int trunk = 6;
int division = 3;
int branchNum = 4; //고정
int branchLen = 2;
int branch = branchNum * branchLen;


String findWay(int* wayArr, int num) {
  int cnt = 0;
  
  if (num%2==0) {
    for (int i=0; i<trunk; i++) {
      wayArr[cnt++] = i;
    }
    for (int i=0; i<branch; i++) {
      if ((int)(i/branchLen) == num) 
        wayArr[cnt++] = i+trunk;
    }
  } else {
    for (int i=0; i<division; i++) {
      wayArr[cnt++] = i;
    }
    for (int i=0; i<branch; i++) {
      if ((int)(i/branchLen)==num) 
        wayArr[cnt++] = i+trunk;
    }
  }
}
int idx = 1;
int prevN = 0;
void neoShow(int num) {
  int wayArr[trunk + branch];  
  for (int i = 0; i < trunk + branch; i++) {
    wayArr[i] = -1; 
  }

  findWay(wayArr, num);
  int len = sizeof(wayArr) / sizeof(wayArr[0]);
  Serial.print("findWay: "); 
  for (int i=0; i<len; i++) {
    Serial.print(wayArr[i]); Serial.print(' ');
  }
  Serial.println();
  Serial.print("wayArr[idx]: "); Serial.println(wayArr[idx]);
  Serial.print("num: "); Serial.println(num);
  Serial.println();

  if (num!=prevN) {
    idx=1;
  }
  prevN = num;
  
  if (idx>=len) {
    idx = 1;
  }

  //pixels.clear();
  if (wayArr[idx] != -1) {
    pixels.setPixelColor(wayArr[idx], pixels.Color(10, 0, 0));
    pixels.setPixelColor(wayArr[idx-1], pixels.Color(10, 0, 0));
    Serial.print("네오픽셀 들어옴");
    Serial.println(wayArr[idx]);
  } else {
    while (wayArr[idx] == -1) {
      idx++;
    }
  }
  pixels.show();
  idx++;
}

int miniDelayTime = 100;
int delayNum = 1000 / miniDelayTime;
bool neoOrCls = false;
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

      for (int j =0; j<(interval[i]*intTimeMS*delayNum); j++) {
        delay(miniDelayTime);
        if (neoOrCls==true) 
          neoShow(i);
        else 
          pixels.clear();
        
        neoOrCls = !(neoOrCls);
        if (playFlag==false) break;
        if(j%delayNum<delayNum/2){
          digitalWrite(ledPin[i], 1);
          digitalWrite(pumpPin, 1);
        } else {
          digitalWrite(ledPin[i], 0);
          digitalWrite(pumpPin, 0);
        }

        nowTime = j/delayNum;

        if ((j%delayNum)==0) {
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
  digitalWrite(pumpPin, 0);

  allLcdPrint(1);
  char data[10] = "READY";
  dotmat(data);

}
