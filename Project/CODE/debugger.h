#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct debugger_image {
    const char* const name;
    const int width;
    const int height;
    const uint8_t* buffer;
    
    struct debugger_image* next;
} debugger_image_t;

#define CREATE_DEBUGGER_IMAGE(str, w, h, buf) {.name=str, .width=w, .height=h, .buffer=(uint8_t*)buf, .next=NULL}

typedef struct debugger_chart {
    const char* const name;
    const double* value;
    
    struct debugger_chart* next;
} debugger_chart_t;

#define CREATE_DEBUGGER_CHART(str, pval) {.name=str, .value=pval, next=NULL}

typedef struct debugger_param {
    const char* const name;
    const float min_value;
    const float max_value;
    const float step_value;
    float* current_value;
    
    struct debugger_param* next;
} debugger_param_t;

#define CREATE_DEBUGGER_PARAM(str, minv, maxv, stpv, pval) {.name=str, .min_value=minv, .max_value=maxv, .step_value=stpv, .current_value=pval, .next=NULL}

typedef struct debugger_option {
    const char* const name;
    bool* current_option;
    
    struct debugger_option* next;
} debugger_option_t;

#define CREATE_DEBUGGER_OPTION(str, popt) {.name=str, .current_option=popt, .next=NULL}

typedef struct debugger_button {
    const char* const name;
    void (*func)(const char*);
    
    struct debugger_button* next;
} debugger_button_t;

#define CREATE_DEBUGGER_BUTTON(str, callback) {.name=str, .func=callback, .next=NULL}

extern debugger_image_t* p_active_image;

void debugger_init();

void debugger_register_image(debugger_image_t* ptr);

void debugger_register_chart(debugger_chart_t* ptr);

void debugger_register_param(debugger_param_t* ptr);

void debugger_register_option(debugger_option_t* ptr);

void debugger_register_button(debugger_button_t* ptr);

void debugger_worker();

#endif // DEBUGGER_H