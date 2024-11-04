		xdef	_clear_screen
		xdef	_set_video

base	equ		64		; offset from SP, not A6
ADDRESS  equ	$FFFF8201
STACK_OFFSET	equ		8



; ID Header:
;   Authors: 	Andrew Boisvert, Kyle Scidmore, Marc Schroeder
;   Emails: 	abois526@mtroyal.ca, kscid215@mtroyal.ca 
;   File Name:	RAST_ASM.S
;   Citations:  
;     - the function _clear_screen was authored by 
;       Marc Schroeder
;
; Program Purposes:
;   Data Structures: 
;     - TODO
;
;   Functions:
;     - TODO  
; 

;----- FUNCTION: _clear_screen -----
;
; PURPOSE:
;   TODO - purpose, from the caller's perspective (if not
;   perfectly clear from the name)
;
; CALLER INPUT:
;   TODO - the purpose of each input parameter (if not 
;   perfectly clear from the name)
;
; CALLER OUTPUT:
;   TODO - the purose of each output parameter and return 
;   value (if not perfectly clear from the name)
;
; ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
;   - uses movem to reduce fetch-execute cycle overhead 
;   - takes about half the number of clock cycles as the code 
;     in clear.s, and so runs in about 1/100th of a second (at
;     8Mhz) instead of 1/50th
;
;--------------------------------------------------------
_clear_screen:	movem.l		d0-7/a0-6,-(sp)
		lea		zeros,a0
		movem.l		(a0)+,d1-7/a1-6
		movea.l		base(sp),a0
		adda.l		#32000,a0
		move.w		#614,d0
fill_loop:	movem.l		d1-7/a1-6,-(a0)
		dbra		d0,fill_loop
		movem.l		d1-5,-(a0)
		movem.l		(sp)+,d0-7/a0-6
		rts
;---------------------------------------------------------

;----- FUNCTION: _set_video -----
;
; PURPOSE:
;   Sets the video base address using the provided buffer address.
;
; CALLER INPUT:
;   address - shifted address of buffer (passed on stack)
;
; CALLER OUTPUT:
;   None
;
; ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
;   - working as expected
;
;--------------------------------------------------------
_set_video:
		link	a6,#0
		movem.l	d0-d2/a0-a2,-(sp)		;Save Registers
		
		move.w	STACK_OFFSET(a6),d0		;Get buffer address from stack				
		move.l 	#ADDRESS,a0			;Load video base Hi address into a0
		movep.w d0,(a0)				;Set Buffer 
		
		movem.l	(sp)+,d0-d2/a0-a2
		unlk	a6
		rts

zeros:		ds.l		13