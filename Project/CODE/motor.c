#include "motor.h"
#include "cross.h"
#include "circle.h"
#include "yroad.h"
#include "openart_mini.h"
#include "main.h"

#define MOTOR1_PWM1     PWM2_MODULE3_CHB_D3 
#define MOTOR1_PWM2     PWM1_MODULE3_CHB_D1
#define MOTOR2_PWM1     PWM2_MODULE3_CHA_D2
#define MOTOR2_PWM2     PWM1_MODULE3_CHA_D0


//#define MINMAX(x, l, u) MIN(MAX(x, l), u)
#define MOTOR_PWM_DUTY_MAX    50000

//变积分PID
//motor_param_t motor_r = MOTOR_CREATE(12, 18, 1, 15, 2500, 250, 10,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);

//常规增量PID
motor_param_t motor_l = MOTOR_CREATE(12, 1000, 25, 10 , 2500, 250, 10, MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);
motor_param_t motor_r = MOTOR_CREATE(12, 1000, 25, 10,  2500, 250, 10, MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);

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
    
    int32_t l_encoder = (int32_t)(motor_l.encoder_speed);
    int32_t r_encoder = (int32_t)(motor_r.encoder_speed);
    int32_t l_target = (int32_t)(motor_l.target_speed);
    int32_t r_target = (int32_t)(motor_r.target_speed);
      
    data[4] = BYTE3(l_encoder);
    data[5] = BYTE2(l_encoder);
    data[6] = BYTE1(l_encoder);
    data[7] = BYTE0(l_encoder);
    data[8] = BYTE3(l_target);
    data[9] = BYTE2(l_target);
    data[10] = BYTE1(l_target);
    data[11] = BYTE0(l_target);

    data[12] = BYTE3(r_encoder);
    data[13] = BYTE2(r_encoder);
    data[14] = BYTE1(r_encoder);
    data[15] = BYTE0(r_encoder);
    data[16] = BYTE3(r_target);
    data[17] = BYTE2(r_target);
    data[18] = BYTE1(r_target);
    data[19] = BYTE0(r_target);

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
     motor_l.target_speed = 0;
     motor_r.target_speed = 0;
  }
  else if(clk<6000)
  {
     motor_l.target_speed = 15;
     motor_r.target_speed = 15;
  }
  else if(clk<8000)
  {
     motor_l.target_speed = 28;
     motor_r.target_speed = 28;
  }
  else if(clk<10000)
  {
     motor_l.target_speed = 0;
     motor_r.target_speed = 0;
  }

}

float normal_speed = 15.8;
float target_speed;

void speed_control(void)
{
   motor_l.motor_mode = MODE_NORMAL;
   motor_r.motor_mode = MODE_NORMAL;
   
   //起步
   if(pit_get_ms(TIMER_PIT)<1000 && motor_r.encoder_speed<10){
     motor_l.motor_mode = MODE_STOP;
     motor_r.motor_mode = MODE_STOP;
     target_speed = normal_speed;
     motor_l.target_speed = target_speed;
     motor_r.target_speed = target_speed; 
   }
   //apriltime快停
  if(pit_get_ms(TIMER_PIT) - openart.apriltime<1000){
     motor_l.motor_mode = MODE_STOP;
     motor_r.motor_mode = MODE_STOP;
     motor_r.target_speed = 0;
     motor_l.target_speed = 0;
  }
   else if(yroad_type == YROAD_NEAR){
     motor_r.target_speed = 1;
     motor_l.target_speed = 1;
   }
   else if(yroad_type == YROAD_FOUND){
     motor_l.motor_mode = MODE_STOP;
     motor_r.motor_mode = MODE_STOP;
     motor_r.target_speed = 4;
     motor_l.target_speed = 4;
   }
   else if(circle_type != CIRCLE_NONE){
     target_speed = MINMAX(target_speed - 0.01,normal_speed - 1,normal_speed);
     motor_r.target_speed = target_speed;
     motor_l.target_speed = target_speed;
   }
   else if(is_straight0 && is_straight1){
     target_speed = MINMAX(target_speed + 0.1,normal_speed,normal_speed+4);
     motor_r.target_speed = target_speed;
     motor_l.target_speed = target_speed;
   }
   else{
     target_speed = normal_speed;
     motor_l.target_speed = target_speed;
     motor_r.target_speed = target_speed; 
   }
   
}
        
void motor_control(void)
{    
    //square_signal();
    
    //wireless_show();
  
    speed_control();
    
    if(motor_l.motor_mode == MODE_NORMAL){
        motor_l.duty += changable_pid_solve(&motor_l.pid ,(float)(motor_l.target_speed - motor_l.encoder_speed));	
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX * 7/10, MOTOR_PWM_DUTY_MAX * 7/10);
     
    }else if(motor_l.motor_mode == MODE_STOP){
        motor_l.duty += increment_pid_solve(&motor_l.brake_pid ,(float)(motor_l.target_speed - motor_l.encoder_speed));	
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }
    
    
    if(motor_r.motor_mode == MODE_NORMAL){
        motor_r.duty += changable_pid_solve(&motor_r.pid ,(float)(motor_r.target_speed - motor_r.encoder_speed));	
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX * 7/10, MOTOR_PWM_DUTY_MAX * 7/10);
    }else if(motor_r.motor_mode == MODE_STOP){ 
        motor_r.duty += increment_pid_solve(&motor_r.brake_pid ,(float)(motor_r.target_speed - motor_r.encoder_speed));	
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }
    
    //占空比限幅
    
    
    pwm_duty(MOTOR1_PWM1, (motor_l.duty>=0)? motor_l.duty : 0);
    pwm_duty(MOTOR1_PWM2, (motor_l.duty>=0)? 0 : (-motor_l.duty));
    
    pwm_duty(MOTOR2_PWM1, (motor_r.duty>=0)? motor_r.duty : 0);
    pwm_duty(MOTOR2_PWM2, (motor_r.duty>=0)? 0 : (-motor_r.duty));		
    
    
}

int64_t get_total_encoder(){
    return (int64_t)((motor_l.total_encoder + motor_r.total_encoder) / 2);
}
