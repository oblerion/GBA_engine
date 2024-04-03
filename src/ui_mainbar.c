#include "ui_mainbar.h"

struct UI_MainBar UI_MainBar(int x, int y)
{
    struct UI_MainBar uibar={
    UI_BUTTON(x+5,y+5,"sprite",20,BLACK),
    UI_BUTTON(x,y+5,"script",20,BLACK),
    UI_BUTTON(x+160,y+5,"save",20,BLACK),
    UI_BUTTON(x+350,y+5,"doc",20,BLACK),
    statesprite,
    0,
    false,
    "save.egba"
    };
    uibar.btnscr.x = x+uibar.btnspr.x+uibar.btnspr.width+2;
    uibar.btnsave.x = x+uibar.btnscr.x+uibar.btnscr.width+2;
    uibar.btndoc.x = GetScreenWidth()-uibar.btndoc.width+2;
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
            }
            else if(TextIsEqual(ext,".png"))
            {
                switch(uibar->state)
                {
                    case statesprite:
                        UI_palette_LoadF(uipal,files.paths[i]);
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
void build_exec(char* cart,char* exec,const char* out)
{
    if(FileExists(cart) && FileExists(exec))
    {
        #if defined(__linux)
            FILE* fout = fopen(out,"wb");
            FILE* flinux = fopen(exec,"rb");
            const int filesize=GetFileLength(exec);
            char buflinux[filesize];
            fread(buflinux,filesize,1,flinux);
            fclose(flinux);

            FILE* fcart = fopen(cart,"rb");
            const int filesize2 = GetFileLength(cart);
            char bufcart[filesize2];
            fread(bufcart,filesize2,1,fcart);
            fclose(fcart);

            fwrite(buflinux,filesize,1,fout);
            fwrite(bufcart,filesize2,1,fout);

            fclose(fout);
        #elif defined(_WIN32)
            system(TextFormat("copy /b %s+%s %s",exec,cart,out));
        #endif
        
    }
}
void UI_MainBar_Build(struct UI_MainBar *uibar)
{
    if(!TextIsEqual(uibar->filename,"save.egba") && 
        TextIsEqual(GetFileExtension(uibar->filename),".egba"))
    {
        build_exec(uibar->filename,"egba",TextFormat("%s_linux64",GetFileNameWithoutExt(uibar->filename)));
        build_exec(uibar->filename,"egba.exe",TextFormat("%s_win32.exe",GetFileNameWithoutExt(uibar->filename)));
    }
}
void UI_MainBar_ExportSprite(struct UI_MainBar uibar, struct UI_Sprite uispr,struct UI_Palette uipal)
{
    if((IsKeyDown(KEY_LEFT_CONTROL) || 
            IsKeyDown(KEY_RIGHT_CONTROL)) &&
            IsKeyPressed(KEY_E))
    {
        Image fullimg = GenImageColor(256,257,(Color){0,0,0,0});
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(uispr.sprites[(y*16)+x]);
            Rectangle rso = {0,0,16,16};
            Rectangle rde = {x*16,y*16,16,16};
            ImageDraw(&fullimg,img,rso,rde,WHITE);
            UnloadImage(img);
        }
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<32;j++)
            {
                ImageDrawPixel(&fullimg,(i*32)+j,256,Palette_Get(uipal.palettes[i],j));
            }
        }
        ExportImage(fullimg,TextFormat("%s.png",GetFileNameWithoutExt(uibar.filename)));
        UnloadImage(fullimg);
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
        case statesprite:
            _Button_hightlight(uibar->btnspr);
        break;
        case statescript:
            _Button_hightlight(uibar->btnscr);
        break;
        default:;
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
    {
        OpenURL("https://oblerion.itch.io/gba-engine");
    }
    
}
