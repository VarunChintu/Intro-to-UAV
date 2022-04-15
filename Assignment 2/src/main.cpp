#include <Arduino.h>

#include <WiFi.h>
#include <esp32PWMUtilities.h>

#include <DabbleESP32.h>
Motor Motor1;

Motor Motor2;
void _setup() {
  Serial.begin(9600);
  Motor1.attach(14, 16, 17);

  Motor2.attach(15, 18, 19);

  Dabble.begin("Varun_Esp32");
}

void _loop() {
  Dabble.processInput();
}

void turnRight()
{
  Motor1.moveMotor(2.55 * 100);
  Motor2.moveMotor(-2.55 * 100);
  delay(300);
}

void turnLeft()
{
  Motor1.moveMotor(-2.55 * 100);
  Motor2.moveMotor(2.55 * 100);
  delay(300);
}

void goForward(int time)
{
  Motor1.moveMotor(2.55 * 100);
  Motor2.moveMotor(2.55 * 100);
  delay(time);
}


void setup() {
  _setup();
}

void loop() {
  _loop();
  if (GamePad.isPressed(0)) {
	int  size = 1000
    goForward(size);
	turnRight();
	goForward(size);
	turnRight();
	goForward(size);
	turnRight();
	goForward(size);
	turnRight();
  }
  else {
	Motor1.lockMotor();
	Motor2.lockMotor();
	}
}
