/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.cpp                                                   */
/*    Author:       Iyad H                                                    */
/*    Created:      10 Sep 2020                                               */
/*    Description:  Proportional Integral Derivative controller               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "PID.h"

void PID::run(double goal) {
  double integral = 0; //integral
  double e = error(goal); //current error
  double pe = e; //previous error
  while (e > tolerance) {
    integral += e;
    
    double derivarive = e - pe;
    double out = kp * func(e) + ki * integral + kd * derivarive;
    output(out);

    pe = e;
    e = error(goal);
  }
}