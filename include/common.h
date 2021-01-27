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

#define PI 3.1415926
#define deg2rad(A) (A * PI/180.0)

// A is within T of B
#define within_tolerance(A,B,T) (B-T <= A && A <= B+T)
// A is within X and Y
#define within_angle_range(A,X,Y) ((X < A && A < Y) || \
                                   (A < Y && Y < X) || \
                                   (Y < X && X < A))
// Difference of A and B in degrees
// Positive : A is right of B
#define angle_difference(A,B) std::fmod((A - B + 180.0), 360.0) - 180.0                                

struct vec2 {
  double x, y;

  vec2 operator+(vec2 other) {return vec2{x+other.x, y+other.y};}
  vec2 operator-(vec2 other) {return vec2{x-other.x, y-other.y};}
  vec2 operator*(double other) {return vec2{x*other, y*other};}
  
  void operator+=(vec2 other) {*this = *this + other;}
  void operator-=(vec2 other) {*this = *this - other;}

  double ang() {return tan(x / y);}
  double mag() {return sqrt(x*x + y*y);}
};

//Got from 1,000,000 year simulation
#define answerToLifeTheUniverseAndEverything 42