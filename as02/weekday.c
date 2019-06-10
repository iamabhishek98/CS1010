/**
 * CS1010 Semester 1 AY18/19
 * Assignment 2: Weekday
 *
 * @file: weekday.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include "cs1010.h"
#include "math.h"
#include <stdbool.h>

//function to check if the year is a leap year
bool is_leap_year(long year)
{
  if (year % 4 == 0)
  {
    if (year % 100 == 0)
    {
      if (year % 400 == 0)
        return true;
      else
        return false;
    }
    else
      return true;
  }
  else {
    return false;
  }
}

//function to output which day of the year
long count_for_day_yr(long month, long day)
{
  if (month == 1) {
    return day;
  }
  else if (month == 2) {
    return day + 31;
  }
  else if (month == 3) {
    return day + 59;
  }
  else if (month == 4) {
    return day + 90;
  }
  else if (month == 5) {
    return day + 120;
  }
  else if (month == 6) {
    return day + 151;
  }
  else if (month == 7) {
    return day + 181;
  }
  else if (month == 8) {
    return day + 212;
  }
  else if (month == 9) {
    return day + 243;
  }
  else if (month == 10) {
    return day + 273;
  }
  else if (month == 11) {
    return day + 304;
  }
  else {
    return day + 334;
  }
}

//function to check which day of the week
long weekday(long year, long month, long day) {
  long count = 0;

  //loop to check if every year from 1900 to input year is a leap year
  for (long i =1900; i < year; i += 1)
  {
    //bool j = is_leap_year(i);
    //conditions to check if i is leap year 
    if (is_leap_year(i) == true) {
      count = count + 366;
    }
    else if (is_leap_year(i) == false) {
      count = count + 365; 
    }
  }

  count += count_for_day_yr(month, day);
  long check = count % 7;

  return check;
}

//function to print day of the week
void output (long check)
{
  if (check == 1) { 
    cs1010_println_string("Monday");
  }
  else if (check == 2) {
    cs1010_println_string("Tuesday");
  }
  else if (check == 3) {
    cs1010_println_string("Wednesday");
  }
  else if (check == 4) {
    cs1010_println_string("Thursday");
  }
  else if (check == 5) {
    cs1010_println_string("Friday");
  }
  else if (check == 6) {
    cs1010_println_string("Saturday");
  }
  else if (check == 0) {
    cs1010_println_string("Sunday");
  }
}


int main()
{
  //reads all inputs from user
  long year = cs1010_read_long();
  long month = cs1010_read_long();
  long day = cs1010_read_long();

  //if condition to check for validity of input
  if (year>=1900 && ((month >= 1) && (month<= 12)) && ((day >= 1) && (day <= 31))) 
  {
    //functions to print the day of the week
    output(weekday(year, month, day));
  }

  return 0;
}




