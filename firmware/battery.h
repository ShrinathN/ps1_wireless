#ifndef BATTERY_H
#define BATTERY_H

#include "main.h"

//constants
#define BATTERY_VREF 2.56
#define BATTERY_ADC_VMAX 400 //4V
#define BATTERY_ADC_VMIN 270 //2.7V
#define BATTERY_ADC_BANDGAP_VOLTAGE 130 //1.3V * 100
#define BATTERY_ADC_SAMPLES 10

//macros
#define ADC_START_CONVERSION ADCSRA |= (1 << ADSC)
#define ADC_WAIT while(ADCSRA & (1 << ADSC))
#define ADC_SAMPLE ((uint16_t)((ADCL)) | (ADCH << 8))

void BATTERY_AdcInit();
uint8_t BATTERY_GetPercentage();
uint16_t BATTERY_GetAdcRaw();

#endif