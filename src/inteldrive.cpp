/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       inteldrive.cpp                                            */
/*    Author:       Iyad H                                                    */
/*    Created:      Thu Sep 16 2020                                           */
/*    Description:  drivetrain with sensors                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "inteldrive.h"

#include "common.h"
#include "PID.h"

using namespace std;
using namespace vex;

inteldrive::inteldrive(vex::inertial i, double ratio, vex::motor_group l, vex::motor_group r, 
                       vex::encoder le, vex::encoder re)
                      : inertialSensor(i), leftEncoder{le}, rightEncoder{re} {
  inchesRatio = ratio;
  absoluteLocation = vec2{ 0.0 };
  leftDrive = l;
  rightDrive = r;
  handler = vex::thread(callRun, this);
}

void inteldrive::callRun(void* ptr) {
  ((inteldrive *)ptr)->run();
}

void inteldrive::run() {
  for (;;) {
    double left = deg2rad(leftEncoder.rotation(rotationUnits::deg));
    double right = deg2rad(rightEncoder.rotation(rotationUnits::deg));

    //Implemented based on this paper
    //http://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf
    if (left != 0 || right != 0) {
      double theta = getYaw(); //Should be more accurate
      //double theta = left - right / WIDTH_BETWEEN_WHEELS;

      //Gets most likely (average) radius
      double radius = (right/theta) + (WIDTH_BETWEEN_WHEELS/2);
      double dist = 2 * sin(theta/2) * (radius/theta + WIDTH_BETWEEN_WHEELS/2);
      //STEP 6 NOT IMPLEMENTED YET 

      absoluteLocation += vec2{ dist * cos(absoluteRotation), dist * sin(absoluteRotation) };
      absoluteRotation += theta;

      leftEncoder.resetRotation();
      rightEncoder.resetRotation();
    }
    this_thread::sleep_for(100);
  }
}

void inteldrive::drive(directionType dir, double vel, velocityUnits units, double ratio) {
  ratio = sqrt(ratio);
  leftDrive.spin(dir, vel/ratio, units);
  rightDrive.spin(dir, vel*ratio, units);
}

void inteldrive::drive(directionType dir, double pct, percentUnits units) {
  leftDrive.spin(dir, pct, units);
  rightDrive.spin(dir, pct, units);
}

void inteldrive::stop(brakeType mode) {
  leftDrive.stop(mode);
  rightDrive.stop(mode);
}


void inteldrive::turnTo(double a, double vel) {
  function<double(double)> error = [this](double goal){return angle_difference(goal, getYaw());};
  function<void(double)> output = [this](double input){
    leftDrive.spin(directionType::fwd, input, velocityUnits::rpm);
    rightDrive.spin(directionType::rev, input, velocityUnits::rpm);
  };
  function<double(double)> func = [vel](double input){return input * vel;};

  PID pid(1.0, 1.0, 1.0, error, output, func);
  pid.run(a);
}

void inteldrive::driveTo(vec2 loc, double vel) {
  vec2 disp = loc - absoluteLocation;
  turnTo(disp.ang(), vel);
  function<double(double)> error = [this, loc](double goal)->double{return (const_cast<vec2&>(loc) - absoluteLocation).mag();};
  function<void(double)> output = [this](double input){drive(directionType::fwd, input, velocityUnits::rpm);};
  function<double(double)> func = [vel](double input){return input * vel;};

  PID pid(1.0, 1.0, 1.0, error, output, func);
  pid.run(error(0.0));
}

void inteldrive::arcTo(vec2 loc, double ang, bool cw, double vel) {
  double dist = (absoluteLocation - loc).mag();
  //cos(ang)=(r^2+r^2-d^2)/(2*r*r)
  //r^2=-d^2/(2*cos(ang)-2)
  double radius = sqrt((-dist*dist)/(2*cos(ang)-2));
  radius *= cw ? 1.0 : -1.0;
  double r = (radius-(WIDTH_BETWEEN_WHEELS/2))*ang;
  double l = (radius+(WIDTH_BETWEEN_WHEELS/2))*ang;
  double ratio = cw ? r/l : l/r;

  double iang = (180.0-ang)/2.0 + (loc - absoluteLocation).ang();
  //vec2 center = absoluteLocation + vec2{cos(iang) * radius, sin(iang) * radius};
  turnTo(-1/iang, vel);

  function<double(double)> error = [this, loc](double goal)->double{return (const_cast<vec2&>(loc) - absoluteLocation).mag();};
  function<void(double)> output = [this, ratio](double input){drive(directionType::fwd, input, velocityUnits::rpm, ratio);};
  function<double(double)> func = [vel](double input){return input * vel;};

  PID pid(1.0, 1.0, 1.0, error, output, func);
  pid.run(error(0.0));
}





double inteldrive::getEncoderRotation(rotationUnits units) {
  return (leftDrive.rotation(units) + rightDrive.rotation(units)) / 2;
}

double inteldrive::getYaw(rotationUnits units) {
  return inertialSensor.orientation(orientationType::yaw, units);
}
void inteldrive::arcade(double vertical, double horizontal, double vertModifer, double horiModifer) {
  vertical *= vertModifer;
  horizontal *= horiModifer;
  leftDrive.spin(directionType::fwd, vertical + horizontal, percentUnits::pct);
  rightDrive.spin(directionType::fwd, vertical - horizontal, percentUnits::pct); 
}

void inteldrive::tank(double l, double r, double modifer) {
  leftDrive.spin(directionType::fwd, l * modifer, percentUnits::pct);
  rightDrive.spin(directionType::fwd, r * modifer, percentUnits::pct);
}

int inteldrive::gcode(std::vector<gline> lines) {
  for (gline l : lines) {
    switch (l.i) {
      case G00:
        break;
      case G01:
        break;
      case G02:
        break;
      case G03:
        break;
      case G04:
        break;
      case G90:
        break;
      case G91:
        break;
      case M19:
        break;
      default:
        return 1;
    }
  }
  return 0;
}