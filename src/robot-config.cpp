#include "inteldrive.h"
#include "intakes.h"
#include "vex.h"


vex::brain brain;
vex::controller primary(vex::controllerType::primary);

vex::inertial inert(vex::PORT20);
vex::motor backLeft    (vex::PORT3 , vex::ratio18_1, true );
vex::motor backRight   (vex::PORT9 , vex::ratio18_1, true );
vex::motor forwardLeft (vex::PORT8 , vex::ratio18_1, false );
vex::motor forwardRight(vex::PORT10, vex::ratio18_1, false );
vex::motor intakeLeft  (vex::PORT1 , vex::ratio18_1, false);
vex::motor intakeRight (vex::PORT2 , vex::ratio18_1, false);
vex::motor intakeBack  (vex::PORT16, vex::ratio18_1, false);
vex::motor lift        (vex::PORT20, vex::ratio18_1, false);

vex::encoder leftEncoder  = vex::encoder(brain.ThreeWirePort.A);
vex::encoder rightEncoder = vex::encoder(brain.ThreeWirePort.B);
vex::motor_group leftGroup       (backLeft , forwardLeft );
vex::motor_group rightGroup      (backRight, forwardRight);

inteldrive idrive(inert, 1.0, leftGroup, rightGroup, leftEncoder, rightEncoder);
intakes intake(intakeLeft, intakeRight, intakeBack, lift);

void vexcodeInit() {
  // Nothing to initialize
}