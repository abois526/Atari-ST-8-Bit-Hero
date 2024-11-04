/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   events.c
/
/  Program Purposes:
/	 - Library of event handler functions
/--------------------------------------------------------*/

#include <stdio.h>
#include "model.h"
#include "events.h"
#include "types.h"
#include "raster.h"
#include "effects.h"
#include "psg.h"
#include "super.h"

#define GENERATE 69
#define UPPER_BOUND 384
#define LOWER_BOUND 300

/*---------- SYNCHRONOUS EVENTS ------------------------------------*/
/*---------- FUNCTION: generate_note ------------------
/  PURPOSE:
/    Sets a note as active on the next needed lane for the song
/	 when the generate counter reaches 69
/  
/  CALLER INPUT:
/    Model *model
/    - Address of the game model
/  
/  CALLER OUTPUT:
/	 None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void generate_note(Model *model){

	static int note_counter = 0;
    static UINT8 i = 0;
    static UINT8 j = 0;
    static UINT8 k = 0;
    static UINT8 l = 0;
    static BOOL swap = FALSE;

    if(!swap){
        switch (note_counter){
                case 0:
					model->lanes[FRET_A].notes[i].is_active = TRUE;
                    i++;
                    break;
                case 1:
					model->lanes[FRET_S].notes[j].is_active = TRUE;
                    j++;
                    break;
                case 2:
					model->lanes[FRET_D].notes[k].is_active = TRUE;
                    k++;
                    break;
                case 3:
					model->lanes[FRET_F].notes[l].is_active = TRUE;
                    l++;
                    break;
            }
        note_counter++;
        if(note_counter == 4){
            note_counter = 0;
            swap = TRUE;
        }
    }
    else{
        switch (note_counter){
                case 3:
					model->lanes[FRET_A].notes[i].is_active = TRUE;
                    i++;
                    break;
                case 2:
					model->lanes[FRET_S].notes[j].is_active = TRUE;
                    j++;
                    break;
                case 1:
					model->lanes[FRET_D].notes[k].is_active = TRUE;
                    k++;
                    break;
                case 0:
					model->lanes[FRET_F].notes[l].is_active = TRUE;
                    l++;
                    break;
            }
        note_counter++;
        if(note_counter == 4){
            note_counter = 0;
            swap = FALSE;
        }
    }
}

/*---------- ASYNCHRONOUS (INPUT) EVENTS ------------------------------------*/

/*---------- FUNCTION: set_play_on_fret_a -----------------
/  PURPOSE:
/    Sets the given note as played on fret A
/  
/  CALLER INPUT:
/    Model *model
/    - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/	 None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void set_play_on_fret_a(Model *model, UINT8 index)
{
	model->lanes[FRET_A].notes[index].is_played = TRUE;

}


/*---------- FUNCTION: set_play_on_fret_s -----------------
/  PURPOSE:
/    Sets the given note as played on fret S
/  
/  CALLER INPUT:
/    Model *model
/    - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/	 None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void set_play_on_fret_s(Model *model, UINT8 index)
{
	model->lanes[FRET_S].notes[index].is_played = TRUE;
}


/*---------- FUNCTION: set_play_on_fret_d -----------------
/  PURPOSE:
/    Sets the given note as played on fret D
/  
/  CALLER INPUT:
/    Model *model
/    - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/	 None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void set_play_on_fret_d(Model *model, UINT8 index)
{
	model->lanes[FRET_D].notes[index].is_played = TRUE;
}


/*---------- FUNCTION: set_play_on_fret_f -----------------
/  PURPOSE:
/    Sets the given note as played on fret F
/  
/  CALLER INPUT:
/    Model *model
/    - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/	 None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void set_play_on_fret_f(Model *model, UINT8 index)
{
	model->lanes[FRET_F].notes[index].is_played = TRUE;
}


/*---------- CONDITION-BASED (CASCADED) EVENTS ------------------------------*/

/*---------- FUNCTION: note_collision_a -------------------
/  PURPOSE:
/    Checks for a note collision on the A fret and updates
/	 model aspects for whether it is a hit or a miss
/  
/  CALLER INPUT:
/   Model *model
/   - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/    None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void note_collision_a(Model *model, UINT8 index)
{
	if (model->lanes[FRET_A].notes[index].pos_y > LOWER_BOUND &&
		model->lanes[FRET_A].notes[index].pos_y < UPPER_BOUND)
	{
		update_score(model);
		update_multiplier(model);
		update_fail_bar(model, 20);
		update_note_streak(model, FALSE);
	}
	else 
	{
		update_multiplier(model);
		update_fail_bar(model, -20);
		update_note_streak(model, TRUE);
		enter_super();
		play_wrong_note_fx();
		stop_sound_channel_c();
		exit_super();
	}
}


/*---------- FUNCTION: note_collision_s -------------------
/  PURPOSE:
/    Checks for a note collision on the S fret and updates
/	 model aspects for whether it is a hit or a miss
/  
/  CALLER INPUT:
/   Model *model
/   - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/    None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void note_collision_s(Model *model, UINT8 index)
{
	if (model->lanes[FRET_S].notes[index].pos_y > LOWER_BOUND &&
		model->lanes[FRET_S].notes[index].pos_y < UPPER_BOUND)
	{
		update_score(model);
		update_multiplier(model);
		update_fail_bar(model, 20);
		update_note_streak(model, FALSE);
	}
	else 
	{
		update_multiplier(model);
		update_fail_bar(model, -20);
		update_note_streak(model, TRUE);
		enter_super();
		play_wrong_note_fx();
		stop_sound_channel_c();
		exit_super();
	}
}


/*---------- FUNCTION: note_collision_d -------------------
/  PURPOSE:
/    Checks for a note collision on the D fret and updates
/	 model aspects for whether it is a hit or a miss
/  
/  CALLER INPUT:
/   Model *model
/   - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/    None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void note_collision_d(Model *model, UINT8 index)
{
	if (model->lanes[FRET_D].notes[index].pos_y > LOWER_BOUND &&
		model->lanes[FRET_D].notes[index].pos_y < UPPER_BOUND)
	{
		update_score(model);
		update_multiplier(model);
		update_fail_bar(model, 20);
		update_note_streak(model, FALSE);
	}
	else 
	{
		update_multiplier(model);
		update_fail_bar(model, -20);
		update_note_streak(model, TRUE);
		enter_super();
		play_wrong_note_fx();
		stop_sound_channel_c();
		exit_super();		
	}
}


/*---------- FUNCTION: note_collision_f -------------------
/  PURPOSE:
/    Checks for a note collision on the F fret and updates
/	 model aspects for whether it is a hit or a miss
/  
/  CALLER INPUT:
/   Model *model
/   - Address of the game model
/    UINT8 index
/    - Index of the note being played
/  
/  CALLER OUTPUT:
/    None
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void note_collision_f(Model *model, UINT8 index)
{
	if (model->lanes[FRET_F].notes[index].pos_y > LOWER_BOUND &&
		model->lanes[FRET_F].notes[index].pos_y < UPPER_BOUND)
	{
		update_score(model);
		update_multiplier(model);
		update_fail_bar(model, 20);
		update_note_streak(model, FALSE);
	}
	else 
	{
		update_multiplier(model);
		update_fail_bar(model, -20);
		update_note_streak(model, TRUE);
		enter_super();
		play_wrong_note_fx();
		stop_sound_channel_c();
		exit_super();		
	}
}
