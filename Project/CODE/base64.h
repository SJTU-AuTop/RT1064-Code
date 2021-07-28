#ifndef BASE64_H
#define BASE64_H

/*
 * base64编码，用于上位机通信时，在json中传输图像数据
 */

#include <stdint.h>

#if defined(__cplusplus)||defined(c_plusplus)
extern "C"{
#endif

int to_base64(const uint8_t* src, int len, uint8_t *buf);

int from_base64(uint8_t *buf, const uint8_t* src, int len);

#if defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif // BASE64_H
