/**
 * CS1010 Semester 1 AY18/19
 * Assignment 8: Fill
 *
 * Reads from the standard input two positive integers 'm' and 'n' followed by 
 * 'm' lines of strings each of length 'n' consisting of only characters '0' to '9'.
 * The next line is a positive integer 'q' which is the number of color changes the 
 * the techer requires. Following this, there are 'q' lines with three integers on
 * each line: 'x','y' and 'c' whcih mean to color the object containing pixel (x,y)
 * to the color 'c'. The program then prints to the standard output, the drawing after
 * re-coloring the objects according to the teachers commands according to the order
 * of the input. 
 *
 * @file: fill.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include "cs1010.h"

/**
 * Re-colors the objects according to the teacher's commands
 *
 * @param[in, out] grid The drawing consisting of several objects
 * @param[in] rows The number of rows in the drawing
 * @param[in] columns The number of columns in the drawing
 * @param[in, out] x The x coordinate of the pixel
 * @param[in, out] y The y coordinate of the pixel
 * @param[in] new_color The new color of the object after re-coloring
 * @param[in] old_color The original color of the object
 */
void coloring(char **grid, long rows, long columns, long x, long y, 
    char new_color, char old_color) {
  //exits function if the elements beyond the array are accessed or if the cells 
  //extend beyond the object containing the old_color or if new_color and old_color
  //are the same
  if (x < 0 || x > (rows - 1) || y < 0 || y > (columns - 1) 
      || grid[x][y] != old_color || new_color == old_color) {
    return;
  }
  grid[x][y] = new_color;
  //recursively recolors all the cells inside the object
  coloring(grid, rows, columns, x + 1, y, new_color, old_color);
  coloring(grid, rows, columns, x - 1, y, new_color, old_color);
  coloring(grid, rows, columns, x, y + 1, new_color, old_color);
  coloring(grid, rows, columns, x, y - 1, new_color, old_color);
}

/**
 * Prints the drawing 
 *
 * @param[in] grid The drawing consisting of several objects
 * @param[in] rows The number of rows in the drawing 
 */
void print_grid(char **grid, long rows) {
  for (long i = 0; i < rows; i += 1) {
    cs1010_println_string(grid[i]);
  }
}

int main() {
  //reads the inputs
  long rows = cs1010_read_long();
  long columns = cs1010_read_long();
  char **grid = calloc(rows, sizeof(char *));
  for (long i = 0; i < rows; i += 1) {
    grid[i] = cs1010_read_word();
  }
  long num_recolor = cs1010_read_long();
  //initiates the recoloring process
  long x;
  long y;
  long new_color;
  char old_color;
  for (long i = 0; i < num_recolor; i += 1) {
    x = cs1010_read_long();
    y = cs1010_read_long();
    new_color = cs1010_read_long();
    old_color = grid[x][y];
    coloring(grid, rows, columns, x, y, (new_color + '0'), old_color);
  }
  print_grid(grid, rows);
  //frees the memory
  for (long i = 0; i < rows; i += 1) {
    free(grid[i]);
  }
  free(grid);
  return 0;
}
