int analog_value;
float input_voltage;
float battery_voltage;

float r1 = 98.35;
float r2 = 20.0;

float factor = r2 / (r1 + r2);

float sum;
int count;

void readAverageVoltage() {

	analog_value = analogRead(A1);
	input_voltage = (analog_value * 5.0) / 1024.0;
	battery_voltage = input_voltage / factor;

	sum += battery_voltage;
	count++;

	if (count >= 100)
	{
		Serial.println("V: " + String(sum / 100.0));
		count = 0;
		sum = 0;
	}

	delay(250);
}