#include "flash_param.h"
#include "zf_flash.h"

//
#define PARAM_FLASH_SECTOR        (FLASH_SECTOR_NUM-1)

//
#define PARAM_FLASH_SECTOR_PAGE   (0)


uint32_t flash_buffer[64];
uint32_t * const flash_data = (void*)0x20200000;

__attribute__((section(".ARM.__at_0x20200000"))) float thres = 140;
__attribute__((section(".ARM.__at_0x20200004"))) float block_size = 7;
__attribute__((section(".ARM.__at_0x20200008"))) float clip_value = 2;
__attribute__((section(".ARM.__at_0x2020000C"))) float begin_x = 32;
__attribute__((section(".ARM.__at_0x20200010"))) float begin_y = 167;
__attribute__((section(".ARM.__at_0x20200014"))) float line_blur_kernel = 7;
__attribute__((section(".ARM.__at_0x20200018"))) float pixel_per_meter = 102;
__attribute__((section(".ARM.__at_0x2020001C"))) float sample_dist = 0.02;
__attribute__((section(".ARM.__at_0x20200020"))) float angle_dist = 0.2;
__attribute__((section(".ARM.__at_0x20200024"))) float far_rate = 0.5;
__attribute__((section(".ARM.__at_0x20200028"))) float aim_distance = 0.68;
__attribute__((section(".ARM.__at_0x2020002C"))) bool adc_cross = false;

__attribute__((section(".ARM.__at_0x202000FC"))) static uint32_t check = 0;


void flash_param_init(){
    flash_init();
    flash_read_page(PARAM_FLASH_SECTOR, PARAM_FLASH_SECTOR_PAGE, (uint32*)flash_buffer, 64);
}

bool flash_param_check(){
    uint32_t check_value = 0;
    for(int i=0; i<63; i++){
        check_value += flash_buffer[i];
    }
    return check_value == flash_buffer[63];
}

void flash_param_load(){
    memcpy(flash_data, flash_buffer, 256);
}

void flash_param_write(){
    check = 0;
    for(int i=0; i<63; i++){
        check += flash_data[i];
    }
    flash_erase_sector(PARAM_FLASH_SECTOR);
    flash_page_program(PARAM_FLASH_SECTOR, PARAM_FLASH_SECTOR_PAGE, (uint32*)flash_data, 64);
}
