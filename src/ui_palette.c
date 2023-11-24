#include "ui_palette.h"

struct UI_Palette UI_Palette()
{
    struct UI_Palette uipal={
        PaletteManager(),
        UI_BUTTON(19*32,0,"delete",18,BLACK),
        UI_SLIDEBAR_V(GetScreenWidth()-20,10,5)
    };
    return uipal;
}
void UI_palette_LoadF(struct UI_Palette* uipal,const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        PaletteManager_AddF(&uipal->palman,pfile);
    }
}
void UI_Palette_LoadD(struct UI_Palette* uipal,struct sdata sdata)
{
    for(int j=0;j<sdata.mpalette.nb_palette;j++)
    {
        struct spalette pal = sdata.mpalette.list[j];
        PaletteManager_AddD(&uipal->palman,pal);
    }
}
void UI_Palette_Save(struct UI_Palette uipal,struct sdata* sdata)
{
    sdata->mpalette = PaletteManager_GetStruct(uipal.palman);
}
struct Palette UI_Palette_Get(struct UI_Palette uipal,int id)
{
    return PaletteManager_Get(uipal.palman,id);
}
int UI_Palette_Draw(struct UI_Palette* uipal)
{
    int ret=-1;
    const int yborder = 30;
    // UI button,scroll

    if(PaletteManger_Size(uipal->palman)>0)
    {
        UI_SLIDEBAR_V_draw(&uipal->slider);
        for(int j=uipal->slider.pos;j<PaletteManger_Size(uipal->palman);j++)
        {
            int pos= j-uipal->slider.pos;
            if(pos<6 && pos>=0)
            {
                PaletteManager_Draw(uipal->palman,j,23,yborder+23+(pos*45));
                DrawText(PaletteManager_GetName(uipal->palman,j),5,yborder+(pos*45)+5,17,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){23,(float)yborder+23+(pos*45),32*20,20}))
                {
                    uipal->btndelete.y=yborder+21+(pos*45)+2;
                    if(UI_BUTTON_draw(&uipal->btndelete))
                    {
                        PaletteManager_Del(&uipal->palman,j);
                    }
                }
            }
        }
    }
    else
    {
        DrawText("Drop palette image file here",23,100,20,BLACK);
    }
    return ret;
}

void UI_Palette_Free(struct UI_Palette *uipal)
{
    PaletteManager_Free(&uipal->palman);
}
