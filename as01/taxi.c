/**
 * CS1010 Semester 1 AY18/19
 * Assignment 1: Taxi
 * Read the day, hour, and minute when a passenger board a taxi
 * and the distance in meter travelled from the standard input,
 * and print the taxi fare to the standard output.
 * @file: taxi.c
 * @author: Karnati Sai Abhishek (Group C04)
 */
#include <stdbool.h>
#include "cs1010.h"
#include <math.h>

bool day_of_week (long day) {
  if (day>=1 && day<=5) {
    return true;
  }
  else {
    return false;
  }
}

double cost_of_trip(long distance)
{
  if (distance<=1000)
  {
    double price=3.4;
    return price;
  }
  else if (distance<=10200)
  {
    double g = ceil((double)(distance-1000)/400);
    double price = 3.4+(g*0.22);
    return price;
  }
  else 
  {
    double g = ceil((double)(distance-10200)/350);
    double price = 8.46+(g*0.22);
    return price;
  }
}

bool morning_peak (long hours, long minutes) {

  if (hours==9 && minutes<=29)
  {
    return true;
  }
  else if ((hours>=6) && (hours<=8))
  {
    return true;
  }

  else {
    return false;
  }
}

bool evening_peak (long hours, long minutes) {

  if ((hours>=18) && (hours<=23 && minutes<=59))
  {
    return true;
  }

  else {
    return false;
  }
}

bool midnight_peak (long hours, long minutes) {

  if ((hours>=0) && (hours<=5 && minutes<=59))
  {
    return true;
  }

  else {
    return false;
  }
}

double surcharge_rate(bool wc, bool  mp, bool ep, bool  mid) {

  if (wc==true && mp==true)
  {
    return 1.25;
  }
  else if (ep==true) {
    return 1.25;
  }
  else if (mid==true) {
    return 1.5;
  }
  else 
  {
    return 1;
  }
}

int main()
{
  long day = cs1010_read_long();
  long hours = cs1010_read_long();
  long minutes = cs1010_read_long();
  long distance = cs1010_read_long();

  double base_fare=cost_of_trip(distance);

  bool weekday = day_of_week(day);
  bool morning = morning_peak(hours, minutes);
  bool evening = evening_peak(hours, minutes);
  bool midnight = midnight_peak(hours, minutes);

  double surcharge = surcharge_rate(weekday, morning, evening, midnight);
  double price = surcharge*base_fare; 
  cs1010_println_double(price);


  return 0;

}

