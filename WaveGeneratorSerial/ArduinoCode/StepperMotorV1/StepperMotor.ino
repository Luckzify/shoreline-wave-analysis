#include <AccelStepper.h>

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

long moveToPosition = STEP_PER_REVOLUTION;
int value;
int speed;
int distance;

bool setSpeed;


void setup() {
  Serial.begin(9600);

  stepper.setCurrentPosition(0); 

  // Initial Parameters <- Im so dumb before I put it in loop so it always reset
  speed = 1000;
  setSpeed = false;
  distance = 150;
}

void loop() {

  // Wave Type Control
  if(Serial.available()>0){
    value=Serial.read();

    /*Stop everything*/
    if(value == 0){
      stepper.stop();
    }

    // /*Set Speed Mode*/
    // // value of 1: set speed
    // if(setSpeed){
    //   speed = value;
    //   setSpeed = false;
    // }
    // if(value == 1){
    //   setSpeed = true;
    // }


    /*Mono-Pulse Mode*/
    // value of 3: pulse mode
    if(value == 3){
      stepper.setMaxSpeed(speed*10);
      stepper.setAcceleration(speed*10);

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

    /*Constant Pulse Mode*/
    // 2000+ values are pulse mode
    // Distance:2900+ ex: 2910 = 10 in distance
    // Speed: 1000-1500
    // if(value >= 2000){
    // }

  } 
  
  // stepper.moveTo(150);
  // while (stepper.currentPosition() != 150) // Full speed up to 300
  //   stepper.run();
  // stepper.stop(); // Stop as fast as possible: sets new target
  // stepper.runToPosition(); 
  // // Now stopped after quickstop
 
  // // Now go backwards
  // stepper.moveTo(0);
  // while (stepper.currentPosition() != 0) // Full speed basck to 0
  //   stepper.run();
  // stepper.stop(); // Stop as fast as possible: sets new target
  // stepper.runToPosition(); 
  // // Now stopped after quickstop



  // stepper.moveTo(STEP_PER_REVOLUTION);
  // while (stepper.currentPosition() != STEP_PER_REVOLUTION-50) // Full speed up to 300
  //   stepper.run();
  // stepper.stop(); // Stop as fast as possible: sets new target
  // stepper.runToPosition(); 
  // // Now stopped after quickstop
 
  // // Now go backwards
  // stepper.moveTo(0);
  // while (stepper.currentPosition() != 50) // Full speed basck to 0
  //   stepper.run();
  // stepper.stop(); // Stop as fast as possible: sets new target
  // stepper.runToPosition(); 
  // // Now stopped after quickstop

}
