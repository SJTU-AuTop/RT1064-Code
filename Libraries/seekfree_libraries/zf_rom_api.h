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


#ifndef _zf_rom_api_h
#define _zf_rom_api_h


#include "fsl_device_registers.h"
#include "fsl_clock.h"
#include "EVKMIMXRT1064_FLEXSPI_NOR_CONFIG.h"
#include "fsl_rtwdog.h"
#include "fsl_wdog.h"
#include <string.h>


typedef enum _FlexSPIOperationType
{
    kFlexSpiOperation_Command, //!< FlexSPI operation: Only command, both TX and
    //! RX buffer are ignored.
    kFlexSpiOperation_Config, //!< FlexSPI operation: Configure device mode, the
    //! TX FIFO size is fixed in LUT.
    kFlexSpiOperation_Write, //!< FlexSPI operation: Write,  only TX buffer is
    //! effective
    kFlexSpiOperation_Read, //!< FlexSPI operation: Read, only Rx Buffer is
    //! effective.
    kFlexSpiOperation_End = kFlexSpiOperation_Read,
} flexspi_operation_t;

//!@brief FlexSPI Transfer Context
typedef struct _FlexSpiXfer
{
    flexspi_operation_t operation; //!< FlexSPI operation
    uint32_t baseAddress;          //!< FlexSPI operation base address
    uint32_t seqId;                //!< Sequence Id
    uint32_t seqNum;               //!< Sequence Number
    bool isParallelModeEnable;     //!< Is a parallel transfer
    uint32_t *txBuffer;            //!< Tx buffer
    uint32_t txSize;               //!< Tx size in bytes
    uint32_t *rxBuffer;            //!< Rx buffer
    uint32_t rxSize;               //!< Rx size in bytes
} flexspi_xfer_t;

/*
 * Serial NOR Configuration Option
 */
typedef struct _serial_nor_config_option
{
    union
    {
        struct
        {
            uint32_t max_freq : 4;          //!< Maximum supported Frequency
            uint32_t misc_mode : 4;         //!< miscellaneous mode
            uint32_t quad_mode_setting : 4; //!< Quad mode setting
            uint32_t cmd_pads : 4;          //!< Command pads
            uint32_t query_pads : 4;        //!< SFDP read pads
            uint32_t device_type : 4;       //!< Device type
            uint32_t option_size : 4;       //!< Option size, in terms of uint32_t, size = (option_size + 1) * 4
            uint32_t tag : 4;               //!< Tag, must be 0x0E
        } B;
        uint32_t U;
    } option0;

    union
    {
        struct
        {
            uint32_t dummy_cycles : 8;     //!< Dummy cycles before read
            uint32_t status_override : 8;  //!< Override status register value during device mode configuration
            uint32_t is_pinmux_group2 : 4; //!< The second group of pinmux
            uint32_t reserved : 12;        //!< Reserved for future use
        } B;
        uint32_t U;
    } option1;

} serial_nor_config_option_t;


typedef struct
{
    uint32_t version;
    status_t (*init)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*program)(uint32_t instance, flexspi_nor_config_t *config, uint32_t dst_addr, const uint32_t *src);
    status_t (*erase_all)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*erase)(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*read)(
        uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t addr, uint32_t lengthInBytes);
    void (*clear_cache)(uint32_t instance);
    status_t (*xfer)(uint32_t instance, flexspi_xfer_t *xfer);
    status_t (*update_lut)(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t seqNumber);
    status_t (*get_config)(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option);
} flexspi_nor_driver_interface_t;

typedef struct
{
    uint32_t version;
    void (*CLOCK_SetMux)(clock_mux_t mux, uint32_t value);
    uint32_t (*CLOCK_GetMux)(clock_mux_t mux);
    void (*CLOCK_SetDiv)(clock_div_t divider, uint32_t value);
    uint32_t (*CLOCK_GetDiv)(clock_div_t divider);
    void (*CLOCK_ControlGate)(clock_ip_name_t name, clock_gate_value_t value);
    void (*CLOCK_EnableClock)(clock_ip_name_t name);
    void (*CLOCK_DisableClock)(clock_ip_name_t name);
    void (*CLOCK_SetMode)(clock_mode_t mode);
    void (*CLOCK_SetPllBypass)(CCM_ANALOG_Type *base, clock_pll_t pll, bool bypass);
    uint32_t (*CLOCK_GetFreq)(clock_name_t name);
    uint32_t (*CLOCK_GetCpuClkFreq)(void);
    void (*CLOCK_InitExternalClk)(bool bypassXtalOsc);
    void (*CLOCK_DeinitExternalClk)(void);
    void (*CLOCK_SwitchOsc)(clock_osc_t osc);
    uint32_t (*CLOCK_GetRtcFreq)(void);
    void (*CLOCK_SetXtalFreq)(uint32_t freq);
    void (*CLOCK_SetRtcXtalFreq)(uint32_t freq);
    void (*CLOCK_InitRcOsc24M)(void);
    void (*CLOCK_DeinitRcOsc24M)(void);
    void (*CLOCK_InitArmPll)(const clock_arm_pll_config_t *config);
    void (*CLOCK_DeinitArmPll)(void);
    void (*CLOCK_InitSysPll)(const clock_sys_pll_config_t *config);
    void (*CLOCK_DeinitSysPll)(void);
    void (*CLOCK_InitUsb1Pll)(const clock_usb_pll_config_t *config);
    void (*CLOCK_DeinitUsb1Pll)(void);
    void (*CLOCK_InitUsb2Pll)(const clock_usb_pll_config_t *config);
    void (*CLOCK_DeinitUsb2Pll)(void);
    void (*CLOCK_InitAudioPll)(const clock_audio_pll_config_t *config);
    void (*CLOCK_DeinitAudioPll)(void);
    void (*CLOCK_InitVideoPll)(const clock_video_pll_config_t *config);
    void (*CLOCK_DeinitVideoPll)(void);
    void (*CLOCK_InitEnetPll)(const clock_enet_pll_config_t *config);
    void (*CLOCK_DeinitEnetPll)(void);
    uint32_t (*CLOCK_GetPllFreq)(clock_pll_t pll);
    void (*CLOCK_InitSysPfd)(clock_pfd_t pfd, uint8_t pfdFrac);
    void (*CLOCK_DeinitSysPfd)(clock_pfd_t pfd);
    void (*CLOCK_InitUsb1Pfd)(clock_pfd_t pfd, uint8_t pfdFrac);
    void (*CLOCK_DeinitUsb1Pfd)(clock_pfd_t pfd);
    uint32_t (*CLOCK_GetSysPfdFreq)(clock_pfd_t pfd);
    uint32_t (*CLOCK_GetUsb1PfdFreq)(clock_pfd_t pfd);
    bool (*CLOCK_EnableUsbhs0Clock)(clock_usb_src_t src, uint32_t freq);
    bool (*CLOCK_EnableUsbhs0PhyPllClock)(clock_usb_phy_src_t src, uint32_t freq);
    void (*CLOCK_DisableUsbhs0PhyPllClock)(void);
    bool (*CLOCK_EnableUsbhs1Clock)(clock_usb_src_t src, uint32_t freq);
    bool (*CLOCK_EnableUsbhs1PhyPllClock)(clock_usb_phy_src_t src, uint32_t freq);
    void (*CLOCK_DisableUsbhs1PhyPllClock)(void);
} clock_driver_interface_t;

typedef struct
{
    void (*RTWDOG_GetDefaultConfig)(rtwdog_config_t *config);
    void (*RTWDOG_Init)(RTWDOG_Type *base, const rtwdog_config_t *config);
    void (*RTWDOG_Deinit)(RTWDOG_Type *base);
    void (*RTWDOG_Enable)(RTWDOG_Type *base);
    void (*RTWDOG_Disable)(RTWDOG_Type *base);
    void (*RTWDOG_EnableInterrupts)(RTWDOG_Type *base, uint32_t mask);
    void (*RTWDOG_DisableInterrupts)(RTWDOG_Type *base, uint32_t mask);
    uint32_t (*RTWDOG_GetStatusFlags)(RTWDOG_Type *base);
    void (*RTWDOG_ClearStatusFlags)(RTWDOG_Type *base, uint32_t mask);
    void (*RTWDOG_SetTimeoutValue)(RTWDOG_Type *base, uint16_t timeoutCount);
    void (*RTWDOG_SetWindowValue)(RTWDOG_Type *base, uint16_t windowValue);
    void (*RTWDOG_Unlock)(RTWDOG_Type *base);
    void (*RTWDOG_Refresh)(RTWDOG_Type *base);
    uint16_t (*RTWDOG_GetCounterValue)(RTWDOG_Type *base);
} rtwdog_driver_interface_t;

typedef struct
{
    void (*WDOG_GetDefaultConfig)(wdog_config_t *config);
    void (*WDOG_Init)(WDOG_Type *base, const wdog_config_t *config);
    void (*WDOG_Deinit)(WDOG_Type *base);
    void (*WDOG_Enable)(WDOG_Type *base);
    void (*WDOG_Disable)(WDOG_Type *base);
    void (*WDOG_EnableInterrupts)(WDOG_Type *base, uint16_t mask);
    uint16_t (*WDOG_GetStatusFlags)(WDOG_Type *base);
    void (*WDOG_ClearInterruptStatus)(WDOG_Type *base, uint16_t mask);
    void (*WDOG_SetTimeoutValue)(WDOG_Type *base, uint16_t timeoutCount);
    void (*WDOG_SetInterrputTimeoutValue)(WDOG_Type *base, uint16_t timeoutCount);
    void (*WDOG_DisablePowerDownEnable)(WDOG_Type *base);
    void (*WDOG_Refresh)(WDOG_Type *base);
} wdog_driver_interface_t;

typedef struct
{
    const uint32_t version;                                 // Bootloader版本号
    const char *copyright;                                  // Bootloader版权
    void (*runBootloader)(void *arg);                       // Function to start the bootloader executing
    const uint32_t *reserved0;                              // 保留
    const flexspi_nor_driver_interface_t *flexSpiNorDriver; // FlexSPI NOR Flash API
    const uint32_t *reserved1;                              // 保留
    const clock_driver_interface_t *clockDriver;
    const rtwdog_driver_interface_t *rtwdogDriver;
    const wdog_driver_interface_t *wdogDriver;
    const uint32_t *reserved2;
} rom_api_entry_t;

enum
{
    kEnterBootloader_Tag = 0xEB,
    kEnterBootloader_Mode_Default = 0,
    kEnterBootloader_Mode_SerialDownloader = 1,

    kEnterBootloader_SerialInterface_Auto = 0,
    kEnterBootloader_SerialInterface_USB = 1,
    kEnterBootloader_SerialInterface_UART = 2,

    kEnterBootloader_ImageIndex_Max = 3,
};

typedef union
{
    struct
    {
        uint32_t imageIndex : 4;
        uint32_t reserved : 12;
        uint32_t serialBootInterface : 4;
        uint32_t bootMode : 4;
        uint32_t tag : 8;
    } B;
    uint32_t U;
} run_bootloader_ctx_t;

void rom_api_init(void);
//-------------------------Clock--------------------------------------------
void rom_api_CLOCK_SetMux(clock_mux_t mux, uint32_t value);
uint32_t rom_api_CLOCK_GetMux(clock_mux_t mux);
void rom_api_CLOCK_SetDiv(clock_div_t divider, uint32_t value);
uint32_t rom_api_CLOCK_GetDiv(clock_div_t divider);
void rom_api_CLOCK_ControlGate(clock_ip_name_t name, clock_gate_value_t value);
void rom_api_CLOCK_EnableClock(clock_ip_name_t name);
void rom_api_CLOCK_DisableClock(clock_ip_name_t name);
void rom_api_CLOCK_SetMode(clock_mode_t mode);
void rom_api_CLOCK_SetPllBypass(CCM_ANALOG_Type *base, clock_pll_t pll, bool bypass);
uint32_t rom_api_CLOCK_GetCpuClkFreq(void);
uint32_t rom_api_CLOCK_GetRtcFreq(void);
void rom_api_CLOCK_SetXtalFreq(uint32_t freq);
void rom_api_CLOCK_SetRtcXtalFreq(uint32_t freq);
void rom_api_CLOCK_InitExternalClk(bool bypassXtalOsc);
void rom_api_CLOCK_DeinitExternalClk(void);
void rom_api_CLOCK_SwitchOsc(clock_osc_t osc);
void rom_api_CLOCK_InitRcOsc24M(void);
void rom_api_CLOCK_DeinitRcOsc24M(void);
uint32_t rom_api_CLOCK_GetFreq(clock_name_t name);
bool rom_api_CLOCK_EnableUsbhs0Clock(clock_usb_src_t src, uint32_t freq);
bool rom_api_CLOCK_EnableUsbhs1Clock(clock_usb_src_t src, uint32_t freq);
bool rom_api_CLOCK_EnableUsbhs0PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);
void rom_api_CLOCK_DisableUsbhs0PhyPllClock(void);
void rom_api_CLOCK_InitArmPll(const clock_arm_pll_config_t *config);
void rom_api_CLOCK_DeinitArmPll(void);
void rom_api_CLOCK_InitSysPll(const clock_sys_pll_config_t *config);
void rom_api_CLOCK_DeinitSysPll(void);
void rom_api_CLOCK_InitUsb1Pll(const clock_usb_pll_config_t *config);
void rom_api_CLOCK_DeinitUsb1Pll(void);
void rom_api_CLOCK_InitUsb2Pll(const clock_usb_pll_config_t *config);
void rom_api_CLOCK_DeinitUsb2Pll(void);
void rom_api_CLOCK_InitAudioPll(const clock_audio_pll_config_t *config);
void rom_api_CLOCK_DeinitAudioPll(void);
void rom_api_CLOCK_InitVideoPll(const clock_video_pll_config_t *config);
void rom_api_CLOCK_DeinitVideoPll(void);
void rom_api_CLOCK_InitEnetPll(const clock_enet_pll_config_t *config);
void rom_api_CLOCK_DeinitEnetPll(void);
uint32_t rom_api_CLOCK_GetPllFreq(clock_pll_t pll);
void rom_api_CLOCK_InitSysPfd(clock_pfd_t pfd, uint8_t pfdFrac);
void rom_api_CLOCK_DeinitSysPfd(clock_pfd_t pfd);
void rom_api_CLOCK_InitUsb1Pfd(clock_pfd_t pfd, uint8_t pfdFrac);
void rom_api_CLOCK_DeinitUsb1Pfd(clock_pfd_t pfd);
uint32_t rom_api_CLOCK_GetSysPfdFreq(clock_pfd_t pfd);
uint32_t rom_api_CLOCK_GetUsb1PfdFreq(clock_pfd_t pfd);
bool rom_api_CLOCK_EnableUsbhs1PhyPllClock(clock_usb_phy_src_t src, uint32_t freq);
void rom_api_CLOCK_DisableUsbhs1PhyPllClock(void);
//-------------------------RTWDOG--------------------------------------------
void rom_api_RTWDOG_ClearStatusFlags(RTWDOG_Type *base, uint32_t mask);
void rom_api_RTWDOG_GetDefaultConfig(rtwdog_config_t *config);
void rom_api_RTWDOG_Init(RTWDOG_Type *base, const rtwdog_config_t *config);
void rom_api_RTWDOG_Deinit(RTWDOG_Type *base);
//-------------------------WDOG--------------------------------------------
void rom_api_WDOG_GetDefaultConfig(wdog_config_t *config);
void rom_api_WDOG_Init(WDOG_Type *base, const wdog_config_t *config);
void rom_api_WDOG_Deinit(WDOG_Type *base);
uint16_t rom_api_WDOG_GetStatusFlags(WDOG_Type *base);
void rom_api_WDOG_ClearInterruptStatus(WDOG_Type *base, uint16_t mask);
void rom_api_WDOG_Refresh(WDOG_Type *base);
//-------------------------FlexSPI NOR --------------------------------------------
status_t rom_api_flexspi_nor_flash_init(uint32_t instance, flexspi_nor_config_t *config);
status_t rom_api_flexspi_nor_flash_page_program(uint32_t instance, flexspi_nor_config_t *config, uint32_t dstAddr, const uint32_t *src);
status_t rom_api_flexspi_nor_flash_erase_all(uint32_t instance, flexspi_nor_config_t *config);
status_t rom_api_flexspi_nor_get_config(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option);
status_t rom_api_flexspi_nor_flash_erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length);
status_t rom_api_flexspi_nor_flash_read(uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes);
status_t rom_api_flexspi_update_lut(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq);
status_t rom_api_flexspi_command_xfer(uint32_t instance, flexspi_xfer_t *xfer);
void rom_api_flexspi_clear_cache(uint32_t instance);


#endif

