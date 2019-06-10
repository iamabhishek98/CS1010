/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Permutation 2
 * 
 * Reads, from the standard input, two strings consisting of n lowercase 
 * alphabets and prints, to the standard output "YES" if the second string
 * is a permutation of the first string and "NO" otherwise.
 *
 * @file: permutation2.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"
#include <stdbool.h>

//ascii value of the character 'z'
#define MAX 122

/**
 * Sorts the ascii values in the array
 *
 * @param[in] arr Array holding the ascii values
 * @param[in,out] count Array holding the count for each element in the array holding 
 * the ascii values.
 * @param[in] len The length of the string
 */
void counting_sort(long *arr, long *count, long len) {
  //loops through the elements to count the number of occurences of ascii values 
  //and store it in the count array
  for (long i = 0; i < len; i += 1) {
    //case for when the input equals the max_value
    if (arr[i] == MAX) {
      count[MAX] += 1; 
    }
    //case when inputs are less than the max value
    else if (arr[i] >= 1 && arr[i] < MAX) {
      count[arr[i]] += 1; 
    }
  }
}

/**
 * Checks whether the second string is a permutation of the first string
 *
 * @param[in,out] str_one Array holding the first string
 * @param[in,out] str_two Array holding the second string
 * @param[in] len The length of the strings
 * @param[in,out] ascii_one Array holding the ascii values for the first string
 * @param[in,out] ascii_two Array holding the ascii values for the second string
 */
void permutation(char *str_one, char *str_two, long len, long *ascii_one, long *ascii_two) {
  //for loop to store ascii values of alphabets in the strings in the ascii arrays
  for (long i = 0; i < len; i += 1) {
    ascii_one[i] = (long)str_one[i]; 
    ascii_two[i] = (long)str_two[i]; 
  }

  //count arrays must be 1 larger than the max value to be able to store the max value
  long *count_one = calloc(MAX + 1, sizeof(long)); 
  long *count_two = calloc(MAX + 1, sizeof(long)); 

  //sorts the ascii values in both arrays
  counting_sort(ascii_one, count_one, len);
  counting_sort(ascii_two, count_two, len);

  //loops through all elements of the count arrays to check if thet are equal
  bool status = true;
  for (long i = 97; i <= MAX; i += 1) {
    if (count_one[i] != count_two[i]) {
      //exits loop as soon as condition is not met
      status = false;
      break;
    }
  }
  
  //Prints whether the second string is a permutation of the first string
  if (status == true) {
    cs1010_println_string("YES");
  }
  else {
    cs1010_println_string("NO");
  }

  //frees the memory
  free(str_one);
  free(str_two);
  free(ascii_one);
  free(ascii_two);
  free(count_one);
  free(count_two);
}


int main()
{
  //reads the inputs
  char *string_one = cs1010_read_word();
  char *string_two = cs1010_read_word();

  //variable to hold the length of the string
  long len = strlen(string_one);

  //arrays to hold the ascii values of the alphabets in the strings
  long *ascii_one = calloc(len, sizeof(long));
  long *ascii_two = calloc(len, sizeof(long));

  permutation(string_one, string_two, len, ascii_one, ascii_two);

  return 0;
}
