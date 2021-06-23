#ifndef _zf_vector_H
#define _zf_vector_H

#include "common.h"

#if (defined(__ICCARM__))
typedef void (*vector_entry)(void);         //定义中断向量表的函数类型

extern const vector_entry __zf_vector_table[];



extern unsigned int __CSTACK_ADDRESS[];     //声明栈地址，从linker文件（*.icf ）获得
extern void Reset_Handler(void);            //声明复位函数，在 .s 文件里定义
extern void DefaultISR(void);               //定义默认中断服务函数
void NMI_Handler                    (void);
void HardFault_Handler              (void);
void MemManage_Handler              (void);
void BusFault_Handler               (void);
void UsageFault_Handler             (void);




void SVC_Handler                    (void);
void DebugMon_Handler               (void);

void PendSV_Handler                 (void);
void SysTick_Handler                (void);
//-----------------------------------------
void DMA0_DMA16_DriverIRQHandler          (void);
void DMA1_DMA17_DriverIRQHandler          (void);
void DMA2_DMA18_DriverIRQHandler          (void);
void DMA3_DMA19_DriverIRQHandler          (void);
void DMA4_DMA20_DriverIRQHandler          (void);
void DMA5_DMA21_DriverIRQHandler          (void);
void DMA6_DMA22_DriverIRQHandler          (void);
void DMA7_DMA23_DriverIRQHandler          (void);
void DMA8_DMA24_DriverIRQHandler          (void);
void DMA9_DMA25_DriverIRQHandler          (void);
void DMA10_DMA26_DriverIRQHandler         (void);
void DMA11_DMA27_DriverIRQHandler         (void);
void DMA12_DMA28_DriverIRQHandler         (void);
void DMA13_DMA29_DriverIRQHandler         (void);
void DMA14_DMA30_DriverIRQHandler         (void);
void DMA15_DMA31_DriverIRQHandler         (void);
void DMA_ERROR_DriverIRQHandler           (void);


void LPUART1_DriverIRQHandler             (void);
void LPUART2_DriverIRQHandler             (void);
void LPUART3_DriverIRQHandler             (void);
void LPUART4_DriverIRQHandler             (void);
void LPUART5_DriverIRQHandler             (void);
void LPUART6_DriverIRQHandler             (void);
void LPUART7_DriverIRQHandler             (void);
void LPUART8_DriverIRQHandler             (void);
void LPI2C1_DriverIRQHandler              (void);
void LPI2C2_DriverIRQHandler              (void);
void LPI2C3_DriverIRQHandler              (void);
void LPI2C4_DriverIRQHandler              (void);
void LPSPI1_DriverIRQHandler              (void);
void LPSPI2_DriverIRQHandler              (void);
void LPSPI3_DriverIRQHandler              (void);
void LPSPI4_DriverIRQHandler              (void);
void CAN1_DriverIRQHandler                (void);
void CAN2_DriverIRQHandler                (void);

void SAI1_DriverIRQHandler                (void);
void SAI2_DriverIRQHandler                (void);
void SAI3_RX_DriverIRQHandler             (void);
void SAI3_TX_DriverIRQHandler             (void);
void SPDIF_DriverIRQHandler               (void);

void FLEXIO1_DriverIRQHandler             (void);
void FLEXIO2_DriverIRQHandler             (void);

void FLEXSPI2_DriverIRQHandler            (void);
void FLEXSPI_DriverIRQHandler             (void);

void USDHC1_DriverIRQHandler              (void);
void USDHC2_DriverIRQHandler              (void);

void ENET_DriverIRQHandler                (void);
void ENET_1588_Timer_DriverIRQHandler     (void);

void ENET2_DriverIRQHandler               (void);
void ENET2_1588_Timer_DriverIRQHandler    (void);
void CAN3_DriverIRQHandler                (void);

void FLEXIO3_DriverIRQHandler             (void);



void DMA0_DMA16_IRQHandler          (void);
void DMA1_DMA17_IRQHandler          (void);
void DMA2_DMA18_IRQHandler          (void);
void DMA3_DMA19_IRQHandler          (void);
void DMA4_DMA20_IRQHandler          (void);
void DMA5_DMA21_IRQHandler          (void);
void DMA6_DMA22_IRQHandler          (void);
void DMA7_DMA23_IRQHandler          (void);
void DMA8_DMA24_IRQHandler          (void);
void DMA9_DMA25_IRQHandler          (void);
void DMA10_DMA26_IRQHandler         (void);
void DMA11_DMA27_IRQHandler         (void);
void DMA12_DMA28_IRQHandler         (void);
void DMA13_DMA29_IRQHandler         (void);
void DMA14_DMA30_IRQHandler         (void);
void DMA15_DMA31_IRQHandler         (void);
void DMA_ERROR_IRQHandler           (void);
void CTI0_ERROR_IRQHandler          (void);
void CTI1_ERROR_IRQHandler          (void);
void CORE_IRQHandler                (void);
void LPUART1_IRQHandler             (void);
void LPUART2_IRQHandler             (void);
void LPUART3_IRQHandler             (void);
void LPUART4_IRQHandler             (void);
void LPUART5_IRQHandler             (void);
void LPUART6_IRQHandler             (void);
void LPUART7_IRQHandler             (void);
void LPUART8_IRQHandler             (void);
void LPI2C1_IRQHandler              (void);
void LPI2C2_IRQHandler              (void);
void LPI2C3_IRQHandler              (void);
void LPI2C4_IRQHandler              (void);
void LPSPI1_IRQHandler              (void);
void LPSPI2_IRQHandler              (void);
void LPSPI3_IRQHandler              (void);
void LPSPI4_IRQHandler              (void);
void CAN1_IRQHandler                (void);
void CAN2_IRQHandler                (void);
void FLEXRAM_IRQHandler             (void);
void KPP_IRQHandler                 (void);
void TSC_DIG_IRQHandler             (void);
void GPR_IRQ_IRQHandler             (void);
void LCDIF_IRQHandler               (void);
void CSI_IRQHandler                 (void);
void PXP_IRQHandler                 (void);
void WDOG2_IRQHandler               (void);
void SNVS_HP_WRAPPER_IRQHandler     (void);
void SNVS_HP_WRAPPER_TZ_IRQHandler  (void);
void SNVS_LP_WRAPPER_IRQHandler     (void);
void CSU_IRQHandler                 (void);
void DCP_IRQHandler                 (void);
void DCP_VMI_IRQHandler             (void);
void Reserved68_IRQHandler          (void);
void TRNG_IRQHandler                (void);
void SJC_IRQHandler                 (void);
void BEE_IRQHandler                 (void);
void SAI1_IRQHandler                (void);
void SAI2_IRQHandler                (void);
void SAI3_RX_IRQHandler             (void);
void SAI3_TX_IRQHandler             (void);
void SPDIF_IRQHandler               (void);
void PMU_EVENT_IRQHandler           (void);
void Reserved78_IRQHandler          (void);
void TEMP_LOW_HIGH_IRQHandler       (void);
void TEMP_PANIC_IRQHandler          (void);
void USB_PHY1_IRQHandler            (void);
void USB_PHY2_IRQHandler            (void);
void ADC1_IRQHandler                (void);
void ADC2_IRQHandler                (void);
void DCDC_IRQHandler                (void);
void Reserved86_IRQHandler          (void);
void Reserved87_IRQHandler          (void);
void GPIO1_INT0_IRQHandler          (void);
void GPIO1_INT1_IRQHandler          (void);
void GPIO1_INT2_IRQHandler          (void);
void GPIO1_INT3_IRQHandler          (void);
void GPIO1_INT4_IRQHandler          (void);
void GPIO1_INT5_IRQHandler          (void);
void GPIO1_INT6_IRQHandler          (void);
void GPIO1_INT7_IRQHandler          (void);
void GPIO1_Combined_0_15_IRQHandler (void);
void GPIO1_Combined_16_31_IRQHandler(void);
void GPIO2_Combined_0_15_IRQHandler (void);
void GPIO2_Combined_16_31_IRQHandler(void);
void GPIO3_Combined_0_15_IRQHandler (void);
void GPIO3_Combined_16_31_IRQHandler(void);
void GPIO4_Combined_0_15_IRQHandler (void);
void GPIO4_Combined_16_31_IRQHandler(void);
void GPIO5_Combined_0_15_IRQHandler (void);
void GPIO5_Combined_16_31_IRQHandler(void);
void FLEXIO1_IRQHandler             (void);
void FLEXIO2_IRQHandler             (void);
void WDOG1_IRQHandler               (void);
void RTWDOG_IRQHandler              (void);
void EWM_IRQHandler                 (void);
void CCM_1_IRQHandler               (void);
void CCM_2_IRQHandler               (void);
void GPC_IRQHandler                 (void);
void SRC_IRQHandler                 (void);
void Reserved115_IRQHandler         (void);
void GPT1_IRQHandler                (void);
void GPT2_IRQHandler                (void);
void PWM1_0_IRQHandler              (void);
void PWM1_1_IRQHandler              (void);
void PWM1_2_IRQHandler              (void);
void PWM1_3_IRQHandler              (void);
void PWM1_FAULT_IRQHandler          (void);
void FLEXSPI2_IRQHandler            (void);
void FLEXSPI_IRQHandler             (void);
void SEMC_IRQHandler                (void);
void USDHC1_IRQHandler              (void);
void USDHC2_IRQHandler              (void);
void USB_OTG2_IRQHandler            (void);
void USB_OTG1_IRQHandler            (void);
void ENET_IRQHandler                (void);
void ENET_1588_Timer_IRQHandler     (void);
void XBAR1_IRQ_0_1_IRQHandler       (void);
void XBAR1_IRQ_2_3_IRQHandler       (void);
void ADC_ETC_IRQ0_IRQHandler        (void);
void ADC_ETC_IRQ1_IRQHandler        (void);
void ADC_ETC_IRQ2_IRQHandler        (void);
void ADC_ETC_ERROR_IRQ_IRQHandler   (void);
void PIT_IRQHandler                 (void);
void ACMP1_IRQHandler               (void);
void ACMP2_IRQHandler               (void);
void ACMP3_IRQHandler               (void);
void ACMP4_IRQHandler               (void);
void Reserved143_IRQHandler         (void);
void Reserved144_IRQHandler         (void);
void ENC1_IRQHandler                (void);
void ENC2_IRQHandler                (void);
void ENC3_IRQHandler                (void);
void ENC4_IRQHandler                (void);
void TMR1_IRQHandler                (void);
void TMR2_IRQHandler                (void);
void TMR3_IRQHandler                (void);
void TMR4_IRQHandler                (void);
void PWM2_0_IRQHandler              (void);
void PWM2_1_IRQHandler              (void);
void PWM2_2_IRQHandler              (void);
void PWM2_3_IRQHandler              (void);
void PWM2_FAULT_IRQHandler          (void);
void PWM3_0_IRQHandler              (void);
void PWM3_1_IRQHandler              (void);
void PWM3_2_IRQHandler              (void);
void PWM3_3_IRQHandler              (void);
void PWM3_FAULT_IRQHandler          (void);
void PWM4_0_IRQHandler              (void);
void PWM4_1_IRQHandler              (void);
void PWM4_2_IRQHandler              (void);
void PWM4_3_IRQHandler              (void);
void PWM4_FAULT_IRQHandler          (void);
void ENET2_IRQHandler               (void);
void ENET2_1588_Timer_IRQHandler    (void);
void CAN3_IRQHandler                (void);
void Reserved171_IRQHandler         (void);
void FLEXIO3_IRQHandler             (void);
void GPIO6_7_8_9_IRQHandler         (void);





#endif

#endif

