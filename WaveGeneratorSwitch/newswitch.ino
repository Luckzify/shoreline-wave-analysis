#include <ezButton.h>

ezButton button1(11);
ezButton button2(12);
ezButton button3(13);
ezButton button4(0);

int oldb1,newb1,oldb2,newb2,oldb3,newb3,oldb4,newb4;
int mode;
bool on = false;
bool b1toggled,b2toggled,b3toggled,b4toggled;

void setup() {
  Serial.begin(9600);
  button1.setDebounceTime(50);
  button2.setDebounceTime(50);
  button3.setDebounceTime(50);
  button4.setDebounceTime(50);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(1,OUTPUT);
}
void togglesensing(){
  oldb1 = newb1, oldb2 = newb2, oldb3 = newb3, oldb4 = newb4;
  newb1 = button1.isPressed(), newb2 = button2.isPressed(), newb3 = button3.isPressed(), newb4 = button4.isPressed();
  b1toggled = (oldb1 == true && newb1 == false); 
  b2toggled = (oldb2 == true && newb2 == false);
  b3toggled = (oldb3 == true && newb3 == false);
  b4toggled = (oldb4 == true && newb4 == false);
}

void loop() {
  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  togglesensing();
  if (!on){
    digitalWrite(1,LOW);
  }
  if (b4toggled){
    on = !on;
    if (on){
      if (mode == 1){
        digitalWrite(1,HIGH);
      }
      if (mode == 2){
        digitalWrite(1,LOW);
      }
      if (mode == 3){
        digitalWrite(1,LOW);
      }
    }
  }
}
