/*
 * apriltag识别。赛道中线发现一坨黑色，并且不是斑马线即判定为apriltag
 */

#ifndef APRILTAG_H
#define APRILTAG_H

enum apriltag_type_e {
    APRILTAG_NONE = 0,  // 无黑斑apriltag
    APRILTAG_MAYBE,     // 识别到远距离黑斑，减速
    APRILTAG_FOUND,     // 识别到近距离黑斑，停车
    APRILTAG_LEAVE,     // 驶离apriltag中，编码器判断，防止其他标志的判断受到apriltag的影响
    APRILTAG_NUM,       // 
};

extern enum apriltag_type_e apriltag_type;
extern int apriltag_time;

extern const char *apriltag_type_name[APRILTAG_NUM];

void check_apriltag();

#endif // APRILTAG_H