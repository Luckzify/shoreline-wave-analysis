#include <AccelStepper.h>

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

long moveToPosition = STEP_PER_REVOLUTION;
int value;
int speed;
int distance;

void setup() {
  Serial.begin(9600);

  stepper.setCurrentPosition(0); 

  speed = 100;
  distance = 150;
}

void loop() {
  // Read Wave Type
  if(Serial.available()>0){
    value=Serial.read();

    // Reset All Parameters
    if(value == 0){
      speed = 100;
      distance = 150;
    } 

    // Speed Increments
    if(value == 1){
      speed += 50;
    } 
    if(value == 2){
      speed -= 50;
    } 

    // Distance Increments
    if(value == 3){
      distance += 10;
    } 
    if(value == 4){
      distance -= 10;
    } 


    // Run Wave Type
    /*MonoPulse Mode*/
    // value of 255: pulse mode
    if(value == 255){
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

    /*ConstantPulse Mode*/
    // value of 254: Constant Pulse
    if(value == 254){
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

    // Run Wave Type
    /*FastSlow Pulse Mode*/
    // value of 253: FastSlow pulse mode
    if(value == 253){
      stepper.setMaxSpeed(speed);
      stepper.setAcceleration(speed);

      stepper.moveTo(distance);
      while (stepper.currentPosition() != distance) // Full speed up to 300
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition(); 
      // Now stopped after quickstop
    
      // Now go backwards
      stepper.setMaxSpeed(100);
      stepper.setAcceleration(100);
      stepper.moveTo(0);
      while (stepper.currentPosition() != 0) // Full speed basck to 0
        stepper.run();
      stepper.stop(); // Stop as fast as possible: sets new target
      stepper.runToPosition(); 
      // Now stopped after quickstop
    }
  } 
}
