#include <SoftwareSerial.h>
#include <Servo.h>

//SoftwareSerial to keep Serial for Servo communication free
SoftwareSerial BTSerial(8, 9); // RX | TX on Arduino. RX(Arduino) -> TX(HC-06). TX(Arduino) -> RX(HC-06)

Servo servo;  // create servo object to control a servo

String message = "";

int minSpeed = 5;  //min speed
int maxSpeed = 40; //max effective speed = 90

int analog_value;
float input_voltage;
float battery_voltage;

float r1 = 99.0;
float r2 = 20.0;

float factor = r2 / (r1 + r2);

float sum;
int count;

unsigned long currentMillis;
long previousTransmitMillis = 0;        // will store last time LED was updated
long previousVoltageMeasureMillis = 0;        // will store last time LED was updated
long previousMillis = 0;        // will store last time LED was updated
long transmitInterval = 10000;           // interval at which to blink (milliseconds)
long voltageMeasureInterval = 250;           // interval at which to blink (milliseconds)

float voltage;

void readVoltage() {

	analog_value = analogRead(A1);
	input_voltage = (analog_value * 5.0) / 1024.0;
	battery_voltage = input_voltage / factor;

	sum += battery_voltage;
	count++;

	if (count >= 100)
	{
		voltage = sum / 100.0;
		count = 0;
		sum = 0;
	}
}

void setup()
{
	Serial.begin(9600);   //Sets the baud for serial data transmission
	pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin

	BTSerial.begin(9600); // HC-06 current baud rate (default 115200)

	servo.attach(14);  // attaches the servo on pin 14 = A0

	servo.write(0);
	delay(500);
}

void receive()
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

void loop()
{
	receive();

	currentMillis = millis();

	if (currentMillis - previousVoltageMeasureMillis > voltageMeasureInterval) {
		previousVoltageMeasureMillis = currentMillis;
		readVoltage();
	}

	if (currentMillis - previousTransmitMillis > transmitInterval) {
		previousTransmitMillis = currentMillis;
		BTSerial.println("~" + String(voltage) + ";");
	}

}