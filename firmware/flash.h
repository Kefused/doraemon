#ifndef _COMMON_FLASH_H
#define _COMMON_FLASH_H

#include <stdint.h>

void flash_config();
void flash_select();
void flash_unselect();

/*
5.4 Continuous Array Read (Low Frequency Mode: 03h Opcode) 
 */
void flash_start_read(uint16_t page, uint16_t offset);
uint8_t flash_read();
void flash_stop_read();

/*
6.1 Buffer Write
 */
void flash_buffer_start_write(uint16_t offset);
void flash_buffer_write(uint8_t data);
void flash_buffer_stop_write();

/*
6.2 Buffer to Main Memory Page Program with Built-In Erase
 */
void flash_buffer_flush(uint16_t page);

uint8_t flash_test();

#endif /* !_COMMON_FLASH_H*/