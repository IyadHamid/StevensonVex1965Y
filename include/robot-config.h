#pragma once

#include "inteldrive.h"
#include "intakes.h"

extern vex::brain brain;
extern vex::controller primary;

extern vex::inertial inert;
extern vex::motor backLeft;
extern vex::motor backRight;
extern vex::motor forwardLeft;
extern vex::motor forwardRight;
extern vex::motor intakeLeft;
extern vex::motor intakeRight;
extern vex::motor intakeBack;
extern vex::motor lift;
extern vex::motor_group leftGroup;
extern vex::motor_group rightGroup;

extern inteldrive idrive;
extern intakes intake;

void vexcodeInit(void);
