#include <SoftwareSerial.h>

//SoftwareSerial to keep Serial for Servo communication free
SoftwareSerial BTSerial(8, 9); // RX | TX on Arduino. RX(Arduino) -> TX(HC-06). TX(Arduino) -> RX(HC-06)

void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin

    BTSerial.begin(9600); // HC-06 current baud rate (default 115200)
}
void loop()
{
  if (BTSerial.available())
  {
     char c = BTSerial.read();

    if(c == ';')
      Serial.println();
    else
      Serial.write(c);
  }
}^
