#include "ui_mainbar.h"

struct UI_MainBar UI_MainBar(int x, int y)
{
    struct UI_MainBar uibar={
    UI_BUTTON(x+5,y+5,"palette",20,BLACK),
    UI_BUTTON(x+88,y+5,"sprite",20,BLACK),
    UI_BUTTON(x+160,y+5,"save",20,BLACK),
    statepalette,
    0};
    return uibar;
}

enum UISTATE UI_MainBar_GetState(struct UI_MainBar uibar)
{
    return uibar.state;
}

void UI_MainBar_DropLoad(struct UI_MainBar *uibar,struct UI_Palette *uipal,struct UI_Sprite *uispr)
{
    if(IsFileDropped())
    {
        FilePathList files = LoadDroppedFiles();
        for(int i=0;i<files.count;i++)
        {
            const char* ext = GetFileExtension(files.paths[i]);
            if(TextIsEqual(ext,".dat"))
            {
                struct sdata sdata;
                FILE* fic = fopen(files.paths[i],"rb");
                fread(&sdata,sizeof(struct sdata),1,fic);
                fclose(fic);
                UI_Palette_LoadD(uipal,sdata);
                UI_Sprite_LoadD(uispr,sdata);
            }
            else if(TextIsEqual(ext,".png"))
            {
                switch(uibar->state)
                {
                    case statepalette:
                        UI_palette_LoadF(uipal,files.paths[i]);
                    break;
                    case statesprite:
                    break;
                    default:;
                }
            }
        }
        UnloadDroppedFiles(files);
    }
}

void UI_MainBar_Save(struct UI_MainBar *uibar,struct UI_Palette uipal,struct UI_Sprite uispr)
{
    if(uibar->issave==1)
    {
        struct sdata sdata;
        UI_Palette_Save(uipal,&sdata);
        UI_Sprite_Save(uispr,&sdata);
        FILE* fic = fopen("save.dat","wb");
        fwrite(&sdata,sizeof(struct sdata),1,fic);
        fclose(fic);
        uibar->issave=0;
    }
}

void UI_MainBar_Draw(struct UI_MainBar* uibar)
{
    if(uibar->state==statepalette)
        DrawRectangle(  uibar->btnpal.x-4,
                        uibar->btnpal.y-2,
                        uibar->btnpal.width,
                        uibar->btnpal.height,WHITE);
    if(uibar->state==statesprite)
        DrawRectangle(  uibar->btnspr.x-4,
                        uibar->btnspr.y-2,
                        uibar->btnspr.width,
                        uibar->btnspr.height,WHITE);
    if(UI_BUTTON_draw(&uibar->btnpal))
        uibar->state=statepalette;
    if(UI_BUTTON_draw(&uibar->btnspr))
        uibar->state=statesprite;
    if(UI_BUTTON_draw(&uibar->btnsave))
        uibar->issave=1;
}
