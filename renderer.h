#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "model.h"

/*Constant Defines*/
#define LANE_1_LEFT 156
#define LANE_1_RIGHT 192
#define LANE_2_LEFT 252
#define LANE_2_RIGHT 288
#define LANE_3_LEFT 348
#define LANE_3_RIGHT 384
#define LANE_4_LEFT 444
#define LANE_4_RIGHT 480
#define BOARD_Y 84
#define BOARD_HEIGHT 274
#define LINE_SIZE 4
#define SCREEN_X 0
#define SCREEN_Y 0
#define START_X 156
#define END_X 483
#define START_Y 80
#define ARRAY_SIZE 50
#define FRET_BOTTOM 358
#define SCORE_Y 16


/*Function Prototypes*/
void render_fretboard(UINT8 *base);
void render_frets(UINT32 *base, Model *model);
void render_score(UINT32 *base, Model *model);
void render_multiplier(UINT32 *base, Model *model);
void render_start_failbar(UINT32 *base, Model *model);
void render_failbar(UINT32 *base, Model *model);
void render_x(UINT32 *base, Model *model);
void render_start_score(UINT32 *base, Model *model);
void render_start_multiplier(UINT32 *base, Model *model);
void init_scene(UINT8 *base, UINT32 *base_long, Model *model);
void render_next(UINT32 *base, Model *model);
void render_active_notes(UINT32 *base, Model *model);
void clear_top(UINT32 *base, Model *model);
void render_splashscreen(UINT8* base);
void clear_active_notes(UINT32 *base, Model *model);

#endif