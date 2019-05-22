
// Arduino Mega

#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <Wire.h>

#define I2C_address 11

// ROS Position Var
float Pos_M1, Pos_M2, Pos_M3;

void Set_Pos(const sensor_msgs::JointState& POS)
{
  Pos_M1 = degrees(POS.position[0]);
  Pos_M2 = degrees(POS.position[1]);
  Pos_M3 = degrees(POS.position[2]);
}

ros::NodeHandle NH;
ros::Subscriber<sensor_msgs::JointState> PWM_SCR("/joint_states", Set_Pos);

void setup()
{
  // Join i2c bus, address 11
  Wire.begin(I2C_address);
  // register event
  Wire.onRequest(requestEvent);

  // Ros node init
  NH.initNode();
  NH.subscribe(PWM_SCR);
}

void loop()
{
  NH.spinOnce();
  delay(1);
}

void requestEvent()
{
  long M1 = (long)((Pos_M1+180)*100);
  long M2 = (long)((Pos_M2+180)*100);
  long M3 = (long)((Pos_M3+180)*100);
  
  Wire.write(M1); // lower byte
  Wire.write(M1>>8); // upper byte

  Wire.write(M2); // lower byte
  Wire.write(M2>>8); // upper byte

  Wire.write(M3); // lower byte
  Wire.write(M3>>8); // upper byte
}

