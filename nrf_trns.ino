
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24G.h>

#define x A0
#define y A1
#define z A2

int x_val;
int y_val;
int z_val;

int x_val2;
int y_val2;
int z_val2;
char text='F';

RF24 radio(7, 8); // CE, CSN
const byte address[][6] = {"00001","00002"};
void setup() {


  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(z, INPUT);
  Serial.begin(9600);
  x_val2 = analogRead(x);
  y_val2 = analogRead(y);
  z_val2 = analogRead(z);
  
  radio.begin();
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {

radio.stopListening();
// put your main code here, to run repeatedly:
  x_val = analogRead(x);
  y_val = analogRead(y);
  z_val = analogRead(z);

  int x_axis = x_val - x_val2;
  int y_axis = y_val - y_val2;
  int z_axis = z_val - z_val2;

  if(y_axis <= -40)
  {
   /* Serial.print("x = ");
    Serial.println(x_val);
    Serial.print("y = ");
    Serial.println(y_val);
    Serial.print("z = ");
    Serial.println(z_val);*/
    text = 'F';
    Serial.println("Forward");
  }
  else if(y_axis >= 40)
  {
    /* Serial.print("x = ");
    Serial.println(x_val);
    Serial.print("y = ");
    Serial.println(y_val);
    Serial.print("z = ");
    Serial.println(z_val);*/
    text = 'B';
    Serial.println("Backward");
  }
  else if(z_axis <= -40)
  {
   /*Serial.print("x = ");
    Serial.println(x_val);
    Serial.print("y = ");
    Serial.println(y_val);
    Serial.print("z = ");
    Serial.println(z_val);*/
    text = 'R';
    Serial.println("Right");
  }
  else if(z_axis >= 30)
  {
    /*Serial.print("x = ");
    Serial.println(x_val);
    Serial.print("y = ");
    Serial.println(y_val);
    Serial.print("z = ");
    Serial.println(z_val);*/
    text = 'L';
   Serial.println("Left");
  }
  else
  {
    /*Serial.print("x = ");
    Serial.println(x_val);
    Serial.print("y = ");
    Serial.println(y_val);
    Serial.print("z = ");
    Serial.println(z_val);*/
    text = 'S';
    Serial.println("Stop");
  }

  
  //const char text[] = "Hello";
  radio.write(&text, sizeof(text));
  //delay(1000);
}
