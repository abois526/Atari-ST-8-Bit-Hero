/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   ebh.h
/  Citations:   
/    
/
/  Program Purposes:
/    Header file for ebh.c
/--------------------------------------------------------*/
#ifndef EBH_H
#define EBH_H

/*Function Prototypes*/
void game_loop();
void set_buffer(UINT32** front_buffer, UINT32** back_buffer, UINT8 buffer_array[]);
void swap_buffer(UINT32* front_buffer, UINT32* back_buffer, UINT32** curr_buffer);
void enter_super();
void exit_super();


#endif