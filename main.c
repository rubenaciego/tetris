#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <game.h>

uint8_t running = 1;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("Error creating the window: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        printf("Error creating the renderer: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetSwapInterval(1);
    SDL_Event event;

    game_init();

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = 0;
                break;

                case SDL_KEYDOWN:
                    key_press(event.key.keysym.scancode);
                break;

                case SDL_KEYUP:
                    key_release(event.key.keysym.scancode);
                break;
            }
        }

        game_update(window);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        game_render(renderer);

        SDL_RenderPresent(renderer);            
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
