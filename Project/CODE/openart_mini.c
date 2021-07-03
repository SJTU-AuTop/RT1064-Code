#include "openart_mini.h"
#include "yroad.h"
#include "buzzer.h"
#include "motor.h"
#include "smotor.h"
#include "main.h"

openart_param_t openart;



uint8               openart_rx_buffer;
lpuart_transfer_t   openart_receivexfer;
lpuart_handle_t     openart_g_lpuartHandle;


char *fa_labels[] = {"animal","fruit"}; 
char *obj_labels[] = {"dog","horse","cat","casttle","pig","apple","orange","banana", "durian", "grape"}; 
char *num_labels[] = {"0","1","2","3","4","5","6","7", "8", "9" }; 


uint8_t pre_mode = FA_MODE;
//0 -动物
//0 -偶数
void openart_uart1_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        openart.openart_buff[openart_rx_buffer - 48]++;
        openart_putbuff(& openart.cycle_array[0],openart_rx_buffer - 48, & openart.num_time[0],pit_get_ms(TIMER_PIT));
        openart.openart_result = openart_rx_buffer - 48;
        openart.number_time = pit_get_ms(TIMER_PIT);
    }
    
    handle->rxDataSize = openart_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = openart_receivexfer.data;          //还原缓冲区地址
}

void check_openart(void)
{
    static int art_cnt = 0;
    art_cnt++;
    if(openart.openart_mode != pre_mode || art_cnt%20 == 0){
       openart_send();
       pre_mode = openart.openart_mode;
    }
    
    int32_t buzz_num;
    if(get_total_encoder() - openart.aprilencoder<ENCODER_PER_METER * 0.5 || get_total_encoder() - openart.numencoder< ENCODER_PER_METER * 0.5)
    {
         openart.openart_mode = OFF_MODE; //OFF_MODE
         openart.openart_buff[0] = openart.openart_buff[1] = 0;
    }
    else if(yroad_type == YROAD_FOUND || yroad_type == YROAD_NEAR)
    {
        openart.openart_mode = NUM_MODE;
        /*
        if(openart.openart_buff[1]+openart.openart_buff[0]>0){           	
          
          openart.numencoder = get_total_encoder();
          if(openart.openart_buff[1]>=openart.openart_buff[0]){
            yroad_type = YROAD_RIGHT_RUN;
            buzz_num = 2;
          }
          else if(openart.openart_buff[0]>openart.openart_buff[1]){
            yroad_type = YROAD_LEFT_RUN;
            buzz_num = 1;
          }
          rt_mb_send(buzzer_mailbox, (rt_uint32_t)buzz_num);
       }
       */
        /*
        if((pit_get_ms(TIMER_PIT) - openart.num_time[0])<2500 
             && (pit_get_ms(TIMER_PIT) - openart.num_time[1])<2500
               && (pit_get_ms(TIMER_PIT) - openart.num_time[2])<2500)
        {
          
          if(openart.cycle_array[0] + openart.cycle_array[1] + openart.cycle_array[2]<2)      
          {
                openart.numencoder = get_total_encoder();
                yroad_type = YROAD_RIGHT_RUN;
                buzz_num = 2;
          }
          else{
                openart.numencoder = get_total_encoder();
                yroad_type = YROAD_LEFT_RUN;
                buzz_num = 1;
          }
          
          rt_mb_send(buzzer_mailbox, (rt_uint32_t)buzz_num);
        }
        */
       if(pit_get_ms(TIMER_PIT) - openart.number_time<1200)
       {
          if(openart.openart_result==0)      
          {
                openart.numencoder = get_total_encoder();
                yroad_type = YROAD_RIGHT_RUN;
                buzz_num = 2;
          }
          else{
                openart.numencoder = get_total_encoder();
                yroad_type = YROAD_LEFT_RUN;
                buzz_num = 1;
          }
          
          rt_mb_send(buzzer_mailbox, (rt_uint32_t)buzz_num);
         
       } 
       
        
    }
    else if(yroad_type != YROAD_FOUND && yroad_type != YROAD_NEAR)
    {
      openart.openart_mode = NUM_MODE;  //TAG_MODE
      /*
      if(openart.openart_buff[0] + openart.openart_buff[1] >0)
      {
          if(openart.openart_buff[0]>=openart.openart_buff[1]){ smotor2_control(2300);}
          else    { smotor2_control(-2300);}
          buzz_num = 3;
          rt_mb_send(buzzer_mailbox, (rt_uint32_t)buzz_num);
          openart.aprilencoder = get_total_encoder();
          openart.apriltime = pit_get_ms(TIMER_PIT);
      }
      else{
           smotor2_control(0);
      }
      */
    }
}

 

uint8_t array_num = 0;  
void openart_putbuff(int32_t *array1,int32_t input_dat1,int32_t *array2,int32_t input_dat2)
{
      *(array1+array_num) = input_dat1;
      *(array2+array_num) = input_dat2;
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
    openart.apriltime = -20000;
    openart.numencoder = -20000;
    openart.number_time = -3000;
    memset(openart.cycle_array, 2, sizeof(openart.cycle_array));
    memset(openart.num_time, -2000, sizeof(openart.num_time));
}