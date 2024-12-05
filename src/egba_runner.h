#pragma once
#include "egba.h"
bool Egba_Runner_Load(const char* sfile);
void Egba_Runner_Init(int narg,char** sarg);
const char* Egba_Runner_GetExt();
const char* Egba_Runner_GetName();
char Egba_Runner_IsDebug();
char Egba_Runner_IsDown();
void Egba_Runner_Draw();
void Egba_Runner_Free();
