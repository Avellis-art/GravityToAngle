#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64);

class Interface{
public:
	Interface();
	void start();
	void show(float pitch, float roll, float MaxAngle);
	void update();
};

Interface::Interface(){}

void Interface::start(){
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.setTextColor(WHITE);
}

void Interface::show(float pitch, float roll, float MaxAngle){
	//OverLine
	display.setCursor(90, 0);
	display.print("ver2.1");
	display.drawLine(0, 8, 125, 8, WHITE);
	//AngleData
	display.setCursor(6,12);
	display.print("AngleData");
	display.setCursor(10,23);
	display.print("r:");
	display.print(roll);
	display.setCursor(10,32);
	display.print("p:");
	display.print(pitch);
	// MaxAngle
	display.setCursor(6,45);
	display.print("MaxAngle");
	display.setCursor(10,56);
	display.print("a:");
	display.print(MaxAngle);
	//
	display.setCursor(70,12);
	display.print("PWM");
	display.setCursor(74,23);
	display.print(constrain(map(roll*1000, -MaxAngle*1000, MaxAngle*1000 , 0, 255), 0, 255));

	display.setCursor(70,45);
	display.print("Vol");
	display.setCursor(74,56);
	display.print("u:");
	display.print(constrain(map(roll*1000, -MaxAngle*1000, MaxAngle*1000, 0, 255), 0, 255) / 51.0);


}

void Interface::update(){
	display.display();
	display.clearDisplay();
}