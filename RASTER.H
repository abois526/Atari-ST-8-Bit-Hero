#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void plot_pixel(UINT8 *base, int x, int y);
void plot_h_line(UINT8 *base, int x1, int x2, int y);
void plot_gen_line(UINT8 *base, int x0, int y0, int x1, int y1);
void plot_line_low(UINT8 *base, int x0, int y0, int x1, int y1);
void plot_line_high(UINT8 *base, int x0, int y0, int x1, int y1);
int abs_val(int value);
void plot_diamond(UINT8 *base, int cx, int cy, int r);
void vertical_line(UINT8 *base, int x, int y_start, int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, 
                    unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, 
                    unsigned int height);
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap, 
                    unsigned int height);
void clear_32(UINT32 *base, int x , int y, unsigned int height);
void black_32(UINT32 *base, int x , int y, unsigned int height);
UINT8* get_video_base();
void set_video_base(UINT32 *buffer);


#endif
