/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   model.c
/
/  Program Purposes:
/    - Library of model functions
/--------------------------------------------------------*/

#include "model.h"
#include "types.h"
#include "raster.h"

#define FULL 120
#define EMPTY 0

/*---------- Model Functions ------------------------------------------------*/
/*---------- FUNCTION: init_model -------------------------
/  PURPOSE:
/    Initializes the model structure with default values for various 
/	 components such as frets, lanes, notes, score, etc.
/ 
/  CALLER INPUT:
/    Model *model
/ 	 	- Pointer to a Model structure
/ 
/  CALLER OUTPUT:
/    N/A
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void init_model(Model *model)
{
	init_fret(model, FRET_A, 160, 326);
	init_fret(model, FRET_S, 256, 326);
	init_fret(model, FRET_D, 352, 326);
	init_fret(model, FRET_F, 448, 326);
	init_lane(model, FRET_A, 0, 160, 84, 0, SHORT_NOTE);
	init_lane(model, FRET_S, 0, 256, 84, 0, SHORT_NOTE);
	init_lane(model, FRET_D, 0, 352, 84, 0, SHORT_NOTE);
	init_lane(model, FRET_F, 0, 448, 84, 0, SHORT_NOTE);
	init_score(model, 32, 0, 0);
	init_multiplier(model, 544, 32, 1);
	init_fail_bar(model, 224, 0, 60);
}

/*---------- Fret Functions -------------------------------------------------*/
/*---------- FUNCTION: init_fret --------------------------
/  PURPOSE:
/    Initializes a fret object. 
/ 
/  CALLER INPUT:
/	 Model *model 
/ 		- Pointer to a Model structure
/    FRET_POS fret_pos 
/ 		- which fret to initalize
/    UINT16 pos_x 
/ 		- the object's x-coordinate for its screen position
/    UINT16 pos_y 
/ 		- the object's y-coordinate for its screen position
/ 
/  CALLER OUTPUT:
/    N/A
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void init_fret(Model *model, FRET_POS fret_pos, UINT16 pos_x, UINT16 pos_y)
{
	model->frets[fret_pos].pos_x = pos_x;
    model->frets[fret_pos].pos_y = pos_y;
    model->frets[fret_pos].size_x = 32;
    model->frets[fret_pos].size_y = 32;
	model->frets[fret_pos].is_depressed = FALSE;
}

/*---------- Note Functions -------------------------------------------------*/
/*---------- FUNCTION: init_note --------------------------
/  PURPOSE:
/    Initializes a note object. 
/ 
/  CALLER INPUT:
/	 Note *note 
/	 	- Pointer to a note structure
/    FRET_POS fret_pos 
/		- which fret to initalize the note on
/	 UINT8 index
/ 		- the index of the note to be initalized
/    UINT16 pos_x 
/ 		- the object's x-coordinate for its screen position
/    UINT16 pos_y	
/	 	- the object's y-coordinate for its screen position
/	 int delta_y 
/	 	- current y position
/	 NOTE_TYPE note_type 
/		- The type of note to initalize
/
/  CALLER OUTPUT:
/    N/A
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void init_note(Note *note, FRET_POS fret, UINT8 index, UINT16 pos_x, UINT16 pos_y, int delta_y, NOTE_TYPE note_type)
{
    note->pos_x = pos_x;
    note->pos_y = pos_y;
    note->delta_y = delta_y;
    note->v_dir = 1;            	/* constant */
    note->size_x = 32;          	/* constant */
    note->size_y = 32;          	/* constant */
    note->is_played = FALSE;
	note->is_active = FALSE;
	note->note_type = note_type;
}

/*---------- FUNCTION: set_note_pos-----------------------
/  PURPOSE:
/    Updates a notes position
/ 
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/    FRET_POS fret_pos 
/		- which fret the note is on
/	 UINT8 index
/ 		- the index of the note to be updated
/ 
/  CALLER OUTPUT:
/	 N/A
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void set_note_pos(Model *model)
{
	int i;

    for(i = 0; i < NOTES_SIZE ; i++){

    
        if(model->lanes[FRET_A].notes[i].is_active == TRUE){

            model->lanes[FRET_A].notes[i].pos_y += 1;

        }

        if(model->lanes[FRET_S].notes[i].is_active == TRUE){

			model->lanes[FRET_S].notes[i].pos_y += 1;

        }

        if(model->lanes[FRET_D].notes[i].is_active == TRUE){

			model->lanes[FRET_D].notes[i].pos_y += 1;
            
        }

        if(model->lanes[FRET_F].notes[i].is_active == TRUE){

			model->lanes[FRET_F].notes[i].pos_y += 1;

        }
    }
}

/*---------- Lane Functions -------------------------------------------------*/
/*---------- FUNCTION: init_lane --------------------------
/  PURPOSE:
/    Initalizes a lane structure
/ 
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/    FRET_POS fret_pos 
/		- which lane is being initalized
/	 UINT8 index
/ 		- the index of the note to be initalized
/    UINT16 pos_x 
/ 		- the object's x-coordinate for its screen position
/    UINT16 pos_y	
/	 	- the object's y-coordinate for its screen position
/	 int delta_y 
/	 	- current y position
/	 NOTE_TYPE note_type 
/		- The type of note
/ 
/  CALLER OUTPUT:
/    N/A
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void init_lane(Model *model, FRET_POS fret, UINT8 index, UINT16 pos_x, UINT16 pos_y, int delta_y, 
				NOTE_TYPE note_type)
{
	UINT8 i;

	model->lanes[fret].start_x = 0;
	model->lanes[fret].curr_x = 0;

	for(i = 0; i < NOTES_SIZE; i++)
	{
		init_note(&model->lanes[fret].notes[i], fret, index, pos_x, pos_y, delta_y, note_type);
	}
}

/*---------- Note Streak Functions ------------------------------------------*/
/*---------- FUNCTION: update_note_streak -----------------
/  PURPOSE:
/    Updates note streak when a note is hit and sets
/	 it to zero if a note is missed
/  
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/    BOOL miss 
/		- Flag for whether the note was missed
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected 
/--------------------------------------------------------*/
void update_note_streak(Model *model, BOOL miss)
{
	if(miss){

		model->score.note_streak = 0;

	}else{

		model->score.note_streak += 1;

	}
}

/*---------- Score Functions ------------------------------------------------*/
/*---------- FUNCTION: init_score -------------------------
/  PURPOSE:
/    Initalizes the score structure with starting values
/ 
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/    UINT16 pos_x 
/ 		- the object's x-coordinate for its screen position
/    UINT16 pos_y	
/	 	- the object's y-coordinate for its screen position
/ 	 UINT16 value
/		- the scores starting value
/ 
/  CALLER OUTPUT:
/    N/A
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void init_score(Model *model, UINT16 pos_x, UINT16 pos_y, UINT16 value)
{
    model->score.thous_x = pos_x;
	model->score.hunds_x = pos_x + 32;
	model->score.tens_x = pos_x + 64;
	model->score.ones_x = pos_x + 96;
    model->score.pos_y = pos_y;
    model->score.size_x = 128;
    model->score.size_y = 32;
	model->score.value = 0;
	model->score.note_streak = 0;
	model->score.prev_ones = 0;
	model->score.prev_tens = 0;
	model->score.prev_hunds = 0;
	model->score.prev_thous = 0;
	model->score.updated_flag = FALSE;
}


/*---------- FUNCTION: update_score ----------------------
/  PURPOSE:
/    Updates the scores value by a base amount of 10 
/	 multiplied by the muultiplier value and sets the 
/	 updated flag to true
/ 
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/ 
/  CALLER OUTPUT:
/    N/A
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void update_score(Model *model)
{	

		model->score.value += NOTE_VALUE * model->multiplier.value;
		model->score.updated_flag = TRUE;
	
}

/*---------- Multiplier Functions -------------------------------------------*/
/*---------- FUNCTION: init_multiplier --------------------
/  PURPOSE:
/    Initalizes the multiplier structure with starting values
/  
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/    UINT16 pos_x 
/ 		- the object's x-coordinate for its screen position
/    UINT16 pos_y	
/	 	- the object's y-coordinate for its screen position
/ 	 UINT16 value
/		- the multiplier's starting value
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void init_multiplier(Model *model, UINT16 pos_x, UINT16 pos_y, UINT16 value)
{
    model->multiplier.pos_x = pos_x;
    model->multiplier.pos_y = pos_y;
    model->multiplier.total_size_x = 64;
    model->multiplier.total_size_y = 32;
    model->multiplier.digit_size_x = 32;
    model->multiplier.digit_size_y = 32;
    model->multiplier.value = value;
	model->multiplier.prev_value = 1;
}


/*---------- FUNCTION: update_multiplier ----------------
/  PURPOSE:
/    Updates the multiplier value based on the current
/ 	 note streak value
/  
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void update_multiplier(Model *model)
{
	if (model->score.note_streak >= 30)
	{
		model->multiplier.value = 8;
	}
	else if (model->score.note_streak >= 20)
	{
		model->multiplier.value = 4;
	}
	else if (model->score.note_streak >= 10)
	{
		model->multiplier.value = 2;
	}
	else 
	{
		model->multiplier.value = 1;
	}
}

/*---------- Failbar Functions ----------------------------------------------*/
/*---------- FUNCTION: init_failbar ----------------------
/  PURPOSE:
/    Initializes the failbar structure with starting values
/  
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/    UINT16 pos_x 
/ 		- the object's x-coordinate for its screen position
/    UINT16 pos_y	
/	 	- the object's y-coordinate for its screen position
/ 	 UINT16 value
/		- the failbar's starting value
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    Working as expected
/--------------------------------------------------------*/
void init_fail_bar(Model *model, UINT16 pos_x, UINT16 pos_y, UINT16 value)
{
    model->fail_bar.pos_x = pos_x; 
    model->fail_bar.pos_y = pos_y; 
    model->fail_bar.size_x = 136; 
    model->fail_bar.size_y = 16; 
    model->fail_bar.value = value;
}


/*---------- FUNCTION: update_fail_bar ------------------
/  PURPOSE:
/    Updates the failbar value ensuring the value stays
/ 	 below 120
/  
/  CALLER INPUT:
/	 Model *model 
/	 	- Pointer to a model structure
/    UINT16 pos_x 
/ 		- the object's x-coordinate for its screen position
/    UINT16 pos_y	
/	 	- the object's y-coordinate for its screen position
/ 	 UINT16 value
/		- the value to add to the failbar
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Without a fail state at zero elsewhere value could
/ 	   go below zero
/--------------------------------------------------------*/
void update_fail_bar(Model *model, UINT16 value)
{
	if(model->fail_bar.value >= EMPTY && model->fail_bar.value <= FULL){

		model->fail_bar.value += value;

	}

	if(model->fail_bar.value > FULL){

		model->fail_bar.value = FULL;
	}
}