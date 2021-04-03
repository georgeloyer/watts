/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

 modified 27 Aug 2020
 by George Loyer
 Create a test program for pan and tilt platform for watts
*/

#include <Servo.h>

Servo panservo;  // create servo object to control pan servo
Servo tiltservo; // create servo object to control tilt servo
// twelve servo objects can be created on most boards

#define PANPIN  3
#define PANMIN  0
#define PANMID  85
#define PANMAX  170

#define TILTPIN 28
#define TILTMIN 90
#define TILTMAX 170
#define TILTMID 120

int led = 13;
int pos = 0;    // variable to store the servo position

void setup() {
  pinMode(led, OUTPUT);
  panservo.attach(3);   // attaches the servo on pin for pan servo
  tiltservo.attach(28); // attaches the servo on pin for tilt servo
  panservo.write(PANMID);   // move to mid position for pan
  delay(250);
  tiltservo.write(TILTMID); // move to mid position for tilt
}

void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  for (pos = PANMID; pos <= PANMAX; pos += 1) { // Goes MID to MAX, MAX to MID, MID to MIN, MIN to MID
    // in steps of 1 degree
    panservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(250);
  for (pos = PANMAX; pos >= PANMID; pos -= 1) { 
    // in steps of 1 degree
    panservo.write(pos);              
    delay(15);                       
  }
  delay(250);
  for (pos = PANMID; pos >= PANMIN; pos -= 1) { 
    panservo.write(pos);              
    delay(15);                      
  }
  delay(250);
  for (pos = PANMIN; pos <= PANMID; pos += 1) { 
    panservo.write(pos);              
    delay(15);                       
  }
  delay(250);

  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
 
  for (pos = TILTMID; pos <= TILTMAX; pos += 1) { // Goes MID to MAX, MAX to MID, MID to MIN, MIN to MID
    // in steps of 1 degree
    tiltservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(250);
  for (pos = TILTMAX; pos >= TILTMID; pos -= 1) { 
    // in steps of 1 degree
    tiltservo.write(pos);              
    delay(15);                       
  }
  delay(250);
  for (pos = TILTMID; pos >= TILTMIN; pos -= 1) { 
    tiltservo.write(pos);              
    delay(15);                      
  }
  delay(250);
  for (pos = TILTMIN; pos <= TILTMID; pos += 1) { 
    tiltservo.write(pos);              
    delay(15);                       
  }
  delay(250);
}
