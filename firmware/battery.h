#ifndef BATTERY_H
#define BATTERY_H

#include "stdint-gcc.h"

//constants
#define BATTERY_VREF 2.56
#define BATTERY_ADC_VMAX 4.0
#define BATTERY_ADC_VMIN 2.7
#define BATTERY_ADC_BANDGAP_VOLTAGE 1.3
#define BATTERY_ADC_SAMPLES 10

//macros
#define ADC_START_CONVERSION ADCSRA |= (1 << ADSC)
#define ADC_WAIT while(ADCSRA & (1 << ADSC))
#define ADC_SAMPLE ((uint16_t)((ADCH << 8) | (ADCL)))

void BATTERY_AdcInit();
uint8_t BATTERY_GetPercentage();
uint16_t BATTERY_GetAdcRaw();

#endif