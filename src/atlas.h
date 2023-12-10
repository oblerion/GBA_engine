#ifndef ATLAS_H
#define ATLAS_H
#include "raylib.h"
#include "Palette.h"
#include "Sprite.h"
void Atlas_DrawPalette(Texture2D texture,int id, int x,int y,int scale);
void Atlas_UpdatePalette(Texture2D texture,struct Palette* palettes);
void Atlas_DrawSprite(Texture2D texture,int id,int x,int y,int scale);
void Atlas_UpdateSprite(Texture2D texture,struct Sprite* sprites);
#endif