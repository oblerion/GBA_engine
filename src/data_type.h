#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include "raylib.h"
#define DT_MAX_COLOR 32
#define DT_MAX_SPRITE 256
#define DT_MAX_PALETTE 5
#define DT_MAX_SCRIPTSIZE 64000
struct spalette
{
    char name[35];
    int data[DT_MAX_COLOR];
};

struct ssprite
{
    int width;
    int height;
    Color data[256];
};

struct sdata
{
    struct ssprite list_spr[DT_MAX_SPRITE];
    int nb_palette;
    struct spalette list_pal[DT_MAX_PALETTE];
    char script[DT_MAX_SCRIPTSIZE];
};
// struct sdata
// {
//     char palette_name[DT_MAX_PALETTE][32];
//     int palette_data[DT_MAX_PALETTE][DT_MAX_COLOR];
//     int sprite_data[DT_MAX_SPRITE][256];
//     char script[DT_MAX_SCRIPTSIZE];
// };
#endif