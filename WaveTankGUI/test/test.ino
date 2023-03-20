/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-controls-stepper-motor-using-l298n-driver
 */

#include <AccelStepper.h>

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

long moveToPosition = STEP_PER_REVOLUTION;

void setup() {
  Serial.begin(9600);

  stepper.setAcceleration(200.0); // set acceleration
  stepper.setSpeed(200);          // set initial speed
  stepper.setCurrentPosition(0);  // set position to 0

}

void loop() {


  Serial.print(F("position: "));
  Serial.println(stepper.currentPosition());

}
