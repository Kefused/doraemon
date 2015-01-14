SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
MCU = attiny861a
MCU_AVRDUDE = t861

firmware.hex: firmware.elf
	avr-objcopy -j .text -j .data -O ihex firmware.elf firmware.hex
	avr-size firmware.elf

firmware.elf: $(OBJS)
	avr-gcc -Os -mmcu=$(MCU) -o firmware.elf $^

%.o : %.c
	avr-gcc -DTRACKS_$(TRACKS_TYPE) -Wall -Os -mmcu=$(MCU) -o $@ -c $<

.PHONY: clean cleaner upload fuse

upload: firmware.hex
	avrdude -c buspirate -P /dev/ttyUSB0 -p $(MCU_AVRDUDE) -U flash:w:firmware.hex

fuse:
	avrdude -c buspirate -P /dev/ttyUSB0 -p $(MCU_AVRDUDE) -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m

clean:
	rm -rf *.o *.elf

cleaner: clean
	rm -rf firmware.hex
