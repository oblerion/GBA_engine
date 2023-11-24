#ifndef SPRITE_H
#define SPRITE_H
#include "raylib.h"
#include "Palette.h"
#include <string.h>
#include "data_type.h"
struct Sprite
{
    int palette_id;
    int width;
    int height;
    int ldata[128];
};

struct Sprite SpriteD(struct ssprite ssprite);
struct Sprite Sprite();
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col);
struct ssprite Sprite_GetStruct(struct Sprite spr);
void Sprite_Draw(struct Sprite spr,int x,int y,int scale);
#endif