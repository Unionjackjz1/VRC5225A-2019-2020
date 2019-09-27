#include "vision.hpp"
pros::Vision vision(6);
visionClass green;
visionClass purple;
int avg_height = 0;
const double FOCAL_LENGTH = 225.9649;
const double CUBE_HEIGHT = 5.7;
const double H_MID = 158;
//Equation to Calculate distance is Distance = (Actual-Width * Focal-Length) / Observed-Pixel-Width

// y/212 *47
void visionClass::reset()
{
  this->x = 0;
  this->y = 0;
  this->average_distance = 0;
  this->average_width = 0;
  this->cur_width = 0;
  this->last_width = 0;
  this->average_height = 0;
  this->cur_height = 0;
  this->last_height = 0;
  this->distance = 0;
  this->good_count = 0;
  this->sig_num = 1;
  this->cube_ratio = 0;
  this->LeftCubex = 0;
  this->LeftCubey = 0;
  this->RightCubex = 0;
  this->RightCubey =0;
}
vector<double> visionClass::position(){
  return {this->x,this->y};
}
void visionClass::update()
{
  printf("in vision class");
  //Update Values - updating all properties of an object
  this->obj = vision.get_by_sig(0, this->sig_num);
  this->cur_height = this->obj.height;

  //Calculating the average height by using the value from the last cycle and filtering out bad values
  if(this->cur_height==this->last_height)
  {
    if(this->good_count==15)
    {
      if(this->average_height==0) this->average_height=this->obj.height;
      else this->average_height = (this->average_height + this->obj.height)/2;
      this->good_count=0;
    }
    else this->good_count++;
  }
  else this->good_count = 0;
// ressets good counts
this->good_count = 0;

  //Calculating the average witdh
  if(this->cur_width==this->last_width)
  {
    if(this->good_count==15)
    {
      if(this->average_width==0) this->average_width=this->obj.width;
      else this->average_width = (this->average_width + this->obj.width)/2;
      this->good_count=0;
    }
    else this->good_count++;
  }
  else this->good_count = 0;

  //Calculate Distance using average height
  if(this->average_height!=0) this->distance = (CUBE_HEIGHT*FOCAL_LENGTH)/this->average_height;

  //Update average distance
  if(this->average_distance==0 and this->distance!=0) this->average_distance=this->distance;
  else if(this->distance!=0) this->average_distance = (this->average_distance + this->distance)/2;

  //Update last height and width to current height
  this->last_height = this->cur_height;
  this->last_width = this->cur_width;
  // 39_in 38px 5.7in
  this->line_dif = this->obj.x_middle_coord-H_MID;

  cube_ratio = average_width / cur_height ;
  //xcord x_middle_cord;
  //ycord x y_middle_cord;
printf("before loop");
if(cube_ratio >= 2.7)
{

  this->LeftCubex = (this->obj.y_middle_coord - this->obj.left_coord) / 2 + this->obj.left_coord;
  this->LeftCubey = this->obj.x_middle_coord;
  this->RightCubex = (this->obj.y_middle_coord - this->LeftCubey ) + this->obj.left_coord * 3;
  this->RightCubey = this->obj.x_middle_coord;
  hight_ratio = this->cur_height / 2 ;
  printf("cube cords: %d \n", LeftCubey);
}
else{
  printf("cube ratio: %d" , cube_ratio);
}

}


void visionClass::lineMiddle(float kP, double yHold, double xHold, double angle){
  double power = 0;
  double kP_a = 200;
  double kP_y = 15;
  this->linedUp = false;
  double error_a = angle - tracking.global_angle;
  double error_y = yHold - tracking.ycoord;
  this->update();
  if(abs(this->line_dif)>4 || fabs(error_a) >= deg_to_rad(0.5) || fabs(error_y) >= 0.5) {
    if(fabs(kP*this->line_dif)>35) power = 35 * sgn(this->line_dif);
    else if(fabs(kP*this->line_dif)<13) power = 13 * sgn(this->line_dif);
    else power = kP*this->line_dif;
    tracking.power_x = power;
    tracking.power_a = error_a*kP_a;
    tracking.power_y = error_y*kP_y;
  }
  else{
   this->linedUp = true;
    brake();

 }
}
