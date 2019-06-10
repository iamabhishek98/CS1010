/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Add
 *
 * Reads from the standard input two non-negative numbers represented as 
 * strings consisting of digits '0' to '9', and prints to the standard output 
 * the sum of the two numbers.
 *
 * @file: add.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include <cs1010.h>
#include <math.h>

/**
 * The number of digits in the sum of the two numbers
 *
 * @param[in] len_one The length of the first number
 * @param[in] len_two The length of the second number
 *
 * @return len_one length of sum cannot be longer than len_one if condition is met
 * @return len_two length of sum cannot be longer than len_two if condition is met
 * @return (len_one + 1) length of sum in the case when len_one = len_two
 *
 */
long len_of_sum(long len_one, long len_two) {
  if (len_one > len_two) {
    return len_one;
  }
  else if (len_two > len_one) {
    return len_two;
  }
  else {
    return len_one + 1;
  }
}

/**
 * Calculate sum of input arrays
 *
 * @param[in] rev_one[] first number in reverse
 * @param[in] len_one length of first number
 * @param[in] rev_two[] second number in reverse
 * @param[in] len_two length of second number
 *
 * Simulation of addition by adding one array element to another at a time
 * Adds carry over digit to the next array element 
 * Reverse the elements of the array to give the correct sum
 * Print the sum by skipping the 0s in front of the number
 */
void sum(char rev_one[], long len_one, char rev_two[], long len_two) {
  //sum_len holds the length of the sum array
  long sum_len = len_of_sum(len_one, len_two) + 1;

  //declaration of a new array to hold the sum of the input arrays in reverse
  char rev_sum[sum_len];

  //initilazes all elements of the sum array to '0'
  for (long i = 0; i < sum_len; i += 1) {
    rev_sum[i] = '0';
  }

  long count = 0;

  //while loop simulates addition by hand
  while (count < sum_len) {
    //variable that holds the value of the carry over digit
    long carry = 0;
    long temp;

    //adds digit of the reversed first number if it exists
    if (len_one > count) {
      temp = (rev_sum[count] - '0') + (rev_one[count] - '0');
      if (temp > 9) {
        carry += 1;
        rev_sum[count] = (temp - 10) + '0';
      }
      else {
        rev_sum[count] = temp + '0';
      }
    }

    //adds digit of the reversed second number if it exists 
    if (len_two > count) {
      temp = (rev_sum[count] - '0') + (rev_two[count] - '0');
      if (temp > 9) {
        carry += 1;
        rev_sum[count] = (temp - 10) + '0';
      }
      else {
        rev_sum[count] = temp + '0';
      }
    }

    //adds the carry over digit to the next element of the sum array
    if (count < (sum_len - 1)) {
      rev_sum[count + 1] = ((rev_sum[count + 1] - '0') + carry) + '0';
    }

    count += 1;
  }

  //sum array to hold the sum in the correct order
  char sum[sum_len + 1];
  for (long g = 0; g < (sum_len + 1); g += 1) {
    if (g == (sum_len)) {
      sum[g] = '\0';
    }
    else {
      sum[g] = rev_sum[sum_len - 1 - g];
    }
  }

  //keeps count of the number of zeros in front of the number
  long counter = 0;
  while (sum[counter] == '0') {
    counter += 1;
  }

  //prints the correct sum skipping the zeros in front
  cs1010_println_string(sum + counter);
}

int main()
{
  //reads inputs from user
  char* num_one = cs1010_read_word();
  char* num_two = cs1010_read_word();

  //gets the length of the input arrays
  long num_one_len = strlen(num_one);
  long num_two_len = strlen(num_two);

  //array which reverses the elements of the first number
  char reverse_one[num_one_len];
  for (long i = 0; i < num_one_len; i += 1) {
    reverse_one[i] = num_one[num_one_len - 1 - i];
  }

  //array which reverses the elements of the second number
  char reverse_two[num_two_len];
  for (long j = 0; j < num_two_len; j += 1) {
    reverse_two[j] = num_two[num_two_len - 1 -j];
  }

  sum(reverse_one, num_one_len, reverse_two, num_two_len);

  return 0;
}
