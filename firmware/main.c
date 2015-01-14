#define F_CPU 8000000UL 

#include <util/delay.h>
#include <stdint.h>

#include "haptic.h"
#include "speaker.h"
#include "sensor.h"
#include "tracks.h"


int main() {
	uint8_t track_number;
	/*
	Configuration
	 */
	haptic_config();
	speaker_config();
	sensor_config();
	_delay_ms(500);

	/*
	Startup sound effect
	 */
	speaker_read_flash(TRACK_0_PAGE, TRACK_0_OFFSET, TRACK_0_LENGHT);
	_delay_ms(500);
	
	/*
	Main loop
	 */
	for(;;) {
		for(track_number=1; track_number<N_TRACKS; track_number++) {
			// Block until sensor detection
			sensor_wait();
			
			// Vibration
			haptic_pulse();
			
			// Audio playback
			switch(track_number) {
				case 1:
					speaker_read_flash(TRACK_1_PAGE, TRACK_1_OFFSET, TRACK_1_LENGHT);
					break;
				case 2:
					speaker_read_flash(TRACK_2_PAGE, TRACK_2_OFFSET, TRACK_2_LENGHT);
					break;
				case 3:
					speaker_read_flash(TRACK_3_PAGE, TRACK_3_OFFSET, TRACK_3_LENGHT);
					break;
				case 4:
					speaker_read_flash(TRACK_4_PAGE, TRACK_4_OFFSET, TRACK_4_LENGHT);
					break;
				case 5:
					speaker_read_flash(TRACK_5_PAGE, TRACK_5_OFFSET, TRACK_5_LENGHT);
					break;
				case 6:
					speaker_read_flash(TRACK_6_PAGE, TRACK_6_OFFSET, TRACK_6_LENGHT);
					break;	
				case 7:
					speaker_read_flash(TRACK_7_PAGE, TRACK_7_OFFSET, TRACK_7_LENGHT);
					break;													
			}
			
			_delay_ms(500);
		}
	}

}

