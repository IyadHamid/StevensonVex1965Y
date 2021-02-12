/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Iyad H                                                    */
/*    Created:      Thu Sep 10 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot-config.h"

vex::competition comp;

void auton() {

}

void manual() {
  for (;;) {
    idrive.arcade(primary.Axis3.value(), primary.Axis4.value());
    if (primary.ButtonL1.pressing())
      intake.intake(100, vex::velocityUnits::pct, intakes::front);
    else if (primary.ButtonL2.pressing())
      intake.intake(-10, vex::velocityUnits::pct, intakes::front);
    else
      intake.stop(intakes::front);

    if (primary.ButtonR1.pressing()) {
      intake.raise(100, vex::velocityUnits::pct);
      intake.intake(100, vex::velocityUnits::pct, intakes::back);
    }
    else if (primary.ButtonR2.pressing()) {
      intake.raise(0, vex::velocityUnits::pct);
      intake.intake(-100, vex::velocityUnits::pct, intakes::back);
    }
    else {
      intake.raise(0, vex::velocityUnits::pct);
      intake.stop(intakes::back);
    }
  }
}

int main() {
  vexcodeInit();

  comp.autonomous(auton);
  comp.drivercontrol(manual);
  return 0;
}
