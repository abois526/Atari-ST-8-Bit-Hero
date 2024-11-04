/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   super.c
/  Citations:   
/  
/
/  Program Purposes:
/    Functions to enter and exit supervisor mode
/--------------------------------------------------------*/
#include <osbind.h>
#include "globals.h"

long old_ssp;

/*---------- FUNCTION: enter_super -------------------------
/  PURPOSE:
/    Enters supervisor mode
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void enter_super(){

    old_ssp = Super(0);

}

/*---------- FUNCTION: exit_super -------------------------
/  PURPOSE:
/    Exits supervisor mode
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/--------------------------------------------------------*/
void exit_super(){

    Super(old_ssp);

}