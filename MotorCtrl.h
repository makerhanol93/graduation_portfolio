/*
  Motor_Servo.h - Library for BGM32-2838 DcEncorderMotor control code.
  Created by HanOl. May 21, 2018.
  Released into the public domain.
  Using Arduino DUE.
*/

#ifndef MotorCtrl_h
#define MotorCtrl_h
#include "Motor.h"
#include "Arduino.h"
 
class MotorCtrl
{
  public:
    MotorCtrl();
    MotorCtrl(double ratio);
    void begin();
    void Go_Motor(int MPWM_PIN,int DIRECTION_PIN, double MPWM);
    double Cal_Real_Pos(double encoder_velue);
    double Cal_Go_Pos(float IN_Value);

  private:
    double _ratio, _realpos, _pos_state;
    
};

#endif
