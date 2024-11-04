/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   isr.c
/  Citations:   
/    - N/A
/
/  Program Purposes:
/    The purpose of this program is to implement our own VBL 
/    ISR to replace TOS's version in order to help our game
/    to stand alone without reliance on TOS.
/--------------------------------------------------------*/

#include <osbind.h>
#include "isr.h"


/*---------- FUNCTION: install_vector ---------------------
/  PURPOSE:
/    This function installs a new ISR for a given interrupt. It does this by
/    modifying the address for the given vector number. To do this, supervisor 
/    mode must be entered, so this function also acts as a wrapper for 
/    this process.
/  
/  CALLER INPUT:
/    int num 
/      The number of the interrupt in the vector table.
/    Vector vector
/      The new ISR address that num will point to.
/  
/  CALLER OUTPUT:
/    Vector orig
/      A pointer to the original ISR that has been changed,
/      allowing the user to restore the state later.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - The original ISR must be stored while using the custom ISR and restored
/      before the program ends, or else TOS will not function properly.
/--------------------------------------------------------*/
Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2); /* request vector, over */
    
    long old_ssp = Super(0); /* we have clearance, Clarence */

    orig = *vectp;
    *vectp = vector; /* what's our vector, Victor? */
    
    Super(old_ssp);

    return orig;
}