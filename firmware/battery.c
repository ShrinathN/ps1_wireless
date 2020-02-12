#include "battery.h"
#include "avr/io.h"


void BATTERY_AdcInit()
{
	//internal 2.56v Vref, channel0
	ADMUX |= (1 << REFS1) | (1 << REFS0) | BATTERY_ADC_CHANNEL;
}

uint8_t BATTERY_GetPercentage()
{
	uint16_t voltage_accumulator;
	//enabling ADC
	ADCSRA |= (1 << ADEN);
	for(uint8_t i = 0, voltage_accumulator = 0; i < BATTERY_ADC_SAMPLES; i++)
	{
		ADC_START_CONVERSION;
		ADC_WAIT;
		voltage_accumulator += ADC_SAMPLE;
	}
	voltage_accumulator /= BATTERY_ADC_SAMPLES;
}