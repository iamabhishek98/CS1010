/**
 * CS1010 Semester 1 AY18/19
 * Assignment 3: CountingSort
 *
 * Read in a positive integer n and a max value k, followed by
 * a list of n numbers between 1 to k.  Print the numbers in
 * increasing order.
 *
 * @file: countingsort.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"
//function to sort the integers
void sort(long integers[], long max, long array_len) {
  //count array counts the number of occurrences of elements in the integers array
  long count[max + 1];

  //for loop to set all elements of count array to 0
  for (long a = 0; a < (max + 1); a += 1) {
    count[a] = 0; 
  }

  //for loop to navigate from one element of the integers array to another
  for (long b = 0; b < array_len; b += 1) {
    //nested for loop to find the element of the count array equal to the integers array 
    for (long c = 0; c < (max + 1); c += 1) {
      //the if condition increments the element of the count array based on the number of times it occurs in the integers array
      if (integers[b] == c) {
        count[c] += 1;
      }
    }
  }

  //for loop to print the integers in increasing order based on the count array
  for (long d = 0; d < (max + 1); d += 1) {
    //nested for loop to print the element of the integers array the number of times it occurs
    for (long e = 0; e < count[d]; e += 1) {
      cs1010_println_long(d);
    }
  }
}

int main()
{
  //reads inputs from user
  long n = cs1010_read_long();
  long k = cs1010_read_long();
  long* integers = cs1010_read_long_array(n);

  sort(integers, k, n);    
  return 0;
}
