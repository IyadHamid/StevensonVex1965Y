/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       common.h                                                  */
/*    Author:       Iyad H                                                    */
/*    Created:      Thu Sep 16 2020                                           */
/*    Description:  Header only math library                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <cmath>
#pragma once

constexpr double pi = 3.14159265359;
constexpr double deg2rad(double a) { return a * pi/180.0; }

// A is within T of B
constexpr bool within_tolerance(double a, double b, double t) { 
  return b-t <= a && a <= b + t;
}
// A is within X and Y
constexpr bool within_angle_range(double a, double x, double y) {
  return (x < a && a < y) ||
         (a < y && y < x) ||
         (y < x && x < a);
}
// Difference of A and B in degrees
// Positive : A is right of B
static const double angle_difference(double a, double b) {
  return std::fmod((a - b + 180.0), 360.0) - 180.0;
}                             

struct vec2 {
  double x, y;

  vec2 operator+(vec2 other) { return vec2{x+other.x, y+other.y}; }
  vec2 operator-(vec2 other) { return vec2{x-other.x, y-other.y}; }
  vec2 operator*(double other) { return vec2{x*other, y*other}; }
  
  void operator+=(vec2 other) { *this = *this + other; }
  void operator-=(vec2 other) { *this = *this - other; }

  double ang() { return tan(y / x); }
  double mag() { return sqrt(x*x + y*y); }
};

//Got from 1,000,000 year simulation
constexpr int answerToLifeTheUniverseAndEverything = 42;