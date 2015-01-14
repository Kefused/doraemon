#define F_CPU 8000000UL 

#include "flash.h"
#include "swspi.h"

#include <util/delay.h>
#include <avr/io.h>


void flash_config() {
	spi_config();
	DDRA |= (1 << 4); // set FLASH_CS as output
	flash_unselect();
	_delay_ms(40);
}

void flash_select() {
	PORTA &= ~(1 << 4);
}

void flash_unselect() {
	PORTA |= (1 << 4);
}

void flash_start_read(uint16_t page, uint16_t offset) {
	flash_select();
	spi_transfer(0x03);
	spi_transfer((uint8_t)(page >> 6));
	spi_transfer((uint8_t)(((page & 0x3f) << 2) + (offset >> 8)));
	spi_transfer((uint8_t)(offset & 0xff));
}

uint8_t flash_read() {
	return spi_transfer(0x00);
}

void flash_stop_read() {
	flash_unselect();
}

void flash_buffer_start_write(uint16_t offset) {
	flash_select();
	spi_transfer(0x84);
	spi_transfer(0x00);
	spi_transfer((uint8_t)(offset >> 8));
	spi_transfer((uint8_t)(offset & 0xff));
}

void flash_buffer_write(uint8_t data) {
	spi_transfer(data);
}

void flash_buffer_stop_write() {
	flash_unselect();
}

void flash_buffer_flush(uint16_t page) {
	flash_select();
	spi_transfer(0x83);
	spi_transfer((uint8_t)(page >> 6));
	spi_transfer((uint8_t)((page & 0x3f) << 2));
	spi_transfer(0x00);
	flash_unselect();
	_delay_ms(40);
}

uint8_t flash_test() {
	uint8_t result;

	flash_select();
	spi_transfer(0xD7);
	result = spi_transfer(0x00);
	flash_unselect();
	if ( (result & (1 << 7)) && (result & (1 << 5)) && ((result & (1 << 4)) == 0) )
		return 1;
	return 0;
}