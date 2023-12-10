#include "ui_palette.h"

struct UI_Palette UI_Palette()
{
    struct UI_Palette uipal={
        UI_BUTTON(19*32,0,"delete",18,BLACK)
    };
    for(int i=0;i<DT_MAX_PALETTE;i++)
        strcpy(uipal.palettes[i].name,"");
    Image img = GenImageColor(32,5,BLACK);
    uipal.texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return uipal;
}
void UI_palette_LoadF(struct UI_Palette* uipal,const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        for(int i=0;i<DT_MAX_PALETTE;i++)
        {
            if(strlen(uipal->palettes[i].name)==0)
            {
                uipal->palettes[i] = PaletteF(pfile);
                Atlas_UpdatePalette(uipal->texture,uipal->palettes);
                break;
            }
        }
    }
}
void UI_Palette_LoadD(struct UI_Palette* uipal,struct sdata sdata)
{
    for(int j=0;j<DT_MAX_PALETTE;j++)
    {
        uipal->palettes[j] = PaletteD(sdata.list_pal[j]);
    }
    Atlas_UpdatePalette(uipal->texture,uipal->palettes);
}
void UI_Palette_Save(struct UI_Palette uipal, struct sdata* sdata)
{
    for(int i=0;i<DT_MAX_PALETTE;i++)
    {
        sdata->list_pal[i] = Palette_GetStruct(uipal.palettes[i]);
    }
}
struct Palette UI_Palette_Get(struct UI_Palette uipal,int id)
{
    return uipal.palettes[id];
}
int UI_Palette_Draw(struct UI_Palette* uipal)
{
    int ret=-1;
    const int yborder = 30;
    // UI button,scroll
    int nbpalette=0;
    for(int i=0;i<DT_MAX_PALETTE;i++)
    {
        if(strlen(uipal->palettes[i].name)>0) nbpalette++;
    }

    if(nbpalette>0)
    {
        for(int j=0;j<DT_MAX_PALETTE;j++)
        {
            if(strlen(uipal->palettes[j].name)>0)
            {
                Atlas_DrawPalette(uipal->texture,j,23,yborder+23+(j*45),20);
                DrawText(uipal->palettes[j].name,5,yborder+(j*45)+5,17,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){23,(float)yborder+23+(j*45),32*20,20}))
                {
                    uipal->btndelete.y=yborder+21+(j*45)+2;
                    if(UI_BUTTON_draw(&uipal->btndelete))
                    {
                        //PaletteManager_Del(&uipal->palman,j);
                        strcpy(uipal->palettes[j].name,"");
                        for(int i=0;i<DT_MAX_COLOR;i++)
                        {
                            uipal->palettes[j].palette[i]=ColorToInt(BLACK);
                        }
                    }
                }
            }
            else if(j+1<DT_MAX_PALETTE)
            {
                if( strlen(uipal->palettes[j+1].name)>0)
                {
                    uipal->palettes[j] = uipal->palettes[j+1];
                    strcpy(uipal->palettes[j+1].name,"");
                    for(int i=0;i<DT_MAX_COLOR;i++)
                    {
                        uipal->palettes[j+1].palette[i]=ColorToInt(BLACK);
                    }
                    Atlas_UpdatePalette(uipal->texture,uipal->palettes);
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

void UI_Palette_Free(struct UI_Palette uipal)
{
    UnloadTexture(uipal.texture);
}
