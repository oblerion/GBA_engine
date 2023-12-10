#ifndef UI_RUNNER_H
#define UI_RUNNER_H
#include <stdio.h>
#include "raylib.h"
#include "clua.h"
#include "data_type.h"
#include "Palette.h"
#include "Sprite.h"
#include "atlas.h"

struct UI_Runner
{
    struct CLUA clua;
    struct Sprite spr[DT_MAX_SPRITE];
    struct Palette pal[DT_MAX_PALETTE];
    Texture2D atlaspal;
    Texture2D atlasspr;
} static uirun;

void UI_Runner();
bool UI_Runner_Load(const char* pfile);
bool UI_Runner_LoadD(struct sdata sdata);
void UI_Runner_Draw();
void UI_Runner_Free();

#endif