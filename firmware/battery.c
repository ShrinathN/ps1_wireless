#include "battery.h"


void BATTERY_AdcInit()
{
	//using internal bandgap (1.3V in atmega8a) as the input and Vcc as Vref
	ADMUX = (1 << REFS0) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

/*
 * Will return the battery percentage
 *
 * Simple voltage measurement, will return a value between 0 to 100 for 2.7V to 4.0V respectively
 * @return (uint8_t)the battery voltage in a range of 0 to 100
*/
uint8_t BATTERY_GetPercentage()
{
	uint32_t voltage_accumulator, voltage_real, voltage_percentage;
	for(uint8_t i = 0, voltage_accumulator = 0; i < BATTERY_ADC_SAMPLES; i++)
	{
		voltage_accumulator += BATTERY_GetAdcRaw();
	}
	voltage_accumulator /= BATTERY_ADC_SAMPLES;
	voltage_real = ((133120) / BATTERY_GetAdcRaw()); //(1024 * 1.3) * 100, 100 is only for convenience
	voltage_percentage = ((voltage_real - BATTERY_ADC_VMIN) * 100) / (BATTERY_ADC_VMAX - BATTERY_ADC_VMIN);
	return (uint8_t)voltage_percentage;
}

uint16_t BATTERY_GetAdcRaw()
{
	ADC_START_CONVERSION;
	ADC_WAIT;
	return ADC_SAMPLE;
}