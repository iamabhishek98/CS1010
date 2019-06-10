/**
 * CS1010 Semester 1 AY18/19
 * Assignment 8: Maze
 *
 * Reads from standard input, two positive integers m and n, followed by m lines of
 * n characters in each line that represents the maze setup. One and only one @ will 
 * present in the maze setup, The program, then prints, to the standard output, an 
 * animation of k iterations. The output should only contain m rows with n characters
 * in each row, with an additional row at last. Similarly, '#' is used to represent a 
 * wall, '.' is used to represent an empty space and '@' is used to represent where
 * Scully is at. After printing the maze, the program also prints the number of steps
 * made by Scully.
 *
 * @file: maze.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"
#include <unistd.h>
#include <stdbool.h>

#define WALL '#'
#define EMPTY '.'
#define VISITED 'x'
#define CROSS 'X'
#define CURRENT '@'
#define SLEEP_INTERVAL 250000

/**
 * Copies the maze to a new array and finds the position of '@' in the maze
 *
 * @param[in] maze The array holding the input maze 
 * @param[out] visited_maze The array holding the new maze to store the visited 
 * cells in the input maze
 * @param[in] rows The number of rows in the input maze
 * @param[in] columns The number of columns in the input maze
 * @param[out] initial_row The row in which '@' is initially present
 * @param[out] initial_column The column in which '@' is initially present
 */
void copy_maze(char **maze, char **visited_maze, long rows, long columns, 
    long *initial_row, long *initial_column) {
  //use of nested for loops to copy the maze and find position of '@'
  for (long i = 0; i < rows; i += 1) {
    for (long j = 0; j < columns; j += 1) {
      visited_maze[i][j] = maze[i][j]; 
      if (maze[i][j] == CURRENT) {
        *initial_row = i;
        *initial_column = j;
      }
    }
  }
}

/**
 * Prints the updated maze and number of steps taken by Scully
 *
 * @param[in] maze The array holding the maze with the updated position of Scully
 * @param[in] rows The number of rows in the maze
 * @param[in] steps The number of steps taken by Scully so far
 */
void print_maze(char **maze, long rows, long *steps) {
  //clears the screen
  char clear_screen[] = { 27, '[', '2', 'J',27, '[', ';', 'H', '\0'};
  cs1010_print_string(clear_screen);
  //prints the updated maze and the number of steps taken by Scully
  for (long i = 0; i < rows; i += 1) {
    cs1010_println_string(maze[i]);
  }
  cs1010_println_long(*steps);
  usleep(SLEEP_INTERVAL);
}

/**
 * Updates the current position of Scully
 *
 * @param[out] maze The array holding the maze with the updated position of Scully
 * @param[out] visited_maze The array holding the maze with the updated position 
 * of Scully and the cels visited by Scully
 * @param[in] prev_i The row holding the previous position of Scully
 * @param[in] prev_j The column holding the previous position of Scully
 * @param[in] i The row holding the current position of Scully
 * @param[in] j The column holding the current position of Scully
 */
void update_cell(char **maze, char **visited_maze, long prev_i, long prev_j, long i,
    long j) {
  visited_maze[prev_i][prev_j] = VISITED;
  visited_maze[i][j] = CURRENT;
  maze[prev_i][prev_j] = EMPTY;
  maze[i][j] = CURRENT;
}

/**
 * Recursively finds the path of Scully and backtracks if Scully reaches a dead end
 *
 * @param[in, out] maze The array holding the maze with the updated position of Scully
 * @param[in, out] visited_maze The array holding the maze with the updated position 
 * of Scully and the cells visited by Scully
 * @param[in] rows The numbers of rows in the maze 
 * @param[in] columns The number of columsn in the maze
 * @param[out] steps The number of steps taken by Scully so far
 * @param[in, out] i The row holding the updated position of Scully
 * @param[in, out] j The column holding the updated position of Scully
 * @return true if path exists. Otherwise, false.
 */
bool navigate(char **maze, char **visited_maze, long rows, long columns, long *steps, 
    long i, long j) {
  //updates the current position of Scully
  maze[i][j] = CURRENT;
  //prints the updated maze
  print_maze(maze, rows, steps); 
  *steps += 1;
  //base case
  if ((i == 0 || i == (rows - 1) || j == 0 || j  == (columns - 1))) {
    return true; 
  }
  //recursively checks if a path exists if Scully goes up by one cell
  if (visited_maze[i - 1][j] == EMPTY) {
    update_cell(maze, visited_maze, i, j, i - 1, j);
    if (navigate(maze, visited_maze, rows, columns, steps, i - 1, j)) {
      return true;
    }
  }
  //recursively checks if a path exists if Scully goes right by one cell
  else if (visited_maze[i][j + 1] == EMPTY) {
    update_cell(maze, visited_maze, i, j, i, j + 1);
    if (navigate(maze, visited_maze, rows, columns, steps, i, j + 1)) {
      return true;
    }
  }
  //recursively checks if a path exists if Scully goes down by one cell
  else if (visited_maze[i + 1][j] == EMPTY) {
    update_cell(maze, visited_maze, i, j, i + 1, j);
    if (navigate(maze, visited_maze, rows, columns, steps, i + 1, j)) {
      return true;
    }
  }
  //recursively checks if a path exists if Scully goes left by one cell
  else if (visited_maze[i][j - 1] == EMPTY) {
    update_cell(maze, visited_maze, i, j, i, j - 1);
    if (navigate(maze, visited_maze, rows, columns, steps, i, j - 1)) {
      return true;
    }
  }
  //updates the visited cell with a CROSS if no path exists
  else {
    visited_maze[i][j] = CROSS;
    maze[i][j] = EMPTY;
    return false;
  }
  //recursively backtracks since no path exists
  visited_maze[i][j] = CURRENT;
  maze[i][j] = CURRENT;
  if (navigate(maze, visited_maze, rows, columns, steps, i, j)) {
    return true;
  }
  return false;
}

/**
 * Frees the memory 
 *
 * @param[out] maze The array holding the maze
 * @param[in] rows The number of rows in the maze
 */
void free_memory(char **maze, long rows) {
  for (long i = 0; i < rows; i += 1) {
    free(maze[i]);
  }
  free(maze);
}

int main() {
  //reads the integers
  long rows = cs1010_read_long(); 
  long columns = cs1010_read_long();
  //reads the maze and creates a new array to store the maze
  char **maze = calloc(rows, sizeof(char *));
  char **visited_maze = calloc(rows, sizeof(char *));
  for (long i = 0; i < rows; i += 1) {
    maze[i] = cs1010_read_word();
    visited_maze[i] = calloc(columns, sizeof(char));
  }
  //finds the intial position of Scully
  long initial_row;
  long initial_column; 
  copy_maze(maze, visited_maze, rows, columns, &initial_row, &initial_column);
  //variable to keep track of steps taken by Scully
  long steps = 0;
  navigate(maze, visited_maze, rows, columns, &steps, initial_row, initial_column);
  //frees the memory
  free_memory(maze, rows);
  free_memory(visited_maze, rows);
  return 0;
}

