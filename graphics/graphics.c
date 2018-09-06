#include <graphics/graphics.h>

SDL_Rect rect;

void graphics_init()
{
    rect.h = BLOCK_SIZE;
    rect.w = BLOCK_SIZE;
}

void draw_scenary(Color scenary[10][20], SDL_Renderer* renderer, int offsetx, int offsety)
{
    for (int x = 0; x < 10; x++)
    {
        rect.x = x * BLOCK_SIZE + offsetx;
        
        for (int y = 0; y < 20; y++)
        {
            rect.y = y * BLOCK_SIZE + offsety;

            Color c = scenary[x][y];
            if (c.color)
            {
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void draw_shape(Shape* shape, SDL_Renderer* renderer, int offsetx, int offsety)
{
    SDL_SetRenderDrawColor(renderer, shape->color.r, shape->color.g,
        shape->color.b, shape->color.a);

    for (int x = 0; x < 4; x++)
    {
        rect.x = (x + shape->x) * BLOCK_SIZE + offsetx;

        for (int y = 0; y < 4; y++)
        {
            if (shape->data[x][y])
            {
                rect.y = (y + shape->y) * BLOCK_SIZE + offsety;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
