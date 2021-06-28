#ifndef IMGPROC_H
#define IMGPROC_H

#include <stdint.h>

typedef struct image{
    uint8_t *data;
    uint32_t width;
    uint32_t height;
    uint32_t step;
} image_t;

typedef struct fimage{
    float *data;
    uint32_t width;
    uint32_t height;
    uint32_t step;
} fimage_t;

#define AT_IMAGE(img, x, y)          ((img)->data[(y)*(img)->step+(x)])

#define DEF_IMAGE(ptr, w, h)         {.data=ptr, .width=w, .height=h, .step=w}
#define ROI_IMAGE(img, x1, y1, w, h) {.data=&AT_IMAGE(img, x1, y1), .width=w, .height=h, .step=img.width}
    
// 深拷贝图片，img0和img1不可以指向相同图片
void clone_image(image_t* img0, image_t* img1);
    
// 清空图片
void clear_image(image_t* img);
    
// 基础二值化，img0和img1可以指向相同图片
void threshold(image_t* img0, image_t* img1, uint8_t thres, uint8_t low_value, uint8_t high_value);

// 像素逻辑与，即都为255时才为255
void image_and(image_t* img0, image_t* img1, image_t *img2);

// 像素逻辑或，即都为255时才为255
void image_or(image_t* img0, image_t* img1, image_t *img2);
    
// 最小值降采样x2
void minpool2(image_t *img0, image_t* img1);

// 3x3高斯滤波，img0和img1不可以指向相同图片，最外圈像素点不参与计算
void blur3(image_t* img0, image_t* img1);

// 3x3 Sobel梯度计算，img0和img1不可以指向相同图片，最外圈像素点不参与计算
void sobel3(image_t* img0, image_t* img1);

// 3x3腐蚀运算，img0和img1不可以指向相同图片，最外圈像素点不参与计算
void erode3(image_t* img0, image_t* img1);

// 3x3膨胀运算，img0和img1不可以指向相同图片，最外圈像素点不参与计算
void dilate3(image_t* img0, image_t* img1);

// 图像变换，最近邻插值。img0和img1不可以指向相同图片（去畸变，投影变换等。使用opencv生成变换表）
// 未测试，可能有BUG
void remap(image_t* img0, image_t* img1, fimage_t* mapx, fimage_t* mapy);
    
// 左手巡线同时二值化，从(x,y)开始向上沿白边线走
void findline_lefthand_with_thres(image_t* img, uint8_t thres, uint8_t delta, int x, int y, int pts[][2], int *num);

// 右手巡线同时二值化，从(x,y)开始向上沿白边线走
void findline_righthand_with_thres(image_t* img, uint8_t thres, uint8_t delta, int x, int y, int pts[][2], int *num);

// 大津法计算二值化阈值
uint16_t getOSTUThreshold(image_t* img, uint8_t MinThreshold,uint8_t MaxThreshold);

// 点集三角滤波
void blur_points(float pts_in[][2], int num, float pts_out[][2], int kernel);

// 点集等距采样
void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist);

// 点集局部角度变化率
void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist);

// 角度变化率非极大抑制
void nms_angle(float angle_in[], int num, float angle_out[], int kernel);

// 左边线跟踪中线
void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);

// 右边线跟踪中线
void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);

// 绘制X
void draw_x(image_t* img, int x, int y, int len);

// 绘制O
void draw_o(image_t* img, int x, int y, int radius);

#endif // IMGPROC_H