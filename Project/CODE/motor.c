#include "motor.h"

#define MOTOR1_PWM1     PWM2_MODULE3_CHB_D3 
#define MOTOR1_PWM2     PWM1_MODULE3_CHB_D1
#define MOTOR2_PWM1     PWM2_MODULE3_CHA_D2
#define MOTOR2_PWM2     PWM1_MODULE3_CHA_D0


//#define MINMAX(x, l, u) MIN(MAX(x, l), u)
#define MOTOR_PWM_DUTY_MAX    50000

//常规增量PID
//motor_param_t motor_l = MOTOR_CREATE(1000, 25, 10, MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);

//变积分PID
//motor_param_t motor_r = MOTOR_CREATE(18, 1, 15, MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);

//专家PID
motor_param_t motor_l = MOTOR_CREATE(1000, 25, 2 , MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);
motor_param_t motor_r = MOTOR_CREATE(1000, 25, 1, MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);

void motor_init(void)
{
    pwm_init(MOTOR1_PWM1, 17000, 0);
    pwm_init(MOTOR1_PWM2, 17000, 0);
    pwm_init(MOTOR2_PWM1, 17000, 0);
    pwm_init(MOTOR2_PWM2, 17000, 0);
}


void wireless_show(void)
{
    static uint8_t data[22];
    data[0] = 0xAA;
    data[1] = 0xFF;
    data[2] = 0xF1;
    data[3] = 16;
    data[4] = BYTE3(motor_l.encoder_speed);
    data[5] = BYTE2(motor_l.encoder_speed);
    data[6] = BYTE1(motor_l.encoder_speed);
    data[7] = BYTE0(motor_l.encoder_speed);
    data[8] = BYTE3(motor_l.target_speed);
    data[9] = BYTE2(motor_l.target_speed);
    data[10] = BYTE1(motor_l.target_speed);
    data[11] = BYTE0(motor_l.target_speed);

    data[12] = BYTE3(motor_r.encoder_speed);
    data[13] = BYTE2(motor_r.encoder_speed);
    data[14] = BYTE1(motor_r.encoder_speed);
    data[15] = BYTE0(motor_r.encoder_speed);
    data[16] = BYTE3(motor_r.target_speed);
    data[17] = BYTE2(motor_r.target_speed);
    data[18] = BYTE1(motor_r.target_speed);
    data[19] = BYTE0(motor_r.target_speed);

    uint8_t sumcheck = 0; 
    uint8_t addcheck = 0; 
    for(uint8_t i=0; i < data[3]+4; i++) 
    { 
      sumcheck += data[i]; //从帧头开始，对每一字节进行求和，直到DATA区结
      addcheck += sumcheck;   //每一字节的求和操作，进行一次sumcheck的加 }
    } 
    data[20] = sumcheck;
    data[21] = addcheck;

    seekfree_wireless_send_buff(data, sizeof(data));
}

uint32_t clk;
void square_signal(void)
{
  clk += 1;
  if(clk>10000) {clk = 0;}
  if(clk<2000)
  {
     motor_l.target_speed = 20;
     motor_r.target_speed = 20;
  }
  else if(clk<4000)
  {
     motor_l.target_speed = 5;
     motor_r.target_speed = 5;
  }
  else if(clk<6000)
  {
     motor_l.target_speed = 25;
     motor_r.target_speed = 25;
  }
  else if(clk<8000)
  {
     motor_l.target_speed = 15;
     motor_r.target_speed = 15;
  }
  else if(clk<10000)
  {
     motor_l.target_speed = 5;
     motor_r.target_speed = 5;
  }

}


        
void motor_control(void)
{
    motor_l.target_speed = 7;
    motor_r.target_speed = 7;
    
    //square_signal();
    
    //wireless_show();
    
    motor_l.duty += increment_pid_solve(&motor_l.pid ,(float)(motor_l.target_speed - motor_l.encoder_speed));
    motor_r.duty += increment_pid_solve(&motor_r.pid ,(float)(motor_r.target_speed - motor_r.encoder_speed));
    
    //占空比限幅
    motor_l.duty = MINMAX(motor_l.duty, 1, MOTOR_PWM_DUTY_MAX  * 1);
    motor_r.duty = MINMAX(motor_r.duty, 1, MOTOR_PWM_DUTY_MAX  * 1);
    
    
    pwm_duty(MOTOR1_PWM1, (motor_l.duty>=0)? motor_l.duty : 0);
    pwm_duty(MOTOR1_PWM2, (motor_l.duty>=0)? 0 : (-motor_l.duty));
    
    pwm_duty(MOTOR2_PWM1, (motor_r.duty>=0)? motor_r.duty : 0);
    pwm_duty(MOTOR2_PWM2, (motor_r.duty>=0)? 0 : (-motor_r.duty));		

}