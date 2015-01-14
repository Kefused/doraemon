#define F_CPU 8000000UL 

#include "speaker.h"
#include "flash.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void speaker_config() {
	flash_config();

	DDRB |= (1 << 4); // Set SPEAKER_CRTL as output
	PORTB |= (1 << 4); //Sound is off

	/*
	PWM TIMER1 port setup 
	 */
	DDRB |= (1 << 5); // Output
	TCCR1C |= (1 << COM1D1) | (1 << PWM1D); // OC1D pin connected, PWM activated
	TCCR1D &= ~((1 << WGM11) | (1 << WGM10)); // Fast PWM mode
	OCR1C = 0xff; // Top value
	OCR1D = 0; // Counter value
	TCCR1B |= (1 << CS10); // Start the PWM, 15khz

	/*
	8kHz TIMER0 interrupt setup
	 */
	TCCR0B |= (1 << CS01); // Prescaler = 8
	OCR0A = 125; // Top value
	TCCR0A |= (1 << WGM00); // Clear timer on compare match
	TIMSK |= (1 << OCIE0A); // Enable the interrupt

}

volatile uint32_t to_play;
volatile uint8_t playback_end;
void speaker_read_flash(uint16_t page, uint16_t offset, uint32_t duration) {
	/*
	Initialize interrupt variables 
	 */
	to_play = duration;
	playback_end = 0;
	
	/*
	Start reading the flash memory at the given position
	 */
	flash_start_read(page, offset);

	/*
	Manage the playback
	 */
	PORTB &= ~(1 << 4); // Sound is on
	sei();
	while(!playback_end); // Wait until the end of the playback
	cli();
	PORTB |= (1 << 4); // Sound is off
	flash_stop_read();
}

ISR(TIMER0_COMPA_vect) {
	if(to_play != 0) {
		OCR1D = flash_read();
		to_play--;
	} else {
		playback_end = 1;
	}
}


void speaker_debug(uint16_t duration) {
	uint16_t i;

	cli();
	TCCR1C &= ~((1 << COM1D1) | (1 << PWM1D));
	TCCR1B &= ~(1 << CS10); // Stop the PWM

	PORTB &= ~(1 << 4); // Sound is on
	for(i=0; i<duration; i++) {
		PORTB |= (1 << 5);
		_delay_us(500);
		PORTB &= ~(1 << 5);
		_delay_us(500);
	}
	for(i=0; i<duration; i++) {
		PORTB |= (1 << 5);
		_delay_us(200);
		PORTB &= ~(1 << 5);
		_delay_us(200);
	}

	PORTB |= (1 << 4); //Sound is off
}
