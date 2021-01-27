#pragma once

#include "inteldrive.h"

using namespace vex;

extern brain Brain;
extern inertial inert;
extern motor backLeft;
extern motor backRight;
extern motor forwardLeft;
extern motor forwardRight;
extern motor_group leftGroup;
extern motor_group rightGroup;

extern inteldrive idrive;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
