#include "ui_mainbar.h"

struct UI_MainBar UI_MainBar(int x, int y)
{
    struct UI_MainBar uibar={
    UI_BUTTON(x+5,y+5,"palette",20,BLACK),
    UI_BUTTON(x+88,y+5,"sprite",20,BLACK),
    UI_BUTTON(x,y+5,"script",20,BLACK),
    UI_BUTTON(x+160,y+5,"save",20,BLACK),
    UI_BUTTON(x+230,y+5,"doc",20,BLACK),
    statepalette,
    0,
    false,
    "save.egba"
    };
    uibar.btnspr.x = x+uibar.btnpal.x+uibar.btnpal.width+2;
    uibar.btnscr.x = x+uibar.btnspr.x+uibar.btnspr.width+2;
    uibar.btnsave.x = x+uibar.btnscr.x+uibar.btnscr.width+2;
    return uibar;
}

enum UISTATE UI_MainBar_GetState(struct UI_MainBar uibar)
{
    return uibar.state;
}

void UI_MainBar_DropLoad(struct UI_MainBar* uibar,struct UI_Palette* uipal,struct UI_Sprite* uispr,struct UI_Script* uiscr)
{
    if(IsFileDropped())
    {
        FilePathList files = LoadDroppedFiles();
        for(int i=0;i<files.count;i++)
        {
            const char* ext = GetFileExtension(files.paths[i]);
            if(TextIsEqual(ext,".egba"))
            {
                strcpy(uibar->filename,files.paths[i]);
                struct sdata sdata;
                FILE* fic = fopen(files.paths[i],"rb");
                fread(&sdata,sizeof(struct sdata),1,fic);
                fclose(fic);
                UI_Palette_LoadD(uipal,sdata);
                UI_Sprite_LoadD(uispr,sdata);
                UI_Script_LoadD(uiscr,sdata);
                UI_Sprite_LoadPalette(uispr,*uipal);
            }
            else if(TextIsEqual(ext,".png"))
            {
                switch(uibar->state)
                {
                    case statepalette:
                        UI_palette_LoadF(uipal,files.paths[i]);
                        UI_Sprite_LoadPalette(uispr,*uipal);
                    break;
                    case statesprite:
                        UI_sprite_LoadF(uispr,files.paths[i]);
                    break;
                    default:;
                }
            }
            else if(TextIsEqual(ext,".lua"))
            {
                if(uibar->state==statescript)
                {
                    UI_Script_LoadF(uiscr,files.paths[i]);
                }
            }
        }
        UnloadDroppedFiles(files);
    }
}

void UI_MainBar_Save(struct UI_MainBar *uibar,struct UI_Palette uipal,struct UI_Sprite uispr,struct UI_Script uiscr)
{
    if(uibar->issave==1)
    {
        struct sdata sdata;
        UI_Palette_Save(uipal,&sdata);
        UI_Sprite_Save(uispr,&sdata);
        UI_Script_Save(uiscr,&sdata);
        FILE* fic = fopen(uibar->filename,"wb");
        fwrite(&sdata,sizeof(struct sdata),1,fic);
        fclose(fic);
        uibar->issave=0;
    }
}
void UI_MainBar_Build(struct UI_MainBar *uibar, const char *pfile)
{
    // int lenex = GetFileLength(pfile);
    // int lensdata = GetFileLength(uibar->filename);
    //char sexec[lenex+lensdata];
    if(!TextIsEqual(uibar->filename,"save.egba"))
    {
        #if defined(__linux)
            system(TextFormat("cat %s %s > %s",pfile,uibar->filename,GetFileNameWithoutExt(uibar->filename)));
        #elif defined(_WIN32)
            system(TextFormat("copy /b %s+%s %s",pfile,uibar->filename,TextFormat("%s.exe",GetFileNameWithoutExt(uibar->filename))));
        #endif
    }
}
void _Button_hightlight(struct UI_BUTTON btn)
{
   DrawRectangle(   btn.x-4,
                    btn.y-2,
                    btn.width,
                    btn.height,WHITE);
}
void UI_MainBar_Draw(struct UI_MainBar *uibar)
{
    uibar->isUpdate=0;
    DrawText(uibar->filename,300,8,18,BLACK);
    switch(uibar->state)
    {
        case statepalette:
            _Button_hightlight(uibar->btnpal);
        break;
        case statesprite:
            _Button_hightlight(uibar->btnspr);
        break;
        case statescript:
            _Button_hightlight(uibar->btnscr);
        break;
        default:;
    }
   
    if(UI_BUTTON_draw(&uibar->btnpal))
    {
        if(uibar->state!=statepalette) uibar->isUpdate=1;
        uibar->state=statepalette;
    }
    if(UI_BUTTON_draw(&uibar->btnspr))
    {
        if(uibar->state!=statesprite) uibar->isUpdate=1;
        uibar->state=statesprite;
    }
    if(UI_BUTTON_draw(&uibar->btnscr))
    {
        if(uibar->state!=statescript) uibar->isUpdate=1;
        uibar->state=statescript;
    }
    if(UI_BUTTON_draw(&uibar->btnsave))
        uibar->issave=1;
    if(UI_BUTTON_draw(&uibar->btndoc))
        OpenURL(
}
