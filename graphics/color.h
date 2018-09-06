#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define COLOR_CYAN 0x00FFFFFF
#define COLOR_RED 0xFF0000FF
#define COLOR_BLUE 0x0000FFFF
#define COLOR_GREEN 0x00FF00FF
#define COLOR_YELLOW 0x00FFFFFF
#define COLOR_ORANGE 0xFFA500FF
#define COLOR_PURPLE 0x551A8BFF

typedef struct
{
    union
    {
        uint32_t color;
        
        struct
        {
            uint8_t a;
            uint8_t b;
            uint8_t g;
            uint8_t r;
        };
    };
} Color;

#endif
