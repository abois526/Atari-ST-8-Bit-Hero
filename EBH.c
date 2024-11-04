/*---------- ID HEADER ------------------------------------
/  Authors:     Andrew Boisvert, Kyle Scidmore
/  Emails:      abois526@mtroyal.ca, kscid125@mtroyal.ca 
/  File Name:   ebh.c
/  Citations:   
/    
/
/  Program Purposes:
/    Main game module
/--------------------------------------------------------*/
#include <osbind.h>
#include "types.h"
#include "model.h"
#include "renderer.h"
#include "rast_asm.h"
#include "inputs.h"
#include "events.h"
#include "raster.h"
#include "ebh.h"
#include "effects.h"
#include "music.h"
#include "psg.h"
#include "isr.h"
#include "isr_asm.h"
#include "vbl.h"
#include "globals.h"
#include "super.h"
#include "ikbd.h"

#define ESC 27
#define BUFFER_SIZE 32256
#define LAST_NOTE 19
#define NO_CHAR '\0'

Model model;
short render_request = 0;


UINT8 buffer_array[BUFFER_SIZE];



int main()
{
    UINT8 ch;
    UINT8 *original_buffer = get_video_base();
    UINT8 *base = get_video_base();
    Vector orig_vector;

    init_char_buffer();
    install_ikbd_vector();


    clear_screen(base);
    render_splashscreen(base);


    orig_vector = install_vector(VEC_VBL_ISR, vbl_isr);

    while(ch != ESC){

        ch = read_char();

        if(ch == ' '){
            enter_super();
            play_menu_selection_fx();
            exit_super();
            game_loop();
            break;
        }

    }

    install_vector(VEC_VBL_ISR, orig_vector);

    restore_ikbd_vector();

    set_video_base((UINT32*)original_buffer);

    return 0;
    
}

/*---------- FUNCTION: game_loop -----------------------
/  PURPOSE:
/    Main gameplay loop
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
void game_loop(){

    UINT32 *front_buffer, *back_buffer, *curr_buffer;

    /*Input Variables*/
    UINT8 ch;
    BOOL quit = FALSE;

    /*Set Buffers Up*/
    set_buffer(&front_buffer, &back_buffer, buffer_array);

    /*Initalize Game Model/Render Start Scene*/
    init_model(&model);

    init_scene((UINT8*) front_buffer, front_buffer, &model);

    back_buffer = front_buffer;

    curr_buffer = back_buffer;

    game_on = TRUE;

    while (!quit){

        ch = read_char();
        if (ch != NO_CHAR){
            switch (ch) {
                case 'a':
                    play_on_fret(&model, FRET_A);
                    break;
                case 's':
                    play_on_fret(&model, FRET_S);
                    break;
                case 'd':
                    play_on_fret(&model, FRET_D);
                    break;
                case 'f':
                    play_on_fret(&model, FRET_F);
                    break;
                case ESC: 
                    quit = TRUE;
                    break;
            }
        
        }

        if(render_request == 1){
            
            if (!model.lanes[FRET_A].notes[LAST_NOTE].is_active){

		    	render_next(curr_buffer, &model);
                set_video_base(curr_buffer);
                swap_buffer(front_buffer, back_buffer, &curr_buffer);


            }else{

                stop_gen = TRUE;
		    	render_next(curr_buffer, &model);
                set_video_base(curr_buffer);
                swap_buffer(front_buffer, back_buffer, &curr_buffer);

                if(!model.lanes[FRET_A].notes[LAST_NOTE].is_active){
                    enter_super();
                    stop_sound_channel_a();
                    play_game_over_win_fx();
                    exit_super();
                    break;
                }
            }
            render_request = 0;
        }

        if (model.fail_bar.value == 0) {
            render_failbar(curr_buffer, &model);
            enter_super();
            stop_sound_channel_a();
            play_game_over_lose_fx();
            exit_super();
            break;
        }

    }
    

}

/*---------- FUNCTION: set_buffer -------------------------
/  PURPOSE:
/    Finds a 256 byte aligned address and sets the front 
/    and back buffer pointers.
/ 
/  CALLER INPUT:
/    - front_buffer: Pointer to the front buffer pointer
/    - back_buffer: Pointer to the back buffer pointer
/    - buffer_array: Array containing the buffer memory
/
/  CALLER OUTPUT:
/    None
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    None
/--------------------------------------------------------*/
void set_buffer(UINT32** front_buffer, UINT32** back_buffer, UINT8 buffer_array[]){

    UINT8 *address = buffer_array;

	while (((UINT32)address) % 256 != 0)
	{
		address++;
	}

	*back_buffer = (UINT32*)address;
    *front_buffer = (UINT32*)get_video_base();


}

/*---------- FUNCTION: swap_buffer -------------------------
/  PURPOSE:
/    Swaps the current buffer pointer between front and back
/ 
/  CALLER INPUT:
/       - front_buffer: Pointer to the front buffer.
/       - back_buffer: Pointer to the back buffer.
/       - curr_buffer: Pointer to the the current buffer pointer.
/  CALLER OUTPUT:
/    none
/ 
/  ASSUMPTIONS, LIMITATIONS, KNOWN BUGS:
/    none
/--------------------------------------------------------*/
void swap_buffer(UINT32* front_buffer, UINT32* back_buffer, UINT32** curr_buffer){

    *curr_buffer = (*curr_buffer == front_buffer) ? back_buffer : front_buffer;

}
