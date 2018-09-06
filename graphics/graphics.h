#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <graphics/shape.h>

void graphics_init();
void draw_scenary(Color scenary[10][20], SDL_Renderer* renderer, int offsetx, int offsety);
void draw_shape(Shape* shape, SDL_Renderer* renderer, int offsetx, int offsety);

#endif
