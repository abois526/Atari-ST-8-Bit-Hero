# 8-bit Hero

A rhythm-based game coded in C and 68000 assembly for Atari systems.

## Project Overview
*8-bit Hero* is a retro-style rhythm game where players must hit notes accurately in time with 8-bit music. Built for Atari emulation with C and 68000 assembly.

## Gameplay
Players press buttons to match incoming notes as they scroll across the screen. Hitting notes at the right time earns points, while misses decrease the fail bar, miss to many and you fail the song.

## Controls
- **A/S/D/F Buttons**: Hit notes in time with the beat.
- **Enter**: Begin the game.

## Installation
To play *8-bit Hero*, you’ll need the Steem emulator and the "full game" folder.

1. Download the "full game" folder from this repository.
2. Ensure you have the [Steem Emulator](http://steem.atari.st/) installed.
3. Navigate to the full game directory in steem.
4. Run make to generate an executable file called EBH.

## Project Structure
- EBH.c and EBH.h: Main game functions and logic.
- PSG.c and PSG.h: Handles sound generation and processing.
- RASTER.C, RASTER.H, RAST_ASM.H, RAST_ASM.S: Raster graphics processing for Atari hardware.
- bitmaps.c and bitmaps.h: Game bitmaps.
- effects.c and effects.h: Manages sound effects.
- events.c and events.h: Manages in-game events.
- globals.h: Contains global definitions and variables.
- ikbd.c, ikbd.h, ikbdisr.h, ikbdisr.s: Input processing and interrupt routines.
- inputs.c and inputs.h: Manages user input.
- isr.c, isr.h, isr_asm.h, isr_asm.s: Interrupt handling and assembly-level control.
- model.c and model.h: Manages game models and structures.
- music.c and music.h: Music playback and timing.
- renderer.c and renderer.h: Game rendering pipeline.
- sndconst.h: Constants for sound generation.
- songdat.c and songdat.h: Song data for in-game tracks.
- super.c and super.h: Supervisor-level controls and routines.
- types.h: Custom type definitions for the project.
- vbl.c: Vertical blank interrupt handling.
- Makefile: Automates the build process.
