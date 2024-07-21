#pragma once
#include "EGBA.h"
bool Runner_Load(const char* sfile);
void Runner_Init(int narg,char** sarg);
const char* Runner_GetExt();
const char* Runner_GetName();
char Runner_IsDebug();
char Runner_IsDown();
void Runner_Draw();
void Runner_Free();
