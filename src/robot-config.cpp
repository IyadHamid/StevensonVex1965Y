#include "vex.h"


vex::brain brain;
vex::controller primary(vex::controllerType::primary);

vex::inertial inert(vex::PORT20);
vex::motor backLeft    (vex::PORT1,vex::ratio18_1, false);
vex::motor backRight   (vex::PORT2,vex::ratio18_1, false);
vex::motor forwardLeft (vex::PORT3,vex::ratio18_1, false);
vex::motor forwardRight(vex::PORT4,vex::ratio18_1, false);
vex::encoder leftEncoder  = vex::encoder(brain.ThreeWirePort.A);
vex::encoder rightEncoder = vex::encoder(brain.ThreeWirePort.B);
vex::motor_group leftGroup (backLeft , forwardLeft );
vex::motor_group rightGroup(backRight, forwardRight);

inteldrive idrive(inert, 1.0, leftGroup, rightGroup, leftEncoder, rightEncoder);

void vexcodeInit() {
  // Nothing to initialize
}