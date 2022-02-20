#ifndef SONAR_STUFF_H_
#define SONAR_STUFF_H_

#include <NewPing.h>

#include <millisDelay.h>

millisDelay check_sonar;

#define MAX_DISTANCE 200 //time = 57*200 + 6000 = 17.4ms
#define F_TRIGGER_PIN  26//purple
#define F_ECHO_PIN 26
#define B_TRIGGER_PIN 48 //green
#define B_ECHO_PIN 48

float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
int iterations = 3;

float soundsp = 343;
float soundcm = soundsp/10000; //cm/ms

bool reading_data = false;

const unsigned long WAIT_TO_GET_NEXT_READING = 90; 
unsigned long sonarCm;
unsigned long sonarPm;


float get_dist(NewPing s1){
  reading_data = true;

  int its = 3;
  float duration = s1.ping_median(its);

  reading_data = false;

  return (duration / 2) * soundcm;
}

#endif
