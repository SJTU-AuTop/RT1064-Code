/*
 * apriltag识别。赛道中线发现一坨黑色，并且不是斑马线即判定为apriltag
 */

#ifndef APRILTAG_H
#define APRILTAG_H

enum apriltag_type_e {
    APRILTAG_NONE,
    APRILTAG_MAYBE,  
    APRILTAG_FOUND,
};

extern enum apriltag_type_e apriltag_type;

void check_apriltag();

#endif // APRILTAG_H