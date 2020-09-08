//level == round, amountlights = how many lights will light up for the pattern in the next round, speedPattern = how fast the pattern will go for the next round

int led1,led2,led3,led4,led5,button1,button2,button3,button4,button5,button6,level,amountLights, speedPattern, placeHolder, buzzer;
long future, previousTime, sectionTime;
int lights[9] = {0,0,0,0,0,0,0,0,0}; 
int buttonsPressed[9] = {0,0,0,0,0,0,0,0,0};
boolean start, lose1, pattern, buttonStart, levelNext;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  start = false;
  lose1 = false;
  levelNext = false;
  pattern = true;
  buttonStart = false;
  amountLights = 3;
  previousTime = 0;
  speedPattern = 1000;
  placeHolder = 0;
  future = 0;
  level = 0;
  led1=2;
  led2=3;
  led3 = 6;
  led4 = 13;
  led5 = 12;
  button1=8;
  button2=4;
  button3=5;
  button4=9;
  button5 = 11;
  button6 = 7;
  buzzer = 10;
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3, INPUT);
  pinMode(button4,INPUT);
  pinMode(button5, INPUT);
  pinMode(button6,INPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(start == false){
    startPattern();
  }
  else if(level <= 30){
    if(pattern == true)
      gamePattern();
    else if(buttonStart == true)
      buttons();
    else if(levelNext == true)
      nextLevel();
    else if(lose1 == true)
      loseCode();
  }
  else{
    winCode();
  }

  //To check the functionality of the hardware
  //checkButtons(button4);
  //turnOnWhenHeld(led1, button1);
  //turnOnWhenHeld(led2, button2);
  //turnOnWhenHeld(led3,button3);
  //turnOnWhenHeld(led4,button4);
  //turnOnWhenHeld(led5,button5);
  //turnOnWhenHeld(led6, button6);
  
}

void checkButtons(int b1)
{
  Serial.print("b1 state = ");
  Serial.println(digitalRead(b1));
}

//puts a start pattern until it detects user input on start button.
void startPattern(){
  long ms = millis();
  long sec = ms/1000;//time
  long interval = 500;
  if(digitalRead(button6) == 1 && (ms-previousTime) >= interval){
    start = true;
    allOff();
    previousTime = 0;
  }
  else if(sec%5 == 0){
    digitalWrite(led5,LOW);
    digitalWrite(led1, HIGH);
  }
  else if(sec%5 == 1){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  else if(sec%5 == 2){
    digitalWrite(led2,LOW);
    digitalWrite(led3,HIGH);
  }
  else if(sec%5 == 3){
    digitalWrite(led3,LOW);
    digitalWrite(led4,HIGH);
  }
  else if(sec%5 == 4){
    digitalWrite(led4,LOW);
    digitalWrite(led5,HIGH);
  }
}

void allOn(){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
    digitalWrite(led5,HIGH);
}
void allOff(){
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    digitalWrite(led5,LOW);
}


void gamePattern(){
  long ms = millis();
  long interval = speedPattern;
  if((ms-previousTime) >= interval && placeHolder < amountLights*2){
    if(placeHolder%2 == 1){
      int ranNum = random(1, 6);
      lights[placeHolder/2] = ranNum;
      if(ranNum == 1){
        digitalWrite(led1,HIGH);
        tone(buzzer,261.63);
      }
      else if(ranNum == 2){
        digitalWrite(led2,HIGH);
        tone(buzzer,293.66);
      }
      else if(ranNum == 3){
        digitalWrite(led3,HIGH);
        tone(buzzer,329.63);
      }
      else if(ranNum == 4){
        digitalWrite(led4,HIGH);
        tone(buzzer,349.23);
      }
      else if(ranNum == 5){
        digitalWrite(led5,HIGH);
        tone(buzzer,392.00);
      }
      previousTime = ms;
    }
    else{
      allOff();
      noTone(buzzer);
      previousTime = ms;
    }
    placeHolder++;
  }
  else if(placeHolder >= amountLights*2 && (ms-previousTime) >= interval){
    allOff();
    noTone(buzzer);
    pattern = false;
    buttonStart = true;
    previousTime = 0;
    placeHolder = 0;
  }
}

void buttons(){
  long ms = millis();
  long interval = 500;
  if(placeHolder < amountLights*2){
    if((ms-previousTime) >= interval){
      if(placeHolder%2 == 0){
        if(digitalRead(button1) == 1){
          buttonsPressed[placeHolder/2] = 1;
          digitalWrite(led1, HIGH);
          tone(buzzer,261.63);
          previousTime = ms;
          placeHolder++;
        }
        else if(digitalRead(button2) == 1){
          buttonsPressed[placeHolder/2] = 2;
          digitalWrite(led2, HIGH);
          tone(buzzer,293.66);
          previousTime = ms;
          placeHolder++;
        }
        else if(digitalRead(button3) == 1){
          buttonsPressed[placeHolder/2] = 3;
          digitalWrite(led3, HIGH);
          tone(buzzer,329.63);
          previousTime = ms;
          placeHolder++;
        }
        else if(digitalRead(button4) == 1){
          buttonsPressed[placeHolder/2] = 4;
          digitalWrite(led4, HIGH);
          tone(buzzer,349.23);
          previousTime = ms;
          placeHolder++;
        }
        else if(digitalRead(button5) == 1){
          buttonsPressed[placeHolder/2] = 5;
          digitalWrite(led5, HIGH);
          tone(buzzer,392.00);
          previousTime = ms;
          placeHolder++;
        }
      }
      else{
        allOff();
        noTone(buzzer);
        previousTime = ms;
        placeHolder++;
      }
    }
  }
  else if(placeHolder >= amountLights*2 && (ms-previousTime) >= interval){
    buttonStart = false;
    placeHolder = 0;
    previousTime = ms;
    levelNext = true;
    noTone(buzzer);
  }    
}
void restart(){
  long ms = millis();
  start = false;
  lose1 = false;
  levelNext = false;
  pattern = true;
  buttonStart = false;
  amountLights = 3;
  previousTime = ms;
  speedPattern = 1000;
  placeHolder = 0;
  future = 0;
  level = 0;
  for(int i = 0; i < 9; i++){
     lights[i] = 0;
  }
  for(int i = 0; i < 9; i++){
     buttonsPressed[i] = 0;
  }
}
void loseCode(){  
  long ms = millis();
  if((ms-previousTime) <= 2500){
    if((ms-previousTime) <= 500){
        allOff();
        noTone(buzzer);
      }
      else if((ms-previousTime) <= 1000){
        allOn();
        tone(buzzer, 146.83);
      }
      else if((ms-previousTime) <=1500){
        noTone(buzzer);
      }
      else if ((ms-previousTime) <= 2000){
        tone(buzzer, 146.83);
      }
      else if((ms-previousTime) <= 2500){
        allOff();
        noTone(buzzer);
      }
  }
  else if(digitalRead(button6) == 1)
    restart();
}
void winCode(){
  long ms = millis();
  if((ms-previousTime) <= 3400){
    if((ms-previousTime) <= 200){
        allOff();
        noTone(buzzer);
      }
      else if((ms-previousTime) <= 400){
        allOn();
        tone(buzzer, 880.00);
      }
      else if((ms-previousTime) <= 600){
        allOff();
        noTone(buzzer);
      }
      else if ((ms-previousTime) <= 800){
        allOn();
        tone(buzzer, 783.99);
      }
      else if((ms-previousTime) <= 1000){
        allOff();
        noTone(buzzer);
      }
      else if ((ms-previousTime) <= 1200){
        allOn();
        tone(buzzer, 698.46);
      }
      else if((ms-previousTime) <= 1400){
        allOff();
        noTone(buzzer);
      }
      else if((ms-previousTime) <= 1600){
        allOn();
        tone(buzzer, 880.00);
      }
      else if((ms-previousTime) <= 1800){
        allOff();
        noTone(buzzer);
      }
      else if ((ms-previousTime) <= 2000){
        allOn();
        tone(buzzer, 783.99);
      }
      else if((ms-previousTime) <= 2200){
        allOff();
        noTone(buzzer);
      }
      else if ((ms-previousTime) <= 2400){
        allOn();
        tone(buzzer, 698.46);
      }
      else if((ms-previousTime) <= 3000){
        allOff();
        noTone(buzzer);
      }
      else if((ms-previousTime) <= 3200){
        allOn();
        tone(buzzer, 880.00);
      }
      else if((ms-previousTime) <= 3400){
        allOff();
        noTone(buzzer);
      }
  }
  else if(digitalRead(button6) == 1)
    restart();
}
void nextLevel(){
  long ms = millis();
    for(int i = 0; i < 9; i++){
      if(lights[i] != buttonsPressed[i])
        lose1 = true;
    }
    if(lose1 == false && (ms-previousTime) <= 2500 && level != 30){
      if((ms-previousTime) <= 500){
        allOff();
        noTone(buzzer);
      }
      else if((ms-previousTime) <= 1000){
        allOn();
        tone(buzzer, 880.00);
      }
      else if((ms-previousTime) <=1500){
        allOff();
        noTone(buzzer);
      }
      else if ((ms-previousTime) <= 2000){
        allOn();
        tone(buzzer, 880.00);
      }
      else if((ms-previousTime) <= 2500){
        allOff();
        noTone(buzzer);
      }
    }
    else if(lose1 == false){
      for(int i = 0; i < 9; i++){
        lights[i] = 0;
      }
      for(int i = 0; i < 9; i++){
        buttonsPressed[i] = 0;
      }
      levelNext = false;
      pattern = true;
      level++;
      previousTime = 0;
      placeHolder = 0;
      speedPattern = speedPattern - 25;
      if(level > 0 && level%5 == 0)
        amountLights++;
      if(level > 30)
        previousTime = ms;
    }
    else{
      previousTime = ms;
      placeHolder = 0;
      levelNext = false;
      lose1 = true;
    }
}
//1
void turnOnWhenHeld(int led,int button){
  int b1State=digitalRead(button);
  if (b1State==1)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  
  
  
}
