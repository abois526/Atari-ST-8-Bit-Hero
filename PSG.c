/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   psg.c
/  Citations:   
/    - geeksforgeeks.org, https://www.geeksforgeeks.org/set-clear-and-toggle-a-given-bit-of-a-number-in-c/
/
/  Program Purposes:
/    Data Structures: 
/      - TODO
/
/    Functions:
/      - TODO  
/--------------------------------------------------------*/

#include <osbind.h>
#include "psg.h"
#include "types.h"


/*---------- FUNCTION: write_psg --------------------------
/  PURPOSE:
/    Selects a register and writes a value to it. This is
/    a helper function for the library.
/  
/  CALLER INPUT:
/    int reg
/      the register which is to be selected
/    UINT8 val
/      the value which is to be assigned to the selected register
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    As a result of val being a UINT8, negative numbers roll
/    to max values and have unpredictible behaviours. This is
/    a helper function for the other functions and the input 
/    parameters for those functions check if the input value 
/    is out of range. If it is, the request is ignored.
/--------------------------------------------------------*/
void write_psg(int reg, UINT8 val)
{
    if (reg >= 0 && reg <= 0xF && val <= 0xFF) 
    {
        volatile UINT8 *register_select = SELECT_ADDRESS;
        volatile UINT8 *register_write = WRITE_ADDRESS;


        *register_select = (UINT8)reg;
        *register_write = val;

    }
}


/*---------- FUNCTION: read_psg ---------------------------
/  PURPOSE:
/    Reads the value at the selected register.
/  
/  CALLER INPUT:
/    int reg
/      the register which is to be selected
/  
/  CALLER OUTPUT:
/    UINT8 curr_val
/      the current value held by the selected register
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
UINT8 read_psg(int reg)
{
    if (reg >= 0 && reg <= 0xF) 
    {
        volatile UINT8 *register_select = SELECT_ADDRESS;
        volatile UINT8 *register_write = WRITE_ADDRESS;
        UINT8 curr_val;

        *register_select = (UINT8)reg;
        curr_val = *register_select;

        return curr_val;
    }
}


/*---------- FUNCTION: set_tone ---------------------------
/  PURPOSE:
/    TODO - purpose, from the caller's perspective (if not 
/    perfectly clear from the name)
/  
/  CALLER INPUT:
/    int channel
/      The channel to be selected (A, B, or C) 
/    int tuning 
/      A 12 bit value representing the fine tone and rough 
/      tone, to be assigned to their appropriate registers
/      based upon the channel. 
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void set_tone(int channel, int tuning)
{
    if (channel >= 0 && channel <= 2 && tuning >= 0 && tuning <= 0xFFF)
    {
        int fine_reg = channel * 2;
        int rough_reg = (channel * 2) + 1;

        int fine_tone = tuning & 0x0FF;
        int rough_tone = (tuning >> 8) & 0x00F;

        write_psg(fine_reg, fine_tone);
        write_psg(rough_reg, rough_tone);
    }
}


/*---------- FUNCTION: set_volume -------------------------
/  PURPOSE:
/    Loads the volume register for the given channel.
/  
/  CALLER INPUT:
/    int channel
/      The channel to be selected (0=A, 1=B, 2=C)
/    int volume 
/      The 5-bit value to load the register with.
/      B4 = Mode (0 = fixed, 1 = variable)
/      B3-B0 = volume level selection 
/      Variable mode uses the envelope generator.
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A 
/--------------------------------------------------------*/
void set_volume(int channel, int volume)
{
    if (channel >= 0 && channel <= 2 && volume >= 0 && volume <= 0x1F)
    {
        /* R8-10 are channel A, B, C */
        write_psg(channel+8, volume);
    }
}


/*---------- FUNCTION: enable_channel ---------------------
/  PURPOSE:
/    Turns the given channel's tone/noise signals on/off.
/  
/  CALLER INPUT:
/    int channel
/      The channel to be selected (0=A, 1=B, 2=C)
/    int tone_on
/      Turns the tone for the channel on/off (0=off, 1=on)
/    int noise_on
/      Turns the noise for the channel on/off (0=off, 1=on)
/  
/  CALLER OUTPUT:
/    N/A 
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A 
/--------------------------------------------------------*/
void enable_channel(int channel, int tone_on, int noise_on)
{
    if (channel >= 0 && channel <= 2 && 
        tone_on >= 0 && tone_on <= 1 &&
        noise_on >= 0 && noise_on <= 1)
    {
        int curr_mixer_state = read_psg(7);

        if (tone_on) {
            curr_mixer_state &= ~(1 << channel); /* clear bit for tone */
        }
        else {
            curr_mixer_state |= 1 << channel; /* set bit for tone */
        }

        if (noise_on) {
            curr_mixer_state &= ~(1 << (channel + 3)); /* clear bit for noise */
        }
        else {
            curr_mixer_state |= 1 << (channel + 3); /* set bit for noise */
        }
        
        write_psg(7, curr_mixer_state);
    }
}


/*---------- FUNCTION: stop_sound -------------------------
/  PURPOSE:
/    Silences all PSG sound production.
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void stop_sound()
{
    write_psg(8, 0);
    write_psg(9, 0);
    write_psg(10, 0);
}


/*---------- FUNCTION: set_noise --------------------------
/  PURPOSE:
/    Loads the noise register with the given tuning. 
/  
/  CALLER INPUT:
/    int tuning
/      The value for the noise frequency register. There
/      are 5 bits of values to set.
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void set_noise(int tuning)
{
    if (tuning >= 0 && tuning <= 0x1F) 
    {
        write_psg(6, tuning);
    }
}

/*---------- FUNCTION: set_envelope -----------------------
/  PURPOSE:
/    Loads the PSG envelope control registers with the given 
/    envelope shape and 16-bit sustain. 
/  
/  CALLER INPUT:
/    int shape
/      The shape is controlled by a 4-bit value where:
/      b3 = CONT
/      b2 = ATT
/      b1 = ALT
/      b0 = HOLD
/    int sustain
/      16-bit value used to help calculate the envelope
/      frequency.
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void set_envelope(int shape, unsigned int sustain)
{
    if (shape >= 0 && shape <= 0xF &&
        sustain >= 0 && sustain <= 0xFFFF)
    {
        int fine = sustain & 0x00FF;
        int rough = (sustain >> 8) & 0x00FF;

        write_psg(13, shape);    
        write_psg(11, fine);
        write_psg(12, rough);
    }
}

/*---------- FUNCTION: stop_sound_channel_a ---------------
/  PURPOSE:
/    Silences all PSG sound production on channel a.
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void stop_sound_channel_a()
{
    write_psg(8, 0);
}


/*---------- FUNCTION: stop_sound_channel_b ---------------
/  PURPOSE:
/    Silences all PSG sound production on channel b.
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void stop_sound_channel_b()
{
    write_psg(9, 0);
}

/*---------- FUNCTION: stop_sound_channel_c ---------------
/  PURPOSE:
/    Silences all PSG sound production on channel c.
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void stop_sound_channel_c()
{
    write_psg(10, 0);
}