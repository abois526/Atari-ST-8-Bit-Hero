/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   psg.h
/  Citations:   
/    - TODO 
/
/  Program Purposes:
/    Data Structures: 
/      - TODO
/
/    Functions:
/      - TODO  
/--------------------------------------------------------*/

#ifndef PSG_H
#define PSG_H

#include "types.h"


/*---------- REGISTER ADDRESSES ---------------------------------------------*/
#define SELECT_ADDRESS  0xFFFF8800
#define WRITE_ADDRESS   0xFFFF8802

/*---------- MASKING VALUES -------------------------------------------------*/
#define IO_PORT_BITS 0x3F

/*---------- FUNCTION PROTOTYPES --------------------------------------------*/
/* PSG Control Functions */
void write_psg(int reg, UINT8 val); 
UINT8 read_psg(int reg); 
void set_tone(int channel, int tuning); 
void set_volume(int channel, int volume); 
void enable_channel(int channel, int tone_on, int noise_on); 
void stop_sound(); 
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);
void stop_sound_channel_a();
void stop_sound_channel_b();
void stop_sound_channel_c();

#endif