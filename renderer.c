/*---------------------------------------------------------
/ ID Header:
/   Authors: 	Andrew Boisvert, Kyle Scidmore
/   Emails: 		abois526@mtroyal.ca, kscid125@mtroyal.ca
/   File Name:	RASTER.C
/   Citations:  
/     - https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
/     - 
/
/
/ Program Purposes:
/   Library of functions to render screen elements
/------------------------------------------------------------*/
#include <stdio.h>
#include <osbind.h>
#include "super.h"
#include "types.h"
#include "renderer.h"
#include "model.h"
#include "RASTER.H"
#include "bitmaps.h"
#include "RAST_ASM.h"
#include "events.h"
#include "effects.h"
#include "psg.h"
#include "globals.h"


/*---------- FUNCTION: init_scene ----------------------
/  PURPOSE:
/  	Renders the initial game scene
/  
/  CALLER INPUT:
/    UINT8 *base
/  	- Starting point of the frame buffer (8bit)
/    UINT32 *base
/  	- Starting point of the frame buffer (32bit)
/    Model *model
/  	- Address of the game model
/  
/  CALLER OUTPUT:
/    Returns Void
/  
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/   
/--------------------------------------------------------*/
void init_scene(UINT8 *base, UINT32 *base32, Model *model){

    clear_screen(base);
    render_frets(base32, model);
    render_fretboard(base);
    render_start_score(base32, model);
    render_x(base32, model);
    render_start_multiplier(base32, model);
    render_start_failbar(base32, model);

}

/*---------- FUNCTION: render_next ---------------------
/  PURPOSE:
/ 	Renders the next frame along with a new note if needed
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_next(UINT32 *base, Model *model){

    render_active_notes(base, model);
    render_score(base, model);
    render_multiplier(base, model);
    render_failbar(base, model);
    render_frets(base, model);
   
}

/*---------- FUNCTION: render_splashscreen ---------------
/  PURPOSE:
/ 	Renders the games splashscreen
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_splashscreen(UINT8* base){

    int i, j;

    for (i = 0; i < SCREEN_HEIGHT; i++) {
        
        for (j = 0; j < SCREEN_WIDTH >> 3; j++) {

            plot_bitmap_8(base, SCREEN_X + j << 3, SCREEN_Y + i, splashscreen + i * (SCREEN_WIDTH >> 3) + j, 1);

        }
    }


}

/*---------- FUNCTION: render_active_notes ---------------
/  PURPOSE:
/ 	de-renders and re-renders all active notes
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_active_notes(UINT32 *base, Model *model){


    int i;

    for(i = 0; i< NOTES_SIZE ; i++){

        /*iterate through note arrays, for active notes: clear note and render*/
    
        if(model->lanes[FRET_A].notes[i].is_active == TRUE){
            clear_32(base, model->lanes[FRET_A].notes[i].pos_x, model->lanes[FRET_A].notes[i].pos_y - 1, model->lanes[FRET_A].notes[i].size_y);
            plot_bitmap_32(base, model->lanes[FRET_A].notes[i].pos_x, model->lanes[FRET_A].notes[i].pos_y, note_map, model->lanes[FRET_A].notes[i].size_y);

            if(model->lanes[FRET_A].notes[i].pos_y >= FRET_BOTTOM){
                
                model->lanes[FRET_A].notes[i].is_active = FALSE;
                if(!model->lanes[FRET_A].notes[i].is_played){
                    enter_super();
                    play_note_not_played_fx();
                    stop_sound_channel_c();
                    exit_super();

                }
                clear_32(base, model->lanes[FRET_A].notes[i].pos_x, model->lanes[FRET_A].notes[i].pos_y, model->lanes[FRET_A].notes[i].size_y);

            }
            
        }

        if(model->lanes[FRET_S].notes[i].is_active == TRUE){

            clear_32(base, model->lanes[FRET_S].notes[i].pos_x, model->lanes[FRET_S].notes[i].pos_y - 1, model->lanes[FRET_S].notes[i].size_y); 
            plot_bitmap_32(base, model->lanes[FRET_S].notes[i].pos_x, model->lanes[FRET_S].notes[i].pos_y, note_map, model->lanes[FRET_S].notes[i].size_y);

            if(model->lanes[FRET_S].notes[i].pos_y >= FRET_BOTTOM){
                
                model->lanes[FRET_S].notes[i].is_active = FALSE;
                if(!model->lanes[FRET_S].notes[i].is_played){
                    enter_super();
                    play_note_not_played_fx();
                    stop_sound_channel_c();
                    exit_super();
                }
                clear_32(base, model->lanes[FRET_S].notes[i].pos_x, model->lanes[FRET_S].notes[i].pos_y, model->lanes[FRET_S].notes[i].size_y);

            }
        }

        if(model->lanes[FRET_D].notes[i].is_active == TRUE){

            clear_32(base, model->lanes[FRET_D].notes[i].pos_x, model->lanes[FRET_D].notes[i].pos_y - 1, model->lanes[FRET_D].notes[i].size_y);
            plot_bitmap_32(base, model->lanes[FRET_D].notes[i].pos_x, model->lanes[FRET_D].notes[i].pos_y, note_map, model->lanes[FRET_D].notes[i].size_y);

            if(model->lanes[FRET_D].notes[i].pos_y >= FRET_BOTTOM){
                
                model->lanes[FRET_D].notes[i].is_active = FALSE;
                if(!model->lanes[FRET_D].notes[i].is_played){
                    enter_super();
                    play_note_not_played_fx();
                    stop_sound_channel_c();
                    exit_super();
                }
                clear_32(base, model->lanes[FRET_D].notes[i].pos_x, model->lanes[FRET_D].notes[i].pos_y, model->lanes[FRET_D].notes[i].size_y);

            }
        }

        if(model->lanes[FRET_F].notes[i].is_active == TRUE){

            clear_32(base, model->lanes[FRET_F].notes[i].pos_x, model->lanes[FRET_F].notes[i].pos_y - 1, model->lanes[FRET_F].notes[i].size_y);
            plot_bitmap_32(base, model->lanes[FRET_F].notes[i].pos_x, model->lanes[FRET_F].notes[i].pos_y, note_map, model->lanes[FRET_F].notes[i].size_y);

            if(model->lanes[FRET_F].notes[i].pos_y >= FRET_BOTTOM){
                
                model->lanes[FRET_F].notes[i].is_active = FALSE;
                if(!model->lanes[FRET_F].notes[i].is_played){
                    enter_super();
                    play_note_not_played_fx();
                    stop_sound_channel_c();
                    exit_super();
                }
                clear_32(base, model->lanes[FRET_F].notes[i].pos_x, model->lanes[FRET_F].notes[i].pos_y, model->lanes[FRET_F].notes[i].size_y);

            }
        }
    }

}
void clear_active_notes(UINT32 *base, Model *model){


    int i;

    for(i = 0; i< NOTES_SIZE ; i++){

        /*iterate through note arrays, for active notes: clear note and render*/
    
        if(model->lanes[FRET_A].notes[i].is_active == TRUE){
            
            clear_32(base, model->lanes[FRET_A].notes[i].pos_x, model->lanes[FRET_A].notes[i].pos_y, model->lanes[FRET_A].notes[i].size_y);
            
        }

        if(model->lanes[FRET_S].notes[i].is_active == TRUE){
            
            clear_32(base, model->lanes[FRET_S].notes[i].pos_x, model->lanes[FRET_S].notes[i].pos_y, model->lanes[FRET_S].notes[i].size_y);

        }

        if(model->lanes[FRET_D].notes[i].is_active == TRUE){
            
            clear_32(base, model->lanes[FRET_D].notes[i].pos_x, model->lanes[FRET_D].notes[i].pos_y, model->lanes[FRET_D].notes[i].size_y);

        }

        if(model->lanes[FRET_F].notes[i].is_active == TRUE){

            clear_32(base, model->lanes[FRET_F].notes[i].pos_x, model->lanes[FRET_F].notes[i].pos_y, model->lanes[FRET_F].notes[i].size_y);
        }
    }

}
/*---------- FUNCTION: clear_top ---------------------
/  PURPOSE:
/ 	Clears top of the lane to deal with weird visual bug
/   of notes slowly drawing themselves
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void clear_top(UINT32 *base, Model *model){

    black_32(base, model->lanes[FRET_A].notes[FRET_A].pos_x, BOARD_Y, 32);
    black_32(base, model->lanes[FRET_S].notes[FRET_S].pos_x, BOARD_Y, 32);
    black_32(base, model->lanes[FRET_D].notes[FRET_D].pos_x, BOARD_Y, 32);
    black_32(base, model->lanes[FRET_F].notes[FRET_F].pos_x, BOARD_Y, 32);
    
}

/*---------- FUNCTION: render_frets ---------------------
/  PURPOSE:
/ 	Renders the 4 frets
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_frets(UINT32 *base, Model *model) 
{  

    plot_bitmap_32(base, model->frets[FRET_A].pos_x, model->frets[FRET_A].pos_y, a_map, model->frets[FRET_A].size_y);
    plot_bitmap_32(base, model->frets[FRET_S].pos_x, model->frets[FRET_S].pos_y, s_map, model->frets[FRET_S].size_y);
    plot_bitmap_32(base, model->frets[FRET_D].pos_x, model->frets[FRET_D].pos_y, d_map, model->frets[FRET_D].size_y);
    plot_bitmap_32(base, model->frets[FRET_F].pos_x, model->frets[FRET_F].pos_y, f_map, model->frets[FRET_F].size_y);

}

/*---------- FUNCTION: render_fretboard -----------------
/  PURPOSE:
/ 	Renders the 4 fretboard lanes and upper bar
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_fretboard(UINT8 *base)
{
    int i, start_y, start_x;
    start_y = START_Y;
    start_x = LANE_1_LEFT;

    for(i = 0; i < LINE_SIZE; i++)
    {

        plot_h_line(base, START_X, END_X, start_y);
        
        start_y += 1;

    }

    /* Plot first track*/
    for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }
    
    start_x = LANE_1_RIGHT;

      for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }

    /*Plot second track*/

    start_x = LANE_2_LEFT;
    
    for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }
    
    start_x = LANE_2_RIGHT;

      for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }

    /*plot third track*/
    start_x = LANE_3_LEFT;
    
    for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }
    
    start_x = LANE_3_RIGHT;

      for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }

    /*plot fourth track*/
    start_x = LANE_4_LEFT;
    
    for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }
    
    start_x = LANE_4_RIGHT;

      for(i = 0; i < LINE_SIZE; i++)
    {
        vertical_line(base, start_x, BOARD_Y, BOARD_HEIGHT);

        start_x += 1;

    }

}

/*---------- FUNCTION: render_start_score ----------------
/  PURPOSE:
/ 	Renders the initial score
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_start_score(UINT32 *base, Model *model){

    int pos_y = model->score.pos_y;
    int height = model->score.size_y;

    plot_bitmap_32(base, model->score.ones_x, pos_y, zero_map, height);
    plot_bitmap_32(base, model->score.tens_x, pos_y, zero_map, height);
    plot_bitmap_32(base, model->score.hunds_x, pos_y, zero_map, height);
    plot_bitmap_32(base, model->score.thous_x, pos_y, zero_map, height);

}

/*---------- FUNCTION: render_score ---------------------
/  PURPOSE:
/ 	Renders the updated score based on models value
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_score(UINT32 *base, Model *model){

    UINT16 value, ones, tens, hundreds, thousands, height, pos_y;
    UINT32 *num_maps[] = {zero_map, one_map, two_map, three_map, four_map, five_map, six_map, seven_map, eight_map, nine_map};

    if(model->score.updated_flag == TRUE){

        height = model->score.size_y;

        pos_y = SCORE_Y;

        value = model->score.value;

        ones = value % 10;         
        tens = (value / 10) % 10;    
        hundreds = (value / 100) % 10;
        thousands = (value / 1000); 
    
        if(ones != model->score.prev_ones){

            model->score.prev_ones = ones;

            clear_32(base, model->score.ones_x, pos_y, height);
            plot_bitmap_32(base, model->score.ones_x, pos_y, num_maps[ones], height);

        }

        if(tens != model->score.prev_tens){

            model->score.prev_tens = tens;

            clear_32(base, model->score.tens_x, pos_y, height);
            plot_bitmap_32(base, model->score.tens_x, pos_y, num_maps[tens], height);

        }

        if(hundreds != model->score.prev_hunds){

            model->score.prev_hunds = hundreds;
            clear_32(base, model->score.hunds_x, pos_y, height);
            plot_bitmap_32(base, model->score.hunds_x, pos_y, num_maps[hundreds], height);

        }

        if(thousands != model->score.prev_thous){

            model->score.prev_thous = thousands;

            clear_32(base, model->score.thous_x, pos_y, height);
            plot_bitmap_32(base, model->score.thous_x, pos_y, num_maps[thousands], height);

        }

         model->score.updated_flag = FALSE;
    }
}

/*---------- FUNCTION: render_x -------------------------
/  PURPOSE:
/ 	Renders the X for the multiplier
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_x(UINT32 *base, Model *model){
    
    plot_bitmap_32(base, model->multiplier.pos_x, model->multiplier.pos_y, x_map, model->multiplier.digit_size_y);

}

/*---------- FUNCTION: render_start_multiplier -----------
/  PURPOSE:
/ 	Renders the initial multiplier number
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_start_multiplier(UINT32 *base, Model *model){

    int pos_x = model->multiplier.pos_x + 32;
    int pos_y = model->multiplier.pos_y;
    int height = model->multiplier.digit_size_y;

    plot_bitmap_32(base, pos_x, pos_y, one_map, height);

}

/*---------- FUNCTION: render_multiplier -----------------
/  PURPOSE:
/ 	Renders the updated multipler number based 
/   on the models value
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/  
/--------------------------------------------------------*/
void render_multiplier(UINT32 *base, Model *model)
{
    int pos_x = model->multiplier.pos_x + 32;
    int pos_y = 0;
    int height = model->multiplier.digit_size_y;

    if(model->multiplier.prev_value != model->multiplier.value){


        if(model->multiplier.value == 1){
            
            clear_32(base, pos_x, pos_y, height);
            plot_bitmap_32(base, pos_x, pos_y, one_map, height);

        }
        else if(model->multiplier.value == 2){

            clear_32(base, pos_x, pos_y, height);
            plot_bitmap_32(base, pos_x, pos_y, two_map, height);

        }
        else if(model->multiplier.value == 4){

            clear_32(base, pos_x, pos_y, height);
            plot_bitmap_32(base, pos_x, pos_y, four_map, height);

        }
        else {

            clear_32(base, pos_x, pos_y, height);
            plot_bitmap_32(base, pos_x, pos_y, eight_map, height);

        }

        model->multiplier.prev_value = model->multiplier.value;

    }

}

/*---------- FUNCTION: render_failbar -------------------
/  PURPOSE:
/   Renders the starting failbar
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/   None
/--------------------------------------------------------*/
void render_start_failbar(UINT32 *base, Model *model){

    int pos_y, sec_one, sec_two, sec_three, sec_four, sec_five, sec_six, height;
    
    pos_y = model->fail_bar.pos_y;
    height = model->fail_bar.size_y;
    sec_one = model->fail_bar.pos_x;
    sec_two = model->fail_bar.pos_x + 32;
    sec_three = model->fail_bar.pos_x + 64;
    sec_four = model->fail_bar.pos_x + 96;
    sec_five = model->fail_bar.pos_x + 128;
    sec_six = model->fail_bar.pos_x + 160;
        
    
    plot_bitmap_32(base, sec_one, pos_y, LEF_fail, height);
    plot_bitmap_32(base, sec_two, pos_y, MF_fail, height);
    plot_bitmap_32(base, sec_three, pos_y, MF_fail, height);
    plot_bitmap_32(base, sec_four, pos_y, ME_fail, height);
    plot_bitmap_32(base, sec_five, pos_y, ME_fail, height);
    plot_bitmap_32(base, sec_six, pos_y, REE_fail, height);

}

/*---------- FUNCTION: render_failbar -------------------
/  PURPOSE:
/   Renders the failbar based on the models value
/ 
/  CALLER INPUT:
/   UINT32 *base
/ 	- Starting point of the frame buffer
/   Model *model
/   - Address of the game model
/
/  CALLER OUTPUT:
/   Returns Void
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/   None
/--------------------------------------------------------*/
void render_failbar(UINT32 *base, Model *model)
{
    int pos_y, sec_one, sec_two, sec_three, sec_four, sec_five, sec_six, height;
    
    pos_y = model->fail_bar.pos_y;
    height = model->fail_bar.size_y;
    sec_one = model->fail_bar.pos_x;
    sec_two = model->fail_bar.pos_x + 32;
    sec_three = model->fail_bar.pos_x + 64;
    sec_four = model->fail_bar.pos_x + 96;
    sec_five = model->fail_bar.pos_x + 128;
    sec_six = model->fail_bar.pos_x + 160;


    if(model->fail_bar.value == 0 ){

        clear_32(base, sec_one, pos_y, height);
        plot_bitmap_32(base, sec_one, pos_y, LEE_fail, height);

    }
    else if(model->fail_bar.value == 20 ){

        plot_bitmap_32(base, sec_one, pos_y, LEF_fail, height);
        clear_32(base, sec_two, pos_y, height);
        plot_bitmap_32(base, sec_two, pos_y, ME_fail, height);

    }
    else if(model->fail_bar.value == 40 ){

        plot_bitmap_32(base, sec_two, pos_y, MF_fail, height);
        clear_32(base, sec_three, pos_y, height);
        plot_bitmap_32(base, sec_three, pos_y, ME_fail, height);

    }
    else if(model->fail_bar.value == 60 ){

        plot_bitmap_32(base, sec_three, pos_y, MF_fail, height);
        clear_32(base, sec_four, pos_y, height);
        plot_bitmap_32(base, sec_four, pos_y, ME_fail, height);

    }
    else if(model->fail_bar.value == 80 ){

        plot_bitmap_32(base, sec_four, pos_y, MF_fail, height);
        clear_32(base, sec_five, pos_y, height);
        plot_bitmap_32(base, sec_five, pos_y, ME_fail, height);

    }
    else if(model->fail_bar.value == 100 ){

        plot_bitmap_32(base, sec_five, pos_y, MF_fail, height);
        clear_32(base, sec_six, pos_y, height);
        plot_bitmap_32(base, sec_six, pos_y, REE_fail, height);

    }
    else{

        plot_bitmap_32(base, sec_six, pos_y, REF_fail, height);

    }
}