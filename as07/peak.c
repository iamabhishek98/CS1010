/**
 * CS1010 Semester 1 AY18/19
 * Assignment 7: Peak
 *
 * Reads from the standard input an integer n which is equal to or greater than
 * 3 followed by n integers, each representing the elevation of a location
 * surveyed by John. It then prints, to the standard output, the index of the 
 * location of the peak if it exists, or "no peak" if a peak does not exist. 
 * The first elevation has an index of 0. 
 *
 * @file: peak.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"
#include <stdbool.h>

/**
 * Searches for a peak, if it exists, in the list of elevation values
 *
 * @param[in] elevation The list of elevation values
 * @param[in] i The start point in the list
 * @param[in] j The end point in the list
 * @param[in,out] status The truth value of whether the peak exists
 * @return The location of the peak if it exists
 */
long search(long *elevation, long i, long j, bool *status) {
  //exits the function if the start point is greater than the end point
  if (i > j) {
    return -1;
  }

  //the midpoint in the list
  long mid = (i + j)/2;

  //return the peak if it exists
  if (elevation[mid] > elevation[mid - 1] && elevation[mid] > elevation[mid + 1]) {
    *status = true; 
    return mid;
  }

  //checks if the elevation is decreasing
  else if (elevation[mid] > elevation[mid + 1]) {
    return search(elevation, i, mid - 1, status);
  }

  //checks if elevation is increasing
  else if (elevation[mid] < elevation[mid + 1]) {
    return search(elevation, mid + 1, j, status);
  }

  //the condition when elevation remains the same
  else {
    long temp_peak = search(elevation, i, mid - 1, status);  

    //checks if peak exists in the first half of the list 
    if (temp_peak != -1) {
      return temp_peak;
    }

    //to check if peak exists in the second half of the list
    else {
      return search(elevation, mid + 1, j, status); 
    }
  }

  return -1;
}

/** 
 * Prints the peak if it exists or otherwise prints "no peak"
 *
 * @param[in] status The truth value of whether the peak exists
 * @param[in] peak The location of the peak if it exists
 */
void print(bool *status, long peak) {
  if (*status == true) {
    cs1010_println_long(peak); 
  }
  else {
    cs1010_println_string("no peak");
  }
}

int main()
{
  //reads inputs
  long n = cs1010_read_long();
  long *elevation = cs1010_read_long_array(n); 

  bool status = false; 
  long peak = search(elevation, 1, n-2, &status); 

  print(&status, peak); 

  //frees the memory
  free(elevation);

  return 0;
}
