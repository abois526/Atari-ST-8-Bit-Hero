;---------- ID HEADER -------------------------------------
;  Authors:	Andrew Boisvert, Kyle Scidmore 
;  Emails:	abois526@mtroyal.ca, kscid125@mtroyal.ca 
;  File Name:	ikbdisr.s 
;  Citations:	
;    - _set_ipl: code taken from interrupts slides 
;  
;  Program Purpose:
;    Handles all of the assembly code for our custom ISRs 
;    that is not possible with the C programming language,
;    i.e. register preservation and restoration.
;----------------------------------------------------------

; xdefs and xrefs
	xdef 	_ikbd_isr
	xdef	_set_ipl
	xref	_do_ikbd_isr

; constants 
in_service 	equ 	$FFFA11



;---------- SUBROUTINE: _ikbd_isr -------------------------
;  PURPOSE:
;    This is our custom IKBD ISR which calls upon the function 
;    do_ikbd_isr() in the main game file and masks the in
;	 in_service bit. 
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
_ikbd_isr:	movem.l	d0-d2/a0-a2,-(sp)
		jsr	_do_ikbd_isr 
		movem.l	(sp)+,d0-d2/a0-a2
		and.b 	#$BF,in_service
		rte


;---------- SUBROUTINE: _set_ipl --------------------------
;  PURPOSE:
;    Sets interrupt priority level.
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
_set_ipl:        
		move.w	sr,d0
		move.w	d0,-(sp)

		lsr.w 	#8,d0
		and.w 	#$0007,d0

		andi.w	#$F8FF,(sp)
		move.w	d1,-(sp)
		move.w	8(sp),d1

		lsl.w 	#8,d1
		and.w 	#$0700,d1
		or.w  	d1,2(sp)
		move.w	(sp)+,d1
		rte