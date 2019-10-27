#pragma once
#include "main.h"
#include "config.hpp"
#include "vision.hpp"
#include "controller.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;
using namespace pros;
int sgn(double num);
double deg_to_rad(double degrees);
void move_drive(int x, int y, int a);
void brake();
void update(void *param);
void pointToAngle(void *param);
class Tracking {
public:
  double xcoord, ycoord, global_angle, power_a, power_x, power_y, x2 , y2 , a2, holdAngle, distance_LR, distance_B  = 0;
  bool toggle_target, toggle_cube, target, cube = false;
  void reset();
  void move_to_target(double target_x, double target_y, double target_a, bool brakeOn = true, double max_xy = 90, bool cubeLineUp = false,  bool debug = false);
  void trackingInput();
  void setAngleHold(double angle);
  void turn_to_target(double target_x, double target_y, bool debug = false);
  void turn_to_angle(double target_a, bool debug = false);
  void flattenAgainstWall(bool forward, bool hold = true);
  void sweepTurn(double x1, double y1, double a1, double x2, double y2, double a2);
};

extern Tracking tracking;
