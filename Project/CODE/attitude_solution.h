#ifndef __ATTITUDE_H
#define __ATTITUDE_H

#include "headfile.h"
typedef struct{
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float acc_x;
  float acc_y;
  float acc_z;
}icm_param_t;


typedef struct{
	float q0;
	float q1;
	float q2;
	float q3;
}quater_param_t;


typedef struct{
	float pitch;    //¸©Ñö½Ç
	float roll;     //Æ«º½½Ç
	float yaw;       //·­¹ö½Ç
}euler_param_t;


typedef struct{
  float Xdata;
  float Ydata;
  float Zdata;
}gyro_param_t;


void gyroOffset_init(void);
float fast_sqrt(float x);

void ICM_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az);
void ICM_getValues();
void ICM_getEulerianAngles(void);

#endif
