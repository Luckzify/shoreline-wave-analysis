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

  speed = 0;
  distance = 150;
}

void loop() {
  stepper.setMaxSpeed(speed*10);
  stepper.setAcceleration(speed*10);

  // Read Wave Type
  if(Serial.available()>0){
    value=Serial.read();

    // Increment method where speed is plus 10 every signal received and tracking of speed is kept in Matlab
    if(value == 2){
      speed = speed + 10;
    } 

    // Run Wave Type
    /*Mono-Pulse Mode*/
    // value of 1: pulse mode
    if(value == 1){

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
