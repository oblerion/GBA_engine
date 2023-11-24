#ifndef UI_SPRITE_H
#define UI_SPRITE_H
#include "raylib.h"
#include "ui.h"
#include "data_type.h"
#include "Sprite.h"
#include "SpriteManager.h"

struct UI_Sprite
{
    struct SpriteManager sprman;
    struct UI_BUTTON btnspr[256];
};

struct UI_Sprite UI_Sprite();
struct Sprite UI_sprite_Get(struct UI_Sprite uispr,int id);
void UI_Sprite_LoadD(struct UI_Sprite* uispr, struct sdata sdata);
void UI_sprite_LoadF(struct UI_Sprite* uispr, const char* pfile);
void UI_Sprite_Save(struct UI_Sprite uispr, struct sdata* sdata);
void UI_Sprite_Draw(struct UI_Sprite uispr);
#endif