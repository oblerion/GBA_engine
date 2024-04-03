#pragma once
#include "raylib.h"
#include "Palette.h"
#include "Sprite.h"

void Atlas_Init();
void Atlas_DrawPalette(int id, int x,int y,int scale);
void Atlas_UpdatePalette(struct Palette* palettes);
void Atlas_DrawSprite(int id,int x,int y,int scale);
void Atlas_UpdateSprite(struct Sprite* sprites);
void Atlas_Free();
