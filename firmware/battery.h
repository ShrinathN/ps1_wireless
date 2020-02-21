#ifndef BATTERY_H
#define BATTERY_H

#include "main.h"

//constants
#define BATTERY_VREF 2.56
#define BATTERY_ADC_VMAX 400 //4V * 100 = 400
#define BATTERY_ADC_VMIN 280 //2.8V * 100 = 280
#define BATTERY_ADC_BANDGAP_VOLTAGE 130 //1.3V * 100
#define BATTERY_ADC_SAMPLES 10
#define BATTERY_SAMPLE_TIMER_THRESHOLD 0xFFFF

//macros
#define ADC_START_CONVERSION ADCSRA |= (1 << ADSC)
#define ADC_WAIT while(ADCSRA & (1 << ADSC))
#define ADC_SAMPLE ((uint16_t)((ADCL)) | (ADCH << 8))

void BATTERY_AdcInit();
uint8_t BATTERY_GetPercentage();
uint16_t BATTERY_GetAdcRaw();

#endif