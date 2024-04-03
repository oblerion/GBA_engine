#pragma once
#include "raylib.h"
#include <math.h>
#include "ui.h"
#include "data_type.h"
#include "Sprite.h"
#include "ui_palette.h"
#include "Atlas.h"
struct UI_Sprite;

struct UI_BUTTONSPRITE 
{
    int x;
    int y;
    int scale;
    int id_sprite;
    bool visible;
};
struct UI_BUTTONSPRITE UI_BUTTONSPRITE(int x,int y,int scale,int id_sprite);
int UI_BUTTONSPRITE_Draw(struct UI_BUTTONSPRITE btnspr,struct UI_Sprite uispr);


struct UI_Sprite
{
    Texture2D sprfond;
    //Texture2D spratlas;
    struct UI_BUTTONSPRITE btnspr[DT_MAX_SPRITE];
    struct UI_BUTTONCOLOR btncolor[256];
    struct UI_BUTTONCOLOR btnpal[32];
    struct UI_BUTTON btnerase;
    struct UI_SLIDEBAR_V slidepalette;
    Color curant_color;
    int curant_spr;
    int curant_pal;
    struct Sprite sprites[DT_MAX_SPRITE];
    int btnspr_size;
    int btncol_size;
};

struct UI_Sprite UI_Sprite();
struct Sprite UI_sprite_Get(struct UI_Sprite uispr,int id);
void UI_Sprite_LoadD(struct UI_Sprite* uispr,struct sdata sdata);
void UI_sprite_LoadF(struct UI_Sprite* uispr,const char* pfile);
void UI_Sprite_LoadPalette(struct UI_Sprite* uispr,struct UI_Palette uipal);
void UI_Sprite_Save(struct UI_Sprite uispr, struct sdata* sdata);
int UI_Sprite_Draw(struct UI_Sprite* uispr,struct UI_Palette uipal);
void UI_Sprite_Free(struct UI_Sprite uispr);
