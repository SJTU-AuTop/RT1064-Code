#include "zf_vector.h"



#if (defined(__ICCARM__))

__weak void NMI_Handler1(void)
{
    while(1);
}

__weak void HardFault_Handler(void)
{
    while(1);
}
__weak void MemManage_Handler(void)
{
    while(1);
}
__weak void BusFault_Handler(void)
{
    while(1);
}
__weak void UsageFault_Handler(void)
{
    while(1);
}
__weak void SVC_Handler                    (void)
{
    while(1);
}
__weak void DebugMon_Handler               (void)
{
    while(1);
}
__weak void PendSV_Handler                 (void)
{
    while(1);
}
__weak void SysTick_Handler                (void)
{
    while(1);
}

__weak void DMA0_DMA16_IRQHandler          (void)
{
    DMA0_DMA16_DriverIRQHandler();
}
__weak void DMA1_DMA17_IRQHandler          (void)
{
    DMA1_DMA17_DriverIRQHandler();
}
__weak void DMA2_DMA18_IRQHandler          (void)
{
    DMA2_DMA18_DriverIRQHandler();
}
__weak void DMA3_DMA19_IRQHandler          (void)
{
    DMA3_DMA19_DriverIRQHandler();
}
__weak void DMA4_DMA20_IRQHandler          (void)
{
    DMA4_DMA20_DriverIRQHandler();
}
__weak void DMA5_DMA21_IRQHandler          (void)
{
    DMA5_DMA21_DriverIRQHandler();
}
__weak void DMA6_DMA22_IRQHandler          (void)
{
    DMA6_DMA22_DriverIRQHandler();
}
__weak void DMA7_DMA23_IRQHandler          (void)
{
    DMA7_DMA23_DriverIRQHandler();
}
__weak void DMA8_DMA24_IRQHandler          (void)
{
    DMA8_DMA24_DriverIRQHandler();
}
__weak void DMA9_DMA25_IRQHandler          (void)
{
    DMA9_DMA25_DriverIRQHandler();
}
__weak void DMA10_DMA26_IRQHandler         (void)
{
    DMA10_DMA26_DriverIRQHandler();
}
__weak void DMA11_DMA27_IRQHandler         (void)
{
    DMA11_DMA27_DriverIRQHandler();
}
__weak void DMA12_DMA28_IRQHandler         (void)
{
    DMA12_DMA28_DriverIRQHandler();
}
__weak void DMA13_DMA29_IRQHandler         (void)
{
    DMA13_DMA29_DriverIRQHandler();
}
__weak void DMA14_DMA30_IRQHandler         (void)
{
    DMA14_DMA30_DriverIRQHandler();
}
__weak void DMA15_DMA31_IRQHandler         (void)
{
    DMA15_DMA31_DriverIRQHandler();
}
__weak void DMA_ERROR_IRQHandler           (void)
{
    DMA_ERROR_DriverIRQHandler();
}
__weak void CTI0_ERROR_IRQHandler          (void)
{
    while(1);
}
__weak void CTI1_ERROR_IRQHandler          (void)
{
    while(1);
}
__weak void CORE_IRQHandler                (void)
{
    while(1);
}
__weak void LPUART1_IRQHandler             (void)
{
    LPUART1_DriverIRQHandler();
}
__weak void LPUART2_IRQHandler             (void)
{
    LPUART2_DriverIRQHandler();
}
__weak void LPUART3_IRQHandler             (void)
{
    LPUART3_DriverIRQHandler();
}
__weak void LPUART4_IRQHandler             (void)
{
    LPUART4_DriverIRQHandler();
}
__weak void LPUART5_IRQHandler             (void)
{
    LPUART5_DriverIRQHandler();
}
__weak void LPUART6_IRQHandler             (void)
{
    LPUART6_DriverIRQHandler();
}
__weak void LPUART7_IRQHandler             (void)
{
    LPUART7_DriverIRQHandler();
}
__weak void LPUART8_IRQHandler             (void)
{
    LPUART8_DriverIRQHandler();
}
__weak void LPI2C1_IRQHandler              (void)
{
    LPI2C1_DriverIRQHandler();
}
__weak void LPI2C2_IRQHandler              (void)
{
    LPI2C2_DriverIRQHandler();
}
__weak void LPI2C3_IRQHandler              (void)
{
    LPI2C3_DriverIRQHandler();
}
__weak void LPI2C4_IRQHandler              (void)
{
    LPI2C4_DriverIRQHandler();
}
__weak void LPSPI1_IRQHandler              (void)
{
    LPSPI1_DriverIRQHandler();
}
__weak void LPSPI2_IRQHandler              (void)
{
    LPSPI2_DriverIRQHandler();
}
__weak void LPSPI3_IRQHandler              (void)
{
    LPSPI3_DriverIRQHandler();
}
__weak void LPSPI4_IRQHandler              (void)
{
    LPSPI4_DriverIRQHandler();
}
__weak void CAN1_IRQHandler                (void)
{
    CAN1_DriverIRQHandler();
}
__weak void CAN2_IRQHandler                (void)
{
    CAN2_DriverIRQHandler();
}
__weak void FLEXRAM_IRQHandler             (void)
{
    while(1);
}
__weak void KPP_IRQHandler                 (void)
{
    while(1);
}
__weak void TSC_DIG_IRQHandler             (void)
{
    while(1);
}
__weak void GPR_IRQ_IRQHandler             (void)
{
    while(1);
}
__weak void LCDIF_IRQHandler               (void)
{
    while(1);
}
__weak void CSI_IRQHandler                 (void)
{
    while(1);
}
__weak void PXP_IRQHandler                 (void)
{
    while(1);
}
__weak void WDOG2_IRQHandler               (void)
{
    while(1);
}
__weak void SNVS_HP_WRAPPER_IRQHandler     (void)
{
    while(1);
}
__weak void SNVS_HP_WRAPPER_TZ_IRQHandler  (void)
{
    while(1);
}
__weak void SNVS_LP_WRAPPER_IRQHandler     (void)
{
    while(1);
}
__weak void CSU_IRQHandler                 (void)
{
    while(1);
}
__weak void DCP_IRQHandler                 (void)
{
    while(1);
}
__weak void DCP_VMI_IRQHandler             (void)
{
    while(1);
}
__weak void Reserved68_IRQHandler          (void)
{
    while(1);
}
__weak void TRNG_IRQHandler                (void)
{
    while(1);
}
__weak void SJC_IRQHandler                 (void)
{
    while(1);
}
__weak void BEE_IRQHandler                 (void)
{
    while(1);
}
__weak void SAI1_IRQHandler                (void)
{
    SAI1_DriverIRQHandler();
}
__weak void SAI2_IRQHandler                (void)
{
    SAI2_DriverIRQHandler();
}
__weak void SAI3_RX_IRQHandler             (void)
{
    SAI3_RX_DriverIRQHandler();
}
__weak void SAI3_TX_IRQHandler             (void)
{
    SAI3_TX_DriverIRQHandler();
}
__weak void SPDIF_IRQHandler               (void)
{
    SPDIF_DriverIRQHandler();
}
__weak void PMU_EVENT_IRQHandler           (void)
{
    while(1);
}
__weak void Reserved78_IRQHandler          (void)
{
    while(1);
}
__weak void TEMP_LOW_HIGH_IRQHandler       (void)
{
    while(1);
}
__weak void TEMP_PANIC_IRQHandler          (void)
{
    while(1);
}
__weak void USB_PHY1_IRQHandler            (void)
{
    while(1);
}
__weak void USB_PHY2_IRQHandler            (void)
{
    while(1);
}
__weak void ADC1_IRQHandler                (void)
{
    while(1);
}
__weak void ADC2_IRQHandler                (void)
{
    while(1);
}
__weak void DCDC_IRQHandler                (void)
{
    while(1);
}
__weak void Reserved86_IRQHandler          (void)
{
    while(1);
}
__weak void Reserved87_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT0_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT1_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT2_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT3_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT4_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT5_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT6_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_INT7_IRQHandler          (void)
{
    while(1);
}
__weak void GPIO1_Combined_0_15_IRQHandler (void)
{
    while(1);
}
__weak void GPIO1_Combined_16_31_IRQHandler(void)
{
    while(1);
}
__weak void GPIO2_Combined_0_15_IRQHandler (void)
{
    while(1);
}
__weak void GPIO2_Combined_16_31_IRQHandler(void)
{
    while(1);
}
__weak void GPIO3_Combined_0_15_IRQHandler (void)
{
    while(1);
}
__weak void GPIO3_Combined_16_31_IRQHandler(void)
{
    while(1);
}
__weak void GPIO4_Combined_0_15_IRQHandler (void)
{
    while(1);
}
__weak void GPIO4_Combined_16_31_IRQHandler(void)
{
    while(1);
}
__weak void GPIO5_Combined_0_15_IRQHandler (void)
{
    while(1);
}
__weak void GPIO5_Combined_16_31_IRQHandler(void)
{
    while(1);
}
__weak void FLEXIO1_IRQHandler             (void)
{
    FLEXIO1_DriverIRQHandler();
}
__weak void FLEXIO2_IRQHandler             (void)
{
    FLEXIO2_DriverIRQHandler();
}
__weak void WDOG1_IRQHandler               (void)
{
    while(1);
}
__weak void RTWDOG_IRQHandler              (void)
{
    while(1);
}
__weak void EWM_IRQHandler                 (void)
{
    while(1);
}
__weak void CCM_1_IRQHandler               (void)
{
    while(1);
}
__weak void CCM_2_IRQHandler               (void)
{
    while(1);
}
__weak void GPC_IRQHandler                 (void)
{
    while(1);
}
__weak void SRC_IRQHandler                 (void)
{
    while(1);
}
__weak void Reserved115_IRQHandler         (void)
{
    while(1);
}
__weak void GPT1_IRQHandler                (void)
{
    while(1);
}
__weak void GPT2_IRQHandler                (void)
{
    while(1);
}
__weak void PWM1_0_IRQHandler              (void)
{
    while(1);
}
__weak void PWM1_1_IRQHandler              (void)
{
    while(1);
}
__weak void PWM1_2_IRQHandler              (void)
{
    while(1);
}
__weak void PWM1_3_IRQHandler              (void)
{
    while(1);
}
__weak void PWM1_FAULT_IRQHandler          (void)
{
    while(1);
}
__weak void FLEXSPI2_IRQHandler            (void)
{
    FLEXSPI2_DriverIRQHandler();
}
__weak void FLEXSPI_IRQHandler             (void)
{
    FLEXSPI_DriverIRQHandler();
}
__weak void SEMC_IRQHandler                (void)
{
    while(1);
}
__weak void USDHC1_IRQHandler              (void)
{
    USDHC1_DriverIRQHandler();
}
__weak void USDHC2_IRQHandler              (void)
{
    USDHC2_DriverIRQHandler();
}
__weak void USB_OTG2_IRQHandler            (void)
{
    while(1);
}
__weak void USB_OTG1_IRQHandler            (void)
{
    while(1);
}
__weak void ENET_IRQHandler                (void)
{
    ENET_DriverIRQHandler();
}
__weak void ENET_1588_Timer_IRQHandler     (void)
{
    ENET_1588_Timer_DriverIRQHandler();
}
__weak void XBAR1_IRQ_0_1_IRQHandler       (void)
{
    while(1);
}
__weak void XBAR1_IRQ_2_3_IRQHandler       (void)
{
    while(1);
}
__weak void ADC_ETC_IRQ0_IRQHandler        (void)
{
    while(1);
}
__weak void ADC_ETC_IRQ1_IRQHandler        (void)
{
    while(1);
}
__weak void ADC_ETC_IRQ2_IRQHandler        (void)
{
    while(1);
}
__weak void ADC_ETC_ERROR_IRQ_IRQHandler   (void)
{
    while(1);
}
__weak void PIT_IRQHandler                 (void)
{
    while(1);
}
__weak void ACMP1_IRQHandler               (void)
{
    while(1);
}
__weak void ACMP2_IRQHandler               (void)
{
    while(1);
}
__weak void ACMP3_IRQHandler               (void)
{
    while(1);
}
__weak void ACMP4_IRQHandler               (void)
{
    while(1);
}
__weak void Reserved143_IRQHandler         (void)
{
    while(1);
}
__weak void Reserved144_IRQHandler         (void)
{
    while(1);
}
__weak void ENC1_IRQHandler                (void)
{
    while(1);
}
__weak void ENC2_IRQHandler                (void)
{
    while(1);
}
__weak void ENC3_IRQHandler                (void)
{
    while(1);
}
__weak void ENC4_IRQHandler                (void)
{
    while(1);
}
__weak void TMR1_IRQHandler                (void)
{
    while(1);
}
__weak void TMR2_IRQHandler                (void)
{
    while(1);
}
__weak void TMR3_IRQHandler                (void)
{
    while(1);
}
__weak void TMR4_IRQHandler                (void)
{
    while(1);
}
__weak void PWM2_0_IRQHandler              (void)
{
    while(1);
}
__weak void PWM2_1_IRQHandler              (void)
{
    while(1);
}
__weak void PWM2_2_IRQHandler              (void)
{
    while(1);
}
__weak void PWM2_3_IRQHandler              (void)
{
    while(1);
}
__weak void PWM2_FAULT_IRQHandler          (void)
{
    while(1);
}
__weak void PWM3_0_IRQHandler              (void)
{
    while(1);
}
__weak void PWM3_1_IRQHandler              (void)
{
    while(1);
}
__weak void PWM3_2_IRQHandler              (void)
{
    while(1);
}
__weak void PWM3_3_IRQHandler              (void)
{
    while(1);
}
__weak void PWM3_FAULT_IRQHandler          (void)
{
    while(1);
}
__weak void PWM4_0_IRQHandler              (void)
{
    while(1);
}
__weak void PWM4_1_IRQHandler              (void)
{
    while(1);
}
__weak void PWM4_2_IRQHandler              (void)
{
    while(1);
}
__weak void PWM4_3_IRQHandler              (void)
{
    while(1);
}
__weak void PWM4_FAULT_IRQHandler          (void)
{
    while(1);
}
__weak void ENET2_IRQHandler               (void)
{
    ENET2_DriverIRQHandler();
}
__weak void ENET2_1588_Timer_IRQHandler    (void)
{
    ENET2_1588_Timer_DriverIRQHandler();
}
__weak void CAN3_IRQHandler                (void)
{
    CAN3_DriverIRQHandler();
}
__weak void Reserved171_IRQHandler         (void)
{
    while(1);
}
__weak void FLEXIO3_IRQHandler             (void)
{
    FLEXIO3_DriverIRQHandler();
}
__weak void GPIO6_7_8_9_IRQHandler         (void)
{
    while(1);
}

//----------------------------------------------------------

//以下函数为SDK自带的中断驱动函数 对其进行弱定义

//----------------------------------------------------------
__weak void DMA0_DMA16_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA1_DMA17_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA2_DMA18_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA3_DMA19_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA4_DMA20_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA5_DMA21_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA6_DMA22_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA7_DMA23_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA8_DMA24_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA9_DMA25_DriverIRQHandler          (void)
{
    while(1);
}
__weak void DMA10_DMA26_DriverIRQHandler         (void)
{
    while(1);
}
__weak void DMA11_DMA27_DriverIRQHandler         (void)
{
    while(1);
}
__weak void DMA12_DMA28_DriverIRQHandler         (void)
{
    while(1);
}
__weak void DMA13_DMA29_DriverIRQHandler         (void)
{
    while(1);
}
__weak void DMA14_DMA30_DriverIRQHandler         (void)
{
    while(1);
}
__weak void DMA15_DMA31_DriverIRQHandler         (void)
{
    while(1);
}
__weak void DMA_ERROR_DriverIRQHandler           (void)
{
    while(1);
}
__weak void LPUART1_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPUART2_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPUART3_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPUART4_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPUART5_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPUART6_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPUART7_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPUART8_DriverIRQHandler             (void)
{
    while(1);
}
__weak void LPI2C1_DriverIRQHandler              (void)
{
    while(1);
}
__weak void LPI2C2_DriverIRQHandler              (void)
{
    while(1);
}
__weak void LPI2C3_DriverIRQHandler              (void)
{
    while(1);
}
__weak void LPI2C4_DriverIRQHandler              (void)
{
    while(1);
}
__weak void LPSPI1_DriverIRQHandler              (void)
{
    while(1);
}
__weak void LPSPI2_DriverIRQHandler              (void)
{
    while(1);
}
__weak void LPSPI3_DriverIRQHandler              (void)
{
    while(1);
}
__weak void LPSPI4_DriverIRQHandler              (void)
{
    while(1);
}
__weak void CAN1_DriverIRQHandler                (void)
{
    while(1);
}
__weak void CAN2_DriverIRQHandler                (void)
{
    while(1);
}
__weak void SAI1_DriverIRQHandler                (void)
{
    while(1);
}
__weak void SAI2_DriverIRQHandler                (void)
{
    while(1);
}
__weak void SAI3_RX_DriverIRQHandler             (void)
{
    while(1);
}
__weak void SAI3_TX_DriverIRQHandler             (void)
{
    while(1);
}
__weak void SPDIF_DriverIRQHandler               (void)
{
    while(1);
}
__weak void FLEXIO1_DriverIRQHandler             (void)
{
    while(1);
}
__weak void FLEXIO2_DriverIRQHandler             (void)
{
    while(1);
}
__weak void FLEXSPI2_DriverIRQHandler            (void)
{
    while(1);
}
__weak void FLEXSPI_DriverIRQHandler             (void)
{
    while(1);
}
__weak void USDHC1_DriverIRQHandler              (void)
{
    while(1);
}
__weak void USDHC2_DriverIRQHandler              (void)
{
    while(1);
}
__weak void ENET_DriverIRQHandler                (void)
{
    while(1);
}
__weak void ENET_1588_Timer_DriverIRQHandler     (void)
{
    while(1);
}
__weak void ENET2_DriverIRQHandler               (void)
{
    while(1);
}
__weak void ENET2_1588_Timer_DriverIRQHandler    (void)
{
    while(1);
}
__weak void CAN3_DriverIRQHandler                (void)
{
    while(1);
}
__weak void FLEXIO3_DriverIRQHandler             (void)
{
    while(1);
}







#pragma location = ".intvec"                    //指定 如下数组放入 intvec 段
const vector_entry __zf_vector_table[] = 
{
    (vector_entry)(__CSTACK_ADDRESS) ,
    Reset_Handler                  ,
    NMI_Handler                    ,
    HardFault_Handler              ,
    MemManage_Handler              ,
    BusFault_Handler               ,
    UsageFault_Handler             ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    SVC_Handler                    ,
    DebugMon_Handler               ,
    DefaultISR                     ,
    PendSV_Handler                 ,
    SysTick_Handler                ,
    //------------------------     ,
    DMA0_DMA16_IRQHandler          ,
    DMA1_DMA17_IRQHandler          ,
    DMA2_DMA18_IRQHandler          ,
    DMA3_DMA19_IRQHandler          ,
    DMA4_DMA20_IRQHandler          ,
    DMA5_DMA21_IRQHandler          ,
    DMA6_DMA22_IRQHandler          ,
    DMA7_DMA23_IRQHandler          ,
    DMA8_DMA24_IRQHandler          ,
    DMA9_DMA25_IRQHandler          ,
    DMA10_DMA26_IRQHandler         ,
    DMA11_DMA27_IRQHandler         ,
    DMA12_DMA28_IRQHandler         ,
    DMA13_DMA29_IRQHandler         ,
    DMA14_DMA30_IRQHandler         ,
    DMA15_DMA31_IRQHandler         ,
    DMA_ERROR_IRQHandler           ,
    CTI0_ERROR_IRQHandler          ,
    CTI1_ERROR_IRQHandler          ,
    CORE_IRQHandler                ,
    LPUART1_IRQHandler             ,
    LPUART2_IRQHandler             ,
    LPUART3_IRQHandler             ,
    LPUART4_IRQHandler             ,
    LPUART5_IRQHandler             ,
    LPUART6_IRQHandler             ,
    LPUART7_IRQHandler             ,
    LPUART8_IRQHandler             ,
    LPI2C1_IRQHandler              ,
    LPI2C2_IRQHandler              ,
    LPI2C3_IRQHandler              ,
    LPI2C4_IRQHandler              ,
    LPSPI1_IRQHandler              ,
    LPSPI2_IRQHandler              ,
    LPSPI3_IRQHandler              ,
    LPSPI4_IRQHandler              ,
    CAN1_IRQHandler                ,
    CAN2_IRQHandler                ,
    FLEXRAM_IRQHandler             ,
    KPP_IRQHandler                 ,
    TSC_DIG_IRQHandler             ,
    GPR_IRQ_IRQHandler             ,
    LCDIF_IRQHandler               ,
    CSI_IRQHandler                 ,
    PXP_IRQHandler                 ,
    WDOG2_IRQHandler               ,
    SNVS_HP_WRAPPER_IRQHandler     ,
    SNVS_HP_WRAPPER_TZ_IRQHandler  ,
    SNVS_LP_WRAPPER_IRQHandler     ,
    CSU_IRQHandler                 ,
    DCP_IRQHandler                 ,
    DCP_VMI_IRQHandler             ,
    Reserved68_IRQHandler          ,
    TRNG_IRQHandler                ,
    SJC_IRQHandler                 ,
    BEE_IRQHandler                 ,
    SAI1_IRQHandler                ,
    SAI2_IRQHandler                ,
    SAI3_RX_IRQHandler             ,
    SAI3_TX_IRQHandler             ,
    SPDIF_IRQHandler               ,
    PMU_EVENT_IRQHandler           ,
    Reserved78_IRQHandler          ,
    TEMP_LOW_HIGH_IRQHandler       ,
    TEMP_PANIC_IRQHandler          ,
    USB_PHY1_IRQHandler            ,
    USB_PHY2_IRQHandler            ,
    ADC1_IRQHandler                ,
    ADC2_IRQHandler                ,
    DCDC_IRQHandler                ,
    Reserved86_IRQHandler          ,
    Reserved87_IRQHandler          ,
    GPIO1_INT0_IRQHandler          ,
    GPIO1_INT1_IRQHandler          ,
    GPIO1_INT2_IRQHandler          ,
    GPIO1_INT3_IRQHandler          ,
    GPIO1_INT4_IRQHandler          ,
    GPIO1_INT5_IRQHandler          ,
    GPIO1_INT6_IRQHandler          ,
    GPIO1_INT7_IRQHandler          ,
    GPIO1_Combined_0_15_IRQHandler ,
    GPIO1_Combined_16_31_IRQHandler,
    GPIO2_Combined_0_15_IRQHandler ,
    GPIO2_Combined_16_31_IRQHandler,
    GPIO3_Combined_0_15_IRQHandler ,
    GPIO3_Combined_16_31_IRQHandler,
    GPIO4_Combined_0_15_IRQHandler ,
    GPIO4_Combined_16_31_IRQHandler,
    GPIO5_Combined_0_15_IRQHandler ,
    GPIO5_Combined_16_31_IRQHandler,
    FLEXIO1_IRQHandler             ,
    FLEXIO2_IRQHandler             ,
    WDOG1_IRQHandler               ,
    RTWDOG_IRQHandler              ,
    EWM_IRQHandler                 ,
    CCM_1_IRQHandler               ,
    CCM_2_IRQHandler               ,
    GPC_IRQHandler                 ,
    SRC_IRQHandler                 ,
    Reserved115_IRQHandler         ,
    GPT1_IRQHandler                ,
    GPT2_IRQHandler                ,
    PWM1_0_IRQHandler              ,
    PWM1_1_IRQHandler              ,
    PWM1_2_IRQHandler              ,
    PWM1_3_IRQHandler              ,
    PWM1_FAULT_IRQHandler          ,
    FLEXSPI2_IRQHandler            ,
    FLEXSPI_IRQHandler             ,
    SEMC_IRQHandler                ,
    USDHC1_IRQHandler              ,
    USDHC2_IRQHandler              ,
    USB_OTG2_IRQHandler            ,
    USB_OTG1_IRQHandler            ,
    ENET_IRQHandler                ,
    ENET_1588_Timer_IRQHandler     ,
    XBAR1_IRQ_0_1_IRQHandler       ,
    XBAR1_IRQ_2_3_IRQHandler       ,
    ADC_ETC_IRQ0_IRQHandler        ,
    ADC_ETC_IRQ1_IRQHandler        ,
    ADC_ETC_IRQ2_IRQHandler        ,
    ADC_ETC_ERROR_IRQ_IRQHandler   ,
    PIT_IRQHandler                 ,
    ACMP1_IRQHandler               ,
    ACMP2_IRQHandler               ,
    ACMP3_IRQHandler               ,
    ACMP4_IRQHandler               ,
    Reserved143_IRQHandler         ,
    Reserved144_IRQHandler         ,
    ENC1_IRQHandler                ,
    ENC2_IRQHandler                ,
    ENC3_IRQHandler                ,
    ENC4_IRQHandler                ,
    TMR1_IRQHandler                ,
    TMR2_IRQHandler                ,
    TMR3_IRQHandler                ,
    TMR4_IRQHandler                ,
    PWM2_0_IRQHandler              ,
    PWM2_1_IRQHandler              ,
    PWM2_2_IRQHandler              ,
    PWM2_3_IRQHandler              ,
    PWM2_FAULT_IRQHandler          ,
    PWM3_0_IRQHandler              ,
    PWM3_1_IRQHandler              ,
    PWM3_2_IRQHandler              ,
    PWM3_3_IRQHandler              ,
    PWM3_FAULT_IRQHandler          ,
    PWM4_0_IRQHandler              ,
    PWM4_1_IRQHandler              ,
    PWM4_2_IRQHandler              ,
    PWM4_3_IRQHandler              ,
    PWM4_FAULT_IRQHandler          ,
    ENET2_IRQHandler               ,
    ENET2_1588_Timer_IRQHandler    ,
    CAN3_IRQHandler                ,
    Reserved171_IRQHandler         ,
    FLEXIO3_IRQHandler             ,
    GPIO6_7_8_9_IRQHandler         ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    DefaultISR                     ,
    (vector_entry)0xFFFFFFFF       ,
};
    
    
#endif
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    