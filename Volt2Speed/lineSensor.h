#ifndef _LINESENSOR_H
#define _LINESENSOR_H

class lineSensor_c {
  
  public:

    int pin;
    float bias;
    // Constructor, accepts a pin number as
    // argument and sets this as input.
    lineSensor_c( int which_pin ) 
    {
       // Record which pin we used.
       pin = which_pin;

       // Set this pin to input.
       pinMode( pin, INPUT );
    };


    // Write your calibration routine here
    // to remove bias offset
    void calibrate(int calibrationTime) 
    {
      bias = 0;
      int counter = 0;
      float counterMax = calibrationTime;
      while (counter < counterMax)
      {
        bias += readSensor()/counterMax;
        delay(1);
        counter++;
      }
    }


    // Write a routine here to check if your
    // sensor is on a line (true or false).
    boolean onLine( float threshold ) {
       if (readCalibrated() > threshold) 
       {
          return true;
       }
             
      return false;
    }

    float readSensor()
    {
      float value = analogRead(pin);
      return value;
    }

    float readCalibrated()
    {
      float value = readSensor() - bias;
      if (value < 25)
      {
        value =  0;
      }
      return value;
    }
    // You can define other functions for
    // yourself. 
    // ...

};

#endif
