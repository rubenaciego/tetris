#include <stdio.h>
#include <string.h>
#include <graphics/shape.h>

void rotate_left(uint8_t src[4][4], uint8_t dest[4][4], ShapeType shape_type)
{
    uint8_t blocks = 3;

    if (shape_type == SHAPE_SQUARE)
    {
        memcpy(dest, src, 16);
        return;
    }
    else if (shape_type == SHAPE_LINE)
        blocks = 4;

    for (int x = 0; x < blocks; x++)
        for (int y = 0; y < blocks; y++)
            dest[y][x] = src[x][blocks - 1 - y];
}

void rotate_right(uint8_t src[4][4], uint8_t dest[4][4], ShapeType shape_type)
{
    uint8_t blocks = 3;

    if (shape_type == SHAPE_SQUARE)
    {
        memcpy(dest, src, 16);
        return;
    }
    else if (shape_type == SHAPE_LINE)
        blocks = 4;

    for (int x = 0; x < blocks; x++)
        for (int y = 0; y < blocks; y++)
            dest[x][blocks - 1 - y] = src[y][x];
}

void debug_draw(uint8_t data[4][4])
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (data[x][y])
                printf("*");
            else
                printf("_");
        }

        printf("\n");
    }
    
    printf("\n");
}

void set_shape_line(uint8_t dest[4][4])
{
    for (int i = 0; i < 4; i++)
        dest[1][i] = 1;
}

void set_shape_square(uint8_t dest[4][4])
{
    for (int i = 1; i < 3; i++)
    {
        dest[1][i] = 1;
        dest[2][i] = 1;
    }
}

void set_shape_l(uint8_t dest[4][4])
{
    dest[0][0] = 1;

    for (int i = 0; i < 3; i++)
        dest[1][i] = 1;
}

void set_shape_j(uint8_t dest[4][4])
{
    dest[2][0] = 1;

    for (int i = 0; i < 3; i++)
        dest[1][i] = 1;
}

void set_shape_tee(uint8_t dest[4][4])
{
    dest[1][0] = 1;

    for (int i = 0; i < 3; i++)
        dest[i][1] = 1;
}

void set_shape_z(uint8_t dest[4][4])
{
    for (int i = 1; i < 3; i++)
        dest[0][i] = 1;
    for (int i = 0; i < 2; i++)
        dest[1][i] = 1;
}

void set_shape_s(uint8_t dest[4][4])
{
    for (int i = 1; i < 3; i++)
        dest[1][i] = 1;
    for (int i = 0; i < 2; i++)
        dest[0][i] = 1;
}
