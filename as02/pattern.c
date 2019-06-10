/**
 * CS1010 Semester 1 AY18/19
 * Assignment 2: Pattern
 *
 * @file: pattern.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <math.h>

//function to check if element is prime or equal to 1
long prime_or_one(long element) {
  long counter = 1;
  if (element == 1) { 
    counter = 1;
  }
  else {
    //for loop to check if number is prime
    for (int i = 2; i <= sqrt(element); i += 1) {
      if (element % i == 0) {
        counter = 0;
        break;
      }
    }
  }
  if (counter == 0) {
    return 0;
  }
  else  {
    return 1;
  }
}

//function to print '#' if element in cell is prime
void character(long num) {
  if (num >= 1) {
    cs1010_print_string("#");
  }
  else if (num == 0) {
    cs1010_print_string(" ");
  }
}

//function to print the pattern
long pattern (long interval, long height) {
  long columns = 2*height - 1;

  //for loop to print rows of canvas
  for (long rows = 1; rows <= height; rows += 1) {

    //for loop to print the empty spaces in front of the pyramid pattern
    for (long blanks_before = 0; blanks_before <= (columns/2 - rows); blanks_before += 1) {
      cs1010_print_string(" ");
    }

    //for loop to create cells in the pattern
    for (long cells = 1; cells <= (2*rows - 1); cells += 1) {
      long count = 0;
      long formula_value = 0;

      //for loop to find leading cell formula 
      for (long temp_row = rows -1; temp_row >= 1; temp_row -= 1) {
        formula_value += temp_row;
      }
      long elements = formula_value*interval + 1;
      long first_cell_element = (elements + (cells - 1));

      //for loop to count number of elements in the cell which are prime or one
      for (long counter = 0; counter < interval; counter += 1) {
        long inside_cell = first_cell_element + (counter*rows);
        count += prime_or_one(inside_cell);
      }
      character(count);
    }

    //for loop to print empty spaces after the pyramid pattern
    for (long blanks_after = 0; blanks_after <= (columns/2 - rows); blanks_after += 1) {
      cs1010_print_string(" ");
    }
    cs1010_println_string("");
  }
  return 0;
}

int main()
{
  //reads inputs for interval and height from user
  long interval = cs1010_read_long();
  long height = cs1010_read_long();

  //if condition to check if the input values are valid
  if (interval >= 1 && height >= 1)
  {
    pattern(interval, height);
  }
  return 0;
}
