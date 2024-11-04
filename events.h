/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   events.h
/  Citations:   
/   
/
/
/  Program Purposes:
/    Header file for events.c
/--------------------------------------------------------*/

#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"
#include "types.h"

/*---------- Synchronous (Input) Events ------------------------------------*/
void generate_note(Model *model);
void activate_note();

/*---------- Asynchronous (Input) Events ------------------------------------*/
void set_play_on_fret_a(Model *model, UINT8 index);
void set_play_on_fret_s(Model *model, UINT8 index);
void set_play_on_fret_d(Model *model, UINT8 index);
void set_play_on_fret_f(Model *model, UINT8 index);

/*---------- Condition-Based (Cascaded) Events ------------------------------*/
void note_collision_a(Model *model, UINT8 index);
void note_collision_s(Model *model, UINT8 index);
void note_collision_d(Model *model, UINT8 index);
void note_collision_f(Model *model, UINT8 index);


#endif 