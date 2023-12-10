#ifndef SPRITE_H
#define SPRITE_H
#include "raylib.h"
#include <string.h>
#include "data_type.h"
struct Sprite
{
    int width;
    int height;
    Color ldata[256];
   // Texture2D texture;
};

struct Sprite SpriteD(struct ssprite ssprite);
struct Sprite Sprite();
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col);
struct ssprite Sprite_GetStruct(struct Sprite spr);
Image Sprite_GetImg(struct Sprite spr);
// void Sprite_Draw(struct Sprite spr,int x,int y,int scale);
// void Sprite_Free(struct Sprite* spr);
#endif