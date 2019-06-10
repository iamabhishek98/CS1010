/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Permutation 1
 * 
 * Reads, from the standard input, a positive integer n and two lists of integers
 * The program then goes on to print whether the second list is a permutation 
 * of the first list. 
 *
 * @file: permutation1.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"

/**
* Checks if the second list is a permutation of the first list
*
* @param[in] n Length of the lists of integers
* @param[in,out] list_one The first list of integers
* @param[in,out] list_two The second list of integers
*/
void permutation(long n, long *list_one, long *list_two) {
  //variable to keep count of the same elements in about lists
  long count = 0;

  //loops through all elements to see if the elements of both lists are the same
  for (long i = 0; i < n; i += 1) {
    for (long j = 0; j < n; j += 1) {
      if (list_two[j] == list_one[i]) {
        //exits loop as soon as match is found
        list_one[i] = '\0';
        list_two[j] = '\0';
        count += 1; 
        break;
      }
    }
  }

  //prints out whether list_two is a permuation of list_one
  if (count == n) {
    cs1010_println_string("YES"); 
  }
  else {
    cs1010_println_string("NO");
  }
}

int main()
{
  //reads the inputs
  long n = cs1010_read_long();
  long *list_one = calloc(n, sizeof(long)); 
  list_one = cs1010_read_long_array(n);
  long *list_two = calloc(n, sizeof(long));
  list_two = cs1010_read_long_array(n);
  
  permutation(n, list_one, list_two);

  //frees the memory
  free(list_one);
  free(list_two);
  
  return 0;
}
