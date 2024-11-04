;---------- ID HEADER -------------------------------------
;  Authors:	Andrew Boisvert, Kyle Scidmore
;  Emails: 	abois526@mtroyal.ca, kscid125@mtroyal.ca 
;  File Name:	isr_asm.s
;  Citations:  
;    - N/A
;
;  Program Purposes:
;    Handles all of the assembly code for our custom ISRs 
;    that is not possible with the C programming language,
;    i.e. register preservation and restoration.
;----------------------------------------------------------

; xdefs and xrefs 
	xdef 	_vbl_isr
	xref	_do_vbl_isr


;---------- SUBROUTINE: _vbl_isr --------------------------
;  PURPOSE:
;    This is our custom VBL ISR which calls upon the 
;    function do_vbl_isr() in the main game file. 
;
;  CALLER INPUT:
;    N/A
;
;  CALLER OUTPUT:
;    N/A
;
;  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
;    N/A
;----------------------------------------------------------
_vbl_isr:	movem.l d0-d2/a0-a2,-(sp)
		jsr	_do_vbl_isr
		movem.l (sp)+,d0-d2/a0-a2
		rte
