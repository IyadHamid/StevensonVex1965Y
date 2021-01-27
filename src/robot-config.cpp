#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
inertial inert(PORT20);
motor backLeft    (PORT1, ratio18_1, false);
motor backRight   (PORT2, ratio18_1, false);
motor forwardLeft (PORT3, ratio18_1, false);
motor forwardRight(PORT4, ratio18_1, false);
encoder leftEncoder = encoder(Brain.ThreeWirePort.A);
encoder rightEncoder = encoder(Brain.ThreeWirePort.B);
motor_group leftGroup(backLeft, forwardLeft);
motor_group rightGroup(backRight, forwardRight);

inteldrive idrive(inert, 1.0, leftGroup, rightGroup, leftEncoder, rightEncoder);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}