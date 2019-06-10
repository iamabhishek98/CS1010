/**
 * CS1010 Semester 1 AY18/19
 * Assignment 1: Invest
 * Read the dollar amount of initial investment, the annual interest rate, 
 * and the number of years k from the standard input, and print the amount 
 * of money in the investment after k years to the standard output.
 * @file: invest.c
 * @author: KARNATI SAI ABHISHEK (Group C04)
 */
#include <math.h>
#include "cs1010.h"

int main() 

{
long m = cs1010_read_long();
double r = cs1010_read_double();
double n = cs1010_read_double();
r= r/100;
n= n + 1;
double c = (double)pow(r,n);
double investment = (double)(m*(1-c))/(1-(r));
cs1010_println_double(investment);
return 0;

}




