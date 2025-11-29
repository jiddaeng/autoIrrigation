int trunk = 25;
int division = 15;
int branchNum = 4; //고정
int branchLen = 4;
int branch = branchNum * branchLen;

int temp = 0;
String findWay(int* wayArr, int num) {
  int cnt = 0;
  
  if (num==0 || num==3) {
    for (int i=0; i<trunk; i++) {
      wayArr[cnt++] = i;
    }
    for (int i=0; i<branch; i++) {
      if ((int)(i/branchLen) == num) {
        if (num%2==1) {
          if (i==12) {temp=15;}
          if (i==13) {temp=14;}
          if (i==14) {temp=13;}
          if (i==15) {temp=12;}

          for (int j=12; j<16; j++) {
            if (i == j) 
              temp = 27-i;
          }
          wayArr[cnt++] = temp+trunk;
        } else {
          wayArr[cnt++] = i+trunk;
        }
        
        
      }
    }
  } else {
    for (int i=0; i<division; i++) {
      wayArr[cnt++] = i;
    }
    for (int i=0; i<branch; i++) {
      if ((int)(i/branchLen)==num) {
        if(num%2==1) {
          if (i==4) {temp=7;}
          if (i==5) {temp=6;}
          if (i==6) {temp=5;}
          if (i==7) {temp=4;}
          

          wayArr[cnt++] = temp+trunk;
        } else {
        wayArr[cnt++] = i+trunk;
        }
      }
    }
  }
}

destShow(int num) {
  int wayArrLen;
  if (num==0 || num==3) {
    wayArrLen = trunk+branchLen;
  } else {
    wayArrLen = division+branchLen;  
  }
  int wayArr[wayArrLen];
  
  findWay(wayArr, num);
  
  if (num < 0)
    pixels.setPixelColor(28, pixels.Color(10,0,0)); // 28
  if (num < 1)
    pixels.setPixelColor(29, pixels.Color(10,0,0)); // 29
  if (num < 2)
    pixels.setPixelColor(36, pixels.Color(10,0,0)); // 36
  if (num < 3)
    pixels.setPixelColor(37, pixels.Color(10,0,0)); // 37
//  pixels.show();

}

void wayShow(int num, int bgC) {
  int wayArrLen;
  if (num==0 || num==3) {
    wayArrLen = trunk+branchLen;
  } else {
    wayArrLen = division+branchLen;  
  }
  int wayArr[wayArrLen];

  findWay(wayArr, num);

  int len = sizeof(wayArr) / sizeof(wayArr[0]);
  for (int i=0; i<len; i++) {
    if (bgC==1) 
      pixels.setPixelColor(wayArr[i], pixels.Color(0,10,0));
    else
      pixels.setPixelColor(wayArr[i], pixels.Color(0,0,0));
  }
  
}
int idx = 1;
int prevN = 0;

void neoShow(int num) {
  Serial.println("neoShow 들어옴");
  int wayArrLen;
  if (num==0 || num==3) {
    wayArrLen = trunk+branchLen;
  } else {
    wayArrLen = division+branchLen;  
  }
  int wayArr[wayArrLen];
  
//  for (int i = 0; i < trunk + branch; i++) {
//    wayArr[i] = -2; 
//  }

  findWay(wayArr, num);
  int len = sizeof(wayArr) / sizeof(wayArr[0]);
  

  if (num!=prevN) {
    idx=4;
  }
  prevN = num;
  
  if (idx>=len) {
    idx = 4;
    buzSound(1);
  }

  //pixels.clear();
  if (wayArr[idx] != -2) {
    pixels.setPixelColor(wayArr[idx], pixels.Color(0, 0, 170));
    pixels.setPixelColor(wayArr[idx-1], pixels.Color(0, 0, 90));
    pixels.setPixelColor(wayArr[idx-2], pixels.Color(0, 0, 40));
    pixels.setPixelColor(wayArr[idx-3], pixels.Color(0, 0, 20));
    pixels.setPixelColor(wayArr[idx-4], pixels.Color(0, 0, 5));
    //Serial.print("네오픽셀 들어옴");
    //Serial.println(wayArr[idx]);
  } else {
//    while (wayArr[idx] == -2) {
//      idx++;
//    }
  }
  pixels.show();
  idx++;
}

int miniDelayTime = 5;
int delayNum = 1000 / miniDelayTime;
int realDelay;
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
      if (i==1 || i==2) 
        realDelay = miniDelayTime * 3;
      else
        realDelay = miniDelayTime * 2;
      delayNum = 1000 / realDelay;
        

      for (int j =0; j<(interval[i]*intTimeMS*delayNum); j++) {
        delay(realDelay);
        
        wayShow(i, 1);
        
        
        
        if (neoOrCls==true) 
          neoShow(i);
        else 
          pixels.clear();
        destShow(i);
        
        neoOrCls = !(neoOrCls);
        if (playFlag==false) break;
        if(j%delayNum<delayNum/2){
          digitalWrite(ledPin[i], 1);
          digitalWrite(pumpPin, 1);
        } else {
          digitalWrite(ledPin[i], 0);
          digitalWrite(pumpPin, 0);
        }

        nowTime = (j/delayNum)/intTimeMS;

        if ((j%delayNum)==0) {
          Serial.println("ledPrint 1초");
          ledLcdPrint(i, (int)nowTime);
          char data[10];
          sprintf(data, "%d : %02d", i+1, (interval[i]-(int)nowTime));
          dotmat(data);
          
        }

        modeTurnRead();
        intvUpDownRead();
        stopRead();
        startRead();
      }
    }
    //Serial.print("playFlag : "); Serial.println(playFlag);
    digitalWrite(ledPin[i], 0);
    pixels.clear();
    pixels.show();
    
  }

  delay(interval[4]*intTimeMS*1000);
  if (interval[4] > 0) {
    playFlag = true;
    againFlag = true;
    interval[4] = 0;
  } else {
    againFlag = false;
  }
  _end_melody();
  pumpState = false;
  digitalWrite(pumpPin, 0);
  

  allLcdPrint(1);
  
  
  char data[10] = "READY";
  dotmat(data);
  
}
