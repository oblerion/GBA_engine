#pragma once
#include "raylib.h"
#include "ui.h"
#include "Palette.h"
#include "data_type.h"
#include <string.h>
#include "Atlas.h"
struct UI_Palette
{
    struct UI_BUTTON btndelete;
    struct Palette palettes[DT_MAX_PALETTE];
};

struct UI_Palette UI_Palette(int pscale);
void UI_palette_LoadF(struct UI_Palette* uipal,const char* pfile);
void UI_Palette_LoadD(struct UI_Palette* uipal,struct sdata sdata);
void UI_Palette_Save(struct UI_Palette uipal,struct sdata* sdata);
struct Palette UI_Palette_Get(struct UI_Palette uipal,int id);
int UI_Palette_Draw(struct UI_Palette* uipal,int px,int py,int pscale);
void UI_Palette_Free(struct UI_Palette uipal);
