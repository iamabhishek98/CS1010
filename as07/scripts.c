/**
 * CS1010 Semester 1 AY18/19
 * Assignment 7: Scripts
 *
 * Reads, from the standard input, an integer n which is greater than 1 followed
 * by n integers, each representing the student ids. The student ids from the inputs 
 * are arranged in such a way that, the first  k are in increasing order, the 
 * remaining n - k are in decreasing order. It then prints to the standard output,
 * the student ids in icncreasing order. 
 *
 * @file: scripts.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"

/**
 * Stores the sorted integers in an output array
 *
 * @param[in] n The number of student ids
 * @param[in] student_id The list of unsorted student ids
 * @param[in,out] sorted_id The list of sorted student ids
 */
void sort(long n, long *student_id, long *sorted_id) {
  long start = 0;
  long end = n - 1; 
  long i = 0;

  while (start <= end) {
    //compares the integers from start and end of the list and accordingly sorts them
    if (student_id[start] < student_id[end]) {
      sorted_id[i] = student_id[start]; 
      start += 1;
    }
    else {
      sorted_id[i] = student_id[end];
      end -= 1;
    }
    i += 1;
  }
}

/**
 * Prints the sorted list
 *
 * @param[in] n The number of student ids
 * @param[in] sorted_id The list of sorted student ids
 */
void print(long n, long *sorted_id) {
  for (long i = 0; i < n; i += 1) {
    cs1010_print_long(sorted_id[i]);
    cs1010_print_string(" "); 
  }
  cs1010_println_string("");
}

int main()
{
  //reads the inputs
  long n = cs1010_read_long();
  long *student_id = cs1010_read_long_array(n); 

  //array to hold the sorted integers
  long *sorted_id = calloc(n, sizeof(long));

  sort(n, student_id, sorted_id); 

  print(n, sorted_id); 

  //frees the memory
  free(student_id);
  free(sorted_id);

  return 0; 
}
