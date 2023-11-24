#ifndef UI_PALETTE_H
#define UI_PALETTE_H
#include "raylib.h"
#include "ui.h"
#include "Palette.h"
#include "PaletteManager.h"
#include "data_type.h"
#include <string.h>
struct UI_Palette
{
    struct PaletteManager palman;
    struct UI_BUTTON btndelete;
    struct UI_SLIDEBAR_V slider;
};
struct UI_Palette UI_Palette();
void UI_palette_LoadF(struct UI_Palette* uipal,const char* pfile);
void UI_Palette_LoadD(struct UI_Palette* uipal,struct sdata sdata);
void UI_Palette_Save(struct UI_Palette uipal,struct sdata* sdata);
struct Palette UI_Palette_Get(struct UI_Palette uipal,int id);
int UI_Palette_Draw(struct UI_Palette* uipal);
void UI_Palette_Free(struct UI_Palette* uipal);
#endif