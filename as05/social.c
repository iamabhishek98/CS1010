/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: Social
 *
 * Reads from standard input two positive intergers n and k, followed by n lines
 * of strings consisting of '1' and '0' representing the social network of these
 * n people. Prints, to the standard output, the social network formed by a 
 * friendship chain of degree k. Also prints "YES" if everyone is connected 
 * to everyone within k hops or "NO" otherwise.
 *
 * @file: social.c
 * @author: Karnati Sai Abhishek (Group C04)
 */

#include <cs1010.h>
#include <stdbool.h>

#define TRUE '1'
#define FALSE '0'

/**
 * Checks whether if a person A is a friend of person B
 * 
 * @param[in] **network Pointer to a jagged array comprising the social network
 * @param[in] A a person in the network
 * @param[in] B another person in the network
 * @return true returns whether A and B are friends or not
 */
bool friend(char **network , long A , long B) {
  long lesser;
  long greater;

  if (A < B) {
    lesser = A;
    greater = B;
  }

  else {
    lesser = B;
    greater = A;
  }

  if (network[greater][lesser] == FALSE) {
    return false;
  }
  else {
    return true;
  }
}


/**
 * Checks whether a person A is related to person B through mutual friends
 *
 * @param[in] **network Pointer to a jagged array comprising the social network
 * @param[in] num_of_people The number of people in the social network
 * @param[in] degree The number of hops allowed in the social network
 * @param[in] A a person in the network
 * @param[in] B another person in the network
 * @return true returns whether A and B are friends or not up to a certain degree
 */
bool mutual_friend(char **network, long num_of_people, long degree, long A, long B) {
  if (degree == 0) {
    return false;
  }

  else if (degree == 1) { 
    return friend(network, A, B);
  }

  if (friend(network, A, B) == true) {
    return true;
  } 

  for (long i = 0; i < num_of_people; i+=1) {
    if (i != A && i != B) {
      if (friend(network , A ,i) == true) {
        if (mutual_friend(network, num_of_people, (degree - 1), i, B) == true) { 
          return true;
        }
      }
    }
  }
  return false; 
}

/**
 * Prints the updated social network
 *
 * @param[in] **updated_network Pointer to the updated network formed by a friendship 
 * chain of a certain degree
 * @param[in] num_of_people The number of people in the social network
 * @param[in] status Holds the truth value of whether everyone is connected
 */
void print_network(char **updated_network, long num_of_people, bool status) {
  for (long i = 0; i < num_of_people; i += 1) {
    cs1010_println_string(updated_network[i]);
  }

  if (status == true) {
    cs1010_println_string("YES");
  } 
  else {
    cs1010_println_string("NO");
  }
}

/**
 * Computes the social network formed by a friendship of a certain degree
 *
 * @param[in] **network Pointer to the input social network
 * @param[in] **updated_network Pointer to the updated social network
 * @param[in] num_of_people The number of people in the social network
 * @param[in] degree The number of hops allowed in the social network
 */
void social_network(char **network, char **updated_network, long num_of_people, 
    long degree) {
  bool status = true; 
  //nested for loops to compare everyone in the network
  for (long i = 0; i < num_of_people; i += 1) {
    for (long j = 0; j <= i; j += 1) {
      if (friend(network, j, i) == false) {
        //checks whether i and j have any mutual friends within degree hops
        if (mutual_friend(network, num_of_people, degree, j, i)) {
          updated_network[i][j] = TRUE;
        }
        else {   
          updated_network[i][j] = FALSE;
        }
      }
      else { 
        updated_network[i][j] = TRUE;
      }
      if (updated_network[i][j] == FALSE) {
        status = false; 
      }
    }
  } 
  print_network(updated_network, num_of_people, status);
}

/**
 * Deallocation of memory in the reverse order of memory allocation
 *
 * @param[in] **network Pointer to the social network
 * @param[in] num_of_people The number of people in the social network
 */
void free_memory(char **network, long num_of_people) {
  for (long i = 0; i < num_of_people; i += 1) {
    free(network[i]);
  }
  free(network);
}

int main() {

  //reads the two positive integers
  long num_of_people = cs1010_read_long();
  long degree = cs1010_read_long();

  //reads the friendship network in the form of a jagged array 
  char **network = calloc(num_of_people, sizeof(char*));
  for(long i = 0; i < num_of_people; i += 1){
    network[i] = calloc(i + 1, sizeof(char));
    network[i] = cs1010_read_word();
  }

  //creates an array to hold the updated social network 
  char **updated_network = calloc(num_of_people, sizeof(char*));
  for(long i = 0; i < num_of_people; i += 1){
    updated_network[i] = calloc(i + 1, sizeof(char));
  }

  social_network(network, updated_network, num_of_people, degree);

  free(network);
  free(updated_network);

  return 0; 
}
