#include "EGBA.h"
#include <stdio.h>
#include <stdlib.h>

struct segba_saving egba_saving;
struct segba_data egba_data;
struct segba_atlas egba_atlas;

struct sconfig
{
    // Color color1;
    // Color color2;
    int theme_nb;
};

struct suiconfig
{
    struct sconfig config;
    char isactive;
    float timer;
};

struct suiconfig _UICONFIG={0};

char UICONFIG_Timer()
{
    if(_UICONFIG.isactive==1)
    {
        return 1;
    }

    if(_UICONFIG.timer>0)
    _UICONFIG.timer -= GetFrameTime();
    return 0;
}
// Color UICONFIG_COL1()
// {
//     return _UICONFIG.config.color1;
// }
// Color UICONFIG_COL2()
// {
//     return _UICONFIG.config.color2;
// }

char UICONFIG_GetActive()
{
    return _UICONFIG.isactive;
}
void UICONFIG_SetActive(char c)
{
    // if(_UICONFIG.timer<=0)
    // {
        _UICONFIG.isactive=c;
        _UICONFIG.timer=0.001f;
    // }
}
int UICONFIG_GetTheme()
{
    return _UICONFIG.config.theme_nb;
}
void UICONFIG_SetTheme(int itheme)
{
    _UICONFIG.config.theme_nb=itheme;
}
/*
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
}*/

void UICONFIG_Save()
{
    FILE* fic = fopen(".egba.conf","wb");
    fwrite(&_UICONFIG.config,sizeof(struct sconfig),1,fic);
    fclose(fic);
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

Image Palette_GetImg(struct Palette pal)
{
    Image img = GenImageColor(32,1,BLACK);
    for(int i=0;i<EGBA_MAX_COLOR_PALETTE;i++)
    {
        ImageDrawPixel(&img,i,0,pal.data[i]);
    }
    return img;
}


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

struct segba_saving Saving_Get()
{
    return egba_saving;
}

void Saving_Set(struct segba_saving saving)
{
    egba_saving = saving;
}

void Saving_LoadSave(const char* name)
{
    // struct segba_saving ssave={0};
    const char* ext = GetFileExtension(name);
    const char* lname =
    GetFileNameWithoutExt(name);

    if(TextIsEqual(ext,".lua") ||
        TextIsEqual(ext,".egba")
    )
    {
        FILE* fic= fopen(TextFormat("%s.sav",lname),"rb");
        if(fic!=NULL)
        {
            fread(&egba_saving,sizeof(struct segba_saving),1,fic);
            fclose(fic);
        }
    }
}
void Saving_WriteSave(const char* name,struct segba_saving saving)
{
    const char* ext = GetFileExtension(name);
    const char* lname =
    GetFileNameWithoutExt(name);

    if(TextIsEqual(ext,".lua") ||
        TextIsEqual(ext,".egba")
    )
    {
        egba_saving = saving;
        FILE* fic= fopen(TextFormat("%s.sav",lname),"wb");
        if(fic!=NULL)
        {
            fwrite(&saving,sizeof(struct segba_saving),1,fic);
            fclose(fic);
        }
    }
}

void Data_Palette_Init()
{
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
        strcpy(egba_data.palettes[i].name,"");
    egba_data.palette_nb=0;
}

void Data_Palette_LoadF(const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        Image img = LoadImage(pfile);
        if(img.width>=16 && img.width<33 && img.height==1)
        {
            Color* lcol = LoadImageColors(img);
            for(int i=0;i<32;i++)
            {
                if(i<img.width)
                {
                    egba_data.palettes[egba_data.palette_nb].data[i]=lcol[i];
                }
                else
                {
                    egba_data.palettes[egba_data.palette_nb].data[i]=(Color){0,0,0,0};
                }

            }
            UnloadImageColors(lcol);
            egba_data.palette_nb+=1;
            Atlas_UpdatePalette(egba_data.palettes);
        }
        else if(img.width==256 && img.height==257)
        {
            for(int i=0;i<EGBA_MAX_PALETTE;i++)
            for(int j=0;j<EGBA_MAX_COLOR_PALETTE;j++)
            {
                //strcpy(data->palettes[i].name,TextFormat("%d",i));
                Color col = GetImageColor(img,i*32+j,256);
                egba_data.palettes[i].data[j]=col;
            }
            Atlas_UpdatePalette(egba_data.palettes);
            egba_data.palette_nb=5;
        }
        else if(img.width==256 && img.height==256)
        {
            struct Palette pal = {{0},{BLACK}};
            UICONFIG_Load();
            pal.data[0]=WHITE;
            pal.data[1]=BLACK;
            egba_data.palettes[0]=pal;
            egba_data.palette_nb=0;
            Atlas_UpdatePalette(egba_data.palettes);
        }
        UnloadImage(img);
    }
}

void Data_Palette_LoadD(struct segba_data sdata)
{
    for(int j=0;j<EGBA_MAX_PALETTE;j++)
    {
        strcpy(egba_data.palettes[j].name,
        sdata.palettes[j].name);
        for(int i=0;i<EGBA_MAX_COLOR_PALETTE;i++)
        {
            egba_data.palettes[j].data[i] = sdata.palettes[j].data[i];
        }
    }
    Atlas_UpdatePalette(egba_data.palettes);
    egba_data.palette_nb=5;
}


void Data_Palette_DelPal(int id)
{
    if(id==egba_data.palette_nb)
    {
        egba_data.palette_nb-=1;
    }
    else if(id<egba_data.palette_nb)
    {
        for(int i=id;i<egba_data.palette_nb;i++)
        {
            egba_data.palettes[i]=egba_data.palettes[i+1];
        }
        Atlas_UpdatePalette(egba_data.palettes);
        egba_data.palette_nb-=1;
    }
}

int Data_Palette_GetNd()
{
    return egba_data.palette_nb;
}

const char* Data_Palette_GetName(int n)
{
    return egba_data.palettes[n].name;
}

struct Palette Data_Palette_Get(int n)
{
    return egba_data.palettes[n];
}
void Data_Sprite_Init()
{
    int size=16;
    for(int y=0;y<size;y++)
    for(int x=0;x<size;x++)
    {
        egba_data.sprites[(size*y)+x] = Sprite();

    }
}
void Data_Sprite_LoadF(const char *pfile)
{
    Image fullimg = LoadImage(pfile);
    if(fullimg.width==256 && fullimg.height==257)
    {
        Image imgspr = ImageFromImage(fullimg,(Rectangle){0,0,256,256});
        Color* lcol = (Color*)imgspr.data;
        UpdateTexture(egba_atlas.sprites,lcol);
        UnloadImage(imgspr);

        for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
        {
            Image img = GenImageColor(16,16,(Color){0,0,0,0});
            ImageDraw(&img,fullimg,
                    (Rectangle){j*16,i*16,16,16},
                    (Rectangle){0,0,16,16},WHITE);

            Color* img_col = (Color*)img.data;
            for(int col=0;col<256;col++)
            egba_data.sprites[(i*16)+j].data[col] = img_col[col];
            UnloadImage(img);
        }
    }
    UnloadImage(fullimg);
}

void Data_Sprite_LoadD(struct segba_data sdata)
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
        egba_data.sprites[i] = sdata.sprites[i];
    }
    Atlas_UpdateSprite(egba_data.sprites);
}

struct Sprite Data_Sprite_Get(int id)
{
    return egba_data.sprites[id];
}

void Data_Script_Init()
{
    strcpy(egba_data.script,"");
    egba_data.script[0]='\0';
}

const char* Data_Script_Get()
{
    return TextFormat("%s",egba_data.script);
}

void Data_Script_LoadF(const char* pfile)
{
    FILE* fic = fopen(pfile,"r");
    if(fic!=NULL)
    {
        fseek(fic,SEEK_END,0);
        long pos = ftell(fic);
        fseek(fic,SEEK_SET,0);
        int p=0;
        strcpy(egba_data.script,"\0");
        if(pos<EGBA_MAX_SCRIPTSIZE)
        {
            do
            {
                fscanf(fic,"%c",&egba_data.script[p]);
                p++;
            }
            while(feof(fic)==0);
        }
        //strcpy(UI_Script.source_script,".lua");
        fclose(fic);
    }
}

void Data_Script_LoadD(struct segba_data sdata)
{
    //strcpy(UI_Script.source_script,".dat");
    strcpy(egba_data.script,sdata.script);
}

void Data_Script_Draw(int x,int y,Color color)
{
     DrawText(egba_data.script,x,y,18,color);
}

void Data_BuildEgba(const char* sfegba,char lock)
{
    // const char* luafile = TextFormat("%s.lua",GetFileNameWithoutExt(sfegba));
    // struct segba_saving save =  Saving_LoadSave(luafile);

    FILE* fic = fopen(sfegba,"wb");
    egba_data.islock=lock;
    // egba_data.saving=save;
	fwrite(&egba_data,sizeof(struct segba_data),1,fic);
	fclose(fic);
}

void Data_ExportSprite(const char* sfsprite)
{
    if(egba_data.palette_nb>0)
    {
        Image fullimg = GenImageColor(256,257,(Color){0,0,0,0});
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(egba_data.sprites[(y*16)+x]);
            Rectangle rso = {0,0,16,16};
            Rectangle rde = {x*16,y*16,16,16};
            ImageDraw(&fullimg,img,rso,rde,WHITE);
            UnloadImage(img);
        }
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<32;j++)
            {
                ImageDrawPixel(&fullimg,(i*32)+j,256,egba_data.palettes[i].data[j]);
            }
        }
        ExportImage(fullimg,sfsprite);
        UnloadImage(fullimg);
    }
    else
    {
        Image fullimg = GenImageColor(256,256,(Color){0,0,0,0});
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(egba_data.sprites[(y*16)+x]);
            Rectangle rso = {0,0,16,16};
            Rectangle rde = {x*16,y*16,16,16};
            ImageDraw(&fullimg,img,rso,rde,WHITE);
            UnloadImage(img);
        }
        ExportImage(fullimg,sfsprite);
        UnloadImage(fullimg);
    }
}

void Data_ExportScript(const char* sfscript)
{
    FILE* fic = fopen(sfscript,"w");
    fprintf(fic,"%s",egba_data.script);
    fclose(fic);
}

void Atlas_Init()
{
    Image img = GenImageColor(32,5,BLACK);
    egba_atlas.palettes = LoadTextureFromImage(img);
    UnloadImage(img);

    img = GenImageColor(256,256,BLACK);
    egba_atlas.sprites = LoadTextureFromImage(img);
    UnloadImage(img);
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
    UpdateTexture(egba_atlas.palettes,img.data);
    UnloadImage(palimg);
    UnloadImage(img);
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
    UpdateTexture(egba_atlas.sprites,img.data);
    UnloadImage(img);
}
#include "raygui.h"
Color _StyleGetColor(char idcol)
{
    int icol=0;
    if(idcol==0)
        icol = GuiGetStyle(0,1);
    else if(idcol==1)
        icol = GuiGetStyle(0,2);
    return GetColor(icol);
}
void Atlas_DrawPalette(int id, int x, int y, int scale)
{
    if(id>-1 && id<6)
    {
        DrawRectangleLines(x-2,y-2,(32*scale)+4,scale+4,_StyleGetColor(1));
        DrawTexturePro(egba_atlas.palettes,(Rectangle){0,id,32,1},(Rectangle){x,y,32*scale,scale},(Vector2){0,0},0,WHITE);
    }

}

void Atlas_DrawSprite(int id,int x,int y,int scale)
{
    DrawTexturePro(egba_atlas.sprites,
        (Rectangle){(id%16)*16,(id/16)*16,16,16},
        (Rectangle){x,y,16*scale,16*scale},(Vector2){0,0},0,WHITE);
}

void Atlas_Free()
{
    UnloadTexture(egba_atlas.palettes);
    UnloadTexture(egba_atlas.sprites);
}
