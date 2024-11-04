/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   music.c
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

#include <osbind.h>
#include "music.h"
#include "psg.h"
#include "types.h"
#include "songdat.h"
#include "sndconst.h"

#define BPM 80
#define TICKS_PER_SEC 70
#define TICKS_PER_W_NOTE (TICKS_PER_SEC * 3)
#define TICKS_PER_H_NOTE (TICKS_PER_W_NOTE / 2)
#define TICKS_PER_Q_NOTE (TICKS_PER_W_NOTE / 4)
#define TICKS_PER_E_NOTE (TICKS_PER_W_NOTE / 8)

UINT32 curr_note_index = 0;
UINT32 time_since_last_note = 0;

/*---------- FUNCTION: start_music ------------------------
/  PURPOSE:
/    Starts music for main game song
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
void start_music()
{

    set_tone(0, channel_a[curr_note_index].pitch);
    enable_channel(0, 1, 0);
    set_volume(0, channel_a[curr_note_index].level);
    set_envelope(channel_a[curr_note_index].env_shape, 
                 channel_a[curr_note_index].env_sustain);

    curr_note_index += 1;

}

/*---------- FUNCTION: update_music -----------------------
/  PURPOSE:
/    Updates main game song
/  
/  CALLER INPUT:
/    UINT32 total_time_elapsed
/      -Total time the game has been running
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void update_music()
{   

        stop_sound_channel_a();
        set_tone(0, channel_a[curr_note_index].pitch);
        enable_channel(0, 1, 0);
        set_volume(0, channel_a[curr_note_index].level);
        set_envelope(channel_a[curr_note_index].env_shape,
                        channel_a[curr_note_index].env_sustain);

        /* making sure it wraps back around */
        curr_note_index = (curr_note_index + 1) % SONG_LENGTH; 
    
}