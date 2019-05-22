
// Arduino Due

#include <Motor.h>
#include <MotorCtrl.h>
#include <Wire.h>
#include <AutoPID.h>

// I2C var
volatile int M1P_a; volatile int M1P_b; volatile int M1P;
volatile int M2P_a; volatile int M2P_b; volatile int M2P;
volatile int M3P_a; volatile int M3P_b; volatile int M3P;

// Encoder Var
double M1_encoderPos = 0, M2_encoderPos = 0, M3_encoderPos = 0;
double Set_Pos_in_1 = 0, Set_Pos_in_2 = 0, Set_Pos_in_3 = 0;

// PID & Motor_drive Var
double M1_Pos = 0, M1_SetPos = 0, M1_PWM_Val = 0;
double M2_Pos = 0, M2_SetPos = 0, M2_PWM_Val = 0;
double M3_Pos = 0, M3_SetPos = 0, M3_PWM_Val = 0;

double Pos[2];

// PID Constructor
AutoPID M1_PID (&M1_Pos, &M1_SetPos, &M1_PWM_Val, M1_PWM_MIN, M1_PWM_MAX, M1_KP, M1_KI, M1_KD);
AutoPID M2_PID (&M2_Pos, &M2_SetPos, &M2_PWM_Val, M2_PWM_MIN, M2_PWM_MAX, M2_KP, M2_KI, M1_KD);
AutoPID M3_PID (&M3_Pos, &M3_SetPos, &M3_PWM_Val, M3_PWM_MIN, M3_PWM_MAX, M3_KP, M3_KI, M1_KD);

MotorCtrl M1_CTR(120/35), M2_CTR(5), M3_CTR(5);

void setup()
{
  // DUE_SET
  Wire.begin(); Serial.begin(57600);
  Motor_Pin_Set(); PID_Set();
  Photo_Pin_Set();

  // Motor Begin
  M1_CTR.begin();
  M2_CTR.begin(M2_STSP,M2_DIRECTION,M2_MPWM);
  M3_CTR.begin();
  
  // Encoder Start
  Encoder_Interrupt_Set();
}

void loop()
{
    /*
    if(Serial.available())
    {
      Set_Pos_Val();
    }
    */
    
    // PID RUN
    M1_PID.run(); //PID_Val_Print(M1_Pos, M1_SetPos, M1_PWM_Val);
    M2_PID.run(); //PID_Val_Print(M2_Pos, M2_SetPos, M2_PWM_Val);
    M3_PID.run(); //PID_Val_Print(M3_Pos, M3_SetPos, M3_PWM_Val);

    Serial.print(" M1: ");
    Serial.print(M1_Pos);
    Serial.print(" M2: ");
    Serial.print(M2_Pos);
    Serial.print(" M3: ");
    Serial.println(M3_Pos);
    
    Set_Real_Pos();

    // Set_Pos
    I2C_Go();
     
    // Motor_drive
    M1_CTR.Go_Motor(M1_MPWM,M1_DIRECTION,M1_PWM_Val);
    M2_CTR.Go_Motor(M2_MPWM,M2_DIRECTION,M2_PWM_Val);
    M3_CTR.Go_Motor(M3_MPWM,M3_DIRECTION,M3_PWM_Val);
}

/*
  Photo Interrupt Call Back
*/
void Photo_back_1(){digitalWrite(M1_STSP,LOW); M1_CTR.Call_back();}
void Photo_back_2(){digitalWrite(M2_STSP,LOW); M2_CTR.Call_back();}
void Photo_back_3(){digitalWrite(M3_STSP,LOW); M3_CTR.Call_back();}

/*
  Encoder Interrupt Call Back
*/
void M1_doEncoderA(){ M1_encoderPos += (digitalRead(M1_ENCODER_A)==digitalRead(M1_ENCODER_B))?1:-1;}
void M1_doEncoderB(){ M1_encoderPos += (digitalRead(M1_ENCODER_A)==digitalRead(M1_ENCODER_B))?-1:1;}
void M2_doEncoderA(){ M2_encoderPos += (digitalRead(M2_ENCODER_A)==digitalRead(M2_ENCODER_B))?1:-1;}
void M2_doEncoderB(){ M2_encoderPos += (digitalRead(M2_ENCODER_A)==digitalRead(M2_ENCODER_B))?-1:1;}
void M3_doEncoderA(){ M3_encoderPos += (digitalRead(M3_ENCODER_A)==digitalRead(M3_ENCODER_B))?1:-1;}
void M3_doEncoderB(){ M3_encoderPos += (digitalRead(M3_ENCODER_A)==digitalRead(M3_ENCODER_B))?-1:1;}

void Photo_Pin_Set()
{
   pinMode(Photo_1, INPUT_PULLUP);
   pinMode(Photo_2, INPUT_PULLUP);
   pinMode(Photo_3, INPUT_PULLUP);
   attachInterrupt(Photo_1, Photo_back_1, FALLING);
   attachInterrupt(Photo_2, Photo_back_2, FALLING);
   attachInterrupt(Photo_3, Photo_back_3, FALLING);
}

void Encoder_Interrupt_Set()
{
  // Interrupt_Pin_Set
  attachInterrupt(M1_ENCODER_A, M1_doEncoderA, CHANGE);
  attachInterrupt(M1_ENCODER_B, M1_doEncoderB, CHANGE);
  attachInterrupt(M2_ENCODER_A, M2_doEncoderA, CHANGE);
  attachInterrupt(M2_ENCODER_B, M2_doEncoderB, CHANGE);
  attachInterrupt(M3_ENCODER_A, M3_doEncoderA, CHANGE);
  attachInterrupt(M3_ENCODER_B, M3_doEncoderB, CHANGE);
}

void PID_Set()
{
  M1_PID.setBangBang(M1_BANGBANG); M1_PID.setTimeStep(M1_TIMESTEP); 
  M2_PID.setBangBang(M2_BANGBANG); M2_PID.setTimeStep(M2_TIMESTEP);
  M3_PID.setBangBang(M3_BANGBANG); M3_PID.setTimeStep(M3_TIMESTEP);
}

/*
double Set_Pos_Val()
{
  Set_Pos_in_1 = (double)Serial.parseFloat();
  Set_Pos_in_2 = (double)Serial.parseFloat();
  Set_Pos_in_3 = (double)Serial.parseFloat();

  M1_SetPos = M1_CTR.Cal_Go_Pos(Set_Pos_in_1);
  M2_SetPos = M2_CTR.Cal_Go_Pos(Set_Pos_in_2);
  M3_SetPos = M3_CTR.Cal_Go_Pos(Set_Pos_in_3);
}
*/

void Set_Real_Pos()
{
  M1_Pos = M1_CTR.Cal_Real_Pos(M1_encoderPos);
  M2_Pos = M2_CTR.Cal_Real_Pos(M2_encoderPos);
  M3_Pos = M3_CTR.Cal_Real_Pos(M3_encoderPos);

  *Pos = Set_3_Pos(M1_Pos, M2_Pos, M3_Pos);
}


void I2C_Go()
{
  Wire.requestFrom(11, 6);
  
  while (Wire.available())
  {
    M1P_a = Wire.read(); M1P_b = Wire.read();
    M1P = (M1P_b << 8) | M1P_a;

    M2P_a = Wire.read(); M2P_b = Wire.read();
    M2P = (M2P_b << 8) | M2P_a;

    M3P_a = Wire.read(); M3P_b = Wire.read();
    M3P = (M3P_b << 8) | M3P_a;
  }

  M1_SetPos = (double(M1P)/100)-180;
  M2_SetPos = (double(M2P)/100)-180;
  M3_SetPos = (double(M3P)/100)-180;

  /*
  Serial.print(" M1P: "); Serial.print(M1_Pos);
  Serial.print(" M2P: "); Serial.print(M2_Pos);
  Serial.print(" M3P: "); Serial.println(M3_Pos);
  */
}


