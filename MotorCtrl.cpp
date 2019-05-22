/*
  Motor_Servo.cpp - Library for BGM32-2838 DcEncorderMotor control code.
  Created by HanOl. May 21, 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MotorCtrl.h"
#include "Motor.h"

MotorCtrl::MotorCtrl()
{
    this->_ratio = 360./516./52.;
}

MotorCtrl::MotorCtrl(double ratio)
{
    this->_ratio = 360./516./52./ratio;
}

void MotorCtrl::begin()
{
    this->_pos_state = 0;

    digitalWrite(M1_STSP, HIGH);
    digitalWrite(M2_STSP, HIGH);
    digitalWrite(M3_STSP, HIGH);

    digitalWrite(M1_DIRECTION, HIGH);
    digitalWrite(M2_DIRECTION, HIGH);
    digitalWrite(M3_DIRECTION, HIGH);
}

double MotorCtrl::Cal_Real_Pos(double encoder_velue)
{
    this->_realpos = (encoder_velue)*(this->_ratio);

    return this->_realpos;
}

void MotorCtrl::Go_Motor(int MPWM_PIN,int DIRECTION_PIN, double MPWM)
{

    if(MPWM <= 0)
    {
      digitalWrite(DIRECTION_PIN, HIGH); //CCW
    }
    else
    {
      digitalWrite(DIRECTION_PIN, LOW); //CCW
    }

    analogWrite(MPWM_PIN,abs(MPWM));
    delay(1);
}

double MotorCtrl::Cal_Go_Pos(float IN_Value)
{
    if(this->_pos_state = 0)
    {
      this->_pos_state = (double)IN_Value;

      return this->_pos_state;
    }
    else
    {
      double Value = (double)IN_Value - this->_pos_state;
      this->_pos_state = IN_Value;

      return Value;
    }
}
