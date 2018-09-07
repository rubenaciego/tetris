#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <graphics/graphics.h>
#include <graphics/shape.h>
#include <game.h>

extern uint8_t running;

Shape* current_shape;
Color scenary[10][20];
clock_t start, stop;

void move_right();
void move_left();
void do_rotation_left();
void do_rotation_right();
void put_shape_in_scenary();
void check_rotation_space();
Shape* generate_new_shape();

void game_init()
{
    graphics_init();
    memset(scenary, 0, sizeof(Color) * 10 * 20);
    srand(time(NULL));
    start = clock();

    current_shape = generate_new_shape();
}

void game_update(SDL_Window* window)
{
    /* Check if there's any shape at the top */

    for (int i = 0; i < 10; i++)
    {
        if (scenary[i][0].color)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                "Game Over", "Sorry, but you lost", window);
            running = 0;
        }
    }

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
            if (current_shape->x < (6 + current_shape->empty_blocks_right))
                move_right();
        break;
    
        case SDL_SCANCODE_LEFT:
            if (current_shape->x > (-current_shape->empty_blocks_left))
                move_left();
        break;

        case SDL_SCANCODE_DOWN:
            if (current_shape->y < 17)
                current_shape->y++;
        break;

        case SDL_SCANCODE_A:
            do_rotation_left();
        break;

        case SDL_SCANCODE_D:
            do_rotation_right();
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

    for (int y = 0; y < 20; y++)
    {
        uint8_t row_full = 1;

        for (int x = 0; x < 10; x++)
        {
            if (!scenary[x][y].color)
            {
                row_full = 0;
                break;
            }
        }

        if (row_full)
        {
            for (int i = y; i > 0; i--)
            {
                for (int j = 0; j < 10; j++)
                    scenary[j][i] = scenary[j][i - 1];
            }
            
            memset(&scenary[0][0], 0, sizeof(Color) * 10);
            y--;
        }
    }
}

Shape* generate_new_shape()
{
    Shape* shape = (Shape*)malloc(sizeof(Shape));
    memset(shape->data, 0, 16);
    shape->shape_type = (ShapeType)(rand() % 7);
    shape->y = 0;
    
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
            shape->empty_blocks_left = 1;
            shape->empty_blocks_right = 2;
        break;

        case SHAPE_SQUARE:
            set_shape_square(shape->data);
            shape->empty_blocks_left = 1;
            shape->empty_blocks_right = 1;
        break;

        case SHAPE_S:
            set_shape_s(shape->data);
            shape->empty_blocks_left = 0;
            shape->empty_blocks_right = 2;
        break;

        case SHAPE_TEE:
            set_shape_tee(shape->data);
            shape->empty_blocks_left = 0;
            shape->empty_blocks_right = 1;
        break;

        case SHAPE_L:
            set_shape_l(shape->data);
            shape->empty_blocks_left = 0;
            shape->empty_blocks_right = 2;
        break;

        case SHAPE_J:
            set_shape_j(shape->data);
            shape->empty_blocks_left = 1;
            shape->empty_blocks_right = 1;
        break;

        case SHAPE_Z:
            set_shape_z(shape->data);
            shape->empty_blocks_left = 0;
            shape->empty_blocks_right = 2;
        break;
    }

    shape->x = rand() % (6 + shape->empty_blocks_right);

    /* The x calculation should consider the
     * empty blocks on the right of the shapes
     * and also when rotating them. It should
     * also check if there are other blocks in
     * the position until it can place one,
     * if it can't the game is over
     */

    return shape;
}

void check_rotation_space()
{
    if (current_shape->shape_type == SHAPE_SQUARE)
        return;

    current_shape->empty_blocks_left = 4;
    current_shape->empty_blocks_right = 4;

    for (int y = 0; y < 4; y++)
    {
        uint8_t temp_left = 0;
        uint8_t temp_right = 0;

        for (int x = 0; x < 4; x++)
        {
            if (current_shape->data[x][y])
                break;
            else
                temp_left++;
        }

        for (int x = 3; x >= 0; x--)
        {
            if (current_shape->data[x][y])
                break;
            else
                temp_right++;
        }

        if (temp_left < current_shape->empty_blocks_left)
            current_shape->empty_blocks_left = temp_left;
        if (temp_right < current_shape->empty_blocks_right)
            current_shape->empty_blocks_right = temp_right;
    }

    if (current_shape->x >= (6 + current_shape->empty_blocks_right))
        current_shape->x = (6 + current_shape->empty_blocks_right);
    if (current_shape->x <= (-current_shape->empty_blocks_left))
        current_shape->x = (-current_shape->empty_blocks_left);
}

void do_rotation_left()
{
    if (current_shape->shape_type == SHAPE_SQUARE)
        return;

    uint8_t data[4][4];
    uint8_t final_rotation[4][4];
    memset(final_rotation, 0, 16);
    memcpy(data, current_shape->data, 16);
    rotate_left(data, final_rotation, current_shape->shape_type);

    /* Check first if there is enough space to rotate
     * otherwise just return
     */

    for (int i = 0; i < 4; i++)
    {
        int y = current_shape->y + i;

        for (int j = 0; j < 4; j++)
        {
            if (final_rotation[j][i])
            {
                int x = current_shape->x + j;

                if (scenary[x][y].color)
                    return;
            }
        }
    }

    memcpy(current_shape->data, final_rotation, 16);
    check_rotation_space();
}

void do_rotation_right()
{
    if (current_shape->shape_type == SHAPE_SQUARE)
        return;
    
    uint8_t data[4][4];
    uint8_t final_rotation[4][4];
    memset(final_rotation, 0, 16);
    memcpy(data, current_shape->data, 16);
    rotate_right(data, final_rotation, current_shape->shape_type);

    /* Check first if there is enough space to rotate
     * otherwise just return
     */

    for (int i = 0; i < 4; i++)
    {
        int y = current_shape->y + i;

        for (int j = 0; j < 4; j++)
        {
            if (final_rotation[j][i])
            {
                int x = current_shape->x + j;

                if (scenary[x][y].color)
                    return;
            }
        }
    }

    memcpy(current_shape->data, final_rotation, 16);
    check_rotation_space();
}

void move_right()
{
    for (int i = 0; i < 4; i++)
    {
        int y = current_shape->y + i;

        for (int j = 0; j < 4; j++)
        {
            if (current_shape->data[j][i])
            {
                int x = current_shape->x + j;

                if (scenary[x + 1][y].color)
                    return;
            }
        }
    }

    current_shape->x++;
}

void move_left()
{
    for (int i = 0; i < 4; i++)
    {
        int y = current_shape->y + i;

        for (int j = 0; j < 4; j++)
        {
            if (current_shape->data[j][i])
            {
                int x = current_shape->x + j;

                if (scenary[x - 1][y].color)
                    return;
            }
        }
    }

    current_shape->x--;
}
