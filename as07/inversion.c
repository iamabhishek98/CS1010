/**
 * CS1010 Semester 1 AY18/19
 * Assignment 7: Inversion
 *
 * Reads, from standard input, an integer n greater than 1 followed by n integers,
 * each representing the student ids. The student ids from the inputs are arranged
 * in such a way that, the first k are in increasing order while the remaining n - k
 * are in decreasing order. The program then prints, to the standard output, the 
 * number of inversions in the input. 
 *
 * @file: inversion.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"

/**
 * Finds the number of inversions in the input
 *
 * @param[in] n The number of student ids
 * @param[in] student_id The array holding the student ids
 */
void inversion(long n, long *student_id) {
  long start = 0;
  long end = n - 1;
  
  //variable to hold number of inversions  
  long num_of_inversions = 0;

  //while loop to find the number of inversions
  while (start <= end) {
    if (student_id[start] < student_id[end]) {
      start += 1;
    } 
    else {
      num_of_inversions += (end - start);
      end -= 1;
    }
  } 
  
  //prints the number of inversions
  cs1010_println_long(num_of_inversions);
} 

int main()
{
  //reads the inputs
  long n = cs1010_read_long();
  long *student_id = cs1010_read_long_array(n);

  inversion(n, student_id);
  
  //frees the memory
  free(student_id);

  return 0;
}
