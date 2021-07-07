#include "cross.h"
#include "motor.h"
#include "main.h"

enum cross_type_e cross_type = CROSS_NONE;


int64_t cross_encoder;


bool far_Lpt0_found,far_Lpt1_found;
int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;

extern float mapx[240][376];
extern float mapy[240][376];



int far_ipts0[FAR_POINTS_MAX_LEN][2];
int far_ipts1[FAR_POINTS_MAX_LEN][2];
int far_ipts0_num, far_ipts1_num;

float far_rpts0[FAR_POINTS_MAX_LEN][2];
float far_rpts1[FAR_POINTS_MAX_LEN][2];
int far_rpts0_num, far_rpts1_num;

float far_rpts0b[FAR_POINTS_MAX_LEN][2];
float far_rpts1b[FAR_POINTS_MAX_LEN][2];
int far_rpts0b_num, far_rpts1b_num;

float far_rpts0s[FAR_POINTS_MAX_LEN][2];
float far_rpts1s[FAR_POINTS_MAX_LEN][2];
int far_rpts0s_num, far_rpts1s_num;

float far_rpts0a[FAR_POINTS_MAX_LEN];
float far_rpts1a[FAR_POINTS_MAX_LEN];
int far_rpts0a_num, far_rpts1a_num;

float far_rpts0an[FAR_POINTS_MAX_LEN];
float far_rpts1an[FAR_POINTS_MAX_LEN];
int far_rpts0an_num, far_rpts1an_num;

int not_have_line = 0;

int far_x1 = 70, far_x2 = 306, far_y1, far_y2;
void check_cross(){
    bool Xfound = Lpt0_found && Lpt1_found;
    if(cross_type == CROSS_NONE && Xfound)  cross_type = CROSS_BEGIN;
}

void run_cross() {
    bool Xfound = Lpt0_found && Lpt1_found;
    int64_t current_encoder = get_total_encoder();
    float Lpt0y = rpts0s[Lpt0_rpts0s_id][1];
    float Lpt1y = rpts1s[Lpt1_rpts1s_id][1];
    //检测到十字，先按照近线走
    if(cross_type == CROSS_BEGIN)
    {
      
      if(Lpt0_found) {rpts0s_num = Lpt0_rpts0s_id;}
      if(Lpt1_found) {rpts1s_num = Lpt1_rpts1s_id;}
         
        aim_distance = 0.68;
        //近角点过少，进入远线控制
        if((Xfound && (Lpt0_rpts0s_id < 30 && Lpt1_rpts1s_id < 30)) || (rpts1_num <30 || rpts0_num<30))
        {
            cross_type = CROSS_IN;
            cross_encoder = current_encoder;
        }
    }
    //远线控制进十字,begin_y渐变靠近防丢线
    else if(cross_type == CROSS_IN)
    {
        cross_farline();
        aim_distance = 0.4;
        
        if(rpts1_num==0 && rpts0_num==0) {not_have_line++;}
        if(not_have_line>2 && rpts1_num>100 && rpts0_num>100){
           cross_type = CROSS_NONE;
           not_have_line = 0;
        }
        if(far_Lpt1_found) {track_type = TRACK_RIGHT;}
        else if(far_Lpt0_found) {track_type = TRACK_LEFT;}
        else if(not_have_line>0 && rpts1_num == 0) {track_type = TRACK_RIGHT;}
        else if(not_have_line>0 && rpts0_num == 0) {track_type = TRACK_LEFT;}      

    }
}

void draw_cross(){

    if(cross_type == CROSS_IN && line_show_sample)
    {
        for(int i=0; i<far_rpts0s_num; i++){
            AT_IMAGE(&img_line, clip(far_rpts0s[i][0], 0, img_line.width-1), clip(far_rpts0s[i][1], 0, img_line.height-1)) = 100;
        }
        for(int i=0; i<far_rpts1s_num; i++){
            AT_IMAGE(&img_line, clip(far_rpts1s[i][0], 0, img_line.width-1), clip(far_rpts1s[i][1], 0, img_line.height-1)) = 100;
        }

        if(far_Lpt0_found){
            draw_o(&img_line, far_rpts0s[far_Lpt0_rpts0s_id][0], far_rpts0s[far_Lpt0_rpts0s_id][1], 3);
        }
        if(far_Lpt1_found){
            draw_o(&img_line, far_rpts1s[far_Lpt1_rpts1s_id][0], far_rpts1s[far_Lpt1_rpts1s_id][1], 3);
        }
        
        draw_o(&img_line, clip(mapx[(int)begin_y][far_x1],0,img_line.width-1), clip(mapy[(int)begin_y][far_x1],0,img_line.height-1),3);
        draw_o(&img_line, clip(mapx[(int)begin_y][far_x2],0,img_line.width-1) , clip(mapy[(int)begin_y][far_x1],0,img_line.height-1),3);
        draw_o(&img_line, clip(mapx[far_y1][far_x1],0,img_line.width-1), clip(mapy[far_y1][far_x1],0,img_line.height-1),3);
        draw_o(&img_line, clip(mapx[far_y2][far_x2],0,img_line.width-1) , clip(mapy[far_y2][far_x2],0,img_line.height-1),3);
        
   }
}


void cross_farline()
{ 
    int cross_width = 4;
//    far_x1 = cross_width, far_x2 = img_raw.width -cross_width;
    far_y1 = 0, far_y2 = 0;
    
    
    int x1=img_raw.width/2-begin_x, y1=begin_y;
    bool white_found = false;
    far_ipts0_num=sizeof(far_ipts0)/sizeof(far_ipts0[0]);

    //在begin_y向两边找黑线
//    for(;x1>cross_width*2; x1--) 
//    {
//      if(AT_IMAGE(&img_raw, x1-1, y1) < low_thres) {
//        far_x1 = x1 - cross_width;
//        break;
//      }   
//    }
    //全白  far_x1 = 0,从边界找
     for(;y1>0;y1--)
    {
      //先黑后白，先找white
      if(AT_IMAGE(&img_raw, far_x1, y1) >= low_thres)  { white_found = true;}
      if(AT_IMAGE(&img_raw, far_x1, y1) < low_thres &&  (white_found || far_x1 ==cross_width)) 
      { 
        far_y1 = y1; 
        break;
      }
    }
    
    //从找到角点位置开始寻找
    if(AT_IMAGE(&img_raw, far_x1, far_y1+1) >= low_thres) findline_lefthand_with_thres(&img_raw, low_thres, high_thres, delta, far_x1, far_y1+1, far_ipts0, &far_ipts0_num);
    else far_ipts0_num = 0;

    int x2=img_raw.width/2 + begin_x , y2=begin_y;
    white_found = false;
    far_ipts1_num=sizeof(far_ipts1)/sizeof(far_ipts1[0]);

    //在begin_y向两边找黑线
//    for(;x2<img_raw.width-cross_width*2; x2++) 
//    {
//      if(AT_IMAGE(&img_raw, x2+1, y2) < low_thres) {
//        far_x2 = x2 + cross_width;
//        break;
//      }   
//    }
    //全白  far_x2 = 0,从边界找
     for(;y2>0;y2--)
    {
      //先黑后白，先找white
      if(AT_IMAGE(&img_raw, far_x2, y2) >= low_thres) { white_found = true;}
      if(AT_IMAGE(&img_raw, far_x2, y2) < low_thres && (white_found || far_x2 == img_raw.width -cross_width)) 
      { 
        far_y2 = y2; 
        break;
      }
    }
         
    //从找到角点位置开始寻找
    if(AT_IMAGE(&img_raw, far_x2, far_y2+1) >= low_thres) findline_righthand_with_thres(&img_raw, low_thres, high_thres, delta, far_x2, far_y2+1, far_ipts1, &far_ipts1_num);
    else far_ipts1_num = 0;
    

       // 去畸变+透视变换
    for(int i=0; i<far_ipts0_num; i++) {
        far_rpts0[i][0] = mapx[far_ipts0[i][1]][far_ipts0[i][0]];
        far_rpts0[i][1] = mapy[far_ipts0[i][1]][far_ipts0[i][0]];
    }
    far_rpts0_num = far_ipts0_num;
    for(int i=0; i<far_ipts1_num; i++) {
        far_rpts1[i][0] = mapx[far_ipts1[i][1]][far_ipts1[i][0]];
        far_rpts1[i][1] = mapy[far_ipts1[i][1]][far_ipts1[i][0]];
    }
    far_rpts1_num = far_ipts1_num;
    
    
    // 边线滤波
    blur_points(far_rpts0, far_rpts0_num, far_rpts0b, (int)round(line_blur_kernel));
    far_rpts0b_num = far_rpts0_num;
    blur_points(far_rpts1, far_rpts1_num, far_rpts1b, (int)round(line_blur_kernel));
    far_rpts1b_num = far_rpts1_num;
    
    // 边线等距采样
    far_rpts0s_num = sizeof(far_rpts0s)/sizeof(far_rpts0s[0]);
    resample_points(far_rpts0b, far_rpts0b_num, far_rpts0s, &far_rpts0s_num, sample_dist * pixel_per_meter);
    far_rpts1s_num = sizeof(far_rpts1s)/sizeof(far_rpts1s[0]);
    resample_points(far_rpts1b, far_rpts1b_num, far_rpts1s, &far_rpts1s_num, sample_dist * pixel_per_meter);
    
    // 边线局部角度变化率
    local_angle_points(far_rpts0s, far_rpts0s_num, far_rpts0a, (int)round(angle_dist / sample_dist));
    far_rpts0a_num = far_rpts0s_num;
    local_angle_points(far_rpts1s, far_rpts1s_num, far_rpts1a, (int)round(angle_dist / sample_dist));
    far_rpts1a_num = far_rpts1s_num;
    
    // 角度变化率非极大抑制
    nms_angle(far_rpts0a, far_rpts0a_num, far_rpts0an, (int)round(angle_dist / sample_dist) * 2 + 1);
    far_rpts0an_num = far_rpts0a_num;
    nms_angle(far_rpts1a, far_rpts1a_num, far_rpts1an, (int)round(angle_dist / sample_dist) * 2 + 1);
    far_rpts1an_num = far_rpts1a_num;
    
    far_Lpt0_found = far_Lpt1_found = false;
    
    for(int i=0; i<MIN(far_rpts0s_num, 80); i++){
        if(far_rpts0an[i] == 0) continue;
        int im1 = clip(i-(int)round(angle_dist / sample_dist), 0, far_rpts0s_num-1);
        int ip1 = clip(i+(int)round(angle_dist / sample_dist), 0, far_rpts0s_num-1);
        float conf = fabs(far_rpts0a[i]) - (fabs(far_rpts0a[im1]) + fabs(far_rpts0a[ip1])) / 2;
        if(70. / 180. * PI < conf && conf < 110. / 180. * PI  && i < 100){
            far_Lpt0_rpts0s_id = i;
            far_Lpt0_found = true;
            break;
        }
    }
    for(int i=0; i<MIN(far_rpts1s_num, 80); i++){
        if(far_rpts1an[i] == 0) continue;
        int im1 = clip(i-(int)round(angle_dist / sample_dist), 0, far_rpts1s_num-1);
        int ip1 = clip(i+(int)round(angle_dist / sample_dist), 0, far_rpts1s_num-1);
        float conf = fabs(far_rpts1a[i]) - (fabs(far_rpts1a[im1]) + fabs(far_rpts1a[ip1])) / 2;

        if(70. / 180. * PI < conf && conf < 110. / 180. * PI && i < 100){
            far_Lpt1_rpts1s_id = i;
            far_Lpt1_found = true;
            break;
        }
    }

}
