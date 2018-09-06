#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <graphics/shape.h>

#define WIDTH SCENARY_WIDTH
#define HEIGHT SCENARY_HEIGHT
#define SCENARY_WIDTH (10 * BLOCK_SIZE)
#define SCENARY_HEIGHT (20 * BLOCK_SIZE)
#define OFFSET_X ((WIDTH - SCENARY_WIDTH) / 2)

void game_init();
void game_update();
void game_render(SDL_Renderer* renderer);
void key_press(int scancode);
void key_release(int scancode);

#endif
