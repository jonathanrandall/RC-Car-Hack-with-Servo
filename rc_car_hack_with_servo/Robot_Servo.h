#ifndef SERVO_STUFF_H_
#define SERVO_STUFF_H_


#include <Servo.h>
#include "sonar_stuff.h"

#define F_SERVO_PIN 24
#define B_SERVO_PIN 50

unsigned long headCm;
unsigned long headPm;
const unsigned long HEAD_MOVEMENT_PERIOD = 105;  //move servo every 105 ms.
int currentReadPosition;

unsigned long usCm;
unsigned long usPm;
const unsigned long WAIT_AFTER_HEAD_STARTS_MOVING = 83;        // Time to wait between checking the US Sensor
//boolean usReadFlag = false;                                
boolean HEAD_DEBUG = true;


class Robot_Servo : public Servo, public NewPing
{
  public:
  Robot_Servo(int SERVO_PIN, int E_PIN, int T_PIN, int offset = 0);

  void move_servo();
  void read_sonar();

//  Servo myservo;

  // Initialize Ultrasonic
  boolean sonar_flag = true;
//  const int ECHO_PIN;  
//  const int TRIG_PIN;

  const int iteratons = 1;
  float distances[3] = {MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE};

  const int NUM_HEAD_POSITIONS = 3;
  const int HEAD_POSITIONS[3] = { 140, 90, 40}; //{150, 120, 90, 60, 30};

  //left , middle, right for front
  //right middle left for backwards

  int offset;

  boolean headDirectionClockwise = false;
  int currentHeadPosition = 1;
  int currentReadPosition;
  
};

Robot_Servo::Robot_Servo(int SERVO_PIN, int E_PIN, int T_PIN, int offset) :  offset(offset), NewPing(E_PIN, T_PIN, MAX_DISTANCE)
{

//    write(90+offset);
}

void Robot_Servo::move_servo(){
  headCm = millis();
  if(headCm > headPm + HEAD_MOVEMENT_PERIOD) {
    headPm = headCm;
    write(HEAD_POSITIONS[currentHeadPosition]+offset);

    // position head to the current position in the array
//    if(SERVO_ON) {
//      headServo.write( HEAD_POSITIONS[currentHeadPosition] );
//    }
    // the the position the US sensor should read at
    currentReadPosition = currentHeadPosition;

    // check timing debug
//    if(TIMING_DEBUG) {
//      Serial.print("Move head initiated: ");
//      Serial.println(headCm);
//    }
//
//    // head debug output
//    if(HEAD_DEBUG) {
//      Serial.print(currentHeadPosition);
//      Serial.print(" - ");
//      Serial.print(HEAD_POSITIONS[currentHeadPosition]);
//    }

    /**
     * Set next head position
     * Moves servo to the next head position and changes direction when needed.
     */
    if(headDirectionClockwise) {  
      if(currentHeadPosition >= (NUM_HEAD_POSITIONS -1)) {
        headDirectionClockwise = !headDirectionClockwise;
        currentHeadPosition--;
      }
      else {
        currentHeadPosition++;
      }
    }
    else {
      if(currentHeadPosition <= 0) {
        headDirectionClockwise = !headDirectionClockwise;
        currentHeadPosition++;
      }
      else {
        currentHeadPosition--;
      }
    }
    
    // reset pervious millis
    
    // reset read flag
    sonar_flag = false;
  }
}


void Robot_Servo::read_sonar() {
  usCm = millis();
  if(usCm > headPm + WAIT_AFTER_HEAD_STARTS_MOVING && !sonar_flag) {
    sonar_flag = true;

    duration = (*this).ping_median(iterations);
    distance = (duration / 2) * soundcm;
    if (distance > MAX_DISTANCE) distance = MAX_DISTANCE;
    if (distance == 0) distance = MAX_DISTANCE;
    distances[currentReadPosition] = distance;

    if(HEAD_DEBUG || true) {
      Serial.print(currentReadPosition);
      Serial.print(" - ");
      Serial.println(distances[currentReadPosition]);
    }
  }
}


//Servo frontservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
unsigned long run_servo_p;
unsigned long run_servo_r = 2000;

//
//void start_servo() {
//  frontservo.attach(F_SERVO_PIN);  // attaches the servo on pin 9 to the servo object
//}
//
//void run_servo() {
//
//  frontservo.write(96);
//  if(false){
//  for (pos = 50; pos <= 150; pos += 5) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    frontservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(10);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 150; pos >= 50; pos -= 5) { // goes from 180 degrees to 0 degrees
//    frontservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(10);                       // waits 15ms for the servo to reach the position
//  }}
//}


#endif
