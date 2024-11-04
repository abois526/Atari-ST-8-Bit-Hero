/*---------- ID HEADER ----------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   model.h
/
/  Program Purposes:
/    Header for model.c including structures for the game model
/ 	 and function prototypes
/--------------------------------------------------------------*/
#ifndef MODEL_H
#define MODEL_H

#include "types.h"

/*---------- STRUCTURE DEFINITIONS ------------------------------------------*/

/*---------- STRUCTURE: Fret ------------------------------
/  INFO:
/    Structure for the fret object
/  
/  ATTRIBUTES:
/    UINT16 pos_x
/       - x-val for position coordinate
/    UINT16 pos_y	
/		- y-val for position coordinate
/    UINT8 size_x	
/		- x-val for size of the object in px
/    UINT8 size_y	
/		- y-val for size of the object in px
/    BOOL is_depressed	
/ 		- Boolean state for if fret is currently
/         being depressed (0=F / 1=T)
/--------------------------------------------------------*/
typedef struct 
{
    UINT16 pos_x, pos_y;    
    UINT8 size_x, size_y;
	BOOL is_depressed;
} Fret; 


/*---------- STRUCTURE: Note ------------------------------
/  INFO:
/    Structure for the note object
/  
/  ATTRIBUTES:
/    UINT16 pos_x
/       - x-val for position coordinate
/    UINT16 pos_y	
/		- y-val for position coordinate
/	 int v_dir
/ 		- vertical direction
/    UINT8 size_x	
/		- x-val for size of the object in px
/    UINT8 size_y	
/		- y-val for size of the object in px
/    BOOL is_played	
/ 		- Boolean state for if note has been
/         played (0=F / 1=T)
/    BOOL is_active	
/ 		- Boolean state for if note is
/         active (0=F / 1=T)
/    NOTE_TYPE note_type	
/ 		- the type of note
/	 
/--------------------------------------------------------*/
typedef struct 
{
    UINT16 pos_x, pos_y;
    int delta_y;                
    int v_dir;                          
    UINT8 size_x, size_y; 
	BOOL is_played;
	BOOL is_active;
	NOTE_TYPE note_type;
} Note;

/*---------- STRUCTURE: Lane ------------------------------
/  INFO:
/    Structure for the lane object
/  
/  ATTRIBUTES:
/    UINT16 start_x
/       - x-val for start coordinate
/    UINT16 curr_x
/       - x-val for current coordinate
/    UINT16 start_y	
/		- y-val for start coordinate
/    UINT16 end_y	
/		- y-val for start coordinate
/    UINT8 counter	
/		- ASK ANDREW
/    NOTE notes[]	
/ 		- An array of notes on the lane
/--------------------------------------------------------*/
typedef struct 
{
    UINT16 start_x, curr_x, start_y, end_y;
	Note notes[NOTES_SIZE];
} Lane;

/*---------- STRUCTURE: Score -----------------------------
/  INFO:
/    Structure for the score object 
/  
/  ATTRIBUTES:
/    UINT16 ones_x
/       - x-val for ones digit coordinate
/    UINT16 tens_x
/       - x-val for tens digit coordinate
/    UINT16 hunds_x	
/		- x-val for hundreds digit coordinate
/    UINT16 thous_x	
/		- x-val for thousands digit coordinate
/    UINT8 size_x	
/		- x-val for size of the object in px
/    UINT8 size_y	
/		- y-val for size of the object in px
/    UINT16 value
/       - the scores current value
/    UINT16 prev_ones
/       - previous ones value
/    UINT16 prev_tens
/       - previous tens value
/    UINT16 prev_hunds	
/		- previous hundreds value
/    UINT16 prev_thous	
/		- previous thousands value
/    BOOL updated flag	
/ 		- Boolean state for if score has been
/         updated (0=F / 1=T)
/--------------------------------------------------------*/
typedef struct 
{
	UINT16  ones_x, tens_x, hunds_x, thous_x, pos_y;
	UINT8 size_x, size_y;
	UINT16 value, note_streak, prev_ones, prev_tens, prev_hunds, prev_thous;
	BOOL updated_flag;
} Score;


/*---------- STRUCTURE: Multiplier ------------------------
/  INFO:
/    Structure for the multiplier object
/  
/  ATTRIBUTES:
/    UINT16 pos_x
/		- x-val for position coordinate
/    UINT16 pos_y	
/		- y-val for position coordinate
/    UINT8 total_size_x	
/		- x-val for size of the object in px
/    UINT8 total_size_y	
/		- y-val for size of the object in px
/    UINT8 digit_size_x	
/		- x-val for size of the digit in px
/    UINT8 digit_size_y	
/		- y-val for size of the digit in px
/    UINT16 value 
/		- the value of the multiplier
/    UINT16 prev_value 
/		- the previous value of the multiplier
/  
/--------------------------------------------------------*/
typedef struct 
{
	UINT16 pos_x, pos_y;
	UINT8 total_size_x, total_size_y, digit_size_x, digit_size_y;
	UINT16 value, prev_value;
} Multiplier;


/*---------- STRUCTURE: Fail_Bar --------------------------
/  INFO:
/    Structure for the failbar object
/  
/  ATTRIBUTES:
/    UINT16 pos_x
/		- x-val for position coordinate
/    UINT16 pos_y	
/		- y-val for position coordinate
/    UINT16 size_x	
/		- x-val for size of the object in px
/    UINT16 size_y	
/		- y-val for size of the object in px
/    UINT8 value 
/		- the value of the bail bar (starts @ 50%)
/--------------------------------------------------------*/
typedef struct 
{
	UINT16 pos_x, pos_y;
	UINT16 size_x, size_y;
	UINT8 value;
} Fail_Bar;

/*---------- STRUCTURE: Model ------------------------------
/  INFO:
/    Structure for the main game model
/  
/  ATTRIBUTES:
/    Frets frets[]
/ 		- Fret structure
/ 	 Lane lanes[]
/		- Lane structure
/ 	 Score score
/		- Score structure
/    Multiplier multiplier
/ 		- Multiplier structure
/    Fail_Bar fail_bar
/ 		- Failbar structure
/ 	
/--------------------------------------------------------*/
typedef struct 
{
	Fret frets[FRETS_SIZE]; /* frets A, S, D, and F */
	Lane lanes[LANES_SIZE]; /* lanes for the 4 frets */
	Score score;
	Multiplier multiplier;
	Fail_Bar fail_bar;	
} Model;



/*---------- FUNCTION PROTOTYPES --------------------------------------------*/
/* Model Functions */
void init_model(Model *model);

/* Fret Functions */
void init_fret(Model *model, FRET_POS fret_pos, UINT16 pos_x, UINT16 pos_y);
void set_fret_depressed(Model *model, FRET_POS fret, BOOL is_depressed);

/* Note Functions */
void init_note(Note *note, FRET_POS fret, UINT8 index, UINT16 pos_x, UINT16 pos_y, int delta_y, NOTE_TYPE note_type);
void set_note_pos(Model *model);
void set_note_is_played(Model *model, FRET_POS fret, UINT8 index, BOOL is_played);

/* Lane Functions */
void init_lane(Model *model, FRET_POS fret, UINT8 index, UINT16 pos_x, UINT16 pos_y, int delta_y, 
				NOTE_TYPE note_type);

/* Note Streak Functions */
void update_note_streak(Model *model, BOOL miss);

/* Score Functions */
void init_score(Model *model, UINT16 pos_x, UINT16 pos_y, UINT16 value);
void update_score(Model *model);

/* Multiplier Functions */
void init_multiplier(Model *model, UINT16 pos_x, UINT16 pos_y, UINT16 value);
void update_multiplier(Model *model);

/* Failbar Functions */
void init_fail_bar(Model *model, UINT16 pos_x, UINT16 pos_y, UINT16 value);
void update_fail_bar(Model *model, UINT16 value);


#endif 