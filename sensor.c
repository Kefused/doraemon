#define F_CPU 8000000UL 

#include "sensor.h"

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


/*
Filter configuration
 */
#define SIZE 60
#define DELTA 100


void sensor_config() {
	/*
	ADC configration
	 */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // prescaler = 64 -> f=125 kHz
	ADMUX  |= 0b110; // Select ADC6 (PA7)
	ADCSRA |= (1 << ADATE); // Auto retrigger
	ADCSRA |= (1 << ADEN); // Enabling
	ADCSRA |= (1 << ADSC); // Starting convertions, free running mode
}

void sensor_wait() {
	uint16_t voltage, noise_floor;
	uint16_t moving_average = 0;
	uint16_t old_values[SIZE] = {0};
	uint8_t k = 0;
	uint16_t i;

	/*
	Noise floor calculation
	 */
	for (i=0; i<SIZE*10; i++) {
		voltage  = ADCL;
		voltage |= (ADCH << 8);
		moving_average = moving_average + voltage - old_values[k];
		old_values[k] = voltage;
		k++;
		if (k == SIZE)
			k = 0;
		_delay_ms(1);
	}
	noise_floor = moving_average;


	/*
	Waiting for event detection
	 */
	for (;;) {
		voltage  = ADCL;
		voltage |= (ADCH << 8);
		moving_average = moving_average + voltage - old_values[k];
		old_values[k] = voltage;
		k++;
		if (k == SIZE)
			k = 0;
		_delay_ms(1);

		if (abs((int32_t)moving_average - (int32_t)noise_floor) > DELTA)
			break;
	}
}
