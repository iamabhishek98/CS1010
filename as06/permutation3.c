/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Permutation 3
 * 
 * Reads, from the standard input, a string consisting k characters chosen
 * from 'a' to 'z' and another string consisting n characters chosen from 'a'
 * to 'z'. It then prints, from the standard output, "YES" if the first string
 * is a permutation of some substring of length k from the second string and 
 * "NO" otherwise. 
 *
 * @file: permutation3.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"
#include <stdbool.h>

/**
 * Gets the count of the frequency of characters in the string and stores it in an array
 *
 * @param[in] string Array holding the string
 * @param[in,out] count Array holding the count of the frequency of
 * characters in the string
 * @param[in] len The length of the string
 */
void get_count(char *string, long *count, long len) {
  for (long i = 0; i < len; i += 1) {
    count[string[i]-'a'] += 1; 
  }
}

/**
 * Checks whether the window is a permutation of the first string
 *
 * @param[in] count_substring Array holding the count of the frequency of 
 * characters in the first string
 * @param[in] count_window Array holding the count of the frequency of 
 * characters in the window of the second string
 * @return true if array elements are equal. Otherwise, false. 
 */
bool check(long *count_substring, long *count_window) {
  //loops through all the elements of both arrays to see if they are equal
  for (long i = 0; i < 26; i += 1) {
    if (count_substring[i] != count_window[i]) {
      return false;
    }
  }
  return true; 
}

/**
 * Prints out whether the first string is a permutation of some substring in the 
 * second string
 *
 * @param[in] status Variable holding the truth value of whether the first string 
 * is a permutation of the some substring in the second string
 */
void print_output(bool status) {
  if (status == true) {
    cs1010_println_string("YES");
  }
  else {
    cs1010_println_string("NO");
  }
}

/**
 * Loops through the entire second string checking one window at a time to check
 * if some substring is a permutation of the first string
 *
 * @param[in] str_two Array holding the second string
 * @param[in] len_one Holds the length of the first string
 * @param[in] len_two Holds the length of the second string
 * @param[in,out] count_substring Array holding the count of the frequency of 
 * characters in the first string
 * @param[in,out] count_window Array holding the count of the frequencey of 
 * characters in the window of the second string
 */
void permutation(char *str_two, long len_one, long len_two, long *count_substring, 
    long *count_window) {
  
  //variable to hold the truth value of whether the first string is a permutation
  //of some substring of the second string
  bool status = false;

  //checks whether the first window is a permutation of the first string 
  if (check(count_substring, count_window) == true) {
    status = true; 
  }

  //checks the remaining windows to see if they are permutations of the first string
  else {
    for (long i = 0; i < (len_two - len_one + 1); i += 1) {
      //navigates to next window
      count_window[str_two[i] - 'a'] -= 1; 
      count_window[str_two[i + len_one] - 'a'] += 1;

      //checks if the window is a permutation of the first string
      if (check(count_substring, count_window) == true) {
        //exits from the loop as soon as a match is found
        status = true; 
        break;
      }
    }
  }

  //prints the status
  print_output(status);
}

int main()
{
  //reads the inputs
  char *string_one = cs1010_read_word();
  char *string_two = cs1010_read_word();

  //finds the length of the first and second string
  long len_one = strlen(string_one);
  long len_two = strlen(string_two);

  //arrays to keep count of the frequencies of the characters in the first string
  //and the window of the second string
  long *count_substring = calloc(26, sizeof(long));
  long *count_window = calloc(26, sizeof(long));

  //gets the count for the first string and the first window of the second string 
  //of the same length as the first string
  get_count(string_one, count_substring, len_one);
  get_count(string_two, count_window, len_one); 

  permutation(string_two, len_one, len_two, count_substring, count_window);

  //frees the memory
  free(string_one);
  free(string_two);
  free(count_substring);
  free(count_window);

  return 0;
}
