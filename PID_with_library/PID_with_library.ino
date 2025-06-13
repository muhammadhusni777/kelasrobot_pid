/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

#define PIN_OUTPUT 9

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=0.1, Kd=0.08;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  Serial.begin(9600);
  //initialize the variables we're linked to
  Input = analogRead(A0);
  Setpoint = 350;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = analogRead(A0);
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
  Serial.print("sp : ");
  Serial.print(Setpoint);
  Serial.print(", pv : ");
  Serial.print(Input);
  Serial.print(", pid : ");
  Serial.println(Output);
  delay(500);
}


