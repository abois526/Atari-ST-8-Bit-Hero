/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   inputs.h
/  Citations:   
/   
/
/
/  Program Purposes:
/    Header file for inputs.c
/--------------------------------------------------------*/
#ifndef INPUTS_H
#define INPUTS_H

#include "types.h"
#include "model.h"
#include "globals.h"

UINT32 get_time();
UINT8 read_char();
void play_on_fret(Model *model, FRET_POS fret);



#endif