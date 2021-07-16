/*
 * apriltag识别。赛道中线发现一坨黑色，并且不是斑马线即判定为apriltag
 */

#ifndef APRILTAG_H
#define APRILTAG_H

enum apriltag_type_e {
    APRILTAG_NONE = 0,
    APRILTAG_MAYBE,
    APRILTAG_FOUND,
    APRILTAG_LEAVE,
    APRILTAG_NUM,
};

extern enum apriltag_type_e apriltag_type;
extern int apriltag_time;

extern const char* apriltag_type_name[APRILTAG_NUM];

void check_apriltag();

#endif // APRILTAG_H