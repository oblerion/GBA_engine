#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "EGBA.h"
#include "../cimg.h"

struct segba_data Editor_data;
struct segba_atlas Editor_atlas;
//------------------ config editor
struct sconfig
{
    Color color1;
    Color color2;
};

struct suiconfig
{
    struct sconfig config;
    char isactive;
    float timer;
}_UICONFIG;

#define UICONFIG_COL1() (_UICONFIG.config.color1)
#define UICONFIG_COL2() (_UICONFIG.config.color2)

// ---------------------- ext lib
#define _MATH_collide(x,y,w,h,x2,y2,w2,h2) (x+w>x2 && x<x2+w2 && y+h>y2 && y2+h2>y)
int UIBUTTON_W(const char* pname,int fontsize)
{
	return MeasureText(pname,fontsize)+8;
}
int UIBUTTON_H(int fontsize)
{
	return fontsize+4;
}
bool UIBUTTON(int px,int py,const char* pname,int fontsize,Color color)
{
    bool lbool = false;
    const int width = UIBUTTON_W(pname,fontsize);
    const int height = UIBUTTON_H(fontsize);
    Color lcol = ColorBrightness(color,0.3f);
    if(_MATH_collide(GetMouseX(),GetMouseY(),10,10,px-4,py-2,width,height))
    {
        lcol = ColorBrightness(color,-0.3f);
        if(IsMouseButtonPressed(0)) lbool = true;
    }
    DrawRectangle(px-4,py-2,width,height,ColorBrightness(color,-0.35f));
    DrawRectangleLines(px-4,py-2,width,height,lcol);
    DrawText(pname,px,py,fontsize,lcol);
    return lbool;
}

char UIBUTTONIMG(int x,int y,Texture text)
{
    int scale = 3;
    DrawTextureEx(text,(Vector2){(float)x,(float)y},0,scale,WHITE);
    if(_MATH_collide(GetMouseX(),GetMouseY(),10,10,x,y,text.width*scale,text.height*scale))
    {
        DrawRectangle(x,y,text.width*scale,text.height*scale,(Color){255,255,255,50});
        if(IsMouseButtonPressed(0)) return 1;
    }
    return 0;
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


struct Palette PaletteF(const char *pfile)
{
    struct Palette pal={"",{BLACK}};
    const char* cext = GetFileExtension(pfile);
    if(TextIsEqual(cext,".png"))
    {

        Image img = LoadImage(pfile);;
        if(img.width<=32 && img.height==1)
        {
            strcpy(pal.name,GetFileNameWithoutExt(pfile));
            for(int i=0;i<img.width;i++)
            {
                Color col = GetImageColor(img,i,0);
                pal.data[i]=col;
            }
        }
        UnloadImage(img);
    }
    return pal;
}

Color Palette_Get(struct Palette pal, int id)
{
    if(id<0 || id>EGBA_MAX_COLOR_PALETTE) return WHITE;
    return pal.data[id];
}
void Palette_Copy(struct Palette* dest,struct Palette sou)
{
	*dest = sou;
}
const char *Palette_GetName(struct Palette pal)
{
    return TextFormat("%s",pal.name);
}

Image Palette_GetImg(struct Palette pal)
{
    Image img = GenImageColor(32,1,BLACK);
    for(int i=0;i<EGBA_MAX_COLOR_PALETTE;i++)
    {
        ImageDrawPixel(&img,i,0,pal.data[i]);
    }
    return img;
}

//--------- sprite --------

struct Sprite Sprite()
{
	struct Sprite spr={16,16};
	for(int i=0;i<spr.width*spr.height;i++)
	{
		spr.data[i]=BLACK;
	}
	return spr;
}
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col)
{
    spr->data[(y*spr->width)+x]=col;
}

Image Sprite_GetImg(struct Sprite spr)
{
    Image img = GenImageColor(spr.width,spr.height,BLACK);
    for(int i=0;i<spr.width*spr.height;i++)
	{
        ImageDrawPixel(&img,i%spr.width,i/spr.width,spr.data[i]);
	}
    return img;
}

//----- atlas  ------------


void Atlas_Init()
{
    Image img = GenImageColor(32,5,BLACK);
    Editor_atlas.palettes = LoadTextureFromImage(img);
    UnloadImage(img);

    img = GenImageColor(256,256,BLACK);
    Editor_atlas.sprites = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Atlas_DrawPalette(int id, int x, int y, int scale)
{
    if(id>-1 && id<6)
    {
        DrawRectangleLines(x-2,y-2,(32*scale)+4,scale+4,UICONFIG_COL2());
        DrawTexturePro(Editor_atlas.palettes,(Rectangle){0,id,32,1},(Rectangle){x,y,32*scale,scale},(Vector2){0,0},0,WHITE);
    }

}
void Atlas_UpdatePalette(struct Palette* palettes)
{
    Image img = GenImageColor(32,5,BLACK);
    Image palimg;
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
    {
        palimg = Palette_GetImg(palettes[i]);
        ImageDraw(&img,palimg,(Rectangle){0,0,32,1},(Rectangle){0,i,32,1},WHITE);
    }
    UpdateTexture(Editor_atlas.palettes,img.data);
    UnloadImage(palimg);
    UnloadImage(img);
}
void Atlas_DrawSprite(int id,int x,int y,int scale)
{
    DrawTexturePro(Editor_atlas.sprites,
        (Rectangle){(id%16)*16,(id/16)*16,16,16},
        (Rectangle){x,y,16*scale,16*scale},(Vector2){0,0},0,WHITE);
}
void Atlas_UpdateSprite(struct Sprite* sprites)
{
    Image img = GenImageColor(256,256,(Color){0,0,0,0});
    for(int i=0;i<EGBA_MAX_SPRITE;i++)
    {
        Image imgspr = Sprite_GetImg(sprites[i]);
        ImageDraw(&img,imgspr,
            (Rectangle){0,0,16,16},
            (Rectangle){(i%16)*16,(i/16)*16,16,16},
            WHITE
        );
        UnloadImage(imgspr);
    }
    UpdateTexture(Editor_atlas.sprites,img.data);
    UnloadImage(img);
}

void Atlas_Free()
{
    UnloadTexture(Editor_atlas.palettes);
    UnloadTexture(Editor_atlas.sprites);
}


void UI_Palette_Init(struct segba_data* data)
{
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
        strcpy(data->palettes[i].name,"");
    data->palette_nb=0;
}
void UI_palette_LoadF(struct segba_data* data, const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        Image img = LoadImage(pfile);
        if(img.width>0 && img.width<=32 && img.height==1)
        {
            if(data->palette_nb<EGBA_MAX_PALETTE)
            {
                    data->palettes[data->palette_nb] = PaletteF(pfile);
                    Atlas_UpdatePalette(data->palettes);
                    data->palette_nb+=1;
            }
        }
        // else if(img.width==256 && img.height==256)
        // {
        //     struct Palette pal = {{0},{BLACK}};
        //     pal.data[0]=UICONFIG_COL1();
        //     pal.data[1]=UICONFIG_COL2();
        //     data->palettes[0]=pal;
        //     data->palette_nb=0;
        //     Atlas_UpdatePalette(data->palettes);
        // }
        else if(img.width==256 && img.height==257)
        {
            for(int i=0;i<160;i++)
            {
                strcpy(data->palettes[i/32].name,TextFormat("%d",i/32));
                Color col = GetImageColor(img,i,256);
                data->palettes[i/32].data[i%32]=col;//i-((i/32)*32)]=col;
            }
            Atlas_UpdatePalette(data->palettes);
            data->palette_nb=5;
        }
        UnloadImage(img);
    }
}
void UI_Palette_LoadD(struct segba_data* ddata,struct segba_data sdata)
{
    for(int j=0;j<EGBA_MAX_PALETTE;j++)
    {
        strcpy(ddata->palettes[j].name,
        sdata.palettes[j].name);
        for(int i=0;i<EGBA_MAX_PALETTE;i++)
        {
            ddata->palettes[j].data[i] = sdata.palettes[j].data[i];
        }
    }
    Atlas_UpdatePalette(ddata->palettes);
    ddata->palette_nb=5;
}
void UI_Palette_Save(struct segba_data* sdata)
{
    // for(int i=0;i<EGBA_MAX_PALETTE;i++)
    // {
    //     strcpy(sdata->palette_name[i],
    //     UI_Palette.palettes[i].name);
    //     for(int j=0;j<EGBA_MAX_COLOR_PALETTE;j++)
    //     {
    //         sdata->palette_data[(i*EGBA_MAX_COLOR_PALETTE)+j] = UI_Palette.palettes[i].data[j];
    //     }
    // }
}
struct Palette UI_Palette_Get(struct segba_data data,int id)
{
    return data.palettes[id];
}
void UI_Palette_DelPal(struct segba_data* data, int id)
{
    if(id==data->palette_nb)
    {
        data->palette_nb-=1;
    }
    else if(id<data->palette_nb)
    {
        for(int i=id;i<data->palette_nb;i++)
        {
            Palette_Copy(&data->palettes[i],data->palettes[i+1]);
        }
        Atlas_UpdatePalette(data->palettes);
        data->palette_nb-=1;
    }
}
int UI_Palette_Draw(struct segba_data* data, int px,int py,int pscale)
{
    int ret=-1;
    const int yborder = 30;
    // UI button,scroll
    int nbpalette=data->palette_nb;

    if(nbpalette>0)
    {
        for(int j=0;j<nbpalette;j++)
        {
			Atlas_DrawPalette(j,px+23,py+yborder+23+(j*45),pscale);
			DrawText(data->palettes[j].name,px+5,py+yborder+(j*45)+5,10,UICONFIG_COL2());
			if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){px+23,py+(float)yborder+23+(j*45),32*pscale,pscale}))
			{
				if(UIBUTTON((pscale-1)*32,py+yborder+21+(j*45)+2,"delete",pscale+4,UICONFIG_COL2()))
				{
				   UI_Palette_DelPal(data,j);
				}
			}
        }
    }
    else
    {
        DrawText("Drop palette image file here",px+23,py+100,pscale+5,UICONFIG_COL2());
    }
    return ret;
}

struct UI_BUTTONSPRITE
{
    int x;
    int y;
    int scale;
    int id_sprite;
    bool visible;
};

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

Texture2D UISprite_sprfond;

void UI_Sprite_GenSprFont()
{
    Image itrangle = GenTriangle(26,UICONFIG_COL2());
    Image img = GenImageColor(26*16,26*16,UICONFIG_COL1());
    for(int i=0;i<16;i++)
    for(int j=0;j<16;j++)
    {
        ImageDraw(&img,itrangle,(Rectangle){0,0,26,26},(Rectangle){i*26,j*26,26,26},WHITE);
    }
    UpdateTexture(UISprite_sprfond,img.data);
    UnloadImage(itrangle);
    UnloadImage(img);
}

int UISprite_curantsprite=0;
struct UI_BUTTONSPRITE UISprite_btnspr[EGBA_MAX_SPRITE];
const int UISprite_btnspr_size = 2;
const int UISprite_btncol_size = 26;
void UI_Sprite_Init(struct segba_data* data)
{
    //struct UI_Sprite uispr;
	//UI_Sprite.slidepalette = UI_SLIDEBAR_V(420,460,10,50,5);
    const int size = 16;

    for(int y=0;y<size;y++)
    for(int x=0;x<size;x++)
    {
        data->sprites[(size*y)+x] = Sprite();
        UISprite_btnspr[(size*y)+x] = UI_BUTTONSPRITE(440+(x*UISprite_btnspr_size*16),
                                                    30+(y*UISprite_btnspr_size*16),
                                                    UISprite_btnspr_size,
                                                    (size*y)+x);
    }
    // fond spr
    UISprite_sprfond = LoadTextureFromImage(GenImageColor(26*16,26*16,UICONFIG_COL1()));
    UI_Sprite_GenSprFont();
}

struct Sprite UI_sprite_Get(struct segba_data data,int id)
{
    return data.sprites[id];
}

void UI_Sprite_LoadD(struct segba_data* ddata,struct segba_data sdata)
{
    // for(int i=0;i<EGBA_MAX_SPRITE;i++)
    // for(int j=0;j<EGBA_MAX_COLOR_SPRITE;j++)
    // {
    //     int mapid = sdata.sprite_mapid[i][j];
    //     if(mapid<0)
    //         UI_Sprite.sprites[i].data[j] = (Color){0,0,0,0};
    //     else
    //         UI_Sprite.sprites[i].data[j] =  sdata.palette_data[mapid];
    // }
    for(int i=0;i<EGBA_MAX_SPRITE;i++)
    {
        ddata->sprites[i] = sdata.sprites[i];
    }
    Atlas_UpdateSprite(ddata->sprites);
}

void UI_sprite_LoadF(struct segba_data* data, const char *pfile)
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
            data->sprites[(i*16)+j].data[col] = img_col[col];
            UnloadImage(img);
        }
        Atlas_UpdateSprite(data->sprites);

    }
    UnloadImage(fullimg);
}

void UI_Sprite_Save(struct segba_data *sdata)
{
    // for(int i=0;i<EGBA_MAX_SPRITE;i++)
    // for(int j=0;j<EGBA_MAX_COLOR_SPRITE;j++)
    // {
    //     sdata->sprite_mapid[i][j]=-1;
    //     for(int i2=0;i2<EGBA_MAX_PALETTE;i2++)
    //     for(int j2=0;j2<EGBA_MAX_COLOR_PALETTE;j2++)
    //     {
    //         int icolpal = ColorToInt(UI_Palette.palettes[i2].data[j2]);
    //         int icolspr = ColorToInt(UI_Sprite.sprites[i].data[j]);
    //         if(icolpal==icolspr)
    //         {
    //
    //             sdata->sprite_mapid[i][j] = (i2*EGBA_MAX_COLOR_PALETTE)+j2;
    //             break;
    //             break;
    //         }
    //     }
    // }
}

int UI_Sprite_Draw()
{
    int ret=0;
    DrawTexture(UISprite_sprfond,2,30,WHITE);
    DrawRectangleLines(440,30,16*2*16,16*2*16,UICONFIG_COL2());
    for(int y=0;y<16;y++)
    for(int x=0;x<16;x++)
    {
        int id = (16*y)+x;
        if(UI_BUTTONSPRITE_Draw(UISprite_btnspr[id]))
        {
			UISprite_curantsprite=id;
        }
    }
    Atlas_DrawSprite(UISprite_curantsprite,2,30,UISprite_btncol_size);
    return ret;
}

void UI_Sprite_Free()
{
    UnloadTexture(UISprite_sprfond);
}


void UI_Script_LoadF(struct segba_data* data, const char* pfile)
{
    FILE* fic = fopen(pfile,"r");
    if(fic!=NULL)
    {
        fseek(fic,SEEK_END,0);
        long pos = ftell(fic);
        fseek(fic,SEEK_SET,0);
        int p=0;
        strcpy(data->script,"\0");
        if(pos<EGBA_MAX_SCRIPTSIZE)
        {
            do
            {
                fscanf(fic,"%c",&data->script[p]);
                p++;
            }
            while(feof(fic)==0);
        }
        //strcpy(UI_Script.source_script,".lua");
        fclose(fic);
    }
}

void UI_Script_LoadD(struct segba_data* ddata,struct segba_data sdata)
{
    //strcpy(UI_Script.source_script,".dat");
    strcpy(ddata->script,sdata.script);
}

// void UI_Script_Save(struct sdata *sdata)
// {
//     strcpy(sdata->script,UI_Script.script);
// }

void UI_Script_Draw(struct segba_data data)
{
    DrawText(data.script,15,30,18,UICONFIG_COL2());
}

void UICONFIG_SetActive(char c)
{
    if(_UICONFIG.timer<=0)
    {
        _UICONFIG.isactive=c;
        _UICONFIG.timer=0.001f;
    }
}

void UICONFIG_SetYellowTheme()
{
    _UICONFIG.config.color1=(Color){130,145,2};
    _UICONFIG.config.color2=YELLOW;
}

void UICONFIG_SetGreenTheme()
{
    _UICONFIG.config.color1=(Color){2,145,2};
    _UICONFIG.config.color2=GREEN;
}

void UICONFIG_SetRedTheme()
{
    _UICONFIG.config.color1=(Color){145,2,2};
    _UICONFIG.config.color2=RED;
}
void UICONFIG_SetBlueTheme()
{
    _UICONFIG.config.color1=(Color){2,2,175};
    _UICONFIG.config.color2=BLUE;
}

void UICONFIG_SetWhiteTheme()
{
    _UICONFIG.config.color1=WHITE;
    _UICONFIG.config.color2=LIGHTGRAY;
}

void UICONFIG_SetBlackTheme()
{
    _UICONFIG.config.color1=BLACK;
    _UICONFIG.config.color2=DARKGRAY;
}

void UICONFIG_Save()
{
    FILE* fic = fopen(".egba.conf","wb");
    fwrite(&_UICONFIG.config,sizeof(struct sconfig),1,fic);
    fclose(fic);
    UI_Sprite_GenSprFont();
}

void UICONFIG_Load()
{
    FILE* fic = fopen(".egba.conf","rb");
    if(fic!=NULL)
    {
        fread(&_UICONFIG.config,sizeof(struct sconfig),1,fic);
        fclose(fic);
    }
}

void UICONFIG_Init()
{
    UICONFIG_SetWhiteTheme();
    UICONFIG_Load();
}

void UICONFIG_Draw(int x,int y)
{
    if(_UICONFIG.isactive==1)
    {
		DrawText("Setting",23,5,25,UICONFIG_COL2());
		DrawRectangleLines(4,31,951,682,UICONFIG_COL2());
        DrawText("theme :",x+3,y+35,20,UICONFIG_COL2());
        if(UIBUTTON(x+78,y+35,"white",20,WHITE))
        {
            UICONFIG_SetWhiteTheme();
            UICONFIG_Save();
        }
        if(UIBUTTON(x+148,y+35,"black",20,DARKGRAY))
        {
            UICONFIG_SetBlackTheme();
            UICONFIG_Save();
        }

        if(UIBUTTON(x+218,y+35,"blue",20,BLUE))
        {
            UICONFIG_SetBlueTheme();
            UICONFIG_Save();
        }

        if(UIBUTTON(x+278,y+35,"red",20,RED))
        {
            UICONFIG_SetRedTheme();
            UICONFIG_Save();
        }

        if(UIBUTTON(x+328,y+35,"green",20,GREEN))
        {
            UICONFIG_SetGreenTheme();
            UICONFIG_Save();
        }

        if(UIBUTTON(x+408,y+35,"yellow",20,YELLOW))
        {
            UICONFIG_SetYellowTheme();
            UICONFIG_Save();
        }
    }

    if(_UICONFIG.timer>0)
        _UICONFIG.timer -= GetFrameTime();
}

struct sproject
{
	char name[50];
	char islua;
	char isegba;
	char ispng;
};
typedef struct sproject Project;

#define PROJECT_GetFileLua(spjt) (TextFormat("%s.lua",spjt.name))
#define PROJECT_GetFilePng(spjt) (TextFormat("%s.png",spjt.name))
#define PROJECT_GetFileEgba(spjt) (TextFormat("%s.egba",spjt.name))

void PROJECT_LoadSprite(Project ppjt)
{
	UI_palette_LoadF(&Editor_data, PROJECT_GetFilePng(ppjt));
    UI_sprite_LoadF(&Editor_data, PROJECT_GetFilePng(ppjt));
}

void PROJECT_LoadScript(Project ppjt)
{
	UI_Script_LoadF(&Editor_data, PROJECT_GetFileLua(ppjt));
}

char PROJECT_LoadEgba(Project ppjt)
{
	struct segba_data lsdata;
	FILE* fic = fopen(PROJECT_GetFileEgba(ppjt),"rb");
	fread(&lsdata,sizeof(struct segba_data),1,fic);
	fclose(fic);
	UI_Palette_LoadD(&Editor_data,lsdata);
	UI_Sprite_LoadD(&Editor_data,lsdata);
	UI_Script_LoadD(&Editor_data,lsdata);
    return lsdata.islock;
}

void PROJECT_BuildEgba(Project ppjt,char islock)
{
	// struct segba_data lsdata={0};
 //    lsdata.islock = islock;
	// UI_Palette_Save(&lsdata);
	// UI_Sprite_Save(&lsdata);
	// strcpy(lsdata.script,Editor_data.script);
	FILE* fic = fopen(PROJECT_GetFileEgba(ppjt),"wb");
	fwrite(&Editor_data,sizeof(struct segba_data),1,fic);
	fclose(fic);
}

void PROJECT_BuildExec(Project ppjt)
{
	char names[2][3][50];
	strcpy(names[0][0],EGBA_RUN_NAME);
	strcpy(names[0][1],PROJECT_GetFileEgba(ppjt));
	strcpy(names[0][2],ppjt.name);

	strcpy(names[1][0],EGBA_RUN_NAME);
    strcat(names[1][0],".exe");
	strcpy(names[1][1],PROJECT_GetFileEgba(ppjt));
	strcpy(names[1][2],TextFormat("%s.exe",ppjt.name));

	for(int i=0;i<2;i++)
	{
		const char* out = names[i][2];
		const char* exec = names[i][0];
		const char* cart = names[i][1];

		if(FileExists(exec) && FileExists(cart))
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
}

void PROJECT_ExportSprite(Project ppjt)
{
    if(Editor_data.palette_nb>0)
    {
        Image fullimg = GenImageColor(256,257,(Color){0,0,0,0});
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(Editor_data.sprites[(y*16)+x]);
            Rectangle rso = {0,0,16,16};
            Rectangle rde = {x*16,y*16,16,16};
            ImageDraw(&fullimg,img,rso,rde,WHITE);
            UnloadImage(img);
        }
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<32;j++)
            {
                ImageDrawPixel(&fullimg,(i*32)+j,256,Palette_Get(Editor_data.palettes[i],j));
            }
        }
        ExportImage(fullimg,PROJECT_GetFilePng(ppjt));
        UnloadImage(fullimg);
    }
    else
    {
        Image fullimg = GenImageColor(256,256,(Color){0,0,0,0});
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(Editor_data.sprites[(y*16)+x]);
            Rectangle rso = {0,0,16,16};
            Rectangle rde = {x*16,y*16,16,16};
            ImageDraw(&fullimg,img,rso,rde,WHITE);
            UnloadImage(img);
        }
        ExportImage(fullimg,PROJECT_GetFilePng(ppjt));
        UnloadImage(fullimg);
    }

}

void PROJECT_ExportScript(Project ppjt)
{
    FILE* fic = fopen(PROJECT_GetFileLua(ppjt),"w");
    fprintf(fic,"%s",Editor_data.script);
    fclose(fic);
}
char PROJECT_DebugInit(Project ppjt)
{
    const char* lfile = PROJECT_GetFileLua(ppjt);
    if(FileExists(lfile))
    {
		// UI_Runner();
		// uirun.isdebug=1;
		// CLUA_dofile(&uirun.clua,lfile);
#ifdef WIN32
        system(TextFormat("%s.exe %s",EGBA_RUN_NAME, lfile));
#endif
#ifdef __linux
        system(TextFormat("./%s %s",EGBA_RUN_NAME, lfile));
#endif
        return 1;
    }
    return 0;
}

char PROJECT_RunInit(Project ppjt)
{
    const char* lfile = PROJECT_GetFileEgba(ppjt);
    if(FileExists(lfile))
    {
		// uirun.isdebug=0;
  //       UI_Runner_Load(lfile);
#ifdef WIN32
        system(TextFormat("%s.exe %s",EGBA_RUN_NAME, lfile));
#endif
#ifdef __linux
        system(TextFormat("./%s %s",EGBA_RUN_NAME, lfile));
#endif
        return 1;
    }
    return 0;
}
Project PROJECT_Init(const char* pname)
{
	Project spjt = {0};
	TextCopy(spjt.name,pname);

	if(FileExists(PROJECT_GetFileLua(spjt)))
	{
		spjt.islua=1;
	}
	if(FileExists(PROJECT_GetFilePng(spjt)))
	{
		spjt.ispng=1;
	}
	if(FileExists(PROJECT_GetFileEgba(spjt)))
	{
		spjt.isegba=1;
	}
	return spjt;
}

#define BROWSER_PROJECT_MAX_H 24
struct sbrowser
{
	Project list[EGBA_MAX_PROJECT];
	int project_nb;
	float timer;

};
typedef struct sbrowser Browser;
Browser _BROWSER;
//browser project add/del

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
	if(_BROWSER.project_nb<EGBA_MAX_PROJECT)
	{
		char tmp_name[100];
		int tmp_i = 0;
		strcpy(tmp_name,name);
		while(BROWSER_IfProjectExist(tmp_name))
		{
			++tmp_i;
			strcpy(tmp_name,TextFormat("%s%d",name,tmp_i));
		}

		Image img = GenImageColor(256,256,BLACK);
		ExportImage(img,TextFormat("%s.png",tmp_name));
		UnloadImage(img);

        FILE* fic = fopen(TextFormat("%s.lua",tmp_name),"w");
        fprintf(fic,
        "function EGBA()\n-- code run 60/seconds\ncls(0)\ntext(%chello world%c,100,50,1,20)\nend",'"','"');
        fclose(fic);
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


int BROWSER_Draw()
{
	int ri=-1;
    int offsety = 40;
	DrawText("Project browser",23,5,25,UICONFIG_COL2());
    DrawRectangleLines(5,33,950,680,UICONFIG_COL2());
    for(int i=0;i<_BROWSER.project_nb;i++)
    {
		if(UIBUTTON(
		((i/BROWSER_PROJECT_MAX_H)*200)+23+16,
		offsety+((i%BROWSER_PROJECT_MAX_H)*28),
		_BROWSER.list[i].name,
		18,UICONFIG_COL2())
		)
		{
			ri=i;
		}
		//del button
		if(UIBUTTON(
		((i/BROWSER_PROJECT_MAX_H)*200)+13,
		offsety+((i%BROWSER_PROJECT_MAX_H)*28),
		"-",
		20,UICONFIG_COL2())
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
	if(_BROWSER.project_nb<EGBA_MAX_PROJECT)
	{
		if(UIBUTTON(
			(((_BROWSER.project_nb)/BROWSER_PROJECT_MAX_H)*200)+13,
			offsety+(((_BROWSER.project_nb)%BROWSER_PROJECT_MAX_H)*28),
			"+",
			20,UICONFIG_COL2()))
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
	UIPROJECT_STATE_VRUNNER
};

struct suiproject
{
	int id;
	enum UIPROJECT_STATE state;
	char isactive;
    float timer;
    // texture img ui
    Texture spr;
    Texture lua;
    Texture egba;
    char islock;
}_UIPROJECT;


void UIPROJECT_LoadIcons()
{
	_UIPROJECT.spr = LoadTextureFromImage(spr);
    _UIPROJECT.lua = LoadTextureFromImage(lua);
    _UIPROJECT.egba = LoadTextureFromImage(egba);
}
void UIPROJECT_Init(int idproject)
{
	_UIPROJECT.id=idproject;
	_UIPROJECT.isactive=1;
    _UIPROJECT.timer = 0.001f;
	Project pjt = _BROWSER.list[idproject];
	if(pjt.islua)
	{
		PROJECT_LoadScript(pjt);
	}
	if(pjt.ispng)
	{
		PROJECT_LoadSprite(pjt);
	}
	if(pjt.isegba)
		_UIPROJECT.islock = PROJECT_LoadEgba(pjt);

}
void UIPROJECT_Update()
{
    BROWSER_Scan();
    UIPROJECT_Init(_UIPROJECT.id);
}

void UIPROJECT_DrawInfo()
{
    DrawText("[space] for start/end debug script",10,300,20,UICONFIG_COL2());
    DrawText("[enter] for start/end run egba",10,330,20,UICONFIG_COL2());
    DrawText("[ctrl]+[i] import sprite/script from egba",10,360,20,UICONFIG_COL2());
    DrawText("[ctrl]+[e] export sprite/script to egba",10,390,20,UICONFIG_COL2());
    DrawText("[ctrl]+[l] export sprite/script to lock egba",10,420,20,UICONFIG_COL2());
    DrawText("[ctrl]+[b] create binairy from egba",10,450,20,UICONFIG_COL2());
}

void UIPROJECT_Draw()
{
    if(_UIPROJECT.timer>0)
    {
        _UIPROJECT.timer -= GetFrameTime();
    }
	else if(_UIPROJECT.isactive)
	{
		Project lproject = _BROWSER.list[_UIPROJECT.id];

		switch(_UIPROJECT.state)
		{
			case UIPROJECT_STATE_DEFAULT:
                DrawRectangleLines(5,33,950,680,UICONFIG_COL2());
                DrawText(TextFormat("Project : %s",lproject.name),90,5,25,UICONFIG_COL2());
                UIPROJECT_DrawInfo();

                DrawRectangleLines(45,50,110,180,UICONFIG_COL2());
				if(UIBUTTON(5,5,"back",20,UICONFIG_COL2()))
				{
                    BROWSER_Scan();
					_UIPROJECT.isactive=0;
				}
				if(lproject.islua)
				{
                    if(UIBUTTONIMG(60,70,_UIPROJECT.lua))
					{
						_UIPROJECT.state=UIPROJECT_STATE_VSCRIPT;
                        PROJECT_LoadScript(lproject);
					}
				}
				if(lproject.ispng)
				{
                    if(UIBUTTONIMG(60,140,_UIPROJECT.spr))
					{
						_UIPROJECT.state=UIPROJECT_STATE_VSPRITE;
                        PROJECT_LoadSprite(lproject);
					}
				}

				if(lproject.islua && lproject.ispng)
				{
					if(IsKeyPressed(KEY_SPACE))
					{
                        puts("[EGBA][DEBUG INIT]");
						if(!PROJECT_DebugInit(lproject))
                            printf("\n[EGBA] : error %s not found\n",PROJECT_GetFileLua(lproject));
					}

					if(UIBUTTON(170,90," -> ",20,UICONFIG_COL2()) ||
                        (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_E))
                    )
					{
                        puts("[EGBA] : sprite/script -> egba ...");
						PROJECT_BuildEgba(lproject,0);
                        puts("[EGBA] : done");
                        UIPROJECT_Update();
					}

					if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_L))
                    {
                        puts("[EGBA] : sprite/script -> lock egba ...");
						PROJECT_BuildEgba(lproject,1);
                        puts("[EGBA] : done");
                        UIPROJECT_Update();
                    }
				}

				DrawRectangleLines(220,50,110,180,UICONFIG_COL2());
				if(lproject.isegba)
				{
                    if(UIBUTTONIMG(225,75,_UIPROJECT.egba))
					{

					}
					if(IsKeyPressed(KEY_ENTER))
					{
                        puts("[EGBA][RUNNER START]");
						if(!PROJECT_RunInit(lproject))
                            printf("\n[EGBA] : error %s not found\n",PROJECT_GetFileEgba(lproject));
					}

					if(UIBUTTON(350,90,"export bin",20,UICONFIG_COL2()) ||
                        (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B))
                    )
                    {
                        puts("[EGBA] : export bin ...");
                        PROJECT_BuildExec(lproject);
                        puts("[EGBA] : done");
                    }

                    if(_UIPROJECT.islock==0)
                    {
                        if(UIBUTTON(170,150," <- ",20,UICONFIG_COL2()) ||
                            (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_I)))
                        {
                            puts("[EGBA] : import script/sprite ...");
                            PROJECT_ExportScript(lproject);
                            PROJECT_ExportSprite(lproject);
                            UIPROJECT_Update();
                            puts("[EGBA] : done");

                        }
                    }
                    else
                        DrawText("lock",165,150,20,UICONFIG_COL2());

				}

			break;
			case UIPROJECT_STATE_VSPRITE:
				if(UIBUTTON(5,5,"back",20,UICONFIG_COL2()))
				{
					_UIPROJECT.state=UIPROJECT_STATE_DEFAULT;
				}
				if(((IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL)) &&
                    IsKeyPressed(KEY_S)) ||
                    UIBUTTON(70,5,"save",20,UICONFIG_COL2()))
                {
                    puts("[EGBA] : saving sprite ...");
                    PROJECT_ExportSprite(lproject);
                    puts("[EGBA] : done");
                }
				if(IsFileDropped())
                {
                    FilePathList files = LoadDroppedFiles();
                    for(int i=0;i<files.count;i++)
                    {
                        printf("\n[EGBA] : load sprite %s ...\n",files.paths[i]);
                        UI_palette_LoadF(&Editor_data,files.paths[i]);
                        UI_sprite_LoadF(&Editor_data,files.paths[i]);
                        puts("[EGBA] : done");
                    }
                    UnloadDroppedFiles(files);
                }
                UI_Sprite_Draw();
				UI_Palette_Draw(&Editor_data,0,430,12);
			break;
			case UIPROJECT_STATE_VSCRIPT:
				if(UIBUTTON(5,5,"back",20,UICONFIG_COL2()))
				{
					_UIPROJECT.state=UIPROJECT_STATE_DEFAULT;
				}
				UI_Script_Draw(Editor_data);
			break;
			// case UIPROJECT_STATE_VRUNNER:
			// 	// UI_Runner_Draw();
			// 	// if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
			// 	// {
			// 	// 	_UIPROJECT.state = UIPROJECT_STATE_DEFAULT;
   //  //                 puts("[EGBA][DEBUG/RUN END]");
			// 	// }
			// break;
			default:;
		};
	}
}

void UIPROJECT_Free()
{
	UnloadTexture(_UIPROJECT.lua);
	UnloadTexture(_UIPROJECT.spr);
	UnloadTexture(_UIPROJECT.egba);
}




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

    //init
    Atlas_Init();
    UICONFIG_Init();
    UI_Palette_Init(&Editor_data);
    UI_Sprite_Init(&Editor_data);
    Editor_data.script[0]='\0';
    UIPROJECT_LoadIcons();
    BROWSER_Init();
    int browser_state=-1;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(UICONFIG_COL1());

        if(_UIPROJECT.isactive==0)
        {

            if(UIBUTTON(900,5,"doc",20,UICONFIG_COL2()))
            {
                OpenURL("https://oblerion.itch.io/gba-engine");
            }

            if(_UICONFIG.isactive==0)
            {
                if(UIBUTTON(800,5,"setting",20,UICONFIG_COL2()))
                {
                    UICONFIG_SetActive(1);
                }
                browser_state = BROWSER_Draw();
                if(browser_state>-1)
                {
                    UIPROJECT_Init(browser_state);
                }
            }
            else if(UIBUTTON(800,5,"browser",20,UICONFIG_COL2()))
            {
                //_UICONFIG.isactive = 0;
                UICONFIG_SetActive(0);
            }
            UICONFIG_Draw(5,5);
        }
        UIPROJECT_Draw();

        EndDrawing();
    }

    // free editor
    UI_Sprite_Free();
    UIPROJECT_Free();
    Atlas_Free();

    CloseWindow();        // Close window and OpenGL
    return 0;
}
