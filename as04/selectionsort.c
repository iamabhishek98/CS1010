/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: SelectionSort
 *
 * Reads the the number of integers (n) to sort followed by n integers into 
 * an array, and prints, to the standard output, n−1 lines, each line showing 
 * the array after moving the largest or the next largest element into position.
 *
 * @file: selectionsort.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include <cs1010.h>

/**
 * Sorts and prints the elements of the input array
 *
 * @param[in] n number of integers
 * @param[in] arr[] array of integers in an array
 *
 * First the maximum element of the array excluding the last one is found 
   and compared with the last element.
 * If the maximum element  is greater than the last element then their 
   positions are swapped.
 * The new array is then printed. 
 * This swapping process till the entire sorting process is complete. 
 */
void selection_sort(long n, long arr[]) {
  //variable to hold the length of the array
  long len = n;

  //while loop to repeat the swapping process till the sorting process is complete
  while (n > 1) {
    //variable to store the maximum element
    long max = 0;
    //variable to store the position of the maximum element
    long ele = 0;

    //for loop to find the maximum element of the array excluding the last element
    for (long i = 0; i < (n - 1); i += 1) {
      if (arr[i] > max) {
        max = arr[i];
        ele = i;
      }
    }

    //if condition to see if the maximum element is greater than the last element
    if (arr[ele] > arr[n - 1]) {
      //swaps position of maximum element and last element
      long temp = arr[n - 1];
      arr[n - 1] = arr[ele];
      arr[ele] = temp;
    }

    //for loop to print the array
    for (long j = 0; j < len; j += 1) {
      cs1010_print_long(arr[j]);
      cs1010_print_string(" ");
    }
    cs1010_println_string("");

    n -= 1;
  }
}

int main()
{
  //reads inputs from user
  long arr_len = cs1010_read_long();
  long* arr = cs1010_read_long_array(arr_len);

  selection_sort(arr_len, arr);

  return 0;
}
