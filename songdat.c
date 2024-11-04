/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   songdat.c
/  Citations:   
/ 
/
/  Program Purposes:
/    Contains data for the main game song
/--------------------------------------------------------*/

#include "songdat.h"
#include "sndconst.h"

Psg_notes channel_a[SONG_LENGTH] = {
    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 1 */
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {E5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},

    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 2 */
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {E5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},

    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 3 */
    {F5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {F5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},

    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 4 */
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {E5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},

    {E5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 5 */
    {G5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {B5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},

    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 6 */
    {F5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {F5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},

    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 7 */
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {E5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {D5<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {C5_SHARP<<2, 0x13, ENV_SHAPE_4, ENV_FREQ},

    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},            /* part 8 */
    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {G5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ},
    {A5<<3, 0x13, ENV_SHAPE_4, ENV_FREQ}
};