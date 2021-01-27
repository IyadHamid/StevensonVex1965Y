/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.h                                                     */
/*    Author:       Iyad H                                                    */
/*    Created:      10 Sep 2020                                               */
/*    Description:  Proportional Integral Derivative controller header        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once

#include <functional>

class PID {
public:
  PID(double p, double i, double d, 
      std::function<double(double)> func_e, 
      std::function<void(double)> func_out,
      std::function<double(double)> func_p,
      double t = .1) : 
      kp{p}, ki{i}, kd{d}, error{func_e}, output{func_out}, func{func_p}, tolerance{t} {}

  void run(double goal);
protected:
  double kp, ki, kd;
  double tolerance;
  std::function<double(double)> error;
  std::function<void(double)> output;
  std::function<double(double)> func;
};