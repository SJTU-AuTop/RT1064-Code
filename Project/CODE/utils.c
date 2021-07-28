#include "utils.h"


int clip(int x, int low, int up){
    return x>up?up:x<low?low:x;
}

float fclip(float x, float low, float up){
    return x>up?up:x<low?low:x;
}
