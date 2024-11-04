/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   effects.h
/  Citations:   
/    
/
/  Program Purposes:
/    Header file for effects.c
/--------------------------------------------------------*/

#ifndef EFFECTS_H
#define EFFECTS_H


/*---------- FUNCTION PROTOTYPES --------------------------------------------*/
/* main functions */
void play_wrong_note_fx();
void play_note_not_played_fx();
void play_game_over_win_fx();
void play_game_over_lose_fx();
void play_menu_selection_fx();

/* helper functions */
void play_note(int channel, int tone_tuning, int noise_tuning, int volume, 
               int shape, unsigned int sustain, int tone_on, int noise_on);


#endif