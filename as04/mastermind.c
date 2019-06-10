/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Mastermind

 * Reads in the 4-letter code from the standard inputs. It then reads 
 * in a sequence of 4-letter guesses. For each guess, the program prints 
 * out two numbers, the first is the number of pegs that are correct in 
 * both position and color.The second, is the number of pegs that are 
 * correct in color but not position.
 *
 * @file: mastermind.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include <cs1010.h>
#include <string.h>

/**
 * Simulation of the Mastermind game
 *
 * @param[in] code[] The 4-ltter code read from the user
 *
 * Simulation of Mastermind rounds by terminating when number of rounds is 8
   or when the count of black pins is 4
 * Counts the black pins by comparing elements of code and guess 
 * Counts the white pins by the use of temporary array to store guess in
   which if condition is true, the elements are initialized to '0' to prevent
   double counting.
 * Prints out the number of black pins and white pins
 */
void game(char code[]) {
  //count variable counts the number of rounds
  long count = 0;

  //variables to count the number of black and white pins
  long black;
  long white;

  //while loop to simulate the rounds of Mastermind 
  while (count < 8 && black != 4) {
    //reads the guess array from the user
    char* guess = cs1010_read_word(4);

    /* temp_guess array to hold the values of the guess array 
       used for counting white pins */
    char temp_guess[4]; 
    for (long i = 0; i < 4; i += 1) {
      temp_guess[i] = guess[i];
    }

    //initializing number of black and white pins to 0
    black = 0;
    white = 0;

    //for loop to navigate from one element of the code array to another
    for (long j = 0; j < 4; j += 1) {
      /* if statement to check if the elements are correct 
         in both position and colour */
      if (code[j] == guess[j]) {
        black += 1;
      }

      //else statement to check if the elements are correct in colour 
      else {
        //counter variable to prevent double counting
        long counter = 0;
        for (long k = 0; k < 4; k += 1) {
          if (code[j] == temp_guess[k]) {
            counter += 1;
            /* changing element of temp_guess array to 0 to prevent 
               double counting if condition is met */
            temp_guess[k] = '0';
          }
        }
        if (counter > 0) {
          white += 1;
        }
      }
    }

    /* the number of black pins can never be greater than the number of 
       white pins due to the nature of the game */
    if (black > white) {
      white = 0;
    }

    //prints the outputs 
    cs1010_print_long(black);
    cs1010_print_string(" ");
    cs1010_println_long(white);

    //incrementing the count variable to move on to the next round
    count += 1;
  }
}


int main()
{
  //reads the main array from the user
  char* code = cs1010_read_word();

  game(code);

  return 0;
}
