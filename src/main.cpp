/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\twright                                          */
/*    Created:      Tue Jul 27 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    9, 10           
// Lifter               motor         7               
// Loader               motor         1               
// Controller1          controller                    
// CAM                  vision        4               
// Basket               sonar         G, H            
// CountFlap            pot           E               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

int MODEID = 0;

void toggleMode();
void toggleMode(int);
void takePhoto();
void eject();

int main() {
  
  bool togglePressed = false;
  int intakeTimer = 0;
  bool targetFound = false;
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Loader.setVelocity(150, rpm);
  Lifter.setVelocity(100, rpm);
  Brain.Screen.print("Lemon Mode");
  Controller1.Screen.print("Lemon Mode");

  while(true){
    
    //vision sensor camera checking for fruit
    takePhoto();
    if(CAM.largestObject.exists){
      targetFound = true;
      intakeTimer = 500000;
    }
    else
      targetFound = false;
    
    //if fruit was seen take it in.
    if(Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing())
    {
      intakeTimer = 0;
    }
    else if(intakeTimer > 0){
      Loader.spin(forward);
      intakeTimer--;
    }
    else
      Loader.stop();

    //toggle type of fruit to take in
    if(!togglePressed && Controller1.ButtonL2.pressing()){
      togglePressed = true;
      toggleMode();
    }else if(!Controller1.ButtonL2.pressing())
      togglePressed = false;

    //if eject is pressed eject all fruit in basket.
    if(Controller1.ButtonL1.pressing()){
      eject();
    }
  }
}

void toggleMode(){
  MODEID = ++MODEID%3;

  Brain.Screen.clearLine();
  Controller1.Screen.clearLine();

  switch(MODEID) {
    case 0:
      Brain.Screen.print("Lemon Mode");
      Brain.Screen.print(CountFlap.angle(degrees));
      Controller1.Screen.print("Lemon Mode");
      Controller1.Screen.print(CountFlap.angle(degrees));
      break;
    case 1:
      Brain.Screen.print("Apple Mode");
      Controller1.Screen.print("Apple Mode");
      break;
    case 2:
      Brain.Screen.print("FREE SHAVACADO");
      Controller1.Screen.print("Avacado Mode");
      break;
    case 3:
      Brain.Screen.print("Eject");
      Controller1.Screen.print("Eject Mode");
      break;
   default : 
      Brain.Screen.print("Error");
      Controller1.Screen.print("Error");
      break;
   }
}
void toggleMode(int exit){
  MODEID = 3;
  Brain.Screen.clearLine();
  Controller1.Screen.clearLine();
  Brain.Screen.print("Eject");
  Controller1.Screen.print("Eject Mode");
}

void takePhoto(){
  switch(MODEID) {
    case 0:
      CAM.takeSnapshot(CAM__LEMON);
      break;
    case 1:
      CAM.takeSnapshot(CAM__APPLE);
      break;
    case 2:
      CAM.takeSnapshot(CAM__AVACADO);
      break;
    case 3:
      CAM.takeSnapshot(CAM__SIG_4);
      break;
   default : 
      Brain.Screen.print("Error");
      break;
   }
}

void eject(){
  bool unloaded = false;
  bool countOn = false;
  int exitCount = 0;
  toggleMode(0);
  
  while (Basket.distance(inches) < 10){
    Loader.spin(reverse);
    unloaded = true;

    if(!countOn && CountFlap.angle(degrees) < 90){
      countOn = true;
      exitCount++;
    }
    else if(CountFlap.angle(degrees) > 90){
      countOn = false;
    }
  }

  if(unloaded)
  {
    Loader.spin(reverse);
    for(int endTime=0;endTime<3000;endTime++){

      if(!countOn && CountFlap.angle(degrees) < 90){
      countOn = true;
      exitCount++;
      }
      else if(CountFlap.angle(degrees) > 90){
      countOn = false;
      }

      wait(0.001,seconds);
    }
    //wait(3,seconds);
    Loader.stop();
    toggleMode();
    Brain.Screen.print(" Units: ");
    Brain.Screen.print(exitCount);
    Controller1.Screen.print(" Units: ");
    Controller1.Screen.print(exitCount);
  }
  
}
