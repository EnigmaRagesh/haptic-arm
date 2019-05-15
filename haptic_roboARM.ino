#include <VarSpeedServo.h>
int a1,a2a,a3a,a4a,a5,a6,a3b,a4b,a2b,temp=0,timed;

int buttonPin = 51;    
int buttonPin1 = 53;    
int buttonState;
int buttonState2;             
int lastButtonState = LOW;
int lastButtonState2 = LOW;   
long lastDebounceTime = 0;
long lastDebounceTime2 = 0;  
long debounceDelay = 20 ;  
VarSpeedServo myservo1;
VarSpeedServo myservo2a;
VarSpeedServo myservo2b;
VarSpeedServo myservo3a;
VarSpeedServo myservo3b;
VarSpeedServo myservo4a;
VarSpeedServo myservo4b;
VarSpeedServo myservo5;
VarSpeedServo myservo6;
int pos1[100],pos2a[100],pos2b[100],pos3a[100],pos3b[100],pos4a[100],pos4b[100],pos5[100],pos6[100],times[100];
int button;

void record(){
  temp+=1;
  if(temp<100)
  {
    pos1[temp]=a1;
    pos2a[temp]=a2a;
    pos2b[temp]=a2b;
    pos3a[temp]=a3a;
    pos3b[temp]=a3b;
    pos4a[temp]=a4a;
    pos4b[temp]=a4b;
    pos5[temp]=a5;
    pos6[temp]=a6;
  }
  else{
    Serial.println("stop recording");
  }
}

void readButton1(){
int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) 
  {
   lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    
    if (reading != buttonState) {
      buttonState = reading;


      if (buttonState == HIGH)
      {
       button=1;
      }
    }
  }
  lastButtonState = reading;}
void readButton2(){
  int reading1 = digitalRead(buttonPin1);
  if (reading1 != lastButtonState2) {
    
    lastDebounceTime2 = millis();
  } 
  
  if ((millis() - lastDebounceTime2) > debounceDelay) {
  
    if (reading1 != buttonState2) {
      buttonState2 = reading1;

      if (buttonState2 == HIGH) {
      button=2;
      }
    }
  }
  
 
  lastButtonState2 = reading1;
}
void playArm(){
  Serial.println("playing");
  for(int i=1;i<100;i++){
    if(pos1[i]!=0){
  myservo1.write(pos1[i],50,true);
    myservo2a.write(pos2a[i],50,true);
  myservo2b.write(pos2b[i],50,true);
   myservo3a.write(pos3a[i],50,true);
    myservo3b.write(pos3b[i],50,true);
    myservo4a.write(pos4a[i],50,true);
  myservo4b.write(pos4b[i],50,true);
   myservo5.write(pos5[i],50,true);
  myservo6.write(pos6[i],50,true);
  }
  else break;
  }
   Serial.println("stopped playing");
   }
void setup() {
  pinMode(49,OUTPUT);
 pinMode(buttonPin, INPUT);
 pinMode(buttonPin1, INPUT);
  Serial.begin(9600);
  myservo1.attach(2);
  myservo2a.attach(3);
  myservo2b.attach(4);
  myservo3a.attach(5);
  myservo3b.attach(6);
  myservo4a.attach(7);
  myservo4b.attach(8);
  myservo5.attach(9);
  myservo6.attach(10);

    myservo1.write(90);
  myservo2a.write(90);
  myservo2b.write(90);
  myservo3a.write(90);
  myservo3b.write(90);
  myservo4a.write(90);
  myservo4b.write(90);
  myservo5.write(90);
  myservo6.write(90);
}
void readValues()
{
  a1=map(analogRead(5), 0, 912, 0, 180);
  a2a=map(analogRead(4), 0, 912, 180, 0);
  a2b=map(analogRead(4), 0, 912, 180, 0);
  a3a=map(analogRead(3), 0, 912, 0, 180);
  a3b=map(analogRead(3), 0, 912, 0, 180);
  a4a=map(analogRead(2), 0, 912, 0, 180);
  a4b=map(analogRead(2), 0, 912, 0, 180);
  a5=map(analogRead(0), 0, 912, 180, 0);
  a6=map(analogRead(1), 0, 1024, 0, 180);
}

void loop() 
{
  readValues();
  myservo1.write(a1);
  myservo2a.write(a2a);
  myservo2b.write(a2b);
  myservo3a.write(a3a);
  myservo3b.write(a3b);
  myservo4a.write(a4a);
  myservo4b.write(a4b);
  myservo5.write(a5);
  myservo6.write(a6);
    readButton1();
    readButton2();
  if(button==1)
  {
    digitalWrite(49,HIGH);
    delay(100);
    digitalWrite(49,LOW);
    Serial.print("recorded ");
    Serial.print(temp);
    Serial.println(" position.");
    button=0;
    record();
  }
  
   if(button==2)
   {
      button=0;
      playArm();
      temp=0;
    }
}
