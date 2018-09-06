#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <graphics/graphics.h>
#include <graphics/shape.h>
#include <game.h>

Shape* current_shape;
Color scenary[10][20];
clock_t start, stop;

void put_shape_in_scenary();
Shape* generate_new_shape();

void game_init()
{
    graphics_init();
    memset(scenary, 0, sizeof(Color) * 10 * 20);
    srand(time(NULL));
    start = clock();

    current_shape = generate_new_shape();
}

void game_update()
{
    stop = clock();

    if ((double)(stop - start) / CLOCKS_PER_SEC > 0.5)
    {
        current_shape->y++;
        start = clock();
    }

    /* Check collisions */

    for (int i = 3; i >= 0; i--)
    {
        int y = current_shape->y + i;

        for (int j = 0; j < 4; j++)
        {
            if (current_shape->data[j][i])
            {
                int x = current_shape->x + j;

                if (y == 19 || scenary[x][y + 1].color)
                {
                    put_shape_in_scenary();
                    
                    free(current_shape);
                    current_shape = generate_new_shape();

                    return;
                }
            }
        }
    }
}

void game_render(SDL_Renderer* renderer)
{
    draw_scenary(scenary, renderer, 0, 0);
    draw_shape(current_shape, renderer, 0, 0);   
}

void key_press(int scancode)
{

}

void key_release(int scancode)
{
    switch (scancode)
    {
        case SDL_SCANCODE_RIGHT:
            if (current_shape->x < 8)
                current_shape->x++;
        break;
    
        case SDL_SCANCODE_LEFT:
            if (current_shape->x > 0)
                current_shape->x--;
        break;

        case SDL_SCANCODE_DOWN:
            if (current_shape->y < 17)
                current_shape->y++;
        break;

        case SDL_SCANCODE_A:
        {
            uint8_t data[4][4];
            memcpy(data, current_shape->data, 16);
            rotate_left(data, current_shape->data, current_shape->shape_type);
        }
        break;

        case SDL_SCANCODE_D:
        {
            uint8_t data[4][4];
            memcpy(data, current_shape->data, 16);
            rotate_right(data, current_shape->data, current_shape->shape_type);
        }
        break;
    }
}

void put_shape_in_scenary()
{
    for (int x = 0; x < 4; x++)
    {
        int xpos = current_shape->x + x;

        for (int y = 0; y < 4; y++)
        {
            int ypos = current_shape->y + y;

            if (current_shape->data[x][y])
                scenary[xpos][ypos] = current_shape->color;
        }
    }
}

Shape* generate_new_shape()
{
    Shape* shape = (Shape*)malloc(sizeof(Shape));
    memset(shape->data, 0, 16);
    shape->shape_type = (ShapeType)(rand() % 7);
    shape->y = -2;
    
    switch (rand() % 7)
    {
        case 0:
            shape->color.color = COLOR_BLUE;
        break;

        case 1:
            shape->color.color = COLOR_CYAN;
        break;
    
        case 2:
            shape->color.color = COLOR_GREEN;
        break;

        case 3:
            shape->color.color = COLOR_ORANGE;
        break;

        case 4:
            shape->color.color = COLOR_PURPLE;
        break;

        case 5:
            shape->color.color = COLOR_RED;
        break;

        case 6:
            shape->color.color = COLOR_YELLOW;
        break;
    }

    switch (shape->shape_type)
    {
        case SHAPE_LINE:
            set_shape_line(shape->data);
        break;

        case SHAPE_SQUARE:
            set_shape_square(shape->data);
        break;

        case SHAPE_S:
            set_shape_s(shape->data);
        break;

        case SHAPE_TEE:
            set_shape_tee(shape->data);
        break;

        case SHAPE_L:
            set_shape_l(shape->data);
        break;

        case SHAPE_J:
            set_shape_j(shape->data);
        break;

        case SHAPE_Z:
            set_shape_z(shape->data);
        break;
    }

    shape->x = rand() % (10 - 3);

    /* The x calculation should consider the
     * empty blocks on the right of the shapes
     * and also when rotating them. It should
     * also check if there are other blocks in
     * the position until it can place one,
     * if it can't the game is over
     */

    return shape;
}
