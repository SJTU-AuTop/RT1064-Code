#include "elec.h"

#define ADC_CH1			ADC1_CH3_B14
#define ADC_CH2			ADC1_CH4_B15
#define ADC_CH3			ADC1_CH10_B21
#define ADC_CH4			ADC1_CH12_B23

void elec_init(void)
{
    adc_init(ADC_1, ADC_CH1, ADC_10BIT);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_1, ADC_CH2, ADC_10BIT);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_1, ADC_CH3, ADC_10BIT);    // 初始化 ADC 已经对应通道引脚 10位精度
	adc_init(ADC_1, ADC_CH4, ADC_10BIT);    // 初始化 ADC 已经对应通道引脚 10位精度
}

uint16 elec_data[4];
void elec_get(void)
{
    elec_data[0] = adc_convert(ADC_1, ADC_CH1);
    elec_data[1] = adc_convert(ADC_1, ADC_CH2);
    elec_data[2] = adc_convert(ADC_1, ADC_CH3);
    elec_data[3] = adc_convert(ADC_1, ADC_CH4);
    
}

void elec_calculate(void)
{
    
}