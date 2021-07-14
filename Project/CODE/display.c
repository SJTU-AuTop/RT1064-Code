#include "headfile.h"
#include "encoder.h"
#include "display.h"
#include "imgproc.h"
#include "attitude_solution.h"


extern int clip(int x, int low, int up);

void display_entry(void *parameter)
{
    ips200_clear(BLACK);
    while(1)
    {
        ips200_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, MT9V03X_CSI_W/2, MT9V03X_CSI_H/2);//缩小显示区域便于同步显示一些参数
    }
}






void display_init(void)
{
    rt_thread_t tid;
    
    //初始化屏幕
    ips200_init();
    
    //创建显示线程 优先级设置为31
    tid = rt_thread_create("display", display_entry, RT_NULL, 1024, 31, 30);
    
    //启动显示线程
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}