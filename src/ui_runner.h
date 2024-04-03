#pragma once
#include <stdio.h>
#include "raylib.h"
#include "clua.h"
#include "data_type.h"
#include "Palette.h"
#include "Sprite.h"
#include "Atlas.h"

void UI_Runner();
bool UI_Runner_Load(const char* pfile);
bool UI_Runner_LoadD(struct sdata sdata);
void UI_Runner_Draw();
void UI_Runner_Free();
