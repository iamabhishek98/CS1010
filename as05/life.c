/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Life
 *
 * Reads, from the standard inputs, three positive integers n, m and k,
 * where n and m denotes the number of rows and number of columns of the 
 * universe while k is the number of iterations to simulate. It then reads,
 * from the standard input, n rows, with m characters in each row representing 
 * the initial state. Each character is either alive or dead. The program then 
 * prints, to standard output, an animation of the universe for k iterations.
 *
 * @file: life.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"
#include <unistd.h>

#define LIVE '#'
#define DEAD '.'
#define SLEEP_INTERVAL 250000

/**
 * Temporarily store the values from the input array in a temporary array
 * The function duplicates every cell of the pattern array into the canvas
 * array one by one.
 *
 * @param[in] **pattern Pointer to the pattern array
 * @param[in] **temp_pattern Pointer to the temp_pattern array
 * @param[in] rows The number of rows in the input array
 * @param[in] columns The number of columns in the input array
 */
void initialize_temp(char **pattern, char **temp_pattern, long rows, long columns) {
  //use of nested for loops to duplicate the pattern array in canvas array
  for (long i = 0; i < rows; i += 1) {
    for (long j = 0; j < columns; j += 1) {
      temp_pattern[i][j] = pattern[i][j];
    }
  }
}

/**
 * Update the previous pattern array
 * The function updates the the old pattern array with the new cell states.
 * 
 * @param[in] **pattern Pointer to the pattern array
 * @param[in] **temp_pattern Pointer to the temp_pattern array
 * @param[in] rows The number of rows in the input array
 * @param[in] columns The number of columns in the input array
 */
void new_pattern(char **pattern, char **temp_pattern, long rows, long columns) {
  //use of nested for loops to update the individual pattern cells
  for (long i = 0; i < rows; i += 1) {
    for (long j = 0; j < columns; j += 1) {
      pattern[i][j] = temp_pattern[i][j];
    }
  }
}

/**
 * Prints the pattern 
 * The function prints the pattern.
 * The program is then paused for a specified amount of time on the screen. 
 *
 * @param[in] **pattern Pointer to the pattern array
 * @param[in] rows The number of rows in the input array
 */
void print_pattern(char **pattern, long rows) {
  //for loop to print the pattern array row by row
  for (long i = 0; i < rows; i += 1) {
    cs1010_println_string(pattern[i]);
  }

  //pauses the program for a specified amount of time
  usleep(SLEEP_INTERVAL); 
}

/**
 * Simulates the "Game of Life"
 * The screen is cleared.
 * The states of the neighbouring cells are then stored in an array.
 * The number of dead cells is recorded. 
 * The status of the cell is updated according to the status of the 
 * neighbouring cells.
 * The main pattern array is updated with the new statuses of its cells.
 * The pattern is printed. 
 * The same process is then repeated for the number of iterations.
 * 
 * @param[in] **pattern Pointer to the pattern array
 * @param[in] **temp_pattern Pointer to the temp_pattern array
 * @param[in] rows The number of rows in the input array
 * @param[in] columns The number of columns in the input array
 * @param[in] iterations The number of iterations to simulate the game
 */
void life(char **pattern, char **temp_pattern, long rows, long columns, long iterations) {
  //for loop to repeat printing the updated patten for the number of iterations
  for (long a = 0; a < iterations; a += 1) {
    //screen is cleared
    char clear_screen[] = { 27, '[', '2', 'J',27, '[', ';', 'H', '\0'};
    cs1010_print_string(clear_screen);

    //nested for loops to navigate to each cell of the pattern array
    //excluding the border cells
    for (long i = 1; i < (rows - 1); i += 1) {
      for (long j = 1; j < (columns - 1); j += 1) {
        //variable to keep count of the number of live neighbouring cells
        long live_count = 0;

        //array to store the statuses of the neighbouring cells
        char neighbours[8] = {pattern[i - 1][j - 1], pattern[i - 1][j], 
          pattern[i - 1][j + 1], pattern[i][j - 1], pattern[i][j + 1], 
          pattern[i + 1][j - 1], pattern[i + 1][j], pattern[i + 1][j + 1]};

        //for loop to count the number of live neighbouring cells
        for (long k = 0; k < 8; k += 1) {
          if (neighbours[k] == LIVE) {
            live_count += 1;
          }
        }

        //nested if and else statements to update the cell status 
        //according to status of the neighbouring cells
        if (pattern[i][j] == LIVE) {
          if (live_count < 2 || live_count > 3) {
            temp_pattern[i][j] = DEAD;
          }
        }
        else if (pattern[i][j] == DEAD) {
          if (live_count == 3) {
            temp_pattern[i][j] = LIVE;
          }
        }
      }
    }

    //updates the pattern array
    new_pattern(pattern, temp_pattern, rows, columns);

    //prints the pattern array
    print_pattern(pattern, rows);
  }
}

/**
 * Deallocation of memory in the reverse order of memory allocation.
 *
 * @param[in] **temp_pattern Pointer to the temp_pattern array
 * @param[in] rows The number of rows in the temp_pattern array
 */
void free_memory(char **temp_pattern, long rows) {
  for (long i = 0; i < rows; i += 1) {
    free(temp_pattern[i]);
  }
  free(temp_pattern);
}

int main()
{
  //reads the three positive integers
  long rows = cs1010_read_long();
  long columns = cs1010_read_long(); 
  long iterations = cs1010_read_long();

  //reads the pattern array 
  char *pattern[rows];
  for (long i = 0; i < rows; i += 1) {
    pattern[i] = cs1010_read_word(); 
  }

  //creates a new array and allocates the dimensions dynamically
  char **temp_pattern = calloc(rows, sizeof(char *));
  for (long i = 0; i < rows; i += 1) {
    temp_pattern[i] = calloc(columns, sizeof(char));
  }

  initialize_temp(pattern, temp_pattern, rows, columns);

  life(pattern, temp_pattern, rows, columns, iterations);

  free_memory(temp_pattern, rows);

  return 0;
}
