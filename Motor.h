
#ifndef Motor_h
#define Motor_h

#include "AutoPID.h"

/*
    Motor_1_Pin & PID_Value
*/
#define M1_MPWM 2 
#define M1_STSP 22
#define M1_DIRECTION 24  
#define M1_ENCODER_A 26
#define M1_ENCODER_B 27
#define M1_PWM_MIN -1000
#define M1_PWM_MAX 1000
#define M1_KP 20
#define M1_KI 0.01
#define M1_KD 0.4
#define M1_BANGBANG 3
#define M1_TIMESTEP 10

/*
    Motor_2_Pin & PID_Value
*/
#define M2_MPWM 3
#define M2_STSP 28
#define M2_DIRECTION 30  
#define M2_ENCODER_A 32
#define M2_ENCODER_B 33
#define M2_PWM_MIN -1000
#define M2_PWM_MAX 1000
#define M2_KP 25
#define M2_KI 0.01
#define M2_KD 0.4
#define M2_BANGBANG 3
#define M2_TIMESTEP 10

/*
    Motor_3_Pin & PID_Value
*/
#define M3_MPWM 4
#define M3_STSP 34
#define M3_DIRECTION 36  
#define M3_ENCODER_A 38
#define M3_ENCODER_B 39
#define M3_PWM_MIN -1000
#define M3_PWM_MAX 1000
#define M3_KP 25
#define M3_KI 0.01
#define M3_KD 0.4
#define M3_BANGBANG 3
#define M3_TIMESTEP 10

/*
photo_I/O Pin
*/
#define photo_io_1 40
#define photo_io_2 42
#define photo_io_3 44

double Set_3_Pos(double M1, double M2, double M3);
void Motor_Pin_Set(void);
void PID_Val_Print(double Pos, double SetPos, double MPWM);
void SPI_DUE_SET();
void SPI_Go(double *Pos, float Msg);

#endif
