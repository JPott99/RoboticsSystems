#ifndef _MOTOR_H
#define _MOTOR_H

#define DIR_FWD LOW
#define DIR_BWD HIGH

// A class to neatly contain commands for the
// motors, to take care of +/- values, a min/max
// power value, & pin setup.

class motor_c {
  public:

    // This is a function prototype.
    // The actual function is written outside
    // of the class (see below).
    motor_c(int pwmPinIn, int dirPinIn);
    float whichDirection();
    void motorControl();
    float controlSpeed(int encoderCount, float mySpeed, float targetSpeed, float timeDiff);
   
    float currentSpeed;
    float topSpeed = 255;

    int pwmPin;
    int dirPin;

    int oldEncoderCount;
};

// Constructor: when you create an instance
// of this class, your constructor will be
// called automatically.  You can treat it
// a bit like the main setup().  What needs
// to be setup initially within this class?
motor_c::motor_c(int pwmPinIn, int dirPinIn)
{
  currentSpeed = 0;
  pwmPin = pwmPinIn;
  dirPin = dirPinIn;


  oldEncoderCount = 0;
  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}


float motor_c::whichDirection() //Function to split direction and speed from currentSpeed vector.
{
  float outputSpeed;
  if (currentSpeed < 0)
  {
    outputSpeed = currentSpeed*-1;
    digitalWrite( dirPin, DIR_BWD);
  }
  else
  {
    outputSpeed = currentSpeed;
    digitalWrite( dirPin, DIR_FWD);
  }
  return outputSpeed;
}

void motor_c::motorControl() //Change direction and drive motor.
{
  float mySpeed = whichDirection();
  if (mySpeed > topSpeed)
  {
    mySpeed = topSpeed;
  }
  analogWrite(pwmPin,mySpeed);
}
float motor_c::controlSpeed(int encoderCount,float  mySpeed, float targetSpeed, float timeDiff)
{
  float calcSpeed = (encoderCount - oldEncoderCount)/timeDiff; 
  float newSpeedChange = 1+(targetSpeed-calcSpeed)/calcSpeed;
  oldEncoderCount = encoderCount;
  return (mySpeed*newSpeedChange);
}
// You can add your own functions to the class.
// Don't forget to also prototype in the class
// definition above.
//void motor_c::myOwnFunction( float an_argument ) {
//
//}

#endif
