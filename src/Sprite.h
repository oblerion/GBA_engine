#pragma once
#include "raylib.h"
#include <string.h>
#include "data_type.h"
struct Sprite
{
    int width;
    int height;
    Color ldata[256];
};

struct Sprite SpriteD(struct ssprite ssprite);
struct Sprite Sprite();
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col);
struct ssprite Sprite_GetStruct(struct Sprite spr);
Image Sprite_GetImg(struct Sprite spr);