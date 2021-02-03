/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Iyad H                                                    */
/*    Created:      Thu Sep 10 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

vex::competition comp;

void auton() {

}

void manual() {
  idrive.arcade(primary.Axis3.value(), primary.Axis4.value());
}

int main() {
  vexcodeInit();

  comp.autonomous(auton);
  comp.drivercontrol(manual);

  return 0;
}
