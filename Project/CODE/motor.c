#include "motor.h"
#include "cross.h"
#include "circle.h"
#include "yroad.h"
#include "garage.h"
#include "apriltag.h"
#include "elec.h"
#include "smotor.h"
#include "openart_mini.h"
#include "main.h"
#include "elec.h"
// left
#define MOTOR1_PWM1     PWM2_MODULE3_CHB_D3
#define MOTOR1_PWM2     PWM1_MODULE3_CHB_D1
// right
#define MOTOR2_PWM1     PWM2_MODULE3_CHA_D2
#define MOTOR2_PWM2     PWM1_MODULE3_CHA_D0


//#define MINMAX(x, l, u) MIN(MAX(x, l), u)
#define MOTOR_PWM_DUTY_MAX    50000

//变积分PID
//motor_param_t motor_r = MOTOR_CREATE(12, 18, 1, 15, 2500, 250, 10,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3 ,MOTOR_PWM_DUTY_MAX/3);

//常规增量PID
motor_param_t motor_l = MOTOR_CREATE(12, 1000, 25, 100, 5000, 500, 600, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
motor_param_t motor_r = MOTOR_CREATE(12, 1000, 25, 100, 5000, 500, 600, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);


// Matlab位置PID
// 0.5s
pid_param_t motor_pid_l = PID_CREATE(7021, 10000 / 1e3, 0, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
pid_param_t motor_pid_r = PID_CREATE(7021, 10000 / 1e3, 0, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
// 0.4s
//pid_param_t motor_pid_l = PID_CREATE(8830, 14117/1e3, 0, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
//pid_param_t motor_pid_r = PID_CREATE(8830, 14117/1e3, 0, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
// 0.3s
//pid_param_t motor_pid_l = PID_CREATE(11864, 22367/1e3, 0, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
//pid_param_t motor_pid_r = PID_CREATE(11864, 22367/1e3, 0, 1, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);

// 从赛道弯曲情况，计算目标速度
pid_param_t target_speed_pid = PID_CREATE(5., 0, 30., 0.6, 5, 5, 5);

// 位置环PID
pid_param_t posloop_pid = PID_CREATE(200., 0, 0., 0.7, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);

// 基准速度
float NORMAL_SPEED = 17.;  //16.4
// 当前目标速度
float target_speed;

//三叉识别速度    
float YROAD_FOUND_SPEED = 3, YROAD_NEAR_SPEED = 3;
//圆环速度 + NORMAL_SPEED
float CIRCLE_MAX_SPEED = 0, CIRCLE_MIN_SPEED = -6;
//速度限+  NORMAL_SPEED
float NORMAL_MAX_SPEED = 0, NORMAL_MIN_SPEED = -8;


void motor_init(void) {
    pwm_init(MOTOR1_PWM1, 17000, 0);
    pwm_init(MOTOR1_PWM2, 17000, 0);
    pwm_init(MOTOR2_PWM1, 17000, 0);
    pwm_init(MOTOR2_PWM2, 17000, 0);
}

// 三点圆弧半径
float radius_3pts(float pt0[2], float pt1[2], float pt2[2]) {
    float a, b, c, d, e, f, r, x, y;
    a = 2 * (pt1[0] - pt0[0]);
    b = 2 * (pt1[1] - pt0[1]);
    c = pt1[0] * pt1[0] + pt1[1] * pt1[1] - pt0[0] * pt0[0] - pt0[1] * pt0[1];
    d = 2 * (pt2[0] - pt1[0]);
    e = 2 * (pt2[1] - pt1[1]);
    f = pt2[0] * pt2[0] + pt2[1] * pt2[1] - pt1[0] * pt1[0] - pt1[1] * pt1[1];
    x = (b * f - e * c) / (b * d - e * a);
    y = (d * c - a * f) / (b * d - e * a);
    r = sqrt((x - pt0[0]) * (x - pt0[0]) + (y - pt0[1]) * (y - pt0[1]));
    return r;
}

// 方波生成，用于调试
uint32_t clk;

void square_signal(void) {
    clk += 1;
    if (clk > 10000) { clk = 0; }
    if (clk < 2000) {
        motor_l.target_speed = 20;
        motor_r.target_speed = 20;
    } else if (clk < 4000) {
        motor_l.target_speed = 0;
        motor_r.target_speed = 0;
    } else if (clk < 6000) {
        motor_l.target_speed = 15;
        motor_r.target_speed = 15;
    } else if (clk < 8000) {
        motor_l.target_speed = 28;
        motor_r.target_speed = 28;
    } else if (clk < 10000) {
        motor_l.target_speed = 0;
        motor_r.target_speed = 0;
    }
}

// 起步特殊PID(已弃用)
bool isStarting = 0;

void speed_control(void) {
    //差速
    float diff = 15.8 * tan(angle / 180 * PI * 2.4) / 40 / 2;
    //diff = MINMAX(diff, -NORMAL_SPEED / 4, NORMAL_SPEED / 4);

    // 默认常规控制模式
    motor_l.motor_mode = MODE_NORMAL;
    motor_r.motor_mode = MODE_NORMAL;

    //起步特殊模式(已弃用)
    /*
    if(isStarting){
      if((motor_l.encoder_speed + motor_r.encoder_speed)/2>= NORMAL_SPEED -5)
      {
         isStarting  = 0;
      }
      motor_l.motor_mode = MODE_NORMAL;
      motor_r.motor_mode = MODE_NORMAL;
    }
    */
    extern float laser_angle;
    //动物停车 三秒
    if (rt_tick_get_millisecond() - openart.animaltime < 2500 && openart.fa_type == ANIMAL) {
        target_speed = 0;
        diff = 0;
    } else if (openart.fruit_delta < 0 && (laser_angle < 5 || laser_angle > 175)) { // 激光转不动了，后退
        target_speed = -1;
    } else if (openart.tag_type == TAG_SEARCH) {                                    // 寻找靶牌，缓慢前进
        target_speed = 1;
    } else if (openart.tag_type == TAG_STOP || openart.tag_type == TAG_SHOOTING) {  // 开始打靶，停车
        target_speed = 0;
    }
        // 黑斑apriltime停车
    else if (apriltag_type == APRILTAG_FOUND) {
        target_speed = 0.5; // 缓慢前进避免完全停车后，OpenArt却没识别到apriltag的情况
        diff = 0;
        // 位置环停车(弃用)
        //motor_l.motor_mode = MODE_POSLOOP;
        //motor_r.motor_mode = MODE_POSLOOP;
    } else if (apriltag_type == APRILTAG_MAYBE) {
        // 远处黑斑，减速
        target_speed = 1;
        motor_l.motor_mode = MODE_NORMAL;
        motor_r.motor_mode = MODE_NORMAL;
    } else if (garage_type == GARAGE_OUT_LEFT || garage_type == GARAGE_OUT_RIGHT) {
        // 出库缓启动模式，避免一下冲的太猛，冲出赛道
        motor_l.motor_mode = MODE_SOFT;
        motor_r.motor_mode = MODE_SOFT;
        target_speed = 14;
    } else if (garage_type == GARAGE_IN_RIGHT || garage_type == GARAGE_IN_LEFT) {
        // 入库中减速
        target_speed = 10;
    } else if (enable_adc) {
        // 坡道减速，避免飞坡翻车
        target_speed = 9;
        motor_l.motor_mode = MODE_BANGBANG;
        motor_r.motor_mode = MODE_BANGBANG;
    } else if (yroad_type == YROAD_NEAR) {
        //三叉near, 近乎停车
        target_speed = YROAD_NEAR_SPEED;
    } else if (yroad_type == YROAD_FOUND) {
        //三叉found, 减速
        target_speed = YROAD_FOUND_SPEED;
    } else if (circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_RIGHT_BEGIN) {
        // 圆环速度  左圆环max 16.2 -1.5
        // 圆环开始，斜坡函数减速
        target_speed = MINMAX(target_speed - 0.02, NORMAL_SPEED + CIRCLE_MIN_SPEED, NORMAL_SPEED + CIRCLE_MAX_SPEED);
    }
//    else if (circle_type == CIRCLE_LEFT_END || circle_type == CIRCLE_RIGHT_END) {
//        // 出环加速
//        target_speed = MINMAX(target_speed + 0.01, NORMAL_SPEED + CIRCLE_MIN_SPEED, NORMAL_SPEED);
//    }
    else if (rptsn_num > 20) {
        // 直道/弯道速度
        int id = MIN(70, rptsn_num - 1);
        float error = fabs((rptsn[id][0] - rptsn[0][0]) / (rptsn[id][1] - rptsn[0][1]));

        // 减速加入kd, 突入大弯
//        if(error >= 0.5) target_speed_pid.kd = 20;
//        else target_speed_pid.kd = 0;

        float speed = -pid_solve(&target_speed_pid, error);
        target_speed = MINMAX(NORMAL_SPEED + speed, NORMAL_SPEED + NORMAL_MIN_SPEED, NORMAL_SPEED + NORMAL_MAX_SPEED);
    } else if (rptsn_num > 5) {
        //点太少,不对劲直接慢速
        target_speed = NORMAL_SPEED + NORMAL_MIN_SPEED;
    }
    // 急停(车库停车，或电感值太小即冲出赛道)
    if (garage_type == GARAGE_STOP || (garage_type != GARAGE_OUT_LEFT && garage_type != GARAGE_OUT_RIGHT && elec_data[0] + elec_data[1] < 60)) {
        motor_l.motor_mode = MODE_NORMAL;
        motor_r.motor_mode = MODE_NORMAL;
        target_speed = 0;
        diff = 0;
    }

    // 动态舵机Kp
    //servo_pid.kp = 1. + (motor_l.encoder_speed + motor_r.encoder_speed) / 40;

    // 附加差速
    motor_l.target_speed = target_speed - diff * target_speed;
    motor_r.target_speed = target_speed + diff * target_speed;
}

void motor_control(void) {
    //square_signal();

    //wireless_show();

    speed_control();


    if (motor_l.motor_mode == MODE_NORMAL) {
        // 常规模式
        float error = (motor_l.target_speed - motor_l.encoder_speed);
        motor_l.duty = pid_solve(&motor_pid_l, error);
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    } else if (motor_l.motor_mode == MODE_BANGBANG) {
        // 邦邦模式，即猛加猛减
        motor_pid_l.out_i = 0;  // 清除默认模式的积分量

        motor_l.duty += bangbang_pid_solve(&motor_l.brake_pid, (float) (motor_l.target_speed - motor_l.encoder_speed));
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    } else if (motor_l.motor_mode == MODE_SOFT) {
        // 缓启动模式
        motor_pid_l.out_i = 0;  // 清除默认模式的积分量

        motor_l.duty += changable_pid_solve(&motor_l.pid, (float) (motor_l.target_speed - motor_l.encoder_speed));
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    } else if (motor_l.motor_mode == MODE_POSLOOP) {
        //Apriltag停车位置环
        motor_pid_l.out_i = 0; // 清除默认模式的积分量

        motor_l.duty = pid_solve(&posloop_pid, (float) (motor_l.target_encoder - motor_l.total_encoder));
        motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }

    // 右电机，同左电机
    if (motor_r.motor_mode == MODE_NORMAL) {
        float error = (motor_r.target_speed - motor_r.encoder_speed);
        motor_r.duty = pid_solve(&motor_pid_r, error);
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    } else if (motor_r.motor_mode == MODE_BANGBANG) {
        motor_pid_r.out_i = 0;

        motor_r.duty += bangbang_pid_solve(&motor_r.brake_pid, (float) (motor_r.target_speed - motor_r.encoder_speed));
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    } else if (motor_r.motor_mode == MODE_SOFT) {
        motor_pid_r.out_i = 0;

        motor_r.duty += changable_pid_solve(&motor_r.pid, (float) (motor_r.target_speed - motor_r.encoder_speed));
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    } else if (motor_r.motor_mode == MODE_POSLOOP) {
        motor_pid_r.out_i = 0;

        motor_r.duty = pid_solve(&posloop_pid, (float) (motor_r.target_encoder - motor_r.total_encoder));
        motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX);
    }

    //大角度限幅
    if (fabs(angle) > 10) {
        //减速
        if (target_speed - (motor_r.encoder_speed + motor_l.encoder_speed) / 2 < 0) {
            motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX * 8 / 10);
            motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX, MOTOR_PWM_DUTY_MAX * 8 / 10);
        } else {
            motor_l.duty = MINMAX(motor_l.duty, -MOTOR_PWM_DUTY_MAX * 8 / 10, MOTOR_PWM_DUTY_MAX * 8 / 10);
            motor_r.duty = MINMAX(motor_r.duty, -MOTOR_PWM_DUTY_MAX * 8 / 10, MOTOR_PWM_DUTY_MAX * 8 / 10);
        }
    }


    //PWM控制
    pwm_duty(MOTOR1_PWM1, (motor_l.duty >= 0) ? motor_l.duty : 0);
    pwm_duty(MOTOR1_PWM2, (motor_l.duty >= 0) ? 0 : (-motor_l.duty));

    pwm_duty(MOTOR2_PWM1, (motor_r.duty >= 0) ? motor_r.duty : 0);
    pwm_duty(MOTOR2_PWM2, (motor_r.duty >= 0) ? 0 : (-motor_r.duty));
}

int64_t get_total_encoder() {
    return (int64_t) ((motor_l.total_encoder + motor_r.total_encoder) / 2);
}
