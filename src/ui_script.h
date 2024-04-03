#pragma once
#include "raylib.h"
#include "data_type.h"
#include "ui.h"
#include <string.h>
struct UI_Script
{
    char source_script[40];
    char script[DT_MAX_SCRIPTSIZE];
};
struct UI_Script UI_Script();
void UI_Script_LoadF(struct UI_Script* uiscr,const char* pfile);
void UI_Script_LoadD(struct UI_Script* uiscr, struct sdata sdata);
void UI_Script_Save(struct UI_Script uiscr,struct sdata* sdata);
void UI_Script_Draw(struct UI_Script uiscr);