#include "motor.h"
#include "cross.h"
#include "circle.h"
#include "yroad.h"
#include "garage.h"
#include "apriltag.h"
#include "elec.h"
#include "openart_mini.h"
#include "main.h"
#include "elec.h"

#define MOTOR1_PWM1     PWM2_MODULE3_CHB_D3 
#define MOTOR1_PWM2     PWM1_MODULE3_CHB_D1
#define MOTOR2_PWM1     PWM2_MODULE3_CHA_D2
#define MOTOR2_PWM2     PWM1_MODULE3_CHA_D0


//#define MINMAX(x, l, u) MIN(MAX(x, l), u)
#define MOTOR_PWM_DUTY_MAX    50000

//变积分PID
//motor_param_t motor_r = MOTOR_CREATE(12, 18, 1, 15, 2500, 250, 10,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);

//常规增量PID
motor_param_t motor_l = MOTOR_CREATE(12, 1000, 25, 10, 5000, 500, 600, MOTOR_PWM_DUTY_MAX ,MOTOR_PWM_DUTY_MAX ,MOTOR_PWM_DUTY_MAX);
motor_param_t motor_r = MOTOR_CREATE(12, 1000, 25, 10,  5000, 500, 600, MOTOR_PWM_DUTY_MAX ,MOTOR_PWM_DUTY_MAX ,MOTOR_PWM_DUTY_MAX);

float NORMAL_SPEED = 17;  //16.4
float target_speed;

//三叉识别速度   
float YROAD_FOUND_SPEED = 10, YROAD_NEAR_SPEED = 8;
//圆环速度 + NORMAL_SPEED
float CIRCLE_MAX_SPEED = 0 , CIRCLE_MIN_SPEED = - 1.5;
//速度限+  NORMAL_SPEED
float NORMAL_MAX_SPEED = 3, NORMAL_MIN_SPEED = -2;


void motor_init(void)
{
    pwm_init(MOTOR1_PWM1, 17000, 0);
    pwm_init(MOTOR1_PWM2, 17000, 0);
    pwm_init(MOTOR2_PWM1, 17000, 0);
    pwm_init(MOTOR2_PWM2, 17000, 0);
}


void wireless_show(void)
{
    static uint8_t data[30];
    data[0] = 0xAA;
    data[1] = 0xFF;
    data[2] = 0xF1;
    data[3] = sizeof(data)-6;
    
    int32_t l_encoder = (int32_t)(motor_l.encoder_speed);
    int32_t r_encoder = (int32_t)(motor_r.encoder_speed);
    int32_t l_target = (int32_t)(motor_l.target_speed);
    int32_t r_target = (int32_t)(motor_r.target_speed);
    int32_t motor_m = (int32_t)(motor_r.motor_mode);
    int32_t target = target_speed;
    
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
    
    data[20]= BYTE3(motor_m);
    data[21]= BYTE2(motor_m);
    data[22]= BYTE1(motor_m);
    data[23]= BYTE0(motor_m);
    
    data[24]= BYTE3(target);
    data[25]= BYTE2(target);
    data[26]= BYTE1(target);
    data[27]= BYTE0(target);
    
    uint8_t sumcheck = 0; 
    uint8_t addcheck = 0; 
    for(uint8_t i=0; i < data[3]+4; i++) 
    { 
      sumcheck += data[i]; //从帧头开始，对每一字节进行求和，直到DATA区结
      addcheck += sumcheck;   //每一字节的求和操作，进行一次sumcheck的加 }
    } 
    data[28] = sumcheck;
    data[29] = addcheck;

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

pid_param_t diff_pid = PID_CREATE(0.14, 0, 0, 5, 5 ,5);         //差速pid

bool isStarting = 0;

void speed_control(void)
{
   //差速
   float diff = pid_solve(&diff_pid, angle);
   diff = MINMAX(diff, -NORMAL_SPEED / 6, NORMAL_SPEED / 6);
   
   //常规加速度
   motor_l.motor_mode = MODE_NORMAL;
   motor_r.motor_mode = MODE_NORMAL;
   
    
   //起步
   if(isStarting){
     if((motor_l.encoder_speed + motor_r.encoder_speed)/2>= NORMAL_SPEED -2)
     {
        isStarting  = 0;
     }
     motor_l.motor_mode = MODE_BEGIN;
     motor_r.motor_mode = MODE_BEGIN;
   }
   
   //apriltime快停
  if(pit_get_ms(TIMER_PIT) - openart.apriltime<1000 || apriltag_type == APRILTAG_FOUND){
     motor_l.motor_mode = MODE_STOP;
     motor_r.motor_mode = MODE_STOP;
     target_speed = 0;
     diff = 0;
  }
  else if(apriltag_type == APRILTAG_MAYBE){
      target_speed = 8;
  }
  
   else if(garage_type == GARAGE_IN_RIGHT || garage_type == GARAGE_IN_LEFT){
       target_speed = 10;
   }
  else if(enable_adc){
     target_speed = 8; 
  }
  //三叉near, 近乎停车
   else if(yroad_type == YROAD_NEAR){
     motor_l.motor_mode = MODE_NORMAL;
     motor_r.motor_mode = MODE_NORMAL;
     target_speed = YROAD_NEAR_SPEED;
   }
   //三叉found, 减速
   else if(yroad_type == YROAD_FOUND){
     motor_l.motor_mode = MODE_NORMAL;
     motor_r.motor_mode = MODE_NORMAL;
     target_speed = YROAD_FOUND_SPEED;
   }
   //圆环速度  左圆环max 16.2 -1.5
   
     //圆环开始
    else if(circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_RIGHT_BEGIN){
        target_speed = MINMAX(target_speed - 0.02,NORMAL_SPEED + CIRCLE_MIN_SPEED, NORMAL_SPEED + CIRCLE_MAX_SPEED);
    }
     //出环加速
    else if(circle_type == CIRCLE_LEFT_END || circle_type == CIRCLE_RIGHT_END){
        target_speed = MINMAX(target_speed + 0.02,NORMAL_SPEED + CIRCLE_MIN_SPEED,NORMAL_SPEED);
    }
     //圆环运行
//     else{
//        target_speed = MINMAX(target_speed - 0.01,NORMAL_SPEED + CIRCLE_MIN_SPEED,NORMAL_SPEED + CIRCLE_MAX_SPEED);
//     }
//   }
   //直道加速
   else if(rptsn_num > 70){
        float error = 0.2 - fabs((rptsn[70][0] - rptsn[0][0]) / (rptsn[70][1] - rptsn[0][1]));
        error *= 15;
       
        target_speed = MINMAX(NORMAL_SPEED + error, NORMAL_SPEED + NORMAL_MIN_SPEED, NORMAL_SPEED + NORMAL_MAX_SPEED);
   }
   //常规速度
//   else{
//     //if((motor_l.encoder_speed + motor_r.encoder_speed)/2<3) isStarting = 1;
//     target_speed = NORMAL_SPEED;
//   }
   
   // 急停
   
   if(garage_type == GARAGE_STOP || (garage_type != GARAGE_OUT_LEFT && garage_type != GARAGE_OUT_RIGHT && elec_data[0] + elec_data[1] + elec_data[2]+ elec_data[3] < 300)){
     motor_l.motor_mode = MODE_STOP;
     motor_r.motor_mode = MODE_STOP;
     target_speed = 0;
     diff = 0;
   }
   
//   aim_distance = MINMAX(0.55 + (target_speed - 11) * (0.7 - 0.55) / (17 - 11), 0.55,0.7);  
//   aim_distance = 0.65;
   motor_l.target_speed = target_speed - diff;
   motor_r.target_speed = target_speed + diff; 

}
        
void motor_control(void)
{    
    //square_signal();
    
    //wireless_show();
  
    speed_control();
    
    //常规
    if(motor_l.motor_mode == MODE_NORMAL){
        motor_l.duty += changable_pid_solve(&motor_l.pid ,(float)(motor_l.target_speed - motor_l.encoder_speed));	
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX , MOTOR_PWM_DUTY_MAX);
    }
    //停车
    else if(motor_l.motor_mode == MODE_STOP){
        motor_l.duty += bangbang_pid_solve(&motor_l.brake_pid ,(float)(motor_l.target_speed - motor_l.encoder_speed));	
//        motor_l.duty = pid_solve(&motor_l.brake_pid, motor_l.target_encoder - motor_l.total_encoder);
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }
    //起步
    else if(motor_l.motor_mode == MODE_BEGIN){
        motor_l.duty += bangbang_pid_solve(&motor_l.brake_pid ,(float)(motor_l.target_speed - motor_l.encoder_speed));	
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }
    
    
    if(motor_r.motor_mode == MODE_NORMAL){
        motor_r.duty += changable_pid_solve(&motor_r.pid ,(float)(motor_r.target_speed - motor_r.encoder_speed));	
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }else if(motor_r.motor_mode == MODE_STOP){ 
        motor_r.duty += bangbang_pid_solve(&motor_r.brake_pid ,(float)(motor_r.target_speed - motor_r.encoder_speed));	
//        motor_r.duty = pid_solve(&motor_r.brake_pid, motor_r.target_encoder - motor_r.total_encoder);
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }else if(motor_l.motor_mode == MODE_BEGIN){
        motor_r.duty += bangbang_pid_solve(&motor_r.brake_pid ,(float)(motor_r.target_speed - motor_r.encoder_speed));	
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }
    
    //大角度限幅
    if(fabs(angle)>10) 
    {
       motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX * 8/10, MOTOR_PWM_DUTY_MAX  * 8/10);
       motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX * 8/10, MOTOR_PWM_DUTY_MAX  * 8/10);
    }
    
    //PWM控制
    pwm_duty(MOTOR1_PWM1, (motor_l.duty>=0)? motor_l.duty : 0);
    pwm_duty(MOTOR1_PWM2, (motor_l.duty>=0)? 0 : (-motor_l.duty));
    
    pwm_duty(MOTOR2_PWM1, (motor_r.duty>=0)? motor_r.duty : 0);
    pwm_duty(MOTOR2_PWM2, (motor_r.duty>=0)? 0 : (-motor_r.duty));		
    
    
}

int64_t get_total_encoder(){
    return (int64_t)((motor_l.total_encoder + motor_r.total_encoder) / 2);
}
