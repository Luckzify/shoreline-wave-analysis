// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $
 
#include <AccelStepper.h>
 
// Define a stepper and the pins it will use
const int steps_per_rev = 200; //Set to 200 for NIMA 17
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4

AlStepper stepper(steps_per_rev, IN1, IN2, IN3, IN4);

void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(20);
  stepper.moveTo(500);
}
 
void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
 
    stepper.run();
}