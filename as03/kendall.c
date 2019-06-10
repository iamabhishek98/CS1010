/**
 * CS1010 Semester 1 AY18/19
 * Assignment 3: Kendall
 *
 * Read in a positive integer n and a permutation of numbers 
 * 1..n.  Print the normalized Kendall tau distance.
 *
 * @file: kendall.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include "cs1010.h"

//function to calculate the normalized Kendall tau distance
void calc_kendall_distance(long ranking_order[], long len) { 
  long count = 0; 
  //total tracks the number of all possible pairs of elements
  long total = 0;

  //nested for loops to compare the elements of the array 
  for (long i = 0; i < (len - 1); i += 1) {
    for (long j = i + 1; j < len; j += 1) {
      if (ranking_order[i] < ranking_order[j]) {
        count += 1;
      }
      total += 1;
    }
  }

  //variable to calculate the normalized Kendall tau distance
  double normalized_kendall = (double)(total-count)/total;
  cs1010_print_double(normalized_kendall);
}

int main()
{
  //reads inputs from user
  long len = cs1010_read_long();
  long* ranking_order = cs1010_read_long_array(len);

  calc_kendall_distance(ranking_order, len);
  return 0;
}
