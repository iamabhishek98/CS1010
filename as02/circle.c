/**
 * CS1010 Semester 1 AY18/19
 * Assignment 2: Circle
 *
 * @file: circle.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include "cs1010.h"
#include <math.h>

//function to find distance of the point from the center of the canvas
double distance_from_center(double r, double row, double column) 
{
  double dist_row = (r - row);
  double dist_column = (r - column); 
  double dist = sqrt((dist_row*dist_row) + (dist_column*dist_column));
  return dist;
}

//function to print characters according to the distance of the point from the center
long characters(double distance, long r) 
{
  //variable to find absolute value of (distance - r)
  double mod = fabs(distance - r);
  if (mod < 0.1) {
    cs1010_print_string("@");
  }
  else if (mod < 0.3) {
    cs1010_print_string("O");
  }
  else if (mod < 0.5) {
    cs1010_print_string("*");
  }
  else if (mod < 0.7) {
    cs1010_print_string("+");
  }
  else {
    cs1010_print_string(" ");
  }
  return 0;
}

//function to plot the canvas and the circle inside it
void circle(long r) 
{
  long size = 2*r + 1;
  for (int row = 0; row < size; row += 1) {
    for (int column = 0; column < size; column += 1) {
      double distance = distance_from_center(r, row, column);
      characters(distance, r);
    }
    cs1010_println_string("");
  }
}

int main()
{
  //reads the value of r from the user
  long radius = cs1010_read_long();
  circle(radius);
  return 0;
}
