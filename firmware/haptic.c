#define F_CPU 8000000UL 

#include "haptic.h"

#include <util/delay.h>
#include <avr/io.h>


void haptic_config() {
	DDRB |= (1 << 3); // Set MOTOR_CTRL as output

	/*
	PWM TIMER1 port setup 
	 */
	DDRB |= (1 << 5); // Output
	TCCR1A |= (1 << COM1B1) | (1 << PWM1B); // OC1B pin connected, PWM activated
	TCCR1D &= ~((1 << WGM11) | (1 << WGM10)); // Fast PWM mode
	OCR1C = 0xff; // Top value
	OCR1B = 0; // Counter value
	TCCR1B |= (1 << CS10); // Start the PWM, 15khz
}

void haptic_pulse() {
	uint8_t f;

	for(f=0; f<255; f++) {
		OCR1B = f;
		_delay_ms(1);
	}
	OCR1B = 255;
	_delay_ms(80);
	for(f=255; f>0; f--) {
		OCR1B = f;
		_delay_ms(1);
	}
	OCR1B = 0;
}