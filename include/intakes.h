/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       intakes.h                                                 */
/*    Author:       Iyad H                                                    */
/*    Created:      Thu Feb 11 2021                                           */
/*    Description:  intake controller header                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include "vex.h"

class intakes {
public:
  enum side {
    front, back, both
  };

  intakes(vex::motor intakeLeft, vex::motor intakeRight, vex::motor intakeBack, vex::motor lift);

  void intake(double vel, vex::velocityUnits units, side s = both);
  void raise(double vel, vex::velocityUnits units);
  void stop(side s = both);
private:
  vex::motor intakeLeft, intakeRight;
  vex::motor intakeBack;
  vex::motor lift;

  vex::motor_group intakesFront;
};