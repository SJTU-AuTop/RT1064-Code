#include "openart_mini.h"
#include "yroad.h"
#include "buzzer.h"
#include "apriltag.h"
#include "motor.h"
#include "smotor.h"
#include "main.h"
#include "laser.h"

openart_param_t openart = {
    .tag_type = TAG_NONE,
};



uint8               openart_rx_buffer;
lpuart_transfer_t   openart_receivexfer;
lpuart_handle_t     openart_g_lpuartHandle;



char *fa_labels[] = {"animal","fruit"}; 
char *obj_labels[] = {"dog","horse","cat","casttle","pig","apple","orange","banana", "durian", "grape"}; 
char *num_labels[] = {"0","1","2","3","4","5","6","7", "8", "9" }; 


extern bool isStarting;
uint8_t pre_mode = FA_MODE;

extern float laser_angle;
extern  pid_param_t laser_pid;

bool fruit_mode =0;
//0 -动物
//0 -偶数
//串口接受 ： 0XFF  识别模式  识别结果(0,1) 识别图像中心x,y(160,120)
void openart_uart1_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        static int   rx_num = 0;
        
        //将结果存入rx_array
        if(openart_rx_buffer == 0XFF){
          rx_num = 0;
          openart.rx_array[rx_num] =  0XFF;
          rx_num ++;  
        }
        else if(rx_num < 5){
          openart.rx_array[rx_num] = openart_rx_buffer;    
          rx_num ++;
        } 
       
        if(rx_num==5)
        { 
            openart.openart_result = openart.rx_array[2];
            openart.receiver_time = rt_tick_get_millisecond();
            
            //蜂鸣器发声        
//            if(openart.openart_result==0) rt_mb_send(buzzer_mailbox, 2);  
//            else  rt_mb_send(buzzer_mailbox, 1); 
            
          if(openart.rx_array[1] == NUM_MODE){
            laser_angle = SMOTOR2_CENTER;
          }
          //收到动物水果数据
          if(openart.rx_array[1] == FA_MODE){
            
            //动物，记录时间
            if(openart.openart_result == 0){
              openart.fa_num[0]++;
              openart.tag_type = TAG_STOP;
            }
            //水果，记录坐标
            else if(openart.openart_result == 1){
              openart.fa_num[1]++;
              //laser_angle = MINMAX(laser_angle + pid_solve(&laser_pid,openart.rx_array[3] - 160/2),0,180);
              openart.fruit_delta = atan((openart.rx_array[3]*2-1.641845887701845e+02)/2.188872028772782e+02) * 180. / PI;
              if(openart.fa_num[1]%2 == 1 && openart.tag_type == TAG_STOP) laser_angle -= openart.fruit_delta;
              if(fabs(openart.fruit_delta) < 0.3 && openart.tag_type == TAG_STOP) {
                  laser_on();
                  openart.fruittime = rt_tick_get_millisecond();
                  openart.tag_type = TAG_SHOOTING;
              }
              if(openart.fruit_delta < 5 && openart.tag_type == TAG_SEARCH) openart.tag_type = TAG_STOP;
            }
            if(openart.fa_num[0]>openart.fa_num[1]) {openart.fa_type = ANIMAL;}
            else if(openart.fa_num[1]>openart.fa_num[0]) {openart.fa_type = FRUIT;}
          }
          else if(openart.rx_array[1] == TAG_MODE){
              smotor3_control(servo_duty(SMOTOR3_CENTER));
              openart.aprilencoder =   get_total_encoder();
              if(openart.openart_result==0) laser_angle = SMOTOR2_LEFT_CENTER;
              else laser_angle = SMOTOR2_RIGHT_CENTER;
              
              //切换水果模式
             openart.openart_mode = FA_MODE; 
             openart.tag_type = TAG_SEARCH;
              
             openart.animaltime = rt_tick_get_millisecond();
          }
          smotor2_control(servo_duty(laser_angle));
        }
       
    }
    
    handle->rxDataSize = openart_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = openart_receivexfer.data;          //还原缓冲区地址
}



void check_openart(void)
{
    
    if(apriltag_type == APRILTAG_FOUND &&  (openart.fa_type == NONE && rt_tick_get_millisecond() - apriltag_time > 4000)){
          openart.openart_mode = NUM_MODE;
          openart.tag_type = TAG_NONE;
          openart.fa_type = NONE;
          laser_off();
          laser_angle = SMOTOR2_CENTER;
          smotor2_control(servo_duty(laser_angle));
          smotor3_control(servo_duty(SMOTOR3_CENTER));
          apriltag_type = APRILTAG_LEAVE;
    }
    
    //识别到Apriltag，等待水果动物识别
    if(openart.openart_mode == FA_MODE)
   {  
      //退出条件: 水果打靶编码器  动物2.5 或者1m内什么都没识别到
        if((openart.fa_type == ANIMAL && rt_tick_get_millisecond() - openart.animaltime> 3200) ||
          (openart.fa_type == FRUIT && openart.tag_type == TAG_SHOOTING && rt_tick_get_millisecond() - openart.fruittime > 1200)){
          openart.openart_mode = NUM_MODE;
          openart.tag_type = TAG_NONE;
          openart.fa_type = NONE;
          laser_off();
          laser_angle = SMOTOR2_CENTER;
          smotor2_control(servo_duty(laser_angle));
          smotor3_control(servo_duty(SMOTOR3_CENTER));
          apriltag_type = APRILTAG_LEAVE;
      }else if(openart.fa_type == ANIMAL && rt_tick_get_millisecond() - openart.animaltime> 2000){
          laser_angle = SMOTOR2_CENTER;
          smotor2_control(servo_duty(laser_angle));
          smotor3_control(servo_duty(SMOTOR3_CENTER));
      }
      
        if(get_total_encoder() - openart.aprilencoder > ENCODER_PER_METER * 0.8){
            openart.tag_type = TAG_STOP;
        }      
    }
    //检测到黑斑点，减速等待结果
    else if(apriltag_type == APRILTAG_MAYBE || apriltag_type == APRILTAG_FOUND)
    {
      //Apriltag判断
       openart.openart_mode = TAG_MODE;
       //检测到黑斑1m内未识别,清标志
       if(get_total_encoder() - openart.aprilwaitencoder > ENCODER_PER_METER){
          apriltag_type = APRILTAG_LEAVE;
          smotor3_control(servo_duty(SMOTOR3_CENTER));
       }
       openart.fa_type = NONE;
       openart.fa_num[0] = openart.fa_num[1] = 0;
       smotor3_control(servo_duty(SMOTOR3_CENTER + 30));
       openart.animaltime = -30000;
    }
    //常规条件下，打开数字判断，快速三叉
    else if(yroad_type != YROAD_FOUND && yroad_type != YROAD_NEAR)
    {
       smotor3_control(servo_duty(SMOTOR3_CENTER));
       openart.openart_mode = NUM_MODE;  
    }
    
    static int art_cnt = 0;
    art_cnt++;
    if(openart.openart_mode != pre_mode || art_cnt%100 == 0){
       openart_send();
       pre_mode = openart.openart_mode;
    }
}

 

uint8_t array_num = 0;  
void openart_putbuff(int32_t *array,int32_t input_dat)
{
      *(array+array_num) = input_dat;
      array_num++;
      if (array_num > 2)	array_num = 0;		
}

void openart_send(void)
{
    static uint8_t openart_data[1];
    openart_data[0] = openart.openart_mode;
    uart_putbuff(USART_4, (uint8_t *)&openart_data, sizeof(openart_data));
}


void openart_mini(void)
{
    uart_init(USART_4, 115200, UART4_TX_C16, UART4_RX_C17);
    
    //配置串口接收的缓冲区及缓冲区长度
    openart_receivexfer.dataSize = 1;
    openart_receivexfer.data = &openart_rx_buffer;
    
    //设置中断函数及其参数
    uart_set_handle(USART_4, &openart_g_lpuartHandle, openart_uart1_callback, NULL, 0, openart_receivexfer.data, 1);
    
    NVIC_SetPriority(LPUART4_IRQn, 10); //14        //设置串口中断优先级 范围0-15 越小优先级越高
    uart_rx_irq(USART_4, 1);
    
    openart.aprilencoder = -20000;
    openart.animaltime = -30000;
    openart.aprilwaitencoder = -30000;
}