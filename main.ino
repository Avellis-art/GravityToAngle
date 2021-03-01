#include "Interface.h"
#include <Adafruit_GFX.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

//	Programm Setting
#define PWMPort 3
#define MaxAngle 20

Interface interface;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

float AccelerometerVariable[3];
uint8_t error = 0x0F;
float pitch;
float roll;

void AngleData(){
	roll = atan(AccelerometerVariable[1] / sqrt(pow(AccelerometerVariable[0], 2) + pow(AccelerometerVariable[2], 2))) * 180 / PI;
	pitch = atan(-1 * AccelerometerVariable[0] / sqrt(pow(AccelerometerVariable[1], 2) + pow(AccelerometerVariable[2], 2)))* 180 / PI;
}

void GetAngle(){
	sensors_event_t event;
	accel.getEvent(&event);
	AccelerometerVariable[0] = event.acceleration.x;
	AccelerometerVariable[1] = event.acceleration.y;
	AccelerometerVariable[2] = event.acceleration.z;
	AngleData();
}

void OutputData(){
	analogWrite(PWMPort, constrain(map(roll * 1000, -MaxAngle * 1000, MaxAngle * 1000, 0, 255), 0, 255));
}

void setup() {
	Serial.begin(9600);
	interface.start();
	if (!accel.begin()){}
}

void LCDInterface(){
	interface.show(pitch, roll, MaxAngle);
	interface.update();
}

void loop() {
	GetAngle();
	OutputData();
	LCDInterface();
}