#include <SevSeg.h>
#include <ezButton.h>
#include <AccelStepper.h>

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)

AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

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
}
void togglesensing(){
  oldb1 = newb1, oldb2 = newb2;
  newb1 = button1.isPressed(), newb2 = button2.isPressed();
  b1toggled = (oldb1 == true && newb1 == false), b2toggled = (oldb2 == true && newb2 == false);
}
void moveThe17HS19_2004S1StepperMotorAxleBackAndForthInAZigZagMotionPeriodicallyAndContinuouslySoThatWavesMayBeGeneratedFromThisMotionForTheWaveTankToFunctionHopefullyInTheWorkshop(int speed,int distance){
  stepper.setMaxSpeed(speed);
  stepper.setAcceleration(speed);
  stepper.moveTo(distance);
  while ((stepper.currentPosition() != distance) && (!b2toggled && !b1toggled)){ 
    togglesensing();
    Serial.println(!b2toggled && !b1toggled);
    stepper.run();
  }
  togglesensing();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  stepper.moveTo(0);
  while ((stepper.currentPosition() != 0) && (!b2toggled && !b1toggled)) 
    togglesensing();
    Serial.println(!b2toggled && !b1toggled);
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
}
void loop(){
  button1.loop();
  button2.loop();
  togglesensing();
  if (!on){
    Serial.println("OFF"); 
    sevseg.blank();
    stepper.stop();
  }
  else{
    if (i == 1){
      moveThe17HS19_2004S1StepperMotorAxleBackAndForthInAZigZagMotionPeriodicallyAndContinuouslySoThatWavesMayBeGeneratedFromThisMotionForTheWaveTankToFunctionHopefullyInTheWorkshop(100,150);
      Serial.println("MODE1");
      sevseg.setNumber(1);
    }
    if (i == 2){
      Serial.println("MODE2");
      sevseg.setNumber(2);
    }
    if (i == 3){
      Serial.println("MODE3");
      sevseg.setNumber(3);
    }
  }
  if (b2toggled){
    Serial.println("B2Toggled");
    on = !on;
    if (on){i=1;sevseg.setNumber(i);}}
  if (b1toggled && on){
    Serial.println("B1Toggled");
    i = i%3+1;
  }
  sevseg.refreshDisplay();
}


