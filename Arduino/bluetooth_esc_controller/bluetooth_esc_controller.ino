#include <SoftwareSerial.h>
#include <Servo.h>

//SoftwareSerial to keep Serial for Servo communication free
SoftwareSerial BTSerial(8, 9); // RX | TX on Arduino. RX(Arduino) -> TX(HC-06). TX(Arduino) -> RX(HC-06)

Servo servo;  // create servo object to control a servo

String message = "";

int minSpeed = 5;  //min speed
int maxSpeed = 40; //max effective speed = 90

void setup()
{
	Serial.begin(9600);   //Sets the baud for serial data transmission                               
	pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin

	BTSerial.begin(9600); // HC-06 current baud rate (default 115200)

	servo.attach(14);  // attaches the servo on pin 14 = A0
	
	servo.write(0);
	delay(500);
}

void loop()
{
	if (BTSerial.available())
	{
		char c = BTSerial.read();

		if (c == ';')
		{
			int i = message.toInt();

			int val = map(i, 0, 100, minSpeed, maxSpeed);     // scale it to use it with the servo (value between 0 and 180)
			if (i == 0)
				servo.write(0);
			else
				servo.write(val);

			message = "";
		}
		else
		{
			message += c;
		}
	}
}