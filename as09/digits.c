/**
 * CS1010 Semester 1 AY18/19
 * Assignment 9: Digits
 *
 * The program reads, from the standard input a positive integer n, corresponding to
 * the number of training samples, followed by repeatedly read n handwritten digits 
 * containing a label and 28 lines of texts consisting of '.' and '#' representing a 
 * handwritten digit. This is then followed by another positive integer m, corresponding
 * to the number of testing samples, followed by repeatedly read m handwritten digits
 * containing a label and 28 lines of text. The program then prints to the standard 
 * output, for each testing sample, the digit it is labeled as followed by a space,
 * followed by the digit it is recognized as. A double value corresponding to the 
 * accuracy is also printed. 
 * 
 *
 * @file: digits.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5
//the maximum possible difference between the testing and training samples is 28*28 
//because there are only 28 rows and 28 columns in each sample
//so the difference in the samples can never be greater than MAX
#define MAX ((28*28) + 1)

/**
 * The sample holding the label and the handwritten digit
 */
typedef struct matrix {
  //the ground truth
  long label;
  //the sample containing the handwritten digit
  char** digits;
} matrix;

/**
 * Finds the distance between each test sample and all available training samples
 *
 * @param[in] training The array holding the training samples
 * @param[in] num_training The number of training samples
 * @param[in] testing The array holding the testing samples
 * @param[in] num_testing The number of testing samples
 * @param[out] diff The array holding the distance between the testing and training samples
 */
void find_diff(matrix *training, long num_training, matrix *testing, long num_testing, 
    long **diff) {
  long count;
  //nested loops to compare elements of the training and testing sample structures
  for (long i = 0; i < num_testing; i += 1) {
    for (long j = 0; j < num_training; j += 1) {
      //variable to hold the distance
      count = 0;
      for (long a = 0; a < NROWS; a += 1) {
        for (long b = 0; b < NCOLS; b += 1) {
          if (testing[i].digits[a][b] != training[j].digits[a][b]) {
            //increments when the samples are different
            count += 1;
          } 
        }
      }
      //adds the distance to the array
      diff[i][j] += count;
    }
  }
}

/**
 * Finds the k neighbours with the least distance
 *
 * @param[in,out] diff The array holding the distance between the testing and training samples
 * @param[out] neighbour_label The array holding the digits with the smallest distance
 * @param[in] num_testing The number of testing samples
 * @param[in] num_training The number of training samples
 * @param[in] training The array holding the training samples
 */
void find_k_neighbours(long **diff, long **neighbour_label, long num_testing, 
    long num_training, matrix *training) {
  //nested loops to find the k nearest neighbours
  for (long i = 0; i < num_testing; i += 1) {
    for (long a = 0; a < K; a += 1) {
      //min is set to be MAX because no element in the diff array can possibly be 
      //higher than it
      long min = MAX;
      long location = 0;
      //finds the minimum in the array of differences
      for (long j = 0; j < num_training; j += 1) {
        if (diff[i][j] < min) {
          min = diff[i][j];
          location = j;
        }
        else if (diff[i][j] == min && training[j].label < training[location].label) {
          min = diff[i][j];
          location = j;
        }
      }
      //stores the digits with the smallest distance in the array
      neighbour_label[i][a] = training[location].label;
      //element is set to MAX so that when looped through again the min and location 
      //will change 
      diff[i][location] = MAX;
    }
  }
}

/**
 * Finds the most common neighbour with the least distance
 *
 * @param[in] neighbour_label The array holding the digits with the smallest distances
 * @param[out] neighbour The array holding the most common digit for each testing sample
 * @param[in] num_testing The number of testing samples
 */
void find_neighbour(long **neighbour_label, long *neighbour, long num_testing) {
  for (long a = 0; a < num_testing; a += 1) {
    //array to hold the number of occurences of the digits 
    long *count = calloc(10, sizeof(long));
    for (long j = 0; j < K; j += 1) {
      count[neighbour_label[a][j]] += 1;
    }
    long max_occurrence = 0;
    long location = 0;
    for (long i = 0; i < 10; i += 1) {
      if (count[i] > max_occurrence) {
        max_occurrence = count[i];
        location = i;
      }
    }
    //stores the most common digit in the array
    neighbour[a] = location;
    free(count);
  }
}

/**
 * For each testing sample, it prints the digit it is labeled as, the digit it is 
 * recognized as followed by a value corresponding to the accuracy
 *
 * @param[in] testing_samples The array holding the testing samples
 * @param[in] neighbour The array holding the most common digit for each testing sample
 * @param[in] num_testing The number of testing samples
 */
void print_accuracy(matrix *testing_samples, long *neighbour, long num_testing) {
  //stores the total number of testing samples correctly recognized
  long total = 0;
  for (long i = 0; i < num_testing; i += 1) {
    if (testing_samples[i].label == neighbour[i]) {
      total += 1;
    }
    cs1010_print_long(testing_samples[i].label);
    cs1010_print_string(" ");
    cs1010_println_long(neighbour[i]);
  }
  //calculates the accuracy by finding the percentage of testing samples correctly 
  //recognized
  double accuracy = (total/(double)num_testing)*100;
  cs1010_println_double(accuracy);
}

/**
 * Frees the memory occupied by the array
 * 
 * @param[out] array The array
 * @param[in] rows The number of rows in the array
 */
void free_array(long **array, long rows) {
  for (long i = 0; i < rows; i += 1) {
    free(array[i]);
  }
  free(array);
}

/**
 * Frees the memory occupied by the structure
 *
 * @param[out] arr_struct The array holding the samples
 * @param[in] size The number of samples in the array
 */
void free_structure(matrix *arr_struct, long size) {
  for (long i = 0; i < size; i += 1) {
    for (long j = 0; j < NROWS; j += 1) {
      free(arr_struct[i].digits[j]);
    } 
    free(arr_struct[i].digits);
  }
  free(arr_struct);
}

int main()
{
  //reads the training samples
  long num_training = cs1010_read_long();
  matrix *training_samples = calloc(num_training, sizeof(matrix));
  for (long i = 0; i < num_training; i += 1) {
    training_samples[i].label = cs1010_read_long();
    training_samples[i].digits = calloc(NROWS, sizeof(char *));
    for (long j = 0; j < NROWS; j += 1) {
      training_samples[i].digits[j] = cs1010_read_word();
    }
  }
  //reads the testing samples
  long num_testing = cs1010_read_long();
  matrix *testing_samples = calloc(num_testing, sizeof(matrix));
  //array to hold the differences between the training and testing samples
  long **diff = calloc(num_testing, sizeof(long));
  //array to hold the digits with smallest distance for each testing sample
  long **neighbour_label = calloc(num_testing, sizeof(long));
  //array to hold the most common digit for each testing sample
  long *neighbour = calloc(num_testing, sizeof(long));
  for (long i = 0; i < num_testing; i += 1) {
    testing_samples[i].label = cs1010_read_long();
    testing_samples[i].digits = calloc(NROWS, sizeof(char *));
    diff[i] = calloc(num_training, sizeof(long));
    neighbour_label[i] = calloc(K, sizeof(long));
    for (long j = 0; j < NROWS; j += 1) {
      testing_samples[i].digits[j] = cs1010_read_word();
    }
  }
  find_diff(training_samples, num_training, testing_samples, num_testing, diff);
  find_k_neighbours(diff, neighbour_label, num_testing, num_training, training_samples);
  find_neighbour(neighbour_label, neighbour, num_testing);
  print_accuracy(testing_samples, neighbour, num_testing);
  //frees the memory
  free(neighbour);
  free_array(neighbour_label, num_testing);
  free_array(diff, num_testing);
  free_structure(testing_samples, num_testing);
  free_structure(training_samples, num_training);
  return 0;
}
