/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   songdat.h
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

#ifndef SONGDAT_H
#define SONGDAT_H

#include "types.h"

#define SONG_LENGTH 64


/*---------- STRUCTURE DEFINITIONS ------------------------------------------*/
/*---------- STRUCTURE: TODO ------------------------------
/  INFO:
/    Struct for the notes of a circular array for our game 
/    music using the PSG.
/  
/  ATTRIBUTES:
/    pitch      
/      note pitch (B0-B8) 
/    level      
/      5-bit value 
/      b5 = mode, b4-b0 = volume
/    env_shape   
/      4-bit value
/      b3 = CONT, b2 = ATT, b1 = ALT, b0 = HOLD
/    env_sustain 
/      8-bit value
/      higher nibble = fine tune, lower nibble = rough tune
/--------------------------------------------------------*/
typedef struct {
    int pitch;
    int level;
    int env_shape;
    unsigned int env_sustain;
} Psg_notes;

extern Psg_notes channel_a[];
extern Psg_notes channel_b[];


#endif