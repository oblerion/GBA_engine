#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H
#include "Palette.h"
#include <string.h>
#include "data_type.h"
struct PaletteManager
{
    int nb_palette;
    struct Palette list[5]; 
};
struct PaletteManager PaletteManager();
void PaletteManager_AddF(struct PaletteManager* palman,const char* pfile);
void PaletteManager_AddD(struct PaletteManager* palman,struct spalette);
struct Palette PaletteManager_Get(struct PaletteManager palman, int id);
void PaletteManager_Del(struct PaletteManager* palman,int id);
struct smpalette PaletteManager_GetStruct(struct PaletteManager palman);
const char* PaletteManager_GetName(struct PaletteManager palman, int id);
int PaletteManger_Size(struct PaletteManager palman);
void PaletteManager_Draw(struct PaletteManager palman,int id,int x,int y);
void PaletteManager_Free(struct PaletteManager* palman);
#endif