#include "buzzer.h"
#define BUZZER_PIN			B11			// 定义主板上蜂鸣器对应引脚


rt_mailbox_t buzzer_mailbox;


void buzzer_entry(void *parameter)
{
    uint32 mb_data;
    while(1)
    {
        //接收邮箱数据，如果没有数据则持续等待并释放CPU控制权
        rt_mb_recv(buzzer_mailbox, &mb_data, RT_WAITING_FOREVER);

        gpio_set(BUZZER_PIN, 1);    //打开蜂鸣器
        rt_thread_mdelay(mb_data);  //延时
        gpio_set(BUZZER_PIN, 0);    //关闭蜂鸣器
    }
}





void buzzer_init(void)
{
    rt_thread_t tid;
    
    //初始化蜂鸣器所使用的GPIO
    gpio_init(BUZZER_PIN, GPO, 0, GPIO_PIN_CONFIG);			// 初始化为GPIO浮空输入 默认上拉高电平
    
    //创建邮箱
    buzzer_mailbox = rt_mb_create("buzzer", 5, RT_IPC_FLAG_FIFO);
    
    //创建蜂鸣器的线程
    tid = rt_thread_create("buzzer", buzzer_entry, RT_NULL, 1024, 20, 2);
    
    //启动线程
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}