/*
 ID Header:
   Authors: 	Andrew Boisvert, Kyle Scidmore
   Emails: 		abois526@mtroyal.ca, kscid125@mtroyal.ca
   File Name:	RASTER.C
   Citations:  
     - https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
     - 


 Program Purposes:
   Library of Raster Plotting Routines
*/

#include <stdio.h>
#include <osbind.h>
#include "raster.h"
#include "types.h"

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 400

/*Prototype for ASM function*/
void set_video();

/*------------- FUNCTION: get_video_base ---------------
/
/	PURPOSE:
/	  Retrieves the base address of the video buffer
/	
/	CALLER INPUT:
/	  None
/	
/	CALLER OUTPUT:
/	  UINT8 address: A pointer to the base address of the video buffer
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - tested and working as expected 
/------------------------------------------------------*/
UINT8* get_video_base()
{
	UINT8 *high = 0xFFFF8201L;
	UINT8 *low = 0xFFFF8203L;
	long address;
	long old_ssp;
	
	old_ssp = Super(0);
	
	/*Combine high and low bytes and set address*/
	address = ((long)(*high) << 16) | ((long)(*low) << 8);
	
	Super(old_ssp);
	
	return (UINT8*)(address);
}

/*------------- FUNCTION: set_video_base ----------------
/
/	PURPOSE:
/	  Align and sets the video base address using the
/ 	  given buffer pointer
/	
/	CALLER INPUT:
/	  UINT32 *buffer 
/		- Pointer to the buffer to be set
/	
/	CALLER OUTPUT:
/	  returns void 
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - tested and working as expected 
/------------------------------------------------------*/
void set_video_base(UINT32 *buffer){

	long buffer_address = (long)buffer;
	long old_ssp;
	UINT16 address;

	old_ssp = Super(0);

	address = buffer_address >> 8;

	set_video(address);

	Super(old_ssp);


}


/*------------- FUNCTION: plot_pixel --------------------
/
/	PURPOSE:
/	  Plots a pixel to the screen at the provided coordinates.
/	
/	CALLER INPUT:
/	  UINT8 *base 
/	    - starting point of the frame buffer 
/	  int x 
/	    - x coordinate for plotting location 
/	  int y 
/	    - y coordinate for plotting location 
/	
/	CALLER OUTPUT:
/	  returns void 
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - tested and working as expected 
/------------------------------------------------------*/
void plot_pixel(UINT8 *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		*(base + y * 80 + (x >> 3)) |= 1 << (7 - (x & 7));
	}
}

/*----------- FUNCTION: plot_h_line -----------------
/	
/	PURPOSE:
/	  Plots a horizontal line to the screen between
/	  the provided coordinates.
/	
/	CALLER INPUT:
/	  char *base 
/	    - starting point of the frame buffer 
/	  int x1
/	    - starting coordinate for the line 
/	  int x2
/	    - ending coordinate for the line 
/	  int y 
/	    - y coordinate for plotting location 
/	
/	CALLER OUTPUT:
/	  returns void 
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - briefly tested and seems to be working, need to 
/	    complete more thorough testing 
/-----------------------------------------------------*/
void plot_h_line(UINT8 *base, int x1, int x2, int y)
{
	UINT8 *start, *end;
	
	/* check if in screen bounds */
	if (x1 >= 0 && x1 < SCREEN_WIDTH &&
		x2 >= 0 && x2 < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT)
	{
		/* ensure x1 is always less than x2 */
		if (x2 < x1)
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
		}
		
		/* 
		calculate the memory addresses for the 
		start and end of the line 
		- base + y calcs starting address of the line 
		- bitshift operations calculate the byte offset 
		  for x1 and x2 within the line */
		start = base + y * 80 + (x1 >> 3);
		end = base + y * 80 + (x2 >> 3);
		
		if (start == end)
		{
			*start |= (0xFF >> (x1 & 7)) & (0xFF << (7 - (x2 & 7)));
		}
		else 
		{
			if (x1 & 7)
			{
				*start |= (0xFF >> (x1 & 7));
				start++;
			}
			
			if ((x2 & 7) != 7)
			{
				*end |= (0xFF << (7 - (x2 & 7)));
			}
			
			while (start < end)
			{
				*start = 0xFF;
				start++;
			}	
		}
	}
}


/*-------------- FUNCTION: plot_gen_line ---------------
/
/	PURPOSE:
/	  Plots an approximation of a straight line between two coordinates.
/	
/	CALLER INPUT:
/	  UINT8 *base 
/	    - starting point of the frame buffer 
/	  int x0
/	    - starting x-coordinate for the line 
/	  int y0
/	    - starting y-coordinate for the line 
/	  int x1
/	    - ending x-coordinate for the line 
/	  int y1
/	    - ending y-coordinate for the line 
/	
/	CALLER OUTPUT:
/	  returns void 
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS: 
/	  - relies on the plot_line_low and plot_line_high subroutines
/	  
/------------------------------------------------------*/
void plot_gen_line(UINT8 *base, int x0, int y0, int x1, int y1)
{
	/*
	
	*/
	if (x0 >= 0 && x0 < SCREEN_WIDTH &&
		x1 >= 0 && x1 < SCREEN_WIDTH &&
		y0 >= 0 && y0 < SCREEN_HEIGHT &&
		y1 >= 0 && y1 < SCREEN_HEIGHT)
	{
		if (abs_val(y1 - y0) < abs_val(x1 - x0))
		{
			if (x0 > x1)
			{
				plot_line_low(base, x1, y1, x0, y0);
			}
			else
			{
				plot_line_low(base, x0, y0, x1, y1);
			}
		}
		else
		{
			if (y0 > y1)
			{
				plot_line_high(base, x1, y1, x0, y0);
			}
			else
			{
				plot_line_high(base, x0, y0, x1, y1);
			}
		}
	}
}


/*------------- FUNCTION: plot_line_low --------------
/	
/	PURPOSE:
/	  Sub-function for plot_genline. Handles the case when the line 
/	  has an absolute slope less than or equal to 1 (more horizontal).
/	
/	CALLER INPUT:
/	  UINT8 *base 
/	    - starting point of the frame buffer 
/	  int x1
/	    - starting x-coordinate for the line 
/	  int x2
/	    - ending x-coordinate for the line 
/	  int y1
/	    - starting y-coordinate for the line 
/	  int y2
/	    - ending y-coordinate for the line 
/	
/	CALLER OUTPUT:
/	  returns void 
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - tested and working as expected 
/-----------------------------------------------------*/
void plot_line_low(UINT8 *base, int x0, int y0, int x1, int y1)
{
	int dx, dy, yi, d, y, x;
	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;

	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}

	d = (2 * dy) - dx;
	y = y0;

	for (x = x0; x <= x1; x++)
	{
		plot_pixel(base, x,  y);
		if (d > 0)
		{
			y = y + yi;
			d = d + (2 * (dy - dx));
		}
		else
		{
			d = d + 2 * dy;
		}
	}
}

/*------------- FUNCTION: plot_line_high --------------
/	
/	PURPOSE:
/	  Sub-function for plot_genline. Handles the case when the line 
/	  has an absolute slope greater than 1 (more vertical).
/	
/	CALLER INPUT:
/	  UINT8 *base 
/	    - starting point of the frame buffer 
/	  int x1
/	    - starting x-coordinate for the line 
/	  int x2
/	    - ending x-coordinate for the line 
/	  int y1
/	    - starting y-coordinate for the line 
/	  int y2
/	    - ending y-coordinate for the line 
/	
/	CALLER OUTPUT:
/	  returns void 
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - tested and working as expected  
/-------------------------------------------------------*/
void plot_line_high(UINT8 *base, int x0, int y0, int x1, int y1)
{
	int dx, dy, xi, d, x, y;

	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;

	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = x0;

	for (y = y0; y <= y1; y++)
	{
		plot_pixel(base, x, y);
		if (d > 0) 
		{
			x = x + xi;
			d = d + (2 * (dx - dy));
		}
		else
		{
			d = d + 2 * dx;
		}
	}
}

/*------------ FUNCTION: abs_val ------------------------
/	
/	PURPOSE:
/	  Produces the absolute value of an integer.
/	
/	CALLER INPUT:
/	  int value
/	    - the integer the operation will be 
/		  performed upon 
/	
/	CALLER OUTPUT:
/	  int result 
/	    - the absolute value of the input value
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - Limitations:
/	    - only works with integers 
/		- helper function only designed to be used 
/		  by plot_genline 
/------------------------------------------------------*/
int abs_val(int value)
{
	int result;
	if (value < 0)
	{
		result = -value;	
	}
	else 
	{
		result = value;
	}

	return result;
}

/*------------- FUNCTION: vertical_line ------------------
/	
/	PURPOSE:
/	  Plots a vertical line from a given (x,y) with a given
/	  height
/	
/	CALLER INPUT:
/	  UINT8 *base 
/	    - starting point of the frame buffer 
/	  int x 
/	    - x coordinate for defining the hotspot 
/	  int y 
/	    - y coordinate for defining the hotspot 
/	  int height 
/	    - the height of the line to be plotted

/	CALLER OUTPUT:
/	  Returns Void
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - tested and working as expected 
/---------------------------------------------------------*/
void vertical_line(UINT8 *base, int x, int y_start, int height)
{
	int i;
  
	for(i = 0; i < height; i++){

		*(base + (y_start + i) * 80 + (x >> 3)) |= 1 << 7 -((x & 7));

	}
	
}

/*------------- FUNCTION: plot_bitmap_32 ----------
/
/	PURPOSE:
/		Plots a 32 pixel wide bitmap
/	
/	CALLER INPUT:
/	  UINT32 *base
/		-Starting point of the frame buffer
/	  int x
/		- x coordinate for defining the hotspot
/	  int y
/		- y coordinate for defining the hotspot
/	  const UINT32 *bitmap
/		- The bitmap to be plotted
/	  unsigned int height
/		-The height of the bitmap to be plotted
/	
/	CALLER OUTPUT:
/	  Returns Void
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  -  Only plots to multiples of 32 bits
/----------------------------------------------------*/
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
	
	int i;

	UINT32 *plot = (base + ((y + i) * 20 ) + (x >> 5)); 
	
    	
	for (i = 0; i < height; i++) 
	{        

            *plot |= bitmap[i]; 
			      plot += 20;
	}
        
    
}

/*------------- FUNCTION: clear_32 -----------------
/
/	PURPOSE:
/		clears a 32 pixel wide area wiht a given height
/	
/	CALLER INPUT:
/	  UINT32 *base
/		-Starting point of the frame buffer
/	  int x
/		- x coordinate for defining the hotspot
/	  int y
/		- y coordinate for defining the hotspot
/	  unsigned int height
/		-The height of the bitmap to be plotted
/	
/	CALLER OUTPUT:
/	  Returns Void
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  - tested and working as expected 
/----------------------------------------------------*/
void clear_32(UINT32 *base, int x , int y, unsigned int height){

	int i;

	UINT32 *plot = (base + ((y + i) * 20 ) + (x >> 5)); 
	
    	
	for (i = 0; i < height; i++) 
	{        

            *plot = 0; 
			plot += 20;
	}
}

void black_32(UINT32 *base, int x , int y, unsigned int height){

	int i;

	UINT32 *plot = (base + ((y + i) * 20 ) + (x >> 5)); 
	
    	
	for (i = 0; i < height; i++) 
	{        

            *plot = 0xFFFFFFFF; 
			plot += 20;
	}
}
	
/*----------- FUNCTION: plot_bitmap_16 -------------
/
/	PURPOSE:
/	  Plots a 16 pixel wide bitmap
/	
/	CALLER INPUT:
/	  UINT16 *base
/		-Starting point of the frame buffer
/	  int x
/		- x coordinate for defining the hotspot
/	  int y
/		- y coordinate for defining the hotspot
/	  const UINT16 *bitmap
/		- The bitmap to be plotted
/	  unsigned int height
/		-The height of the bitmap to be plotted
/	
/	CALLER OUTPUT:
/	  Returns Void
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  -  Only plots to multiples of 16 bits
/----------------------------------------------------*/
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height) /*Edit to match 32 bit for speed*/
{

	int i = 0;
	
	for (i = 0; i < height; i++) 
	{        

            *(base + ((y + i) * 40 ) + (x >> 4))  = bitmap[i];
    
  }
	
	
}

/*----------- FUNCTION: plot_bitmap_8 -------------
/
/	PURPOSE:
/	  Plots an 8 pixel wide bitmap
/	
/	CALLER INPUT:
/	  UINT8 *base
/		-Starting point of the frame buffer
/	  int x
/		- x coordinate for defining the hotspot
/	  int y
/		- y coordinate for defining the hotspot
/	  const UINT8 *bitmap
/		- The bitmap to be plotted
/	  unsigned int height
/		-The height of the bitmap to be plotted
/	
/	CALLER OUTPUT:
/	  Returns Void
/	
/	ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/	  -  Only plots to multiples of 8 bits 
/----------------------------------------------------*/
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int height) /*Edit to match 32 bit for speed*/
{

	int i = 0;
	
	for (i = 0; i < height; i++) 
	{        

            *(base + ((y + i) * 80 ) +  (x >> 3) )  = bitmap[i];
    
    }
	
	
}
