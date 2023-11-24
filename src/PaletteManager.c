#include "PaletteManager.h"

struct PaletteManager PaletteManager()
{
    struct PaletteManager palman;
    palman.nb_palette=0;

    return palman;
}
void PaletteManager_AddF(struct PaletteManager *palman, const char *pfile)
{
    if(palman->nb_palette<5)
    {
        palman->list[palman->nb_palette]=PaletteF(pfile);
        palman->nb_palette++;
    }
}
void PaletteManager_AddD(struct PaletteManager* palman,struct spalette spalette)
{
    if(palman->nb_palette<5)
    {
        palman->list[palman->nb_palette]=PaletteD(spalette);
        palman->nb_palette++;
    }
}
struct Palette PaletteManager_Get(struct PaletteManager palman, int id)
{
    if(id>-1 && id<palman.nb_palette)
    {
        return palman.list[id];
    }
    return PaletteF("");
}
void PaletteManager_Del(struct PaletteManager* palman,int id)
{
    if(id>=0) palman->nb_palette--;
}
struct smpalette PaletteManager_GetStruct(struct PaletteManager palman)
{
    struct smpalette smpalette;
    smpalette.nb_palette=palman.nb_palette;
    for(int i=0;i<smpalette.nb_palette;i++)
    {
        smpalette.list[i] = Palette_GetStruct(palman.list[i]);
    }
    return smpalette;
}
const char* PaletteManager_GetName(struct PaletteManager palman, int id)
{
   if(id>-1 && id<palman.nb_palette)
        return Palette_GetName(palman.list[id]);
    return "";
}
int PaletteManger_Size(struct PaletteManager palman)
{
    return palman.nb_palette;
}
void PaletteManager_Draw(struct PaletteManager palman,int id,int x,int y)
{
    if(id>-1 && id<palman.nb_palette)
        Palette_Draw(palman.list[id],x,y);
}

void PaletteManager_Free(struct PaletteManager* palman)
{
    for(int i=0;i<palman->nb_palette;i++)
    {
        Palette_Free(&palman->list[i]);
    }
}