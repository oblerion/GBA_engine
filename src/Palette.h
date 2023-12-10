#ifndef PALETTE_H
#define PALETTE_H
#include "raylib.h"
#include <string.h>
#include "data_type.h"
struct Palette
{
    char name[35];
    int palette[DT_MAX_COLOR];
    // Texture2D texture;

};
struct Palette PaletteF(const char* pfile);
struct Palette PaletteD(struct spalette spalette);
Color Palette_Get(struct Palette pal,int id);
const char* Palette_GetName(struct Palette pal);
int Palette_GetHexa(struct Palette pal,int id);
int Palette_Size(struct Palette pal);
struct spalette Palette_GetStruct(struct Palette pal);
Image Palette_GetImg(struct Palette pal);
// void Palette_Draw(struct Palette pal,int x,int y);
// void Palette_Free(struct Palette* pal);
#endif