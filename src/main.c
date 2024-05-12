#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "data_type.h"
#include <string.h>
#include "../cimg.h"


#define _MATH_collide(x,y,w,h,x2,y2,w2,h2) (x+w>x2 && x<x2+w2 && y+h>y2 && y2+h2>y)
bool UIBUTTON(int px,int py,const char* pname,int fontsize,Color color)
{
    bool lbool = false;
    const int width = MeasureText(pname,fontsize)+8;
    const int height = fontsize+4;
    Color lcol = color;
    if(_MATH_collide(GetMouseX(),GetMouseY(),10,10,px-4,py-2,width,height))
    {
        lcol.a = 50;
        if(IsMouseButtonPressed(0)) lbool = true;
    }
    DrawRectangle(px-4,py-2,width,height,GRAY);
    DrawRectangleLines(px-4,py-2,width,height,lcol);
    DrawText(pname,px,py,fontsize,lcol);
    return lbool;
}

struct UI_SLIDEBAR_V
{
    int x;
    int y;
    int size_cursor;
    int nb_pos_max;
    int pos;
    Color color;
    int width;
    int height;
    bool visible;
};

void UI_SLIDEBAR_V_resize(struct UI_SLIDEBAR_V* bar,int pos_max)
{
    //actualize size and max barre
    bar->nb_pos_max=pos_max;
    bar->size_cursor=bar->height/pos_max;
}
struct UI_SLIDEBAR_V UI_SLIDEBAR_V(int x,int y,int width,int height,int pos_max)
{
    struct UI_SLIDEBAR_V bar = {x,y};
    bar.pos=0;
    bar.color=BLACK;
    bar.visible=true;
    bar.width=width;
    bar.height=height;
    UI_SLIDEBAR_V_resize(&bar,pos_max);
    return bar;
}

bool UI_SLIDEBAR_V_draw(struct UI_SLIDEBAR_V* bar)
{
    bool ret = false;
    if(bar->visible==true)
    {
        if(IsKeyPressed(KEY_UP) || GetMouseWheelMove()>0)
        {
            if(bar->pos>0) bar->pos--;
            ret=true;
        }
        if(IsKeyPressed(KEY_DOWN) || GetMouseWheelMove()<0)
        {
            if(bar->pos<bar->nb_pos_max) bar->pos++;
            ret=true;
        }
        DrawRectangle(bar->x,bar->y+(bar->pos*bar->size_cursor),bar->width,bar->size_cursor,bar->color);
        DrawRectangleLines(bar->x,bar->y,bar->width,bar->height,bar->color);
    }
    return ret;
}
//---------- palette -----------
struct Palette
{
    char name[35];
    Color palette[DT_MAX_COLOR];
};

struct Palette PaletteF(const char *pfile)
{
    struct Palette pal={"",{BLACK}};
    const char* cext = GetFileExtension(pfile);
    // Image fullimage = GenImageColor(DT_MAX_COLOR*20,20,BLACK);
    if(TextIsEqual(cext,".png"))
    {
        
        Image img = LoadImage(pfile);
        //palette.clear();
        if(img.width==32 && img.height==1)
        {
            strcpy(pal.name,GetFileNameWithoutExt(pfile));
            for(int i=0;i<img.width;i++)
            {        
                Color col = GetImageColor(img,i,0);
                pal.palette[i]=col;
                // ImageDrawRectangle(&fullimage,i*20,0,20,20,col);
            }
        }
        UnloadImage(img);
    }
    return pal;
}

struct Palette PaletteD(struct spalette spalette)
{
    struct Palette pal;
    strcpy(pal.name,spalette.name);
    // Image img = GenImageColor(DT_MAX_COLOR*20,20,BLACK);
    for(int i=0;i<DT_MAX_COLOR;i++)
    {
        pal.palette[i]= GetColor(spalette.data[i]);
        // ImageDrawRectangle(&img,i*20,0,20,20,GetColor(spalette.data[i]));
    }
    return pal;
}
int Palette_Size(struct Palette pal)
{
    return sizeof(pal.palette)/sizeof(int);
}
Color Palette_Get(struct Palette pal, int id)
{
    if(id<0 || id>Palette_Size(pal)) return WHITE;
    return pal.palette[id];
}

const char *Palette_GetName(struct Palette pal)
{
    return TextFormat("%s",pal.name);
}

struct spalette Palette_GetStruct(struct Palette pal)
{
    struct spalette spalette;
    strcpy(spalette.name,pal.name);
    for(int i=0;i<DT_MAX_COLOR;i++)
    {
        spalette.data[i]= ColorToInt(pal.palette[i]);
    }
    return spalette;
}

Image Palette_GetImg(struct Palette pal)
{
    Image img = GenImageColor(32,1,BLACK);
    for(int i=0;i<DT_MAX_COLOR;i++)
    {
        ImageDrawPixel(&img,i,0,pal.palette[i]);
    }
    return img;
}

//--------- sprite --------
struct Sprite
{
    int width;
    int height;
    Color ldata[256];
};

struct Sprite SpriteD(struct ssprite ssprite)
{
    struct Sprite spr={ssprite.width,ssprite.height};
    for(int i=0;i<spr.width*spr.height;i++)
    {
        spr.ldata[i] = ssprite.data[i];
    }
    return spr;
}
struct Sprite Sprite()
{
	struct Sprite spr={16,16};
	for(int i=0;i<spr.width*spr.height;i++)
	{
		spr.ldata[i]=BLACK;
	}
	return spr;
}
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col)
{
    spr->ldata[(y*spr->width)+x]=col;
}
struct ssprite Sprite_GetStruct(struct Sprite spr)
{
    struct ssprite ssprite;
    ssprite.width=spr.width;
    ssprite.height=spr.height;
    
    for(int i=0;i<spr.width*spr.height;i++)
    {
        ssprite.data[i]=spr.ldata[i];
    }

    return ssprite;
}
Image Sprite_GetImg(struct Sprite spr)
{
    Image img = GenImageColor(spr.width,spr.height,BLACK);
    for(int i=0;i<spr.width*spr.height;i++)
	{
        ImageDrawPixel(&img,i%spr.width,i/spr.width,spr.ldata[i]);
	}
    return img;
}
//----- atlas  ------------
struct satlas
{
    Texture2D sprites;
    Texture2D palettes;
}Atlas;

void Atlas_Init()
{
    Image img = GenImageColor(32,5,BLACK);
    Atlas.palettes = LoadTextureFromImage(img);
    UnloadImage(img);

    img = GenImageColor(256,256,BLACK);
    Atlas.sprites = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Atlas_DrawPalette(int id, int x, int y, int scale)
{
    if(id>-1 && id<6)
    DrawTexturePro(Atlas.palettes,(Rectangle){0,id,32,1},(Rectangle){x,y,32*scale,scale},(Vector2){0,0},0,WHITE);
}
void Atlas_UpdatePalette(struct Palette* palettes)
{
    Image img = GenImageColor(32,5,BLACK);
//LoadImageFromTexture(uipal->texture);
    Image palimg;
    for(int i=0;i<DT_MAX_PALETTE;i++)
    {
        palimg = Palette_GetImg(palettes[i]);
        ImageDraw(&img,palimg,(Rectangle){0,0,32,1},(Rectangle){0,i,32,1},WHITE);
    }
    UpdateTexture(Atlas.palettes,img.data);
    UnloadImage(palimg);
    UnloadImage(img);
}
void Atlas_DrawSprite(int id,int x,int y,int scale)
{
    DrawTexturePro(Atlas.sprites,
        (Rectangle){(id%16)*16,(id/16)*16,16,16},
        (Rectangle){x,y,16*scale,16*scale},(Vector2){0,0},0,WHITE);
}
void Atlas_UpdateSprite(struct Sprite* sprites)
{
    Image img = GenImageColor(256,256,(Color){0,0,0,0});
    for(int i=0;i<DT_MAX_SPRITE;i++)
    {
        Image imgspr = Sprite_GetImg(sprites[i]);
        ImageDraw(&img,imgspr,
            (Rectangle){0,0,16,16},
            (Rectangle){(i%16)*16,(i/16)*16,16,16},
            WHITE
        );
        UnloadImage(imgspr);
    }
    UpdateTexture(Atlas.sprites,img.data);
    UnloadImage(img);
}

void Atlas_Free()
{
    UnloadTexture(Atlas.palettes);
    UnloadTexture(Atlas.sprites);
}


//#include "ui_palette.h"
struct UI_Palette
{
    //struct UI_BUTTON btndelete;
    struct Palette palettes[DT_MAX_PALETTE];
}UI_Palette;

void UI_Palette_Init(int pscale)
{
    //struct UI_Palette uipal={
        //UI_BUTTON((pscale-1)*32,0,"delete",pscale-2,BLACK)
    //};
    for(int i=0;i<DT_MAX_PALETTE;i++)
        strcpy(UI_Palette.palettes[i].name,"");
    //return uipal;
}
void UI_palette_LoadF(const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        Image img = LoadImage(pfile);
        if(img.width>0 && img.width<=32 && img.height==1)
        {
            for(int i=0;i<DT_MAX_PALETTE;i++)
            {
                if(strlen(UI_Palette.palettes[i].name)==0)
                {
                    UI_Palette.palettes[i] = PaletteF(pfile);
                    Atlas_UpdatePalette(UI_Palette.palettes);
                    break;
                }
            }
        }
        else if(img.width==256 && img.height==257)
        {
            for(int i=0;i<160;i++)
            {
                strcpy(UI_Palette.palettes[i/32].name,TextFormat("%d",i/32));
                Color col = GetImageColor(img,i,256);
                UI_Palette.palettes[i/32].palette[i-((i/32)*32)]=col;
                Atlas_UpdatePalette(UI_Palette.palettes);
            }
        }
        UnloadImage(img);
    }
}
void UI_Palette_LoadD(struct sdata sdata)
{
    for(int j=0;j<DT_MAX_PALETTE;j++)
    {
        UI_Palette.palettes[j] = PaletteD(sdata.list_pal[j]);
    }
    Atlas_UpdatePalette(UI_Palette.palettes);
}
void UI_Palette_Save(struct sdata* sdata)
{
    for(int i=0;i<DT_MAX_PALETTE;i++)
    {
        sdata->list_pal[i] = Palette_GetStruct(UI_Palette.palettes[i]);
    }
}
struct Palette UI_Palette_Get(int id)
{
    return UI_Palette.palettes[id];
}
int UI_Palette_Draw(int px,int py,int pscale)
{
    int ret=-1;
    const int yborder = 30;
    // UI button,scroll
    int nbpalette=0;
    for(int i=0;i<DT_MAX_PALETTE;i++)
    {
        if(strlen(UI_Palette.palettes[i].name)>0) nbpalette++;
    }

    if(nbpalette>0)
    {
        for(int j=0;j<DT_MAX_PALETTE;j++)
        {
            if(strlen(UI_Palette.palettes[j].name)>0)
            {
                Atlas_DrawPalette(j,px+23,py+yborder+23+(j*45),pscale);
                DrawText(UI_Palette.palettes[j].name,px+5,py+yborder+(j*45)+5,10,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){px+23,py+(float)yborder+23+(j*45),32*pscale,pscale}))
                {
                    if(UIBUTTON((pscale-1)*32,py+yborder+21+(j*45)+2,"delete",pscale-2,BLACK))
                    //if(UI_BUTTON_draw(&UI_Palette.btndelete))
                    {
                        //PaletteManager_Del(&uipal->palman,j);
                        strcpy(UI_Palette.palettes[j].name,"");
                        for(int i=0;i<DT_MAX_COLOR;i++)
                        {
                            UI_Palette.palettes[j].palette[i]=BLACK;
                        }
                    }
                }
            }
            else if(j+1<DT_MAX_PALETTE)
            {
                if( strlen(UI_Palette.palettes[j+1].name)>0)
                {
                    UI_Palette.palettes[j] = UI_Palette.palettes[j+1];
                    strcpy(UI_Palette.palettes[j+1].name,"");
                    for(int i=0;i<DT_MAX_COLOR;i++)
                    {
                        UI_Palette.palettes[j+1].palette[i]=BLACK;
                    }
                    Atlas_UpdatePalette(UI_Palette.palettes);
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


//#include "ui_sprite.h"

struct UI_BUTTONSPRITE 
{
    int x;
    int y;
    int scale;
    int id_sprite;
    bool visible;
};

struct UI_Sprite
{
    Texture2D sprfond;
    //Texture2D spratlas;
    struct UI_BUTTONSPRITE btnspr[DT_MAX_SPRITE];
    //struct UI_BUTTONCOLOR btncolor[256];
    //struct UI_BUTTONCOLOR btnpal[32];
    //struct UI_BUTTON btnerase;
    struct UI_SLIDEBAR_V slidepalette;
    Color curant_color;
    int curant_spr;
    int curant_pal;
    struct Sprite sprites[DT_MAX_SPRITE];
    int btnspr_size;
    int btncol_size;
}UI_Sprite;


struct UI_BUTTONSPRITE UI_BUTTONSPRITE(int x, int y,int scale,int id_sprite)
{
    struct UI_BUTTONSPRITE btnspr={x,y,scale,id_sprite,true};
    return btnspr;
}

int UI_BUTTONSPRITE_Draw(struct UI_BUTTONSPRITE btnspr)
{
    int ret=0;
    if(btnspr.visible)
    {
        Atlas_DrawSprite(btnspr.id_sprite,btnspr.x,btnspr.y,btnspr.scale);
        int ix = GetMouseX();
        int iy = GetMouseY();
        if(_MATH_collide(ix,iy,1,1,
            btnspr.x,btnspr.y,16*btnspr.scale,16*btnspr.scale)==1)
        {
            if(IsMouseButtonDown(0)) ret = 1;
            DrawRectangle(btnspr.x,btnspr.y,16*btnspr.scale,16*btnspr.scale,(Color){255,255,255,100});
        }
    }
    return ret;
}
Image GenTriangle(int scale,Color col)
{
    Image img = GenImageColor(scale,scale,(Color){0,0,0,0});
    for(int q=0;q<scale;q++)
    {
        ImageDrawLine(&img,q,0,q,q,col);
    }
    return img;
}

void UI_Sprite_Init()
{
    //struct UI_Sprite uispr;
	UI_Sprite.slidepalette = UI_SLIDEBAR_V(420,460,10,50,5);
    const int size = 16;
    UI_Sprite.curant_spr=0;
    UI_Sprite.curant_color=BLACK;  
    UI_Sprite.curant_pal=0;
    UI_Sprite.btnspr_size = 2;
    UI_Sprite.btncol_size = 26;
    for(int y=0;y<size;y++)
    for(int x=0;x<size;x++)
    {
        UI_Sprite.sprites[(size*y)+x] = Sprite();
        UI_Sprite.btnspr[(size*y)+x] = UI_BUTTONSPRITE(440+(x*UI_Sprite.btnspr_size*16),
                                                    30+(y*UI_Sprite.btnspr_size*16),
                                                    UI_Sprite.btnspr_size,
                                                    (size*y)+x);
    }
    // fond spr
    Image itrangle = GenTriangle(26,WHITE);
    Image img = GenImageColor(26*16,26*16,BLACK);
    for(int i=0;i<16;i++)
    for(int j=0;j<16;j++)
    {
        ImageDraw(&img,itrangle,(Rectangle){0,0,26,26},(Rectangle){i*26,j*26,26,26},WHITE);
    }
    UI_Sprite.sprfond = LoadTextureFromImage(img);
    UnloadImage(itrangle);
    UnloadImage(img);
    // atlas
    // img = GenImageColor(256,256,BLACK);
    // uispr.spratlas = LoadTextureFromImage(img);
    // UnloadImage(img);
    //return uispr;
}

struct Sprite UI_sprite_Get(int id)
{
    return UI_Sprite.sprites[id];
}

void UI_Sprite_LoadD(struct sdata sdata)
{
    //uispr->sprman=SpriteManagerD(sdata,uispr->sprman.palman);
    for(int i=0;i<DT_MAX_SPRITE;i++)
    {
        UI_Sprite.sprites[i] = SpriteD(sdata.list_spr[i]);
    }
    Atlas_UpdateSprite(UI_Sprite.sprites);
}

void UI_sprite_LoadF(const char *pfile)
{
    Image fullimg = LoadImage(pfile);
    if(fullimg.width==256 && fullimg.height==257)
    {
      
        for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
        {
            Image img = GenImageColor(16,16,(Color){0,0,0,0});
            ImageDraw(&img,fullimg,
                    (Rectangle){j*16,i*16,16,16},
                    (Rectangle){0,0,16,16},WHITE);
            
            Color* img_col = (Color*)img.data; 
            for(int col=0;col<256;col++)
            UI_Sprite.sprites[(i*16)+j].ldata[col] = img_col[col];
            UnloadImage(img);
        }
        Atlas_UpdateSprite(UI_Sprite.sprites);
    }
    UnloadImage(fullimg);
}

void UI_Sprite_Save(struct sdata *sdata)
{
    for(int i=0;i<DT_MAX_SPRITE;i++)
    {
        sdata->list_spr[i] = Sprite_GetStruct(UI_Sprite.sprites[i]);
    }
}

int UI_Sprite_Draw()
{
    int ret=0;
    DrawTexture(UI_Sprite.sprfond,2,30,WHITE);
    DrawRectangleLines(440,30,16*2*16,16*2*16,BLACK);
    for(int y=0;y<16;y++)
    for(int x=0;x<16;x++)
    {
        int id = (16*y)+x;
        if(UI_BUTTONSPRITE_Draw(UI_Sprite.btnspr[id]))
        {
			UI_Sprite.curant_spr=id;
        }
        Atlas_DrawSprite(UI_Sprite.curant_spr,2,30,UI_Sprite.btncol_size);
    }
    return ret;
}

void UI_Sprite_Free()
{
    UnloadTexture(UI_Sprite.sprfond);
    //UnloadTexture(uispr.spratlas);
}

//#include "ui_script.h"
struct UI_Script
{
    char source_script[40];
    char script[DT_MAX_SCRIPTSIZE];
}UI_Script;

void UI_Script_Init()
{
    UI_Script.script[0]='\0';
    UI_Script.source_script[0]='\0';
}

void UI_Script_LoadF(const char* pfile)
{
    FILE* fic = fopen(pfile,"r");
    if(fic!=NULL)
    {
        fseek(fic,SEEK_END,0);
        long pos = ftell(fic);
        fseek(fic,SEEK_SET,0);
        int p=0;
        strcpy(UI_Script.script,"\0");
        if(pos<DT_MAX_SCRIPTSIZE){
     
            do
            {
                fscanf(fic,"%c",&UI_Script.script[p]);
                p++;
            }
            while(feof(fic)==0);
        }
        strcpy(UI_Script.source_script,".lua");
        fclose(fic);
    }
}

void UI_Script_LoadD(struct sdata sdata)
{
    strcpy(UI_Script.source_script,".dat");
    strcpy(UI_Script.script,sdata.script);
}

void UI_Script_Save(struct sdata *sdata)
{
    strcpy(sdata->script,UI_Script.script);
}

void UI_Script_Draw()
{
    DrawText(UI_Script.script,15,30,18,BLACK);
}

//#include "ui_mainbar.h"

void _LoadEGBA(const char* pfile)
{
    const char* ext = GetFileExtension(pfile);
    if(TextIsEqual(ext,".egba"))
    {
        struct sdata sdata;
        FILE* fic = fopen(pfile,"rb");
        fread(&sdata,sizeof(struct sdata),1,fic);
        fclose(fic);
        UI_Palette_LoadD(sdata);
        UI_Sprite_LoadD(sdata);
        UI_Script_LoadD(sdata);
    }
}
void _LoadSprite(const char* pfile)
{
    const char* ext = GetFileExtension(pfile);
    if(TextIsEqual(ext,".png"))
    {
        UI_palette_LoadF(pfile);
        UI_sprite_LoadF(pfile);
    }
}
void _LoadScript(const char* pfile)
{
    const char* ext = GetFileExtension(pfile);
    if(TextIsEqual(ext,".lua"))
    {
        UI_Script_LoadF(pfile);
    }
}


void _Save(const char* filename)
{
    //if(UI_MainBar.issave==1)
    //{
        struct sdata sdata;
        UI_Palette_Save(&sdata);
        UI_Sprite_Save(&sdata);
        UI_Script_Save(&sdata);
        FILE* fic = fopen(filename,"wb");
        fwrite(&sdata,sizeof(struct sdata),1,fic);
        fclose(fic);
        //UI_MainBar.issave=0;
    //}
}
void _Build_exec(const char* cart,const char* exec,const char* out)
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
void _Build(const char* filename)
{
    if(!TextIsEqual(filename,"save.egba") && 
        TextIsEqual(GetFileExtension(filename),".egba"))
    {
        _Build_exec(filename,"egba",TextFormat("%s_linux64",GetFileNameWithoutExt(filename)));
        _Build_exec(filename,"egba.exe",TextFormat("%s_win32.exe",GetFileNameWithoutExt(filename)));
    }
}
void _ExportSprite(const char* filename)
{
        Image fullimg = GenImageColor(256,257,(Color){0,0,0,0});
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(UI_Sprite.sprites[(y*16)+x]);
            Rectangle rso = {0,0,16,16};
            Rectangle rde = {x*16,y*16,16,16};
            ImageDraw(&fullimg,img,rso,rde,WHITE);
            UnloadImage(img);
        }
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<32;j++)
            {
                ImageDrawPixel(&fullimg,(i*32)+j,256,Palette_Get(UI_Palette.palettes[i],j));
            }
        }
        ExportImage(fullimg,TextFormat("%s.png",GetFileNameWithoutExt(filename)));
        UnloadImage(fullimg);
    
}

//------------- runner -------------------
//#include "ui_runner.h"
#include "clua.h"
struct UI_Runner
{
    struct CLUA clua;
    struct Sprite spr[DT_MAX_SPRITE];
    struct Palette pal[DT_MAX_PALETTE];
}uirun;

int rlua_trace(clua_state* L)
{
    const char* pstr = lua_tostring(L,1);
    puts(pstr);
    return 0;
}

int rlua_cls(clua_state* L)
{
    int id = lua_tointeger(L,1);
    Color col = uirun.pal[0].palette[id];
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),col);
    return 0;
}

int rlua_drawtext(clua_state* L)
{
    // extern struct UI_Runner uirun;
    const char* cstr = lua_tostring(L,1);
    int x = lua_tonumber(L,2);
    int y = lua_tonumber(L,3);
 
    Color col = uirun.pal[0].palette[(int)lua_tonumber(L,4)];
    int scale = lua_tointeger(L,5);
    if(scale==0) scale=16;
    DrawText(cstr,x,y,scale,col);
    //lua_pop(L,4);
    return 0;
}

int rlua_drawsprite(clua_state* L)
{
    int id = lua_tointeger(L,1);
    int x = lua_tonumber(L,2);
    int y = lua_tonumber(L,3);
    int scale = lua_tointeger(L,4);
    if(scale == 0) scale = 2;
    Atlas_DrawSprite(id,x,y,scale);
    return 0;
}

int rlua_drawrect(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);;
    Color col = uirun.pal[0].palette[(int)lua_tonumber(L,5)];
    DrawRectangle(x,y,w,h,col);
    return 0;
}

int rlua_drawrectb(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);;
    Color col = uirun.pal[0].palette[(int)lua_tonumber(L,5)];
    DrawRectangleLines(x,y,w,h,col);
    return 0;
}

int rlua_btn(clua_state* L)
{
    int id = lua_tointeger(L,1);
    switch(id)
    {
        case 0: 
            if(IsKeyDown(KEY_UP)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 1: 
            if(IsKeyDown(KEY_DOWN)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 2: 
            if(IsKeyDown(KEY_LEFT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 3: 
            if(IsKeyDown(KEY_RIGHT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        default:;
    }
    lua_pushboolean(L,0);
    return 1;
}

int rlua_btnp(clua_state* L)
{
    int id = lua_tointeger(L,1);
    switch(id)
    {
        case 0: 
            if(IsKeyPressed(KEY_UP)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 1: 
            if(IsKeyPressed(KEY_DOWN)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 2: 
            if(IsKeyPressed(KEY_LEFT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 3: 
            if(IsKeyPressed(KEY_RIGHT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        default:;
    }
    lua_pushboolean(L,0);
    return 1;
}

int rlua_mouse(clua_state* L)
{
    lua_pushinteger(L,GetMouseX());
    lua_pushinteger(L,GetMouseY());
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_LEFT));
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_MIDDLE));
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
    return 5;
}

void _UI_Runner_functionpush(int (*pfunc)(clua_state*),const char* name)
{
    CLUA_setfunction(&uirun.clua,pfunc,name);
}

void UI_Runner()
{
    uirun.clua = CLUA();
    _UI_Runner_functionpush(rlua_cls,"cls");
    _UI_Runner_functionpush(rlua_drawtext,"print");
    _UI_Runner_functionpush(rlua_drawsprite,"spr");
    _UI_Runner_functionpush(rlua_drawrect,"rect");
    _UI_Runner_functionpush(rlua_drawrectb,"rectb");
    _UI_Runner_functionpush(rlua_btn,"btn");
    _UI_Runner_functionpush(rlua_btnp,"btnp");
    _UI_Runner_functionpush(rlua_mouse,"mouse");
    _UI_Runner_functionpush(rlua_trace,"trace");
}
void UI_Runner_LoadD(struct sdata sdata)
{
    for(int i=0;i<DT_MAX_PALETTE;i++)
        uirun.pal[i]=PaletteD(sdata.list_pal[i]);
    Atlas_UpdatePalette(uirun.pal);
    for(int i=0;i<DT_MAX_SPRITE;i++)
        uirun.spr[i]=SpriteD(sdata.list_spr[i]);
    Atlas_UpdateSprite(uirun.spr);
    CLUA_dostring(&uirun.clua,sdata.script);
}

bool UI_Runner_Load(const char *pfile)
{
    const char* ext = GetFileExtension(pfile);
    if(TextIsEqual(ext,".egba"))
    {
        struct sdata sdata;
        FILE* fic = fopen(pfile,"rb");
        if(fic!=NULL)
        {
            UI_Runner();
            fread(&sdata,sizeof(struct sdata),1,fic);
            fclose(fic);
			UI_Runner_LoadD(sdata);
            return true;
        }
        else puts(TextFormat("runner error : %s not found",pfile));
    }
    else if(TextIsEqual(ext,".lua"))
    {
        //struct sdata sdata;
        const char* fileext = TextFormat("%s.png",GetFileNameWithoutExt(pfile));
        //FILE* fic = fopen(fileext,"rb");
        if(FileExists(fileext))
        {
            UI_Runner();
            //fread(&sdata,sizeof(struct sdata),1,fic);
            //fclose(fic);
            //for(int i=0;i<DT_MAX_PALETTE;i++)
                //uirun.pal[i]=PaletteD(sdata.list_pal[i]);
            //Atlas_UpdatePalette(uirun.pal);
            //for(int i=0;i<DT_MAX_SPRITE;i++)
                //uirun.spr[i]=SpriteD(sdata.list_spr[i]);
            //Atlas_UpdateSprite(uirun.spr);
            _LoadSprite(fileext);
            CLUA_dofile(&uirun.clua,pfile);
            return true;
        }else puts(TextFormat("runner error : %s not found",fileext));
    }
    return false;
}

void UI_Runner_Draw()
{
    if(CLUA_iferror(&uirun.clua))
    {
        DrawText(CLUA_geterror(&uirun.clua),23,23,20,BLACK);
    }
    else
        CLUA_callfunction(&uirun.clua,"EGBA");
}

void UI_Runner_Free()
{
    CLUA_free(&uirun.clua);
}

// project viewer/editor
struct sproject
{
	char name[50];
	char islua;
	char isegba;
	char ispng;
};
typedef struct sproject Project;

const char* PROJECT_GetFileLua(Project spjt)
{
	return TextFormat("%s.lua",spjt.name);
}
const char* PROJECT_GetFilePng(Project spjt)
{
	return TextFormat("%s.png",spjt.name);
}
const char* PROJECT_GetFileEgba(Project spjt)
{
	return TextFormat("%s.egba",spjt.name);
}

Project PROJECT_Init(const char* pname)
{
	Project spjt = {0};
	TextCopy(spjt.name,pname);
	
	if(FileExists(PROJECT_GetFileLua(spjt)))
	{
		spjt.islua=1;
		//_LoadScript(PROJECT_GetFileLua(spjt));
	}
	if(FileExists(PROJECT_GetFilePng(spjt)))
	{
		spjt.ispng=1;
		//_LoadSprite(PROJECT_GetFilePng(spjt));
	}
	if(FileExists(PROJECT_GetFileEgba(spjt)))
	{
		spjt.isegba=1;
		//_LoadEGBA(spjt);
	}
	return spjt;
}

//browser project add/del
#define BROWSER_PROJECT_MAX 100
struct sbrowser
{
	Project list[BROWSER_PROJECT_MAX];
	int project_nb;
	float timer;
	
};
typedef struct sbrowser Browser;
Browser _BROWSER;

char BROWSER_IfProjectExist(const char* name)
{
	char rc = 0;
	const char* filelua = TextFormat("%s.lua",name);
	const char* fileegba = TextFormat("%s.egba",name);
	
	if(FileExists(filelua) || FileExists(fileegba))
		rc=1;
	
	return rc;
}

char BROWSER_IfProjectLoaded(const char* name)
{
	char ir=0;
	for(int i=0;i<_BROWSER.project_nb;i++)
	{
		if(TextIsEqual(name,_BROWSER.list[i].name))
		{
			ir=1;
			break;
		}
	}
	return ir;
}

void BROWSER_LoadProject(const char* name)
{
	if(BROWSER_IfProjectExist(name))
	{
		_BROWSER.list[_BROWSER.project_nb] = PROJECT_Init(name);
		++_BROWSER.project_nb;
	}
}
void BROWSER_Scan()
{
	_BROWSER.project_nb=0;
	FilePathList files = LoadDirectoryFiles(".");
	for(int i=0;i<files.count;i++)
	{  
		if(!DirectoryExists(files.paths[i]))
		{
			const char* file_noext = GetFileNameWithoutExt(files.paths[i]);
			if(!BROWSER_IfProjectLoaded(file_noext))
				BROWSER_LoadProject(file_noext);
		}
	}
	UnloadDirectoryFiles(files);
}
void BROWSER_CreateProject(const char* name)
{
	if(_BROWSER.project_nb<BROWSER_PROJECT_MAX)
	{
		char tmp_name[100];
		int tmp_i = 0;
		strcpy(tmp_name,name);
		while(BROWSER_IfProjectExist(tmp_name))
		{
			++tmp_i;
			strcpy(tmp_name,TextFormat("%s%d",name,tmp_i));
		}
		
		Image img = GenImageColor(256,257,BLACK);
		ExportImage(img,TextFormat("%s.png",tmp_name));
		UnloadImage(img);
		
		char script_data[45] = "function EGBA()\n-- code run 60/seconds\nend";
		script_data[45]='\0';
		SaveFileText(TextFormat("%s.lua",tmp_name),script_data);
		BROWSER_Scan();
	}
}

void BROWSER_DelProject(const char* name)
{
#if defined(__linux)
	const char* CMD_RM = "rm"; 
#elif defined(WIN32)
	const char* CMD_RM = "del"; 
#endif
	
	for(int i=0;i<_BROWSER.project_nb;i++)
	{
		if(TextIsEqual(name,_BROWSER.list[i].name))
		{
			if(_BROWSER.list[i].islua)
				system(TextFormat("%s %s",CMD_RM,
				PROJECT_GetFileLua(_BROWSER.list[i])));
			if(_BROWSER.list[i].ispng)
				system(TextFormat("%s %s",CMD_RM,
				PROJECT_GetFilePng(_BROWSER.list[i])));
			if(_BROWSER.list[i].isegba)
				system(TextFormat("%s %s",CMD_RM,
				PROJECT_GetFileEgba(_BROWSER.list[i])));
			BROWSER_Scan();
			break;
		}
	}
}

void BROWSER_Init()
{
	BROWSER_Scan();
}

#define BROWSER_PROJECT_MAX_H 24
int BROWSER_Draw()
{
	int ri=-1;
	DrawText("project list",23,1,20,BLACK);
    for(int i=0;i<_BROWSER.project_nb;i++)
    {
		if(UIBUTTON(
		((i/BROWSER_PROJECT_MAX_H)*200)+23+16,
		24+((i%BROWSER_PROJECT_MAX_H)*28),
		_BROWSER.list[i].name,
		18,BLACK)
		)
		{
				ri=i;
		}
		//del button
		if(UIBUTTON(
		((i/BROWSER_PROJECT_MAX_H)*200)+13,
		24+((i%BROWSER_PROJECT_MAX_H)*28),
		"-",
		20,BLACK)
		)
		{
			if(_BROWSER.timer==0)
			{
				BROWSER_DelProject(_BROWSER.list[i].name);
				_BROWSER.timer=0.001f;
			}
		}
		
	}

	// add button
	if(_BROWSER.project_nb<BROWSER_PROJECT_MAX)
	{
		if(UIBUTTON(
			(((_BROWSER.project_nb)/BROWSER_PROJECT_MAX_H)*200)+13,
			24+(((_BROWSER.project_nb)%BROWSER_PROJECT_MAX_H)*28),
			"+",
			20,BLACK))
		{
			if(_BROWSER.timer==0)
			{
				BROWSER_CreateProject("new");
				_BROWSER.timer=0.001f;
			}
		}
	}
	
	if(_BROWSER.timer>0)
		_BROWSER.timer-=GetFrameTime();
	else if(_BROWSER.timer<0)
		_BROWSER.timer=0;
	
	return ri;
}

//-------- ui project -----------
enum UIPROJECT_STATE
{
	UIPROJECT_STATE_DEFAULT=0,
	UIPROJECT_STATE_VSPRITE,
	UIPROJECT_STATE_VSCRIPT,
};

struct suiproject
{
	int id;
	enum UIPROJECT_STATE state;
	char isactive;
}_UIPROJECT;

void UIPROJECT_Init(int idproject)
{
	_UIPROJECT.id=idproject;
	_UIPROJECT.isactive=1;
	if(_BROWSER.list[idproject].islua)
		_LoadScript(PROJECT_GetFileLua(_BROWSER.list[idproject]));
	if(_BROWSER.list[idproject].ispng)
		_LoadSprite(PROJECT_GetFilePng(_BROWSER.list[idproject]));
	if(_BROWSER.list[idproject].isegba)
		_LoadEGBA(PROJECT_GetFileEgba(_BROWSER.list[idproject]));
}
void UIPROJECT_Draw()
{
	if(_UIPROJECT.isactive)
	{
		Project lproject = _BROWSER.list[_UIPROJECT.id];
		switch(_UIPROJECT.state)
		{
			case UIPROJECT_STATE_DEFAULT:
				if(UIBUTTON(5,5,"back",20,BLACK))
				{
					_UIPROJECT.isactive=0;
				}
				if(lproject.islua)
				{
					if(UIBUTTON(50,50,"lua",20,BLACK))
					{
						_UIPROJECT.state=UIPROJECT_STATE_VSCRIPT;
					}
				}
				if(lproject.ispng)
				{	
					if(UIBUTTON(50,90,"png",20,BLACK))
					{
						_UIPROJECT.state=UIPROJECT_STATE_VSPRITE;
					}	
				}
				
			break;
			case UIPROJECT_STATE_VSPRITE:
				if(UIBUTTON(5,5,"back",20,BLACK))
				{
					_UIPROJECT.state=UIPROJECT_STATE_DEFAULT;
				}
				UI_Sprite_Draw();
			break;
			case UIPROJECT_STATE_VSCRIPT:
				if(UIBUTTON(5,5,"back",20,BLACK))
				{
					_UIPROJECT.state=UIPROJECT_STATE_DEFAULT;
				}
				UI_Script_Draw();
			break;
			default:;
		};
	}
}
//-------- egba -----------------
//enum EGBA_STATE
//{
		//state_browser=0,
		//state_spriteview,
		//state_scriptview
//};

struct EGBA
{
    bool ifrunner;
    //enum EGBA_STATE state;
}EGBA;
void EGBA_Init(int narg, char **sarg)
{
    Atlas_Init();
    _UIPROJECT.isactive=0;
    //struct EGBA egba = (struct EGBA){false};
    EGBA.ifrunner=false;
    if(narg==1)
    {
        if(TextIsEqual( GetFileNameWithoutExt(sarg[0]) ,"egba"))
        {// init editor
            UI_Palette_Init(12);
            UI_Sprite_Init();
            UI_Script_Init();
        }
        else 
        {// run game
            int size = GetFileLength(sarg[0]);
            FILE* fic = fopen(sarg[0],"rb");
            struct sdata sdata;
            if(fic!=NULL)
            {
                fseek(fic,size-sizeof(struct sdata),0);
                fread(&sdata,sizeof(struct sdata),1,fic);
                fclose(fic);
                UI_Runner();
                UI_Runner_LoadD(sdata);
            }
            EGBA.ifrunner = true;
        }
    }
    else if(narg==2)
    {
        if(UI_Runner_Load(sarg[1]))
        // runner init 
            EGBA.ifrunner = true;
        else
        {// runner fail -> init editor
            puts("error : runner fail");
            UI_Palette_Init(12);
            UI_Sprite_Init();
            UI_Script_Init();
        }
    }
}

void EGBA_Draw()
{
	int browser_state=-1;
    if(EGBA.ifrunner==false)
    {
    
        if(IsKeyDown(KEY_RIGHT_CONTROL) &&
            IsKeyPressed(KEY_B))
        {
           
        }

        //switch(EGBA.state)
        //{
            //case state_browser:
            if(_UIPROJECT.isactive==0)
            {
				browser_state = BROWSER_Draw();
				
				if(browser_state>-1)
				{
					UIPROJECT_Init(browser_state);
				}
			}
			UIPROJECT_Draw();
            //break;
            //case state_spriteview:
                ////UI_MainBar_ExportSprite();
                //UI_Sprite_Draw();
                //UI_Palette_Draw(0,430,12);
            //break;
            //case state_scriptview:
                //UI_Script_Draw();
            //default:;
        //}
    }
    else if(EGBA.ifrunner==true)
    {// runner draw
        UI_Runner_Draw();
    }
}

void EGBA_Free()
{
    if(EGBA.ifrunner==false)
    {// free editor
        Atlas_Free();
    }
    else if(EGBA.ifrunner==true)
    {// free runner / game
        UI_Runner_Free();
    }
}
#define EGBA_VERSION "a0.1-2"
#define EGBA_TITLE TextFormat("GBA engine ver %s by oblerion",EGBA_VERSION)
//------------------ main -------------------
int main(int narg,char** sarg)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = (720*4)/3; //GetMonitorWidth(0);
    const int screenHeight = 720;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, EGBA_TITLE);
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    SetWindowIcon(icon);    

	EGBA_Init(narg,sarg);
    BROWSER_Init();
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EGBA_Draw();
        EndDrawing();
    }
    
    EGBA_Free();
    CloseWindow();        // Close window and OpenGL
    return 0;
}

