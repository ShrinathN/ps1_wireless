#include "battery.h"
#include "avr/io.h"


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
	uint32_t voltage_accumulator;
	for(uint8_t i = 0, voltage_accumulator = 0; i < BATTERY_ADC_SAMPLES; i++)
	{
		ADC_START_CONVERSION;
		ADC_WAIT;
		voltage_accumulator += ADC_SAMPLE;
	}
	voltage_accumulator /= BATTERY_ADC_SAMPLES;
	float battery_voltage = (BATTERY_ADC_BANDGAP_VOLTAGE * 1024) / voltage_accumulator;
	float float_percent = ((battery_voltage - BATTERY_ADC_VMIN) / (BATTERY_ADC_VMAX - BATTERY_ADC_VMIN));
	float_percent *= 100;
	return (uint8_t)(float_percent);
}

uint16_t BATTERY_GetAdcRaw()
{
	ADC_START_CONVERSION;
	ADC_WAIT;
	return (uint16_t)(ADC_SAMPLE);
}