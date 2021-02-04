/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       inteldrive.h                                              */
/*    Author:       Iyad H                                                    */
/*    Created:      Thu Sep 16 2020                                           */
/*    Description:  drivetrain with sensors header                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include <vector>
#include "v5.h"
#include "v5_vcs.h"

#include "common.h"


class inteldrive {
public:
  double absoluteRotation, inchesRatio;
  vec2 absoluteLocation;
  vex::inertial inertialSensor;
  vex::motor_group leftDrive, rightDrive;

  inteldrive(vex::inertial i, double ratio, vex::motor_group l, vex::motor_group r, 
             vex::encoder le, vex::encoder re);

  ~inteldrive() {handler.interrupt();}
  
  double getEncoderRotation(vex::rotationUnits units = vex::rotationUnits::deg);
  double getYaw(vex::rotationUnits units = vex::rotationUnits::deg);

  void drive(vex::directionType dir, double vel, vex::velocityUnits units, double ratio = 1.0);
  void drive(vex::directionType dir, double pct, vex::percentUnits units = vex::percentUnits::pct);
  void stop(vex::brakeType mode = vex::brakeType::brake);

  void turnTo(double a, double vel, vex::velocityUnits units = vex::velocityUnits::pct);
  void driveTo(vec2 loc, double vel, vex::velocityUnits units = vex::velocityUnits::pct);
  void arcTo(vec2 loc, double ang, bool cw, double vel);

  void arcade(double vertical, double horizontal, double vertModifier = 1.0, double horiModifer = 1.0);
  void tank(double l, double r, double modifer = 1.0);

  //TO BE IMPLEMENTED
  //All G-Code instructions, robot is considered the spindel
  enum ginstruct {
    G00, G01, G02, G03, G04, G90, G91,
    M19
  };
  struct gline {
    ginstruct i;
    double X, Y, I, J, F;
  };
  int gcode(std::vector<gline> lines);

protected:
  double robotWidth = 10.0;
  
  vex::thread handler;
  vex::encoder leftEncoder, rightEncoder;

  void driveIndependent(double l, double r, double vel);
  static void callRun(void* ptr);
  void run();
};