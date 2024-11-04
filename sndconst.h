/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   sndconst.h
/  Citations:   
/    - Note Values: http://poi.ribbon.free.fr/tmp/freq2regs.htm 
/
/  Instructions:
/    The range of usable note values for this chip is between
/    B-0 and B-8. 
/    The range of C-5 to B-5 is given. Left shifting and right
/    shifting can be used to move up and down octaves,
/    respectively.
/    In use, left shifting the values will lower them one octave
/    and right shifting them will raise them one octave.  
/    P.S. Most of this stuff was done with keyboard hotkeys and 
/    stuff, I'm not a insane.   
/
/--------------------------------------------------------*/

#ifndef SNDCONST_H
#define SNDCONST_H

/*---------- DEFINING ENVELOPE SHAPES AND FREQ ------------------------------*/
#define ENV_SHAPE_1 0x0
#define ENV_SHAPE_2 0x4
#define ENV_SHAPE_3 0x8
#define ENV_SHAPE_4 0x9
#define ENV_SHAPE_5 0xA
#define ENV_SHAPE_6 0xB
#define ENV_SHAPE_7 0xC
#define ENV_SHAPE_8 0xD
#define ENV_SHAPE_9 0xE
#define ENV_SHAPE_10 0xF

#define ENV_FREQ 0x1F00


/*---------- DEFINING ENVELOPE SHAPES ---------------------------------------*/


/*---------- DEFINING NOTE VALUES -------------------------------------------*/
#define C5          0x0EF
#define C5_SHARP    0x0E2
#define D5          0x0D5
#define D5_SHARP    0x0C9
#define E5          0x0BE
#define F5          0x0B3
#define F5_SHARP    0x0A9
#define G5          0x09F
#define G5_SHARP    0x096
#define A5          0x08E
#define A5_SHARP    0x086
#define B5          0x07F

#endif