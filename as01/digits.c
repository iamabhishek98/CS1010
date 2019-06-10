/**
 * CS1010 Semester 1 AY18/19
 * Assignment 1: Digits
 * Read an integer from the standard input and print 
 * the sum of the digits to the standard output.
 * @file: digits.c
 * @author: KARNATI SAI ABHISHEK (Group C04)
 */
#include "cs1010.h"

long sum_of_digits(long input)
{
  if (input != 0) {
    return ((input % 10) + (sum_of_digits(input/10)));
  }
  else {
    return 0;
  }
}

int main()
{
	long input = cs1010_read_long();
	long sum = sum_of_digits(input);
  cs1010_println_long(sum);
  return 0;
}
