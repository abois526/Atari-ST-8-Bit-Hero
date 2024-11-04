/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   effects.c
/  Citations:   
/    - play_game_over_win_fx: Megadeth's "Sweating Bullets"
/    - play_menu_selection_fx: Super Mario Bros "Coin Sound"
/
/  Program Purposes:
/    Functions for game sound effects
/--------------------------------------------------------*/

#include <osbind.h>
#include "psg.h"
#include "types.h"
#include "sndconst.h"
#include "effects.h"


/*---------- FUNCTION: play_wrong_note_fx -----------------
/  PURPOSE:
/    Plays the sound effect that signals that a wrong note
/    was played. This occurs when a fret is depressed and 
/    there is no collision with a note.
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
void play_wrong_note_fx()
{
    long i;
    play_note(2, E5>>1, 0, 0x18, ENV_SHAPE_4, ENV_FREQ, 1, 0);

}


/*---------- FUNCTION: play_note_not_played_fx ------------
/  PURPOSE:
/    Plays the sound effect that signals that plays when a 
/    note passes the fret without being played. This occurs
/    when the note and fret collide without the fret's key 
/    being depressed. 
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Bugs:
/      - not playing correctly the first time it is played,
/        then it seems to work properly; think that it is
/        related to the envelope perhaps
/--------------------------------------------------------*/
void play_note_not_played_fx()
{
    long i; 
    long length = 100000;
    play_note(2, E5>>1, 0, 0x18, ENV_SHAPE_4, ENV_FREQ, 1, 0);

}


/*---------- FUNCTION: play_game_over_win_fx --------------
/  PURPOSE:
/    Plays the sound effect that signals that the player has
/    won the game.
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
void play_game_over_win_fx()
{
    /* 
    - using part of the solo from Megdeth's "Sweating Bullets"
    - 140 BPM
    E3 D3 E3 G3 E3 G3 A3 G3 A3 B3 A3 
    B3 D4 B3 D4 E4 D4 E4 G4 F4 E4 F4
    */

    long i;
    long length = 40000;
    long length_2 = 120000;

    play_note(2, E5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, D5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, E5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, G5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, E5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, G5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, A5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, G5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, A5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, B5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, A5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, B5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, D5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, B5<<2, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, D5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, E5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, D5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, E5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, G5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, F5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, E5<<1, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length; i++);
    stop_sound_channel_c();


    play_note(2, 0x166, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length_2; i++);
    stop_sound_channel_c();


}


/*---------- FUNCTION: play_game_over_lose_fx -------------
/  PURPOSE:
/    Plays the sound effect that signals that the player has
/    lost the game.
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
void play_game_over_lose_fx()
{
    long i;
    long length_1 = 100000;
    long length_2 = 200000;

    play_note(2, D5_SHARP<<3, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length_1; i++);
    stop_sound_channel_c();


    for (i = 0; i < length_1; i++);

    play_note(2, C5<<3, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length_1; i++);
    stop_sound_channel_c();


    for (i = 0; i < length_1; i++);
    
    play_note(2, F5_SHARP<<3, 0, 0x08, 0, 0, 1, 0);
    for (i = 0; i < length_2; i++);
    stop_sound_channel_c();

}


/*---------- FUNCTION: play_menu_selection_fx -------------
/  PURPOSE:
/    Plays the sound effect that signals a menu selection 
/    has been made.
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Bugs:
/      - not playing correctly the first time it is played,
/        then it seems to work properly; think that it is
/        related to the envelope perhaps
/--------------------------------------------------------*/
void play_menu_selection_fx()
{
    long i;

    play_note(2, B5, 0, 0x18, ENV_SHAPE_4, ENV_FREQ, 1, 0);

    for (i = 0; i < 10000; i++);


    play_note(2, E5>>1, 0, 0x18, ENV_SHAPE_4, ENV_FREQ, 1, 0);

    for (i = 0; i < 80000; i++);
    stop_sound_channel_c();


}


/*---------- FUNCTION: play_note --------------------------
/  PURPOSE:
/    Helper function to make the other functions a bit 
/    easier to manage.
/  
/  CALLER INPUT:
/    int channel 
/      the channel for the sound to play on
/    int tone_tuning
/      the tuning value for set_tone()
/    int noise_tuning
/      the tuning value for set_noise()
/    int volume
/      the mode and volume level for set_volume()
/    int shape
/      the envelope shape for set_envelope()
/    unsigned int sustain
/      the sustain value for set_envelope()
/    int tone_on
/      turns tone on/off for enable_channel()
/    int noise_on
/      turns noise on/off for enable_channel()
/      
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A 
/--------------------------------------------------------*/
void play_note(int channel, int tone_tuning, int noise_tuning, int volume, 
               int shape, unsigned int sustain, int tone_on, int noise_on) {
    
    set_tone(channel, tone_tuning);
    set_noise(noise_tuning);
    enable_channel(channel, tone_on, noise_on);
    set_volume(channel, volume);
    set_envelope(shape, sustain);
}
