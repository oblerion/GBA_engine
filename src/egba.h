#pragma once
#include "raylib.h"
#include "Atlas.h"
#include "ui_mainbar.h"
#include "ui_palette.h"
#include "ui_sprite.h"
#include "ui_script.h"

struct EGBA
{
    bool ifrunner;
    struct UI_MainBar uibar;
    struct UI_Palette uipal;
    struct UI_Sprite uispr;
    struct UI_Script uiscr;
};
struct EGBA EGBA_Init(int narg,char** sarg);
void EGBA_Draw(struct EGBA* egba);
void EGBA_Free(struct EGBA* egba);
