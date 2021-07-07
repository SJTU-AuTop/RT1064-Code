#include "imgproc.h"
#include "common.h"

#define AT AT_IMAGE

extern int clip(int x, int low, int up);


extern float begin_x, begin_y;

AT_ITCM_SECTION_INIT(void clone_image(image_t* img0, image_t* img1)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(img0 != img1 && img0->data != img1->data);
    
    if(img0->width == img0->step && img1->width == img1->step){
        memcpy(img1->data, img0->data, img0->width*img0->height);
    }else{
        for(int y=0; y<img0->height; y++){
            memcpy(&AT(img1, 0, y), &AT(img0, 0, y), img0->width);
        }
    }
}

AT_ITCM_SECTION_INIT(void clear_image(image_t* img)){
    assert(img && img->data);
    if(img->width == img->step){
        memset(img->data, 0, img->width*img->height);
    }else{
        for(int y=0; y<img->height; y++){
            memset(&AT(img, 0, y), 0, img->width);
        }
    }
}

AT_ITCM_SECTION_INIT(void threshold(image_t* img0, image_t* img1, uint8_t thres, uint8_t low_value, uint8_t high_value)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    
    // 先遍历y后遍历x比较cache-friendly
    for(int y=0; y<img0->height; y++){
        for(int x=0; x<img0->width; x++){
            AT(img1, x, y) = AT(img0, x, y) < thres ? low_value : high_value;
        }
    }
    
    for(int i=0; i<img0->width/2 - begin_x; i++){
           AT(img1,(int)i ,(int)begin_y ) = 0;
    }
    for(int i=img0->width/2 + begin_x; i<img0->width; i++){
           AT(img1, (int)i ,(int)begin_y) = 0;
    }
}

AT_ITCM_SECTION_INIT(void image_and(image_t* img0, image_t* img1, image_t *img2)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img2 && img2->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(img0->width == img2->width && img0->height == img2->height);
    
    // 先遍历y后遍历x比较cache-friendly
    for(int y=0; y<img0->height; y++){
        for(int x=0; x<img0->width; x++){
            AT(img2, x, y) = (AT(img0, x, y) == 0 || AT(img1, x, y) == 0) ? 0 : 255;
        }
    }
}

AT_ITCM_SECTION_INIT(void image_or(image_t* img0, image_t* img1, image_t *img2)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img2 && img2->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(img0->width == img2->width && img0->height == img2->height);
    
    // 先遍历y后遍历x比较cache-friendly
    for(int y=0; y<img0->height; y++){
        for(int x=0; x<img0->width; x++){
            AT(img2, x, y) = (AT(img0, x, y) == 0 && AT(img1, x, y) == 0) ? 0 : 255;
        }
    }
}


AT_ITCM_SECTION_INIT(void minpool2(image_t *img0, image_t* img1)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img0->width/2 == img1->width && img0->height/2 == img1->height);
    assert(img0 != img1 && img0->data != img1->data);
    
    uint8_t min_value;
    // 先遍历y后遍历x比较cache-friendly
    for(int y=1; y<img0->height; y+=2){
        for(int x=1; x<img0->width; x+=2){
            min_value = 255;
            if(AT(img0, x, y) < min_value) min_value = AT(img0, x, y);
            if(AT(img0, x-1, y) < min_value) min_value = AT(img0, x-1, y);
            if(AT(img0, x, y-1) < min_value) min_value = AT(img0, x, y-1);
            if(AT(img0, x-1, y-1) < min_value) min_value = AT(img0, x-1, y-1);
            AT(img1, x/2, y/2) = min_value;
        }
    }
}

AT_ITCM_SECTION_INIT(void blur(image_t* img0, image_t* img1, uint32_t kernel)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(img0 != img1 && img0->data != img1->data);
    
    // 先遍历y后遍历x比较cache-friendly
    for(int y=1; y<img0->height-1; y++){
        for(int x=1; x<img0->width-1; x++){
            AT(img1, x, y) = (1*AT(img0, x-1, y-1) + 2*AT(img0, x, y-1) + 1*AT(img0, x+1, y-1) + 
                              2*AT(img0, x-1,   y) + 4*AT(img0, x,   y) + 2*AT(img0, x+1,   y) + 
                              1*AT(img0, x-1, y+1) + 2*AT(img0, x, y+1) + 1*AT(img0, x+1, y+1)) / 16;
        }
    }
}

AT_ITCM_SECTION_INIT(void sobel3(image_t* img0, image_t* img1)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(img0 != img1 && img0->data != img1->data);
    
    int gx, gy;
    // 先遍历y后遍历x比较cache-friendly    
    for(int y=1; y<img0->height-1; y++){
        for(int x=1; x<img0->width-1; x++){
            gx = (-1*AT(img0, x-1, y-1) + 1*AT(img0, x+1, y-1) + 
                  -2*AT(img0, x-1,   y) + 2*AT(img0, x+1,   y) + 
                  -1*AT(img0, x-1, y+1) + 1*AT(img0, x+1, y+1)) / 4;
            gy = ( 1*AT(img0, x-1, y-1) + 2*AT(img0, x, y-1) + 1*AT(img0, x+1, y-1) + 
                  -1*AT(img0, x-1, y+1) - 2*AT(img0, x, y+1) - 1*AT(img0, x+1, y+1)) / 4;
            AT(img1, x, y) = (abs(gx) + abs(gy)) / 2;
        }
    }
}

AT_ITCM_SECTION_INIT(void erode3(image_t* img0, image_t* img1)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(img0 != img1 && img0->data != img1->data);
    
    int min_value;
    // 先遍历y后遍历x比较cache-friendly    
    for(int y=1; y<img0->height-1; y++){
        for(int x=1; x<img0->width-1; x++){
            min_value = 255;
            for(int dy=-1; dy<=1; dy++){
                for(int dx=-1; dx<=1; dx++){
                    if(AT(img0, x+dx, y+dy) < min_value) min_value = AT(img0, x+dx, y+dy);
                }
            }
            AT(img1, x, y) = min_value;
        }
    }
}

AT_ITCM_SECTION_INIT(void dilate3(image_t* img0, image_t* img1)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(img0 != img1 && img0->data != img1->data);
    
    int max_value;
    // 先遍历y后遍历x比较cache-friendly    
    for(int y=1; y<img0->height-1; y++){
        for(int x=1; x<img0->width-1; x++){
            max_value = 0;
            for(int dy=-1; dy<=1; dy++){
                for(int dx=-1; dx<=1; dx++){
                    if(AT(img0, x+dx, y+dy) > max_value) max_value = AT(img0, x+dx, y+dy);
                }
            }
            AT(img1, x, y) = max_value;
        }
    }
}

AT_ITCM_SECTION_INIT(void remap(image_t* img0, image_t* img1, fimage_t* mapx, fimage_t* mapy)){
    assert(img0 && img0->data);
    assert(img1 && img1->data);
    assert(mapx && mapx->data);
    assert(mapy && mapy->data);
    assert(img0 != img1 && img0->data != img1->data);
    assert(img0->width == img1->width && img0->height == img1->height);
    assert(mapx->width == mapy->width && mapx->height == mapy->height);
    assert(img0->width == mapx->width && img0->height == mapx->height);
    
    // 先遍历y后遍历x比较cache-friendly    
    for(int y=1; y<img0->height-1; y++){
        for(int x=1; x<img0->width-1; x++){
            AT(img1, x, y) = AT(img0, (int)(AT(mapx, x, y)+0.5), (int)(AT(mapy, x, y)+0.5));
        }
    }
}

/* 前进方向定义：
 *   0
 * 3   1
 *   2
 */
AT_DTCM_SECTION_ALIGN_INIT(const int dir_front[4][2], 8) = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
AT_DTCM_SECTION_ALIGN_INIT(const int dir_frontleft[4][2], 8) = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
AT_DTCM_SECTION_ALIGN_INIT(const int dir_frontright[4][2], 8) = {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};


AT_ITCM_SECTION_INIT(void findline_lefthand_with_thres(image_t* img, uint8_t low_thres, uint8_t high_thres, uint8_t delta, int x, int y, int pts[][2], int *num)){
    assert(img && img->data);
    assert(num && *num >= 0);
    
    int step=0, dir=0, turn=0;
    while(step<*num && 0<x && x<img->width-1 && 0<y && y<img->height-1 && turn<4){
        int current_value = AT(img, x, y);
        int front_value = AT(img, x+dir_front[dir][0], y+dir_front[dir][1]);
        int frontleft_value = AT(img, x+dir_frontleft[dir][0], y+dir_frontleft[dir][1]);
        if(front_value < low_thres || ((current_value - front_value) > delta && front_value < high_thres)){
            dir = (dir+1)%4;
            turn++;
        }else if(frontleft_value < low_thres || ((current_value - frontleft_value) > delta && frontleft_value < high_thres)){
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn=0;
        }else{
            x += dir_frontleft[dir][0];
            y += dir_frontleft[dir][1];
            dir = (dir+3)%4;
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn=0;
        }
    }
    *num = step;
}

AT_ITCM_SECTION_INIT(void findline_righthand_with_thres(image_t* img, uint8_t low_thres, uint8_t high_thres, uint8_t delta, int x, int y, int pts[][2], int *num)){
    assert(img && img->data);
    assert(num && *num >= 0);
    
    int step=0, dir=0, turn=0;
    while(step<*num && 0<x && x<img->width-1 && 0<y && y<img->height-1 && turn<4){
        int current_value = AT(img, x, y);
        int front_value = AT(img, x+dir_front[dir][0], y+dir_front[dir][1]);
        int frontright_value = AT(img, x+dir_frontright[dir][0], y+dir_frontright[dir][1]);
        if(front_value < low_thres || ((current_value - front_value) > delta && front_value < high_thres)){
            dir = (dir+3)%4;
            turn++;
        }else if(frontright_value < low_thres || ((current_value - frontright_value) > delta && frontright_value < high_thres)){
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn=0;
        }else{
            x += dir_frontright[dir][0];
            y += dir_frontright[dir][1];
            dir = (dir+1)%4;
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn=0;
        }
    }
    *num = step;
}


AT_ITCM_SECTION_INIT(void approx_lines(int pts[][2], int pts_num, float epsilon, int lines[][2], int* lines_num)){
    assert(pts);
    assert(epsilon > 0);
    
    int dx = pts[pts_num-1][0] - pts[0][0];
    int dy = pts[pts_num-1][1] - pts[0][1];
    float nx = -dy / sqrtf(dx*dx+dy*dy);
    float ny = dx / sqrtf(dx*dx+dy*dy);
    float max_dist = 0, dist;
    int idx = -1;
    for(int i=1; i<pts_num-1; i++){
        dist = fabs((pts[i][0]-pts[0][0])*nx + (pts[i][1]-pts[0][1])*ny);
        if(dist > max_dist){
            max_dist = dist;
            idx = i;
        }
    }
    if(max_dist >= epsilon){
        int num1 = *lines_num;
        approx_lines(pts, idx+1, epsilon, lines, &num1);
        int num2 = *lines_num - num1 - 1;
        approx_lines(pts+idx, pts_num-idx, epsilon, lines+num1-1, &num2);
        *lines_num = num1 + num2 - 1;
    }else{
        lines[0][0] = pts[0][0];
        lines[0][1] = pts[0][1];
        lines[1][0] = pts[pts_num-1][0];
        lines[1][1] = pts[pts_num-1][1];
        *lines_num = 2;
    }
}

AT_ITCM_SECTION_INIT(void approx_lines_f(float pts[][2], int pts_num, float epsilon, float lines[][2], int* lines_num)){
    assert(pts);
    assert(epsilon > 0);
    
    int dx = pts[pts_num-1][0] - pts[0][0];
    int dy = pts[pts_num-1][1] - pts[0][1];
    float nx = -dy / sqrtf(dx*dx+dy*dy);
    float ny = dx / sqrtf(dx*dx+dy*dy);
    float max_dist = 0, dist;
    int idx = -1;
    for(int i=1; i<pts_num-1; i++){
        dist = fabs((pts[i][0]-pts[0][0])*nx + (pts[i][1]-pts[0][1])*ny);
        if(dist > max_dist){
            max_dist = dist;
            idx = i;
        }
    }
    if(max_dist >= epsilon && *lines_num > 2){
        int num1 = *lines_num;
        approx_lines_f(pts, idx+1, epsilon, lines, &num1);
        int num2 = *lines_num - num1 - 1;
        approx_lines_f(pts+idx, pts_num-idx, epsilon, lines+num1-1, &num2);
        *lines_num = num1 + num2 - 1;
    }else{
        lines[0][0] = pts[0][0];
        lines[0][1] = pts[0][1];
        lines[1][0] = pts[pts_num-1][0];
        lines[1][1] = pts[pts_num-1][1];
        *lines_num = 2;
    }
}

AT_ITCM_SECTION_INIT(void draw_line(image_t* img, int pt0[2], int pt1[2], uint8_t value)){
    int dx = pt1[0] - pt0[0];
    int dy = pt1[1] - pt0[1];
    if(abs(dx) > abs(dy)){
        for(int x=pt0[0]; x!=pt1[0]; x+=(dx>0?1:-1)){
            int y=pt0[1]+(x-pt0[0])*dy/dx;
            AT(img, clip(x, 0, img->width-1), clip(y, 0, img->height-1)) = value;
        }
    }else{
        for(int y=pt0[1]; y!=pt1[1]; y+=(dy>0?1:-1)){
            int x=pt0[0]+(y-pt0[1])*dx/dy;
            AT(img, clip(x, 0, img->width-1), clip(y, 0, img->height-1)) = value;
        }
    }
}

AT_ITCM_SECTION_INIT(uint16_t getOSTUThreshold(image_t* img, uint8_t MinThreshold,uint8_t MaxThreshold))
{
    uint8_t Histogram[256];
    uint16_t OUSTThreshold  = 0;
    uint32_t PixelAmount = 0, Value_Sum = 0;
    uint64_t sigma = 0, maxSigma = 0;
    float w1 = 0, w2 = 0;
    int32_t u1 = 0, u2 = 0;
    uint8_t MinValue = 0, MaxValue = 255;
    
    //各像素点个数
    uint8_t *ptr = img->data;
    uint8_t *ptrEnd = img->data + img->width * img->height;
    while (ptr != ptrEnd)
    {
        ++Histogram[*ptr++];
    }
    
    for(uint8_t m = 0;m < 100; m++)
    {
    
       Histogram[m] = 0;
    }
    
    for (MinValue = 0; Histogram[MinValue] == 0 && MinValue < 255; ++MinValue)
        ;
    for (MaxValue = 255; Histogram[MaxValue] == 0 && MaxValue > 0; --MaxValue)
        ;
    
    if (MaxValue == MinValue)     return MaxValue;         // 只有一个颜色
    if (MinValue + 1 == MaxValue)  return MinValue;        // 只有二个颜色
    
    if (MinValue < MinThreshold)
    {
        MinValue = MinThreshold;
    }
    if (MaxValue > MaxThreshold)
    {
        MaxValue = MaxThreshold;
    }
    
    uint32_t Pixel_Integral[256] = {0};   //像素积分 
    uint32_t Value_Integral[256] = {0};    //灰度积分
    for (uint8_t i = MinValue; i <= MaxValue; ++i)
    {
        PixelAmount += Histogram[i];      //像素总数
        Value_Sum += Histogram[i] * i;     //灰度总和
        Pixel_Integral[i] = PixelAmount;        
        Value_Integral[i] = Value_Sum;
    }
    for (uint8_t i = MinValue; i < MaxValue + 1; ++i)
    {
        w1 = (float)Pixel_Integral[i] / PixelAmount;  //前景像素点比例
        w2 = 1 - w1;                               //背景比例
        u1 = (int32_t)(Value_Integral[i] / w1);                   //前景平均灰度
        u2 = (int32_t)((Value_Sum - Value_Integral[i]) / w2);      //背景平均灰度
        sigma = (uint64_t)(w1 * w2 * (u1 - u2) * (u1 - u2));
        if (sigma >= maxSigma)
        {
            maxSigma = sigma;
            OUSTThreshold = i;
        }
        else
        {
            break;
        }
    }
    return OUSTThreshold;
}

// 点集三角滤波
AT_ITCM_SECTION_INIT(void blur_points(float pts_in[][2], int num, float pts_out[][2], int kernel)){
    assert(kernel % 2 == 1);
    int half = kernel/2;
    for(int i=0; i<num; i++){
        pts_out[i][0] = pts_out[i][1] = 0;
        for(int j=-half; j<=half; j++){
            pts_out[i][0] += pts_in[clip(i+j, 0, num-1)][0] * (half+1-abs(j));
            pts_out[i][1] += pts_in[clip(i+j, 0, num-1)][1] * (half+1-abs(j));
        }
        pts_out[i][0] /= (2*half+2)*(half+1)/2;
        pts_out[i][1] /= (2*half+2)*(half+1)/2;
    }
}

// 点集等距采样
AT_ITCM_SECTION_INIT(void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist)){
    int remain = 0, len = 0;
    for(int i=0; i<num1-1 && len < *num2; i++){
        float x0 = pts_in[i][0];
        float y0 = pts_in[i][1];
        float dx = pts_in[i+1][0] - x0;
        float dy = pts_in[i+1][1] - y0;
        float dn = sqrt(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;

        while(remain < dn && len < *num2){
            x0 += dx * remain;
            pts_out[len][0] = x0;
            y0 += dy * remain;
            pts_out[len][1] = y0;
            
            len++;
            dn -= remain;
            remain = dist;
        }
        remain -= dn;
    }
    *num2 = len;
}

// 点集局部角度变化率
AT_ITCM_SECTION_INIT(void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist)){
    for(int i=0; i<num; i++){
        if(i<=0 || i>=num-1) {
            angle_out[i] = 0;
            continue;
        }
        float dx1 = pts_in[i][0] - pts_in[clip(i-dist, 0, num-1)][0];
        float dy1 = pts_in[i][1] - pts_in[clip(i-dist, 0, num-1)][1];
        float dn1 = sqrtf(dx1*dx1+dy1*dy1);
        float dx2 = pts_in[clip(i+dist, 0, num-1)][0] - pts_in[i][0];
        float dy2 = pts_in[clip(i+dist, 0, num-1)][1] - pts_in[i][1];
        float dn2 = sqrtf(dx2*dx2+dy2*dy2);
        float c1 = dx1/dn1;
        float s1 = dy1/dn1;
        float c2 = dx2/dn2;
        float s2 = dy2/dn2;
        angle_out[i] = atan2f(c1*s2-c2*s1, c2*c1+s2*s1);
    }
}

// 角度变化率非极大抑制
AT_ITCM_SECTION_INIT(void nms_angle(float angle_in[], int num, float angle_out[], int kernel)){
    assert(kernel % 2 == 1);
    int half = kernel / 2;
    for(int i=0;i<num; i++){
        angle_out[i] = angle_in[i];
        for(int j=-half; j<=half; j++){
            if(fabs(angle_in[clip(i+j, 0, num-1)]) > fabs(angle_out[i])){
                angle_out[i] = 0;
                break;
            }
        }
    }
}

// 左边线跟踪中线
AT_ITCM_SECTION_INIT(void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist)){
    for(int i=0; i<num; i++){
        float dx = pts_in[clip(i+approx_num, 0, num-1)][0] - pts_in[clip(i-approx_num, 0, num-1)][0];
        float dy = pts_in[clip(i+approx_num, 0, num-1)][1] - pts_in[clip(i-approx_num, 0, num-1)][1];
        float dn = sqrt(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] - dy * dist;
        pts_out[i][1] = pts_in[i][1] + dx * dist;
    }
}

// 右边线跟踪中线
AT_ITCM_SECTION_INIT(void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist)){
    for(int i=0; i<num; i++){
        float dx = pts_in[clip(i+approx_num, 0, num-1)][0] - pts_in[clip(i-approx_num, 0, num-1)][0];
        float dy = pts_in[clip(i+approx_num, 0, num-1)][1] - pts_in[clip(i-approx_num, 0, num-1)][1];
        float dn = sqrt(dx*dx+dy*dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] + dy * dist;
        pts_out[i][1] = pts_in[i][1] - dx * dist;
    }
}

void draw_x(image_t* img, int x, int y, int len){
    for(int i=-len; i<=len; i++){
        AT(img, clip(x+i, 0, img->width-1), clip(y+i, 0, img->height-1)) = 255;
        AT(img, clip(x-i, 0, img->width-1), clip(y+i, 0, img->height-1)) = 255;
    }
}

void draw_o(image_t* img, int x, int y, int radius){
    for(float i=-PI; i<=PI; i+=PI/10){
        AT(img, clip(x+radius*cosf(i), 0, img->width-1), clip(y+radius*sinf(i), 0, img->height-1)) = 255;
    }
}
