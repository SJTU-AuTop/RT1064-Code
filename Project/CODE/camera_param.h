#ifndef CAMERA_PARAM_H
#define CAMERA_PARAM_H

#include <stdbool.h>

extern float K[3][3];
extern float D[4];
extern float H[3][3];
extern float H_inv[3][3];
extern float mapx[240][376];
extern float mapy[240][376];
extern int invx[240][376];
extern int invy[240][376];

bool map_inv(float pt0[2], int pt1[2]);

#endif // CAMERA_PARAM_H
