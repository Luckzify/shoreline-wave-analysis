#include "SevSeg.h"
#include "ezButton.h"
#include "Stepper.h"
SevSeg sevseg; 
const int steps_per_rev = 200;
int i = 1;
int oldb1,newb1,oldb2,newb2;
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
  motor.setSpeed(100);
}

void loop(){
  button1.loop();
  button2.loop();
  oldb1 = newb1, oldb2 = newb2;
  newb1 = button1.isPressed(), newb2 = button2.isPressed();
  b1toggled = (oldb1 == true && newb1 == false), b2toggled = (oldb2 == true && newb2 == false);
  if (!on){Serial.println("OFF"); sevseg.blank();motor.setSpeed(0);   }
  else{
    if (i == 1){Serial.println("MODE1"); motor.setSpeed(100); delay(5)}
    if (i == 2){Serial.println("MODE2"); motor.setSpeed(-100); delay(5)}
    if (i == 3){Serial.println("MODE3"); delay(5)}}
  if (b2toggled){
    on = !on;
    if (on){i=1;sevseg.setNumber(i);}}
  if (b1toggled && on){i = i%3+1;sevseg.setNumber(i);}
  motor.step(steps_per_rev);
  sevseg.refreshDisplay();
}


