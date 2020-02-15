#ifndef BATTERY_H
#define BATTERY_H

#include "stdint-gcc.h"

//constants
#define BATTERY_VREF 2.56
#define BATTERY_ADC_VMAX 800 //2V * 2 = 4V
#define BATTERY_ADC_VMIN 540 //1.35V * 2 = 2.7V
#define BATTERY_ADC_CHANNEL 0
#define BATTERY_ADC_SAMPLES 10

//macros
#define ADC_START_CONVERSION ADCSRA |= (1 << ADSC)
#define ADC_WAIT while(ADCSRA & (1 << ADSC))
#define ADC_SAMPLE ((uint16_t)((ADCH << 8) | (ADCL)))

void BATTERY_AdcInit();
uint8_t BATTERY_GetPercentage();

#endif