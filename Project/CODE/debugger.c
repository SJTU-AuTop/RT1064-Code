#include "debugger.h"
#include "base64.h"
#include "headfile.h"
#include <stdio.h>

debugger_image_t* p_image = NULL;
debugger_chart_t* p_chart = NULL;
debugger_param_t* p_param = NULL;
debugger_option_t* p_option = NULL;
debugger_button_t* p_button = NULL;

debugger_image_t* p_active_image = NULL;

AT_SDRAM_SECTION_ALIGN(char json_buffer[1024 + MT9V03X_CSI_H * MT9V03X_CSI_W * 2], 64);

static void debugger_send_image_data(debugger_image_t* image){
    char* pbuf = json_buffer;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"type\":\"image\",\"body\":{"
                    "\"name\":\"%s\",\"width\":%d,\"height\":%d,\"data\":\"", image->name, image->width, image->height);
    pbuf += to_base64(image->buffer, image->width * image->height, (uint8_t*)pbuf);
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"}}\n");
    usb_cdc_send_buff((uint8_t*)json_buffer, pbuf - json_buffer);
}

static void debugger_send_image(debugger_image_t *image){
    int len = snprintf(json_buffer, sizeof(json_buffer), "{\"type\":\"image\",\"body\":{"
                    "\"name\":\"%s\"}}\n",
                    image->name);
    usb_cdc_send_buff((uint8_t*)json_buffer, len);
    
}

static void debugger_send_chart(debugger_chart_t* chart){
    
}

static void debugger_send_param(debugger_param_t* param){
    int len = snprintf(json_buffer, sizeof(json_buffer), "{\"type\":\"param\",\"body\":{"
                    "\"name\":\"%s\",\"min_value\":%f,\"max_value\":%f,\"step_value\":%f,\"current_value\":%f}}\n",
                    param->name, param->min_value, param->max_value, param->step_value, *param->current_value);
    usb_cdc_send_buff((uint8_t*)json_buffer, len);
}

static void debugger_send_option(debugger_option_t* option){
    int len = snprintf(json_buffer, sizeof(json_buffer), "{\"type\":\"option\",\"body\":{"
                    "\"name\":\"%s\",\"current_option\":%s}}\n",
                    option->name, (*option->current_option)?"true":"false");
    usb_cdc_send_buff((uint8_t*)json_buffer, len);
}

static void debugger_send_button(debugger_button_t* button){
    int len = snprintf(json_buffer, sizeof(json_buffer), "{\"type\":\"button\",\"body\":{"
                    "\"name\":\"%s\"}}\n",
                    button->name);
    usb_cdc_send_buff((uint8_t*)json_buffer, len);
}

static uint32_t split_by(uint8_t* str, uint8_t ch, uint32_t length){
    uint32_t i;
    for(i=0; i<length && str[i]!=ch; i++);
    return i;
}

void usb_cdc_recv_callback(uint8_t* buffer, uint32 length){
    char type[32]="", name[32]="", value[32]="";
    int len;
    len = split_by(buffer, ' ', length);
    memcpy(type, buffer, len);
    buffer += len+1;
    length -= len+1;
    len = split_by(buffer, ' ', length);
    memcpy(name, buffer, len);
    buffer += len+1;
    length -= len+1;
    
    if(strcmp(type, "image")==0){
        debugger_image_t *ptr;
        for(ptr=p_image; ptr!=NULL && strcmp(name, ptr->name)!=0; ptr=ptr->next);
        if(ptr!=NULL) p_active_image = ptr;
    }else if(strcmp(type, "param")==0){
        debugger_param_t *ptr;
        for(ptr=p_param; ptr!=NULL && strcmp(name, ptr->name)!=0; ptr=ptr->next);
        if(ptr != NULL) {
            len = split_by(buffer, ' ', length);
            memcpy(value, buffer, len);
            *ptr->current_value = atof(value);
        }
    }else if(strcmp(type, "option")==0){
        debugger_option_t *ptr;
        for(ptr=p_option; ptr!=NULL && strcmp(name, ptr->name)!=0; ptr=ptr->next);
        if(ptr != NULL) {
            *ptr->current_option = buffer[0] != '0';
        }
    }else if(strcmp(type, "button")==0){
        debugger_button_t *ptr;
        for(ptr=p_button; ptr!=NULL && strcmp(name, ptr->name)!=0; ptr=ptr->next);
        if(ptr != NULL) {
            ptr->func(ptr->name);
        }
    }
}

void debugger_init(){
    usb_cdc_init();
}

void debugger_register_image(debugger_image_t* ptr){
    debugger_image_t **pp;
    for(pp = &p_image; *pp != NULL; pp = &(*pp)->next);
    *pp = ptr;
    p_active_image = ptr;
}

void debugger_register_chart(debugger_chart_t* ptr){
    debugger_chart_t **pp;
    for(pp = &p_chart; *pp != NULL; pp = &(*pp)->next);
    *pp = ptr;
}

void debugger_register_param(debugger_param_t* ptr){
    debugger_param_t **pp;
    for(pp = &p_param; *pp != NULL; pp = &(*pp)->next);
    *pp = ptr;
}

void debugger_register_option(debugger_option_t* ptr){
    debugger_option_t **pp;
    for(pp = &p_option; *pp != NULL; pp = &(*pp)->next);
    *pp = ptr;
}

void debugger_register_button(debugger_button_t* ptr){
    debugger_button_t **pp;
    for(pp = &p_button; *pp != NULL; pp = &(*pp)->next);
    *pp = ptr;
}

void debugger_worker(){
    for(debugger_image_t* ptr=p_image; ptr!=NULL; ptr=ptr->next){
        if(ptr == p_active_image){
            debugger_send_image_data(ptr);
        }else{
            debugger_send_image(ptr);
        }
    }
    for(debugger_chart_t* ptr=p_chart; ptr!=NULL; ptr=ptr->next){
        debugger_send_chart(ptr);
    }
    for(debugger_param_t* ptr=p_param; ptr!=NULL; ptr=ptr->next){
        debugger_send_param(ptr);
    }
    for(debugger_option_t* ptr=p_option; ptr!=NULL; ptr=ptr->next){
        debugger_send_option(ptr);
    }
    for(debugger_button_t* ptr=p_button; ptr!=NULL; ptr=ptr->next){
        debugger_send_button(ptr);
    }
}
