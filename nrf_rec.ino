#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include"ServoTimer2.h"

#define m1 A0
#define m2 A1
#define m3 A2
#define m4 A3
#define enA A4
#define enB A5

RF24 radio(7, 8); // CE, CSN

const byte address[][6] = {"00001","00002"};

//sonar

int trig = 4;
int echo = 3;
float duration;
float meter;
float distance;
int buzz = 5;

//-sonar


//servo
int pos1=750;
int pos2=750;
ServoTimer2 servo_back,servo_front;
String val;
//-servo

void setup() {
  Serial.begin(9600);

  //sonar

pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  //delay(6000);
  pinMode(buzz, OUTPUT);
  //Serial.println("Distance");

  //-sonar

  radio.begin();
  radio.openWritingPipe(address[0]); // 00001
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
 pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(m1, OUTPUT);
pinMode(m2, OUTPUT);
pinMode(m3, OUTPUT);
pinMode(m4, OUTPUT);

  
  //servo
   servo_back.attach(9); //pin 3,4
  servo_front.attach(10);
  servo_back.write(750);
  servo_front.write(750);
//-servo
}

void loop() {
  
  radio.startListening();
  if (radio.available()) {
    while(radio.available()){
      char text[32];
    radio.read(&text, sizeof(text));
    Serial.println(text[0]);



      if(text[0] == 'F')
      {  
       digitalWrite(enA,HIGH);
       digitalWrite(enB,HIGH);
       digitalWrite(m1,HIGH);
       digitalWrite(m2,LOW);
       digitalWrite(m3,HIGH);
       digitalWrite(m4,LOW);
       //Serial.println("Forward");
      }  
       else if(text[0] == 'B')
      {
        digitalWrite(enA,HIGH);
       digitalWrite(enB,HIGH);
       digitalWrite(m1,LOW);
       digitalWrite(m2,HIGH);
       digitalWrite(m3,LOW);
       digitalWrite(m4,HIGH);
       //Serial.println("Backward");
      }
      else if(text[0] == 'L')
      {
        digitalWrite(enA,HIGH);
       digitalWrite(enB,HIGH);
       digitalWrite(m1,HIGH);
       digitalWrite(m2,LOW);
       digitalWrite(m3,LOW);
       digitalWrite(m4,LOW);
       //Serial.println("Left");
      }
      else if(text[0] == 'R')
      {
       digitalWrite(enA,HIGH);
       digitalWrite(enB,HIGH);
       digitalWrite(m1,LOW);
       digitalWrite(m2,LOW);
       digitalWrite(m3,HIGH);
       digitalWrite(m4,LOW);
       //Serial.println("Right");
      }
      else if(text[0] == 'S')            
      {
       digitalWrite(enA,LOW);
       digitalWrite(enB,LOW);
       digitalWrite(m1,LOW);
       digitalWrite(m2,LOW);
       digitalWrite(m3,LOW);
       digitalWrite(m4,LOW);
       //Serial.println("Stop");
      }
      //-motor

      //sonar
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance= duration*0.034/2;
  //Serial.println(distance);

  if (distance <= 30)
  {
    digitalWrite(buzz, HIGH);
 } 
 else
 {
  digitalWrite(buzz, LOW);
 }
 //-sonar
    

//servo
   if(Serial.available() == 1)
  {
    val = Serial.readString();
    Serial.println(val);
    if(pos1>1425)
    {pos1=1425;}
    if(pos1<700)
    {pos1=750;}
    if(pos2>1425)
    {pos2=1425;}
    if(pos2<700)
    {pos2=750;}
    Serial.println("pos1 =" + (String)pos1);
    Serial.println("pos2 ="+ (String)pos2);
    Serial.println(val);
    //int num = val.toInt();
    if(val == "FS")
    {
      if(pos1<1500  && pos1>=750 )
      {
        pos1=pos1+75;
        servo_back.write(pos1);
      }
      
    }
   else if(val == "BS")
    {  
      if(pos1>=750 && pos1<1500)
      {
        pos1=pos1-75;
        servo_back.write(pos1);
      }
    } 
    if(val == "RS")
    {
      if(pos2<1500 && pos2 >=750)
      {
         pos2=pos2+75;
        servo_front.write(pos2);
      }
    }
    if(val == "LS")
    {
      if(pos2>=750 && pos2<1500)
      {
        pos2=pos2-75;
        servo_front.write(pos2);
      }
    } 
  }
//-servo


    
    }
  }
