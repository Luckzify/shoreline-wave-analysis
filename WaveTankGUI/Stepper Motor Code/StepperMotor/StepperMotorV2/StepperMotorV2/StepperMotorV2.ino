#include <AccelStepper.h>

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

long moveToPosition = STEP_PER_REVOLUTION;
int wavetype;
int speed;
int distance;

void setup() {
  Serial.begin(9600);

  stepper.setCurrentPosition(0); 
}

void loop() {

  // Read Wave Type
  if(Serial.available()>0){
    wavetype=Serial.read();
    speed=Serial.read();
    distance=Serial.read();


    // Run Wave Type
    /*Mono-Pulse Mode*/
    // value of 1: pulse mode
    if(wavetype == 1){
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
  } 
  // // Read Speed
  // if(Serial.available()>0){
  //   speed=Serial.read();
  // } 
  // // Read Distance
  // if(Serial.available()>0){
  //   distance=Serial.read();
  // } 

    /*Constant Pulse Mode*/
    // 2000+ values are pulse mode
    // Distance:2900+ ex: 2910 = 10 in distance
    // Speed: 1000-1500
    // if(value >= 2000){
    // }


  
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
