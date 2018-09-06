#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>
#include <graphics/color.h>

#define BLOCK_SIZE 30

typedef enum
{
    SHAPE_LINE,
    SHAPE_SQUARE,
    SHAPE_L,
    SHAPE_J,
    SHAPE_TEE,
    SHAPE_Z,
    SHAPE_S
} ShapeType;

typedef struct
{
    uint8_t data[4][4];
    Color color;
    ShapeType shape_type;
    int x;
    int y;
} Shape;

void debug_draw(uint8_t data[4][4]);
void rotate_left(uint8_t src[4][4], uint8_t dest[4][4], ShapeType shape_type);
void rotate_right(uint8_t src[4][4], uint8_t dest[4][4], ShapeType shape_type);
void set_shape_line(uint8_t dest[4][4]);
void set_shape_square(uint8_t dest[4][4]);
void set_shape_l(uint8_t dest[4][4]);
void set_shape_j(uint8_t dest[4][4]);
void set_shape_tee(uint8_t dest[4][4]);
void set_shape_z(uint8_t dest[4][4]);
void set_shape_s(uint8_t dest[4][4]);

#endif
