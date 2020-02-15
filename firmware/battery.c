#include "battery.h"
#include "avr/io.h"


void BATTERY_AdcInit()
{
	//internal 2.56v Vref, channel0
	ADMUX |= (1 << REFS1) | (1 << REFS0) | BATTERY_ADC_CHANNEL;
}

/*
 * Will return the battery percentage
 *
 * Simple voltage measurement, will return a value between 0 to 100 for 2.7V to 4.0V respectively
 * @return (uint8_t)the battery voltage in a range of 0 to 100
*/
uint8_t BATTERY_GetPercentage()
{
	uint32_t voltage_accumulator;
	//enabling ADC
	ADCSRA |= (1 << ADEN);
	for(uint8_t i = 0, voltage_accumulator = 0; i < BATTERY_ADC_SAMPLES; i++)
	{
		ADC_START_CONVERSION;
		ADC_WAIT;
		voltage_accumulator += ADC_SAMPLE;
	}
	voltage_accumulator /= BATTERY_ADC_SAMPLES;
	return (((uint16_t)((voltage_accumulator - BATTERY_ADC_VMIN) * 100)) / (BATTERY_ADC_VMAX - BATTERY_ADC_VMIN));
}