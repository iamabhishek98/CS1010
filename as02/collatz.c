/**
 * CS1010 Semester 1 AY18/19
 * Assignment 2: Collatz 
 *
 * @file: collatz.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include "cs1010.h"

//function to output number with largest stopping time and its corresponding stopping time
void collatz(long n) {
  //variable to record number with maximum stopping time
  long maxstopnumber = 0; 
  //variable to record maximum stopping time
  long maxstoptime = 0; 

  if (n == 1) {
    cs1010_println_long(n);
    cs1010_println_string("0");
  }
  else {

    for (int i = 1; i <= n; i += 1) {
      //temporary variable to store i
      long temp = i; 
      //variable to count the stopping time
      long count = 0; 
      while (temp != 1) {
        if (temp % 2 == 0) {
          temp = temp/2;
          count += 1;
        }
        else {
          temp = 3*temp + 1;
          count += 1;
        }
      };

      if (count > maxstoptime)
      {
        maxstoptime = count;
        maxstopnumber = i;
      }
    }
    cs1010_println_long(maxstopnumber);
    cs1010_println_long(maxstoptime);
  }
}

int main() 
{
  long N = cs1010_read_long();
  //reads input from user
  if (N > 0) {
    collatz(N);
  }
  return 0;
}
