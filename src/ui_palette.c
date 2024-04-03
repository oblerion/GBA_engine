#include "ui_palette.h"

struct UI_Palette UI_Palette(int pscale)
{
    struct UI_Palette uipal={
        UI_BUTTON((pscale-1)*32,0,"delete",pscale-2,BLACK)
    };
    for(int i=0;i<DT_MAX_PALETTE;i++)
        strcpy(uipal.palettes[i].name,"");
    return uipal;
}
void UI_palette_LoadF(struct UI_Palette* uipal,const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        Image img = LoadImage(pfile);
        if(img.width>0 && img.width<=32 && img.height==1)
        {
            for(int i=0;i<DT_MAX_PALETTE;i++)
            {
                if(strlen(uipal->palettes[i].name)==0)
                {
                    uipal->palettes[i] = PaletteF(pfile);
                    Atlas_UpdatePalette(uipal->palettes);
                    break;
                }
            }
        }
        else if(img.width==256 && img.height==257)
        {
            for(int i=0;i<160;i++)
            {
                strcpy(uipal->palettes[i/32].name,TextFormat("%d",i/32));
                Color col = GetImageColor(img,i,256);
                uipal->palettes[i/32].palette[i-((i/32)*32)]=col;
                Atlas_UpdatePalette(uipal->palettes);
            }
        }
        UnloadImage(img);
    }
}
void UI_Palette_LoadD(struct UI_Palette* uipal,struct sdata sdata)
{
    for(int j=0;j<DT_MAX_PALETTE;j++)
    {
        uipal->palettes[j] = PaletteD(sdata.list_pal[j]);
    }
    Atlas_UpdatePalette(uipal->palettes);
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
int UI_Palette_Draw(struct UI_Palette* uipal,int px,int py,int pscale)
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
                Atlas_DrawPalette(j,px+23,py+yborder+23+(j*45),pscale);
                DrawText(uipal->palettes[j].name,px+5,py+yborder+(j*45)+5,10,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){px+23,py+(float)yborder+23+(j*45),32*pscale,pscale}))
                {
                    uipal->btndelete.y=py+yborder+21+(j*45)+2;
                    if(UI_BUTTON_draw(&uipal->btndelete))
                    {
                        //PaletteManager_Del(&uipal->palman,j);
                        strcpy(uipal->palettes[j].name,"");
                        for(int i=0;i<DT_MAX_COLOR;i++)
                        {
                            uipal->palettes[j].palette[i]=BLACK;
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
                        uipal->palettes[j+1].palette[i]=BLACK;
                    }
                    Atlas_UpdatePalette(uipal->palettes);
                }
            }
        }
    }
    else
    {
        DrawText("Drop palette image file here",px+23,py+100,pscale,BLACK);
    }
    return ret;
}
