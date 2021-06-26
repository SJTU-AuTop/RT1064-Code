/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		ROM API
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


#include "zf_rom_api.h"

//ROM API 结构体指针
static rom_api_entry_t *rom_api_entry;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ROM API初始化
//  @param      void
//  @return     void
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void rom_api_init(void)
{
    rom_api_entry = (rom_api_entry_t *)*(uint32_t *)0x0020001c;
}


//-------------------------Clock--------------------------------------------
void rom_api_CLOCK_SetMux(clock_mux_t mux, uint32_t value)
{
    rom_api_entry->clockDriver->CLOCK_SetMux(mux, value);
}

uint32_t rom_api_CLOCK_GetMux(clock_mux_t mux)
{
    return rom_api_entry->clockDriver->CLOCK_GetMux(mux);
}

void rom_api_CLOCK_SetDiv(clock_div_t divider, uint32_t value)
{
    rom_api_entry->clockDriver->CLOCK_SetDiv(divider, value);
}

uint32_t rom_api_CLOCK_GetDiv(clock_div_t divider)
{
    return rom_api_entry->clockDriver->CLOCK_GetDiv(divider);
}

void rom_api_CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value)
{
    rom_api_entry->clockDriver->CLOCK_ControlGate(name, value);
}

void rom_api_CLOCK_EnableClock(clock_ip_name_t name)
{
    rom_api_entry->clockDriver->CLOCK_EnableClock(name);
}

void rom_api_CLOCK_DisableClock(clock_ip_name_t name)
{
    rom_api_entry->clockDriver->CLOCK_DisableClock(name);
}

void rom_api_CLOCK_SetMode(clock_mode_t mode)
{
    rom_api_entry->clockDriver->CLOCK_SetMode(mode);
}

void rom_api_CLOCK_SetPllBypass(CCM_ANALOG_Type *base, clock_pll_t pll, bool bypass)
{
    rom_api_entry->clockDriver->CLOCK_SetPllBypass(base, pll, bypass);
}

uint32_t rom_api_CLOCK_GetCpuClkFreq(void)
{
    return rom_api_entry->clockDriver->CLOCK_GetCpuClkFreq();
}

uint32_t rom_api_CLOCK_GetRtcFreq(void)
{
    return rom_api_entry->clockDriver->CLOCK_GetRtcFreq();
}

void rom_api_CLOCK_SetXtalFreq(uint32_t freq)
{
    rom_api_entry->clockDriver->CLOCK_SetXtalFreq(freq);
}

void rom_api_CLOCK_SetRtcXtalFreq(uint32_t freq)
{
    rom_api_entry->clockDriver->CLOCK_SetRtcXtalFreq(freq);
}

void rom_api_CLOCK_InitExternalClk(bool bypassXtalOsc)
{
    rom_api_entry->clockDriver->CLOCK_InitExternalClk(bypassXtalOsc);
}

void rom_api_CLOCK_DeinitExternalClk(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitExternalClk();
}

void rom_api_CLOCK_SwitchOsc(clock_osc_t osc)
{
    rom_api_entry->clockDriver->CLOCK_SwitchOsc(osc);
}

void rom_api_CLOCK_InitRcOsc24M(void)
{
    rom_api_entry->clockDriver->CLOCK_InitRcOsc24M();
}

void rom_api_CLOCK_DeinitRcOsc24M(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitRcOsc24M();
}

uint32_t rom_api_CLOCK_GetFreq(clock_name_t name)
{
    return rom_api_entry->clockDriver->CLOCK_GetFreq(name);
}

bool rom_api_CLOCK_EnableUsbhs0Clock(clock_usb_src_t src, uint32_t freq)
{
    return rom_api_entry->clockDriver->CLOCK_EnableUsbhs0Clock(src, freq);
}

bool rom_api_CLOCK_EnableUsbhs1Clock(clock_usb_src_t src, uint32_t freq)
{
    return rom_api_entry->clockDriver->CLOCK_EnableUsbhs1Clock(src, freq);
}

bool rom_api_CLOCK_EnableUsbhs0PhyPllClock(clock_usb_phy_src_t src, uint32_t freq)
{
    return rom_api_entry->clockDriver->CLOCK_EnableUsbhs0PhyPllClock(src, freq);
}

void rom_api_CLOCK_DisableUsbhs0PhyPllClock(void)
{
    rom_api_entry->clockDriver->CLOCK_DisableUsbhs0PhyPllClock();
}

void rom_api_CLOCK_InitArmPll(const clock_arm_pll_config_t *config)
{
    rom_api_entry->clockDriver->CLOCK_InitArmPll(config);
}

void rom_api_CLOCK_DeinitArmPll(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitArmPll();
}

void rom_api_CLOCK_InitSysPll(const clock_sys_pll_config_t *config)
{
    rom_api_entry->clockDriver->CLOCK_InitSysPll(config);
}

void rom_api_CLOCK_DeinitSysPll(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitSysPll();
}

void rom_api_CLOCK_InitUsb1Pll(const clock_usb_pll_config_t *config)
{
    rom_api_entry->clockDriver->CLOCK_InitUsb1Pll(config);
}

void rom_api_CLOCK_DeinitUsb1Pll(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitUsb1Pll();
}

void rom_api_CLOCK_InitUsb2Pll(const clock_usb_pll_config_t *config)
{
    rom_api_entry->clockDriver->CLOCK_InitUsb2Pll(config);
}

void rom_api_CLOCK_DeinitUsb2Pll(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitUsb2Pll();
}

void rom_api_CLOCK_InitAudioPll(const clock_audio_pll_config_t *config)
{
    rom_api_entry->clockDriver->CLOCK_InitAudioPll(config);
}

void rom_api_CLOCK_DeinitAudioPll(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitAudioPll();
}

void rom_api_CLOCK_InitVideoPll(const clock_video_pll_config_t *config)
{
    rom_api_entry->clockDriver->CLOCK_InitVideoPll(config);
}

void rom_api_CLOCK_DeinitVideoPll(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitVideoPll();
}

void rom_api_CLOCK_InitEnetPll(const clock_enet_pll_config_t *config)
{
    rom_api_entry->clockDriver->CLOCK_InitEnetPll(config);
}

void rom_api_CLOCK_DeinitEnetPll(void)
{
    rom_api_entry->clockDriver->CLOCK_DeinitEnetPll();
}

uint32_t rom_api_CLOCK_GetPllFreq(clock_pll_t pll)
{
    return rom_api_entry->clockDriver->CLOCK_GetPllFreq(pll);
}

void rom_api_CLOCK_InitSysPfd(clock_pfd_t pfd, uint8_t pfdFrac)
{
    rom_api_entry->clockDriver->CLOCK_InitSysPfd(pfd, pfdFrac);
}

void rom_api_CLOCK_DeinitSysPfd(clock_pfd_t pfd)
{
    rom_api_entry->clockDriver->CLOCK_DeinitSysPfd(pfd);
}

void rom_api_CLOCK_InitUsb1Pfd(clock_pfd_t pfd, uint8_t pfdFrac)
{
    rom_api_entry->clockDriver->CLOCK_InitUsb1Pfd(pfd, pfdFrac);
}

void rom_api_CLOCK_DeinitUsb1Pfd(clock_pfd_t pfd)
{
    rom_api_entry->clockDriver->CLOCK_DeinitUsb1Pfd(pfd);
}

uint32_t rom_api_CLOCK_GetSysPfdFreq(clock_pfd_t pfd)
{
    return rom_api_entry->clockDriver->CLOCK_GetSysPfdFreq(pfd);
}

uint32_t rom_api_CLOCK_GetUsb1PfdFreq(clock_pfd_t pfd)
{
    return rom_api_entry->clockDriver->CLOCK_GetUsb1PfdFreq(pfd);
}

bool rom_api_CLOCK_EnableUsbhs1PhyPllClock(clock_usb_phy_src_t src, uint32_t freq)
{
    return rom_api_entry->clockDriver->CLOCK_EnableUsbhs1PhyPllClock(src, freq);
}

void rom_api_CLOCK_DisableUsbhs1PhyPllClock(void)
{
    rom_api_entry->clockDriver->CLOCK_DisableUsbhs1PhyPllClock();
}


//-------------------------RTWDOG--------------------------------------------
void rom_api_RTWDOG_ClearStatusFlags(RTWDOG_Type *base, uint32_t mask)
{
    rom_api_entry->rtwdogDriver->RTWDOG_ClearStatusFlags(base, mask);
}

void rom_api_RTWDOG_GetDefaultConfig(rtwdog_config_t *config)
{
    rom_api_entry->rtwdogDriver->RTWDOG_GetDefaultConfig(config);
}

void rom_api_RTWDOG_Init(RTWDOG_Type *base, const rtwdog_config_t *config)
{
    rom_api_entry->rtwdogDriver->RTWDOG_Init(base, config);
}

void rom_api_RTWDOG_Deinit(RTWDOG_Type *base)
{
    rom_api_entry->rtwdogDriver->RTWDOG_Deinit(base);
}


//-------------------------WDOG--------------------------------------------
void rom_api_WDOG_GetDefaultConfig(wdog_config_t *config)
{
    rom_api_entry->wdogDriver->WDOG_GetDefaultConfig(config);
}

void rom_api_WDOG_Init(WDOG_Type *base, const wdog_config_t *config)
{
    rom_api_entry->wdogDriver->WDOG_Init(base, config);
}

void rom_api_WDOG_Deinit(WDOG_Type *base)
{
    rom_api_entry->wdogDriver->WDOG_Deinit(base);
}

uint16_t rom_api_WDOG_GetStatusFlags(WDOG_Type *base)
{
    return rom_api_entry->wdogDriver->WDOG_GetStatusFlags(base);
}

void rom_api_WDOG_ClearInterruptStatus(WDOG_Type *base, uint16_t mask)
{
    rom_api_entry->wdogDriver->WDOG_ClearInterruptStatus(base, mask);
}

void rom_api_WDOG_Refresh(WDOG_Type *base)
{
    rom_api_entry->wdogDriver->WDOG_Refresh(base);
}

//-------------------------FlexSPI NOR --------------------------------------------
status_t rom_api_flexspi_nor_flash_init(uint32_t instance, flexspi_nor_config_t *config)
{
    return rom_api_entry->flexSpiNorDriver->init(instance, config);
}

status_t rom_api_flexspi_nor_flash_page_program(uint32_t instance, flexspi_nor_config_t *config, uint32_t dstAddr, const uint32_t *src)                                
{
    return rom_api_entry->flexSpiNorDriver->program(instance, config, dstAddr, src);
}

status_t rom_api_flexspi_nor_flash_erase_all(uint32_t instance, flexspi_nor_config_t *config)
{
    return rom_api_entry->flexSpiNorDriver->erase_all(instance, config);
}

status_t rom_api_flexspi_nor_get_config(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option)
{
    return rom_api_entry->flexSpiNorDriver->get_config(instance, config, option);
}

status_t rom_api_flexspi_nor_flash_erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length)
{
    return rom_api_entry->flexSpiNorDriver->erase(instance, config, start, length);
}

status_t rom_api_flexspi_nor_flash_read(uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes)
{
    return rom_api_entry->flexSpiNorDriver->read(instance, config, dst, start, bytes);
}

status_t rom_api_flexspi_update_lut(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq)
{
    return rom_api_entry->flexSpiNorDriver->update_lut(instance, seqIndex, lutBase, numberOfSeq);
}

status_t rom_api_flexspi_command_xfer(uint32_t instance, flexspi_xfer_t *xfer)
{
    return rom_api_entry->flexSpiNorDriver->xfer(instance, xfer);
}

void rom_api_flexspi_clear_cache(uint32_t instance)
{
    rom_api_entry->flexSpiNorDriver->clear_cache(instance);
}