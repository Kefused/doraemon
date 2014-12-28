#include "swspi.h"
#include <util/delay_basic.h>

/*
Software SPI configuration
 */
#define SWSPI_MOSI_PORT PORTA
#define SWSPI_MOSI_PIN PA1
#define SWSPI_MISO_PORT PINA
#define SWSPI_MISO_PIN PA0
#define SWSPI_SCLK_PORT PORTA
#define SWSPI_SCLK_PIN PA2
#define SWSPI_MODE SPI_MODE1

void spi_config() {
    DDRA  |= (1 << 1) | (1 << 2); // set DO and SCK as outputs
    DDRA  &= ~(1 << 0); // set DI as input
    PORTA |= (1 << 0); // Pull-up on DI
}

#if !defined(SWSPI_MOSI_PORT) || !defined(SWSPI_MOSI_PIN) || \
    !defined(SWSPI_MISO_PORT) || !defined(SWSPI_MISO_PIN) || \
    !defined(SWSPI_SCLK_PORT) || !defined(SWSPI_SCLK_PIN) || \
    !defined(SWSPI_MODE)
#  error Software SPI not configured! SWSPI_* should be configured!
#endif

#define setbit(P, B) ((P) |= (_BV(B)))
#define clibit(P, B) ((P) &= ~(_BV(B)))
#define getbit(P, B) (((P) & (_BV(B)))? 1:0)

#ifdef SWSPI_DIV
#  define SPIDELAYTIME ((SWSPI_DIV)/2)
#else
#  define SPIDELAYTIME 1
#endif
#define SPIHALFDELAY() _delay_loop_1(SPIDELAYTIME) // half of tact (bit transfer) - min 1 CPU tact

#define SETMOSI() setbit(SWSPI_MOSI_PORT, SWSPI_MOSI_PIN)
#define CLIMOSI() clibit(SWSPI_MOSI_PORT, SWSPI_MOSI_PIN)
#define NOMOSI() clibit(SWSPI_MOSI_PORT, SWSPI_MOSI_PIN)

// instead of PORTX may be PINX?
#define READMISO() getbit(SWSPI_MISO_PORT, SWSPI_MISO_PIN)

#if (2 & SWSPI_MODE)
#  define ONSCLK() clibit(SWSPI_SCLK_PORT, SWSPI_SCLK_PIN)
#  define OFFSCLK() setbit(SWSPI_SCLK_PORT, SWSPI_SCLK_PIN)
#else
#  define ONSCLK() setbit(SWSPI_SCLK_PORT, SWSPI_SCLK_PIN)
#  define OFFSCLK() clibit(SWSPI_SCLK_PORT, SWSPI_SCLK_PIN)
#endif

#if (1 & SWSPI_MODE)
#  define SHIFTBIT(outbyte, inbyte) do { \
        (outbyte) & 0x80 ? (SETMOSI()) : (CLIMOSI()); \
        (outbyte) <<= 1; \
        ONSCLK(); \
        SPIHALFDELAY(); \
        (inbyte) <<=1; \
        (inbyte) |= READMISO(); \
        OFFSCLK(); \
        SPIHALFDELAY(); \
} while (0)
#else
#  define SHIFTBIT(outbyte, inbyte) do { \
        (outbyte) & 0x80 ? (SETMOSI()) : (CLIMOSI()); \
        (outbyte) <<= 1; \
        SPIHALFDELAY(); \
        ONSCLK(); \
        SPIHALFDELAY(); \
        (inbyte) <<=1; \
        (inbyte) |= READMISO(); \
        OFFSCLK(); \
} while (0)
#endif

uint8_t
spi_transfer(uint8_t data) {
        int nbit;
        uint8_t res = 0;
        for (nbit=0; nbit<8; nbit++) {
                SHIFTBIT(data, res);
        }
        NOMOSI();
        return (res);
}

#undef ONSCLK
#undef OFFSCLK
#undef SETMOSI
#undef CLIMOSI
#undef NOMOSI
#undef READMISO
#undef SPIHALFDELAY
#undef SPIDELAYTIME
#undef SHIFTBIT
#undef SHIFT0