/*
       @@@@@@@@@@@&*           %@@@@@%       @@@@@@@@@    @@@@@@@@@  @@@@@@@@
       @@@@@@@@@@@@@@@     #@@@@@@@@@@@@    @@@@@@@@@@   @@@@@@@@@* @@@@@@@@@
       @@@@@@   @@@@@@   /@@@@@%  .@@@@@@    @@@/@@@@@ @@@@@@@@@@    @@@@@@
      &@@@@@##&@@@@@@   @@@@@@(   @@@@@@@   @@@,.@@@@@@@@,.@@@@@    @@@@@@
      @@@@@@@@@@@@@    &@@@@@@    @@@@@@   @@@@  @@@@@@@  @@@@@    (@@@@@
     @@@@@@  @@@@@@*   @@@@@@    @@@@@@   .@@@   @@@@@#  @@@@@@    @@@@@&
   @@@@@@@@   @@@@@@%  .@@@@@@@@@@@@@    @@@@@%  @@@@  @@@@@@@@  @@@@@@@@
  %@@@@@@@&   @@@@@@     #@@@@@@@@      @@@@@@   @@@   @@@@@@@/ @@@@@@@@%

  Provided by Paul O'Dowd Oct 2020
*/


// The following files should all appear in
// tabs above.  They are incomplete and match
// up to exercie labsheets provided.
#include "lineSensor.h"
#include "encoders.h"
#include "kinematics.h"
#include "motor.h"
#include "pid.h"
#include "math.h"
#define PI 3.141592654

//
//
//#define LINE_LEFT_PIN A4 //Pin for the left line sensor
//#define LINE_CENTRE_PIN A3 //Pin for the centre line sensor
//#define LINE_RIGHT_PIN A2 //Pin for the right line sensor

#define L_PWM_PIN 10 //Define Motor Pins
#define L_DIR_PIN 16 //Define Motor Pins
#define R_PWM_PIN  9 //Define Motor Pins
#define R_DIR_PIN 15 //Define Motor Pins


float motorTElapsed = 0;
float motorInterval = 100;
float leftCountTE = 0;
float rightCountTE = 0;
//unsigned long long int lineTElapsed = 0;
//float lineInterval = 5;


//float setSpeed = 4;// /motorInterval


float Kp_left = 0.4; //Proportional gain 
float Kd_left = 0.0005; //Derivative gain
float Ki_left = 0.00001; //Integral gain
PID_c left_PID(Kp_left, Ki_left, Kd_left); // controller for left wheel
float leftSpeedMeasure = 0;
float leftOutput = 0;



//float Kp_right = 0.4; //Proportional gain 
//float Kd_right = 0.0005; //Derivative gain
//float Ki_right = 0.00001; //Integral gain
PID_c right_PID(Kp_left, Ki_left, Kd_left); // controller for left wheel
float rightSpeedMeasure = 0;
float rightOutput = 0;

int distMeasure = 0;
int timeResetVal = 0;
//
//float leftDemand = setSpeed;
//float rightDemand = setSpeed;
//float heading;

//lineSensor_c leftLine(LINE_LEFT_PIN); //Create a line sensor object for the left sensor
//lineSensor_c middleLine(LINE_CENTRE_PIN); //Create a line sensor object for the centre sensor
//lineSensor_c rightLine(LINE_RIGHT_PIN); //Create a line sensor object for the right sensor

motor_c leftMotor(L_PWM_PIN, L_DIR_PIN); //Create motor object
motor_c rightMotor(R_PWM_PIN, R_DIR_PIN); //Create Motor object


// Setup, only runs once when the power
// is turned on.  However, if your Romi
// gets reset, it will run again.
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(17, OUTPUT);
  digitalWrite(17,LOW);
  setupEncoder0();
  setupEncoder1();
  // Start up the serial port.
  Serial.begin(9600);

  // Delay to connect properly by calibrating.


  // Print a debug, so we can see a reset on monitor.
//   Serial.println("***RESET***");
   digitalWrite(17,HIGH);
} // end of setup()

void driveMotors(float l_demand, float r_demand)
{
  leftSpeedMeasure = (countLeft-leftCountTE);
  leftOutput = left_PID.update(l_demand, leftSpeedMeasure);
  leftCountTE = countLeft;
  leftMotor.currentSpeed += leftOutput;
  leftMotor.motorControl();

  rightSpeedMeasure = (countRight-rightCountTE);
  rightOutput = right_PID.update(r_demand, rightSpeedMeasure);
  rightCountTE = countRight;
  rightMotor.currentSpeed += rightOutput;
  rightMotor.motorControl();

  motorTElapsed = millis();
}

int maxCount = 25;
int resultLeft[25] = {0}; 
int resultRight[25] = {0}; 
int resultTime[25] = {0};

void printCSV()
{
  int counter = 0;
  while (counter<maxCount)
  {
    Serial.print(resultLeft[counter]);
    Serial.print(",");
    Serial.print(resultRight[counter]);
    Serial.print(",");
    Serial.print(resultTime[counter]);
    Serial.println(",");
    counter++;
  }
}

int currentCount = 0;

int directionMultiplier = 1;
int targetMilliMetersPerInterval = 5;
float targetTicksPerInterval;
void loopMain()
{
  if (millis() - motorTElapsed >=motorInterval)
  {
    targetTicksPerInterval = targetMilliMetersPerInterval*20/PI*directionMultiplier;
    driveMotors(targetTicksPerInterval,targetTicksPerInterval);
  }
  if (abs(countLeft - distMeasure) > 20/PI*50)
  {
    if (directionMultiplier == 1)
    {
      resultLeft[currentCount] = leftMotor.currentSpeed;
      resultRight[currentCount] = rightMotor.currentSpeed;
      resultTime[currentCount] = millis() - timeResetVal;
      currentCount = currentCount+1;
    }
    timeResetVal = millis();
    distMeasure = countLeft;
    if (directionMultiplier == 1)
    {
      directionMultiplier = -1;
    }
    else
    {
      directionMultiplier = 1;
    }
    right_PID.reset();
    left_PID.reset();
  }
}
// The main loop of execution.  This loop()
// function is automatically called every
// time it finishes.  You should try to write
// your code to take advantage of this looping
// behaviour.
char inChar;
void loop() {
  if (currentCount < maxCount)
  {
    loopMain();
  }
  else
  {
    if (currentCount == maxCount)
    {
      currentCount = maxCount+1;
    }
    leftMotor.currentSpeed = 0;
    rightMotor.currentSpeed = 0;
    leftMotor.motorControl();
    rightMotor.motorControl();
    if (inChar != 'o')
    {
      inChar = Serial.read();
      if (inChar =='o')
      {
        printCSV();
      }
    }
  }
  
//  Serial.println(volt);
//  Serial.print(leftDemand);Serial.print(',');
//  Serial.print(rightDemand);Serial.print(',');
//  Serial.print('\n');
}
