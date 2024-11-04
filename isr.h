/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   isr.h
/  Citations:   
/    - N/A
/
/  Program Purpose:
/    
/--------------------------------------------------------*/

#ifndef ISR_H
#define ISR_H

#define VEC_VBL_ISR 28

typedef void (*Vector)(); 

Vector install_vector(int num, Vector vector);

#endif