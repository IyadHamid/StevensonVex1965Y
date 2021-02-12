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

inteldrive::inteldrive(vex::inertial i, double ratio, 
                       vex::motor_group l, vex::motor_group r, 
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
    double left = deg2rad(leftEncoder.rotation(vex::rotationUnits::deg));
    double right = deg2rad(rightEncoder.rotation(vex::rotationUnits::deg));

    //Implemented based on this paper
    //http://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf
    if (left != 0 || right != 0) {
      double theta = getYaw(); //Should be more accurate
      //double theta = left - right / WIDTH_BETWEEN_WHEELS;

      //Gets most likely (average) radius
      double radius = (right/theta) + (robotWidth/2);
      double dist = 2 * sin(theta/2) * (radius/theta + robotWidth/2); 
      
      //STEP 6 NOT IMPLEMENTED YET 

      absoluteLocation += vec2::polar(dist, absoluteRotation);
      //absoluteLocation += offset;
      absoluteRotation += theta;

      leftEncoder.resetRotation();
      rightEncoder.resetRotation();
    }
    vex::this_thread::sleep_for(100);
  }
}

void inteldrive::drive(vex::directionType dir, double vel, vex::velocityUnits units, double ratio) {
  ratio = sqrt(ratio);
  leftDrive .spin(dir, vel / ratio, units);
  rightDrive.spin(dir, vel * ratio, units);
}

void inteldrive::drive(vex::directionType dir, double pct, vex::percentUnits units) {
  leftDrive .spin(dir, pct, units);
  rightDrive.spin(dir, pct, units);
}

void inteldrive::stop(vex::brakeType mode) {
  leftDrive .stop(mode);
  rightDrive.stop(mode);
}


void inteldrive::turnTo(double a, double vel, vex::velocityUnits units) {
  std::function<double(double)> error = [this](double goal) {
    return angle_difference(goal, getYaw());
  };
  std::function<void(double)> output = [this, units](double input) {
    leftDrive .spin(vex::directionType::fwd, input, units);
    rightDrive.spin(vex::directionType::rev, input, units);
  };
  std::function<double(double)> func = [vel](double input) {
    return input * vel;
  };

  PID pid(1.0, 1.0, 1.0, error, output, func);
  pid.run(a);
}

void inteldrive::driveTo(vec2 loc, double vel, vex::velocityUnits units) {
  vec2 disp = loc - absoluteLocation;
  turnTo(disp.ang(), vel);
  std::function<double(double)> error = [this, loc](double goal)->double {
    return (const_cast<vec2&>(loc) - absoluteLocation).mag();
  };
  std::function<void(double)> output = [this, units](double input) {
    drive(vex::directionType::fwd, input, units);
  };
  std::function<double(double)> func = [vel](double input) {
    return input * vel;
  };

  PID pid(1.0, 1.0, 1.0, error, output, func);
  pid.run(error(0.0));
}

void inteldrive::arcTo(vec2 loc, double ang, bool cw, double vel) {
  double dist = (absoluteLocation - loc).mag();
  //cos(ang)=(r^2+r^2-d^2)/(2*r*r)
  //r^2=-d^2/(2*cos(ang)-2)
  double radius = sqrt((-dist*dist)/(2*cos(ang)-2));
  radius *= cw ? 1.0 : -1.0;
  double r = (radius-(robotWidth/2.0))*ang;
  double l = (radius+(robotWidth/2.0))*ang;
  double ratio = cw ? r/l : l/r;

  double iang = (180.0-ang)/2.0 + (loc - absoluteLocation).ang();
  //vec2 center = absoluteLocation + vec2{cos(iang) * radius, sin(iang) * radius};
  turnTo(-1/iang, vel);

  std::function<double(double)> error = [this, loc](double goal)->double {
    return (const_cast<vec2&>(loc) - absoluteLocation).mag();
  };
  std::function<void(double)> output = [this, ratio](double input) { 
    drive(vex::directionType::fwd, input, vex::velocityUnits::rpm, ratio);
  };
  std::function<double(double)> func = [vel](double input) {
    return input * vel;
  };

  PID pid(1.0, 1.0, 1.0, error, output, func);
  pid.run(error(0.0));
}





double inteldrive::getEncoderRotation(vex::rotationUnits units) {
  return (leftDrive.rotation(units) + rightDrive.rotation(units)) / 2;
}

double inteldrive::getYaw(vex::rotationUnits units) {
  return inertialSensor.orientation(vex::orientationType::yaw, units);
}
void inteldrive::arcade(double vertical, double horizontal, double vertModifer, double horiModifer) {
  vertical *= vertModifer;
  horizontal *= horiModifer;
  leftDrive .spin(vex::directionType::fwd, vertical + horizontal, vex::percentUnits::pct);
  rightDrive.spin(vex::directionType::fwd, vertical - horizontal, vex::percentUnits::pct); 
}

void inteldrive::tank(double l, double r, double modifer) {
  leftDrive .spin(vex::directionType::fwd, l * modifer, vex::percentUnits::pct);
  rightDrive.spin(vex::directionType::fwd, r * modifer, vex::percentUnits::pct);
}

int inteldrive::gcode(std::vector<gline> lines) {
  for (gline line : lines) {
    switch (line.i) {
      case G00:
        driveTo(absoluteLocation + vec2{line.X, line.Y}, 100);
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