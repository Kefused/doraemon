#ifndef _COMMON_SPEAKER_H
#define _COMMON_SPEAKER_H

#include <stdint.h>


void speaker_config();
void speaker_read_flash(uint16_t page, uint16_t offset, uint32_t duration);
void speaker_debug(uint16_t duration);

#endif /* !_COMMON_SPEAKER_H*/