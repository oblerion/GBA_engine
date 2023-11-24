#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#define MAX_COLOR 32
struct spalette
{
    char name[35];
    int data[MAX_COLOR];
};

struct smpalette
{
    int nb_palette;
    struct spalette list[5];
};

struct ssprite
{
    int width;
    int height;
    int data[16*16];
};

struct smsprite
{
    int nb_sprite;
    struct ssprite list[255];
};

struct sdata
{
    struct smpalette mpalette;
    struct smsprite msprite;
};
#endif