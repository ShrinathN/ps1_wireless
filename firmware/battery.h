#ifndef BATTERY_H
#define BATTERY_H

//constants
#define BATTERY_VREF 2.56
#define BATTERY_ADC_VMAX 2.1 //this voltage is through the voltage divider
#define BATTERY_ADC_VMIN 1.4 //this voltage is through the voltage divider
#define BATTERY_ADC_CHANNEL 0
#define BATTERY_ADC_SAMPLES 10

//macros
#define ADC_START_CONVERSION ADCSRA |= (1 << ADSC)
#define ADC_WAIT while(ADCSRA & (1 << ADSC))
#define ADC_SAMPLE ((uint16_t)((ADCH << 8) | (ADCL)))

void BATTERY_AdcInit();
uint8_t BATTERY_GetPercentage();

#endif