/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   bitmaps.h
/  Citations:   
/    
/
/  Program Purposes:
/    Header for bitmaps.c
/--------------------------------------------------------*/
#ifndef BITMAPS_H
#define BITMAPS_H

#include "types.h"

/* Fret Bitmaps*/
extern const UINT32 a_map[];
extern const UINT32 s_map[];
extern const UINT32 d_map[];
extern const UINT32 f_map[];

/*Note Bitmaps*/
extern const UINT32 note_map[];
extern const UINT32 clear_note[];

/*Number Bitmaps and X Bitmap*/
extern const UINT32 zero_map[];
extern const UINT32 one_map[];
extern const UINT32 two_map[];
extern const UINT32 three_map[];
extern const UINT32 four_map[];
extern const UINT32 five_map[];
extern const UINT32 six_map[];
extern const UINT32 seven_map[];
extern const UINT32 eight_map[];
extern const UINT32 nine_map[];
extern const UINT32 x_map[];

/*Fail Bar Bitmaps (LEF = Left End Full Etc.)*/
extern const UINT32 LEF_fail[];
extern const UINT32 LEE_fail[];
extern const UINT32 REF_fail[];
extern const UINT32 REE_fail[];
extern const UINT32 MF_fail[];
extern const UINT32 ME_fail[];


extern const UINT8 splashscreen[];

#endif