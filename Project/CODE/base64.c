#include "base64.h"
#include "common.h"

AT_DTCM_SECTION_ALIGN_INIT(static uint8_t raw_to_base64[64], 64) = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
    'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
    'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',
};

AT_DTCM_SECTION_ALIGN_INIT(static uint8_t base64_to_raw[128], 64) = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
     52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255, 255, 255, 255, 255,
    255,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
    255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,
     41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51, 255, 255, 255, 255, 255,
};

typedef struct{
    uint32_t b0: 6;
    uint32_t b1: 6;
    uint32_t b2: 6;
    uint32_t b3: 6;
    uint32_t nop: 8;
} byte3;

int to_base64(const uint8_t* src, int len, uint8_t *buf){
    uint8_t* buf_init = buf;
    while(len >= 3){
        *(buf++) = raw_to_base64[((byte3*)(src))->b0];
        *(buf++) = raw_to_base64[((byte3*)(src))->b1];
        *(buf++) = raw_to_base64[((byte3*)(src))->b2];
        *(buf++) = raw_to_base64[((byte3*)(src))->b3];
        src += 3;
        len -= 3;
    }
    switch(len){
    case 2:
        *(buf++) = raw_to_base64[((byte3*)(src))->b0];
        *(buf++) = raw_to_base64[((byte3*)(src))->b1];
        *(buf++) = raw_to_base64[((byte3*)(src))->b2 & 0x0f];
        src += 2;
        break;
    case 1:
        *(buf++) = raw_to_base64[((byte3*)(src))->b0];
        *(buf++) = raw_to_base64[((byte3*)(src))->b1 & 0x03];
        src += 1;
        break;
    }
    return buf - buf_init;
}

int from_base64(uint8_t *buf, const uint8_t* src, int len){
    uint8_t *buf_init = buf;
    while(len >= 4){
        ((byte3*)(buf))->b0 = base64_to_raw[*(src++)];
        ((byte3*)(buf))->b1 = base64_to_raw[*(src++)];
        ((byte3*)(buf))->b2 = base64_to_raw[*(src++)];
        ((byte3*)(buf))->b3 = base64_to_raw[*(src++)];
        buf += 3;
        len -= 4;
    }
    switch(len){
    case 3:
        ((byte3*)(buf))->b0 = base64_to_raw[*(src++)];
        ((byte3*)(buf))->b1 = base64_to_raw[*(src++)];
        ((byte3*)(buf))->b2 = base64_to_raw[*(src++)];
        buf += 2;
        break;
    case 2:
        ((byte3*)(buf))->b0 = base64_to_raw[*(src++)];
        ((byte3*)(buf))->b1 = base64_to_raw[*(src++)];
        ((byte3*)(buf))->b2 = base64_to_raw[*(src++)];
        buf += 1;
        break;
    }
    return buf - buf_init;
}

