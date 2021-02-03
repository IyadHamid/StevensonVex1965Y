#pragma once

#include "inteldrive.h"

extern vex::brain brain;
extern vex::controller primary;

extern vex::inertial inert;
extern vex::motor backLeft;
extern vex::motor backRight;
extern vex::motor forwardLeft;
extern vex::motor forwardRight;
extern vex::motor_group leftGroup;
extern vex::motor_group rightGroup;

extern inteldrive idrive;

void vexcodeInit(void);
