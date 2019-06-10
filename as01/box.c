/**
 * CS1010 Semester 1 AY18/19
 * Assignment 1: Box
 * Read the dimensions of a rectangular 3D box from 
 * the standard input and print the surface area and 
 * the length of the diagonal to the standard output.
 * @file: box.c
 * @author: KARNATI SAI ABHISHEK (Group C04)
 */
#include <math.h>
#include "cs1010.h"

/*int area_of_rectangle()
{
  long cs1010_read_long(h);
  long cs1010_read_long(w);
  long cs1010_read_long(l);
  double sa=2*l*w+2*l*h+2*h*w;
  cs1010_print_double(double sa);


}*/
void area_of_rectangle(long l, long w, long h)
{
double rectangle = (double)w*h;
double surface_area = 2*rectangle + 2*l*w + 2*l*h;
cs1010_print_long(surface_area);

}

double hypotenuse_of(double a, double b) 
{
    return sqrt(a*a + b*b);
}

int main() 
{
long l= cs1010_read_long();
long w= cs1010_read_long();
long h= cs1010_read_long();

area_of_rectangle(l, w, h);
double bottom = hypotenuse_of(l, w);
double diagonal = hypotenuse_of(bottom, h);


cs1010_print_string(" ");
cs1010_println_double(diagonal);

return 0;

}
