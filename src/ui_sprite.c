#include "ui_sprite.h"

struct UI_Sprite UI_Sprite()
{
    struct UI_Sprite uispr;
    const int size = 16;
    for(int y=0;y<size;y++)
    for(int x=0;x<size;x++)
    {
        uispr.btnspr[(size*y)+x] = UI_BUTTON(x*(size*2),y*(size*2),TextFormat(" %3d ", (size*y)+x),size,BLACK); 
    }
    return uispr;
}

struct Sprite UI_sprite_Get(struct UI_Sprite uispr, int id)
{
    return Sprite();
}

void UI_Sprite_LoadD(struct UI_Sprite *uispr, struct sdata sdata)
{
}

void UI_sprite_LoadF(struct UI_Sprite *uispr, const char *pfile)
{
}

void UI_Sprite_Save(struct UI_Sprite uispr,struct sdata *sdata)
{
}

void UI_Sprite_Draw(struct UI_Sprite uispr)
{
}
