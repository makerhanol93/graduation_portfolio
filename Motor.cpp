
#include "Motor.h"
#include "Arduino.h"
#include <SPI.h>

void Motor_Pin_Set()
{
  // Motor_1
  pinMode(M1_MPWM, OUTPUT);
  pinMode(M1_STSP, OUTPUT);
  pinMode(M1_DIRECTION, OUTPUT);
  pinMode(M1_ENCODER_A, INPUT_PULLUP);
  pinMode(M1_ENCODER_B, INPUT_PULLUP);
  
  // Motor_2
  pinMode(M2_MPWM, OUTPUT);
  pinMode(M2_STSP, OUTPUT);
  pinMode(M2_DIRECTION, OUTPUT);
  pinMode(M2_ENCODER_A, INPUT_PULLUP);
  pinMode(M2_ENCODER_B, INPUT_PULLUP);
  
  // Motor_3
  pinMode(M3_MPWM, OUTPUT);
  pinMode(M3_STSP, OUTPUT);
  pinMode(M3_DIRECTION, OUTPUT);
  pinMode(M3_ENCODER_A, INPUT_PULLUP);
  pinMode(M3_ENCODER_B, INPUT_PULLUP);

}

void PID_Val_Print(double Pos, double SetPos, double MPWM)
{
  Serial.print("Pos : ");
  Serial.print(Pos);
  Serial.print("  setPos : ");
  Serial.print(SetPos);
  Serial.print("  PWM : ");
  Serial.println(MPWM);
}

double Set_3_Pos(double M1, double M2, double M3)
{
  double _Pos[2];

  _Pos[0] = M1;
  _Pos[1] = M2;
  _Pos[2] = M3;

  return *_Pos;
}

void SPI_DUE_SET()
{
  // 슬레이브 선택 해제
  digitalWrite(SS, HIGH);
  // SPI통신 초기화
  SPI.begin();
  // SPI통신속도설정
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void SPI_Go(double *Pos, float Msg)
{
  for(int i=0; i<3; i++)
  {
    // 슬레이브 선택 연결, SS 10
    digitalWrite(SS, LOW);  
    // 데이터 송신
    Pos[i] = SPI.transfer(Msg);
    // disable Slave Select
    digitalWrite(SS, HIGH);
    delay(5);
  }
  
  Serial.println(Pos[0]);
  Serial.println(Pos[1]);
  Serial.println(Pos[2]);
  
  delay(10);
}