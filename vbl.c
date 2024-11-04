/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   vbl.c
/  Citations:   
/ 
/
/  Program Purposes:
/    Contains the VBL ISR routine
/--------------------------------------------------------*/
#include "vbl.h"
#include "events.h"
#include "model.h"
#include "globals.h"
#include "psg.h"
#include "music.h"

short render_timer = 0;
short note_timer = 0;
long total_time = 0;
short music_time = 0;
BOOL game_on = FALSE;
BOOL music_on = FALSE;
BOOL stop_gen = FALSE;


/*---------- FUNCTION: do_vbl_isr -------------------------
/  PURPOSE:
/    Performs the actions of the VBL ISR. This function 
/    is to be called in the assembly function _vbl_isr
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - This function MUST be called in _vbl_isr to ensure that
/      registers d0-d2/a0-a2 are preserved and restored.
/--------------------------------------------------------*/
void do_vbl_isr(){

    if(game_on){

        total_time++;
        render_timer++;
        note_timer++;

        if(render_timer == 1){

            set_note_pos(&model);
            render_request = 1;
            render_timer = 0;
        }

        if(note_timer == 69){

            if(!stop_gen){

                generate_note(&model);
                
            }

            note_timer = 0;
        }

        if(total_time == 300){
            start_music();
            music_on = TRUE;
        }

        if(music_on == TRUE){

            music_time++;

            if(music_time == 69){
                update_music();
                music_time = 0;
            }


        }
    }
    
}