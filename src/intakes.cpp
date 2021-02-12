/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       intakes.cpp                                               */
/*    Author:       Iyad H                                                    */
/*    Created:      Thu Feb 11 2021                                           */
/*    Description:  intake controller                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "intakes.h"

intakes::intakes(vex::motor iL, vex::motor iR, vex::motor iB, vex::motor l)
                : intakeLeft(iL), intakeRight(iR), intakeBack(iB), lift(l) {
  intakesFront = vex::motor_group(iL, iR);
  intakesFront.setStopping(vex::brakeType::coast);
  intakeBack.setStopping(vex::brakeType::coast);
  lift.setStopping(vex::brakeType::hold);
};

void intakes::intake(double vel, vex::velocityUnits units, side s) {
  if (s != back)
    intakesFront.spin(vex::directionType::fwd, vel, units);
  if (s != front)
    intakeBack.spin(vex::directionType::fwd, vel, units);
}

void intakes::raise(double vel, vex::velocityUnits units) {
  lift.setVelocity(vel, units);
}

void intakes::stop(side s) {
  if (s != back)
    intakesFront.stop();
  if (s != front)
    intakeBack.stop();
}