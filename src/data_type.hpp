#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP
#include "raylib.h"

#define MAX_COLOR 32
struct spalette
{
    char name[20];
    int data[MAX_COLOR+1];
};

struct smpalette
{
    struct spalette list[5];
};

struct sdata
{
    struct smpalette mpalette;
};
#endif