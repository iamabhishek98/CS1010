/**
 * CS1010 Semester 1 AY18/19
 * Assignment 3: Histogram
 *
 * Read in a positive integer n followed by n real numbers. 
 * Draw the histogram of the numbers on the stndard output.
 *
 * @file: histogram.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"
#include <math.h>

#define NUM_OF_BUCKETS 10
#define MAX_SCORE 100
#define BLOCK "█"
#define HALF_BLOCK "▌"

//function to draw the histogram
void draw_histogram(double percent[]) 
{

  char *axis_labels[NUM_OF_BUCKETS] = {
    "  0 - 10  ",
    " 10 - 20  ",
    " 20 - 30  ",
    " 30 - 40  ",
    " 40 - 50  ",
    " 50 - 60  ",
    " 60 - 70  ",
    " 70 - 80  ",
    " 80 - 90  ",
    " 90 - 100 ",
  };

  cs1010_println_string("          ┴┴┴┴┴┴┴┴┴┴");

  for (long i = 0; i < NUM_OF_BUCKETS; i += 1) {
    cs1010_print_string(axis_labels[i]);

    //for loop to print out respective type and number of blocks for each bucket
    for (long integer = 0; integer <= 10; integer += 1) {

      //if statement to check if the element of the array is an integer
      if (percent[i] == integer) {
        //for loop to print the BLOCK (integer) times
        for (long k = 0; k < percent[i]; k += 1) {
          cs1010_print_string(BLOCK);
        }
      }

      else {
        //int_percent extracts the integer portion of the element
        double int_percent = floor(percent[i]);

        //decimal extracts the decimal portion of the element
        double decimal = percent[i] - int_percent;

        //if statement to check if int_percent is an integer
        if (int_percent == integer) {

          //if statement to check the condition in order to print the BLOCK (int_percent) times followed by the HALF_BLOCK 
          if (decimal > 0 && decimal <= 0.5) {
            for (long h = 0; h < int_percent; h += 1) {
              cs1010_print_string(BLOCK);
            }
            cs1010_print_string(HALF_BLOCK);
          }

          //else if statement to check condition to print the BLOCK (int_percent + 1) times
          else if (decimal > 0.5 && decimal < 1) {
            for (long y = 0; y < (int_percent + 1); y += 1) {
              cs1010_print_string(BLOCK);
            }
          }
        }
      }
    }
    cs1010_println_string("");
  }
}


int main()
{
  //reads inputs from user
  long n = cs1010_read_long();
  double* real_numbers = cs1010_read_double_array(n);

  double count[10];
  //for loop to set all elements of count array to 0
  for (long z = 0; z < 10; z += 1) {
    count[z] = 0;
  }

  //variables indicating lower and upper bounds of each bucket in histogram
  long lower_bound;
  long upper_bound;

  //for loop to navigate to each bucket
  for (long i = 0; i < 10; i += 1) {

    if (i < 9) {
      lower_bound = 10*i;
      upper_bound = (10*(i + 1)) - 1;
    }
    else if (i == 9) {
      lower_bound = 10*i;
      upper_bound = 10*(i + 1);
    }

    //for loop to count number of elements in each bucket
    for (long ele = 0; ele < n; ele += 1) {
      if (real_numbers[ele] >= lower_bound && real_numbers[ele] <= upper_bound) {
        count[i] += 1;
      }
    }
  }

  //for loop to calculate percentage for each element of count array scaled down by 10
  for (long y = 0; y < 10; y += 1) {
    count[y] = (double)(((count[y])/n)*10);
  }

  draw_histogram(count);
  return 0;
}
