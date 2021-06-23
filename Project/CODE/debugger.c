#include "debugger.h"
#include "base64.h"
#include "headfile.h"
#include <stdio.h>

static debugger_image_t* p_image = NULL;
static debugger_chart_t* p_chart = NULL;
static debugger_param_t* p_param = NULL;
static debugger_option_t* p_option = NULL;
static debugger_button_t* p_button = NULL;

static debugger_image_t* p_active_image = NULL;

AT_SDRAM_SECTION_ALIGN(static char json_buffer[1024 + MT9V03X_CSI_H * MT9V03X_CSI_W * 2], 64);

/* 内部函数 */
static void debugger_send_config(){
    char *pbuf = json_buffer;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"type\":\"config\",\"body\":{");
    
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"image\":[ ");
    for(debugger_image_t* ptr = p_image; ptr != NULL; ptr = ptr->next){
        pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"name\":\"%s\","
                                                     "\"width\":%d,"
                                                     "\"height\":%d},", 
                                                     ptr->name, ptr->width, ptr->height);
    }
    pbuf -= 1;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "],");
    
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"chart\":[ ");
    for(debugger_chart_t* ptr = p_chart; ptr != NULL; ptr = ptr->next){
        pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"name\":\"%s\"},", ptr->name);
    }
    pbuf -= 1;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "],");
    
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"param\":[ ");
    for(debugger_param_t* ptr = p_param; ptr != NULL; ptr = ptr->next){
        pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"name\":\"%s\","
                                                     "\"min_value\":%d,"
                                                     "\"max_value\":%d,"
                                                     "\"default_value\":%d},",
                                                     ptr->name, ptr->min_value, ptr->max_value, ptr->default_value);
    }
    pbuf -= 1;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "],");
    
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"option\":[ ");
    for(debugger_option_t* ptr = p_option; ptr != NULL; ptr = ptr->next){
        pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"name\":\"%s\","
                                                     "\"default_option\":%s},",
                                                     ptr->name, ptr->default_option ? "true" : "false");
    }
    pbuf -= 1;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "],");
    
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"button\":[ ");
    for(debugger_button_t* ptr = p_button; ptr != NULL; ptr = ptr->next){
        pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"name\":\"%s\"},", ptr->name);
    }
    pbuf -= 1;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "]");
    
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "}}\n");
    
    usb_cdc_send_buff((uint8_t*)json_buffer, pbuf - json_buffer);
}

static void debugger_send_image(){
    if(p_active_image == NULL) return;
    char* pbuf = json_buffer;
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "{\"type\":\"image\",\"body\":{");
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"name\":\"%s\",\"data\":\"", p_active_image->name);
    pbuf += to_base64(p_active_image->buffer, p_active_image->width * p_active_image->height, (uint8_t*)pbuf);
    pbuf += snprintf(pbuf, json_buffer + sizeof(json_buffer) - pbuf, "\"}}\n");
    usb_cdc_send_buff((uint8_t*)json_buffer, pbuf - json_buffer);
}

static void debugger_send_chart(){
    
}

uint32_t split_by(uint8_t* str, uint8_t ch, uint32_t length){
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
            *ptr->current_value = atoi(value);
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

/* 接口函数 */
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
    debugger_send_config();
    debugger_send_image();
    debugger_send_chart();
}
