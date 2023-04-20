#include "SevSeg.h"
#include "ezButton.h"
#include "Stepper.h"
#include <AccelStepper.h>

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

int value;
int speed;
int distance;

SevSeg sevseg; 
const int steps_per_rev = 200;
int i = 1;
int oldb1, newb1, oldb2, newb2;
bool on = false;
bool b1toggled,b2toggled;
ezButton button1(12);
ezButton button2(13);

void setup(){
  Serial.begin(9600);
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {8,9,10,1,0,3,2,11};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  sevseg.blank();
  button1.setDebounceTime(50);
  button2.setDebounceTime(50);

  stepper.setCurrentPosition(0); 
  speed = 100;
  distance = 150;
}

void loop(){
  button1.loop();
  button2.loop();
  oldb1 = newb1, oldb2 = newb2;
  newb1 = button1.isPressed(), newb2 = button2.isPressed();
  b1toggled = (oldb1 == true && newb1 == false), b2toggled = (oldb2 == true && newb2 == false);
  if (!on){Serial.println("OFF"); sevseg.blank();}
  else{
    if (i == 1){
      Serial.println("MODE1"); 
      stepper.setMaxSpeed(speed);
      stepper.setAcceleration(speed);

      stepper.moveTo(distance);
      while (stepper.currentPosition() != distance) // Full speed up to 300
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition(); 
      // Now stopped after quickstop
    
      // Now go backwards
      stepper.moveTo(0);
      while (stepper.currentPosition() != 0) // Full speed basck to 0
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition(); 
      // Now stopped after quickstop
      }
    if (i == 2){Serial.println("MODE2");}
    if (i == 3){Serial.println("MODE3");}}
  if (b2toggled){
    on = !on;
    if (on){i=1;sevseg.setNumber(i);}}
  if (b1toggled && on){i = i%3+1;sevseg.setNumber(i);}
  sevseg.refreshDisplay();
}


