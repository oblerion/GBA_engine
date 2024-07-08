#include "main.h"

char _Saving_GetBool(struct ssaving svg,int pid)
{
    return svg.bools[pid];
}
void _Saving_SetBool(struct ssaving* svg,int pid,char pbool)
{
    svg->bools[pid]=pbool;
}

const char* _Saving_GetString(struct ssaving svg,int pid)
{
    return TextFormat("%s",svg.strs[pid]);
}
void _Saving_SetString(struct ssaving* svg,int pid,char* pstr)
{
    strcpy(svg->strs[pid],pstr);
}

int _Saving_GetNumber(struct ssaving svg,int pid)
{
    return svg.numbs[pid];
}
void _Saving_SetNumber(struct ssaving* svg,int pid,int pint)
{
    svg->numbs[pid]=pint;
}




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
    Image palimg;
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
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
    UpdateTexture(Atlas.sprites,img.data);
    UnloadImage(img);
}

void Atlas_Free()
{
    UnloadTexture(Atlas.palettes);
    UnloadTexture(Atlas.sprites);
}


//#include "ui_palette.h"

void UI_Palette_Init()
{
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
        strcpy(UI_Palette.palettes[i].name,"");
    UI_Palette.palette_nb=0;
}
void UI_palette_LoadF(const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        Image img = LoadImage(pfile);
        if(img.width>0 && img.width<=32 && img.height==1)
        {
            if(UI_Palette.palette_nb<EGBA_MAX_PALETTE)
            {
                  UI_Palette.palettes[UI_Palette.palette_nb] = PaletteF(pfile);
                    Atlas_UpdatePalette(UI_Palette.palettes);
                    UI_Palette.palette_nb+=1;
            }
        }
        else if(img.width==256 && img.height==256)
        {
            struct Palette pal = {{0},{BLACK}};
            pal.data[0]=UICONFIG_COL1();
            pal.data[1]=UICONFIG_COL2();
            UI_Palette.palettes[0]=pal;
            UI_Palette.palette_nb=0;
            Atlas_UpdatePalette(UI_Palette.palettes);
        }
        else if(img.width==256 && img.height==257)
        {
            for(int i=0;i<160;i++)
            {
                strcpy(UI_Palette.palettes[i/32].name,TextFormat("%d",i/32));
                Color col = GetImageColor(img,i,256);
                UI_Palette.palettes[i/32].data[i-((i/32)*32)]=col;
            }
            Atlas_UpdatePalette(UI_Palette.palettes);
            UI_Palette.palette_nb=5;
        }
        UnloadImage(img);
    }
}
void UI_Palette_LoadD(struct sdata sdata)
{
    for(int j=0;j<EGBA_MAX_PALETTE;j++)
    {
        strcpy(UI_Palette.palettes[j].name,
        sdata.palette_name[j]);
        for(int i=0;i<EGBA_MAX_PALETTE;i++)
        {
            UI_Palette.palettes[j].data[i] = sdata.palette_data[(j*EGBA_MAX_COLOR_PALETTE)+i];
        }
    }
    Atlas_UpdatePalette(UI_Palette.palettes);
    UI_Palette.palette_nb=5;
}
void UI_Palette_Save(struct sdata* sdata)
{
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
    {
        strcpy(sdata->palette_name[i],
        UI_Palette.palettes[i].name);
        for(int j=0;j<EGBA_MAX_COLOR_PALETTE;j++)
        {
            sdata->palette_data[(i*EGBA_MAX_COLOR_PALETTE)+j] = UI_Palette.palettes[i].data[j];
        }
    }
}
struct Palette UI_Palette_Get(int id)
{
    return UI_Palette.palettes[id];
}
void UI_Palette_DelPal(int id)
{
    if(id==UI_Palette.palette_nb)
    {
        UI_Palette.palette_nb-=1;
    }
    else if(id<UI_Palette.palette_nb)
    {
        for(int i=id;i<UI_Palette.palette_nb;i++)
        {
            Palette_Copy(&UI_Palette.palettes[i],UI_Palette.palettes[i+1]);
        }
        Atlas_UpdatePalette(UI_Palette.palettes);
        UI_Palette.palette_nb-=1;
    }
}
int UI_Palette_Draw(int px,int py,int pscale)
{
    int ret=-1;
    const int yborder = 30;
    // UI button,scroll
    int nbpalette=UI_Palette.palette_nb;

    if(nbpalette>0)
    {
        for(int j=0;j<nbpalette;j++)
        {
			Atlas_DrawPalette(j,px+23,py+yborder+23+(j*45),pscale);
			DrawText(UI_Palette.palettes[j].name,px+5,py+yborder+(j*45)+5,10,UICONFIG_COL2());
			if(CheckCollisionPointRec(GetMousePosition(), (Rectangle){px+23,py+(float)yborder+23+(j*45),32*pscale,pscale}))
			{
				if(UIBUTTON((pscale-1)*32,py+yborder+21+(j*45)+2,"delete",pscale+4,UICONFIG_COL2()))
				{
				   UI_Palette_DelPal(j);
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


//#include "ui_sprite.h"

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
void UI_Sprite_GenSprFont()
{
    Image itrangle = GenTriangle(26,UICONFIG_COL2());
    Image img = GenImageColor(26*16,26*16,UICONFIG_COL1());
    for(int i=0;i<16;i++)
    for(int j=0;j<16;j++)
    {
        ImageDraw(&img,itrangle,(Rectangle){0,0,26,26},(Rectangle){i*26,j*26,26,26},WHITE);
    }
    UpdateTexture(UI_Sprite.sprfond,img.data);
    UnloadImage(itrangle);
    UnloadImage(img);
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
    UI_Sprite.sprfond = LoadTextureFromImage(GenImageColor(26*16,26*16,UICONFIG_COL1()));
    UI_Sprite_GenSprFont();
}

struct Sprite UI_sprite_Get(int id)
{
    return UI_Sprite.sprites[id];
}

void UI_Sprite_LoadD(struct sdata sdata)
{
    for(int i=0;i<EGBA_MAX_SPRITE;i++)
    for(int j=0;j<EGBA_MAX_COLOR_SPRITE;j++)
    {
        int mapid = sdata.sprite_mapid[i][j];
        if(mapid<0)
            UI_Sprite.sprites[i].data[j] = (Color){0,0,0,0};
        else
            UI_Sprite.sprites[i].data[j] =  sdata.palette_data[mapid];
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
            UI_Sprite.sprites[(i*16)+j].data[col] = img_col[col];
            UnloadImage(img);
        }
        Atlas_UpdateSprite(UI_Sprite.sprites);
    }
    UnloadImage(fullimg);
}

void UI_Sprite_Save(struct sdata *sdata)
{
    for(int i=0;i<EGBA_MAX_SPRITE;i++)
    for(int j=0;j<EGBA_MAX_COLOR_SPRITE;j++)
    {
        sdata->sprite_mapid[i][j]=-1;
        for(int i2=0;i2<EGBA_MAX_PALETTE;i2++)
        for(int j2=0;j2<EGBA_MAX_COLOR_PALETTE;j2++)
        {
            int icolpal = ColorToInt(UI_Palette.palettes[i2].data[j2]);
            int icolspr = ColorToInt(UI_Sprite.sprites[i].data[j]);
            if(icolpal==icolspr)
            {

                sdata->sprite_mapid[i][j] = (i2*EGBA_MAX_COLOR_PALETTE)+j2;
                break;
                break;
            }
        }
    }
}

int UI_Sprite_Draw()
{
    int ret=0;
    DrawTexture(UI_Sprite.sprfond,2,30,WHITE);
    DrawRectangleLines(440,30,16*2*16,16*2*16,UICONFIG_COL2());
    for(int y=0;y<16;y++)
    for(int x=0;x<16;x++)
    {
        int id = (16*y)+x;
        if(UI_BUTTONSPRITE_Draw(UI_Sprite.btnspr[id]))
        {
			UI_Sprite.curant_spr=id;
        }
    }
    Atlas_DrawSprite(UI_Sprite.curant_spr,2,30,UI_Sprite.btncol_size);
    return ret;
}

void UI_Sprite_Free()
{
    UnloadTexture(UI_Sprite.sprfond);
}

//#include "ui_script.h"

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
        if(pos<EGBA_MAX_SCRIPTSIZE)
        {
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
    DrawText(UI_Script.script,15,30,18,UICONFIG_COL2());
}

//------------- runner -------------------
//#include "ui_runner.h"


int rlua_trace(clua_state* L)
{
	if(uirun.isdebug)
	{
		const char* pstr = lua_tostring(L,1);
		printf("[EGBA](TRACE)=>%s\n",pstr);
    }
    return 0;
}

int rlua_pal(clua_state* L)
{
    int id = lua_tointeger(L,1);
    if(id>-1 && id<EGBA_MAX_PALETTE) uirun.palette_id=id;
    return 0;
}

int rlua_cls(clua_state* L)
{
    int id = lua_tointeger(L,1);
    struct Palette pal = UI_Palette_Get(uirun.palette_id);
    Color col = pal.data[id];
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),col);
    return 0;
}

int rlua_drawtext(clua_state* L)
{
    // extern struct UI_Runner uirun;
    const char* cstr = lua_tostring(L,1);
    int x = lua_tonumber(L,2);
    int y = lua_tonumber(L,3);
 
    struct Palette pal = UI_Palette_Get(uirun.palette_id);
    Color col = pal.data[(int)lua_tonumber(L,4)];
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

int rlua_drawpix(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    struct Palette pal = UI_Palette_Get(uirun.palette_id);
    Color col = pal.data[(int)lua_tonumber(L,3)];
    DrawPixel(x,y,col);
    return 0;
}

int rlua_drawrect(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);
    struct Palette pal = UI_Palette_Get(uirun.palette_id);
    Color col = pal.data[(int)lua_tonumber(L,5)];
    DrawRectangle(x,y,w,h,col);
    return 0;
}

int rlua_drawrectb(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);
    struct Palette pal = UI_Palette_Get(uirun.palette_id);
    Color col = pal.data[(int)lua_tonumber(L,5)];
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
        case 4:
        if(IsKeyDown(KEY_X)){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        case 5:
        if(IsKeyDown(KEY_C)){
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
        case 4:
        if(IsKeyPressed(KEY_X)){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        case 5:
        if(IsKeyPressed(KEY_C)){
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
    _UI_Runner_functionpush(rlua_drawtext,"text");
    _UI_Runner_functionpush(rlua_drawsprite,"spr");
    _UI_Runner_functionpush(rlua_drawrect,"rect");
    _UI_Runner_functionpush(rlua_drawrectb,"rectb");
    _UI_Runner_functionpush(rlua_btn,"btn");
    _UI_Runner_functionpush(rlua_btnp,"btnp");
    _UI_Runner_functionpush(rlua_mouse,"mouse");
    _UI_Runner_functionpush(rlua_trace,"trace");
    _UI_Runner_functionpush(rlua_pal,"pal");
    _UI_Runner_functionpush(rlua_drawpix,"pix");
	uirun.isload=1;
}
void UI_Runner_LoadD(struct sdata sdata)
{
    UI_Palette_LoadD(sdata);
    UI_Sprite_LoadD(sdata);
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
            uirun.isdebug=0;
            fread(&sdata,sizeof(struct sdata),1,fic);
            fclose(fic);
			UI_Runner_LoadD(sdata);
            return true;
        }
        else puts(TextFormat("[EGBA] : runner error : %s not found",pfile));
    }
    else if(TextIsEqual(ext,".lua"))
    {
        const char* fileext = TextFormat("%s.png",GetFileNameWithoutExt(pfile));
        if(FileExists(fileext))
        {
            UI_Runner();
            uirun.isdebug=1;
            if(_EGBA.ifrunner==true)
            {
				UI_palette_LoadF(fileext);
				UI_sprite_LoadF(fileext);
            }
            CLUA_dofile(&uirun.clua,pfile);
            return true;
        }else puts(TextFormat("[EGBA] : runner error : %s not found",fileext));
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
	if(uirun.isload)
		CLUA_free(&uirun.clua);
}

// project viewer/editor

#define PROJECT_GetFileLua(spjt) (TextFormat("%s.lua",spjt.name))
#define PROJECT_GetFilePng(spjt) (TextFormat("%s.png",spjt.name))
#define PROJECT_GetFileEgba(spjt) (TextFormat("%s.egba",spjt.name))

void PROJECT_LoadSprite(Project ppjt)
{
	UI_palette_LoadF(PROJECT_GetFilePng(ppjt));
    UI_sprite_LoadF(PROJECT_GetFilePng(ppjt));
}

void PROJECT_LoadScript(Project ppjt)
{
	UI_Script_LoadF(PROJECT_GetFileLua(ppjt));
}

char PROJECT_LoadEgba(Project ppjt)
{
	struct sdata lsdata;
	FILE* fic = fopen(PROJECT_GetFileEgba(ppjt),"rb");
	fread(&lsdata,sizeof(struct sdata),1,fic);
	fclose(fic);
	UI_Palette_LoadD(lsdata);
	UI_Sprite_LoadD(lsdata);
	UI_Script_LoadD(lsdata);
    return lsdata.islock;
}

void PROJECT_BuildEgba(Project ppjt,char islock)
{
	struct sdata lsdata={0};
    lsdata.islock = islock;
	UI_Palette_Save(&lsdata);
	UI_Sprite_Save(&lsdata);
	UI_Script_Save(&lsdata);
	FILE* fic = fopen(PROJECT_GetFileEgba(ppjt),"wb");
	fwrite(&lsdata,sizeof(struct sdata),1,fic);
	fclose(fic);
}

void PROJECT_BuildExec(Project ppjt)
{
	char names[2][3][50];
	strcpy(names[0][0],"egba");
	strcpy(names[0][1],PROJECT_GetFileEgba(ppjt));
	strcpy(names[0][2],ppjt.name);
	
	strcpy(names[1][0],"egba.exe");
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
    if(UI_Palette.palette_nb>0)
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
        ExportImage(fullimg,PROJECT_GetFilePng(ppjt));
        UnloadImage(fullimg);
    }
    else
    {
        Image fullimg = GenImageColor(256,256,(Color){0,0,0,0});
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(UI_Sprite.sprites[(y*16)+x]);
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
    fprintf(fic,"%s",UI_Script.script);
    fclose(fic);
}
char PROJECT_DebugInit(Project ppjt)
{
    const char* lfile = PROJECT_GetFileLua(ppjt);
    if(FileExists(lfile))
    {
		UI_Runner();
		uirun.isdebug=1;
		CLUA_dofile(&uirun.clua,lfile);
        return 1;
    }
    return 0;
}

char PROJECT_RunInit(Project ppjt)
{
    const char* lfile = PROJECT_GetFileEgba(ppjt);
    if(FileExists(lfile))
    {
		uirun.isdebug=0;
        UI_Runner_Load(lfile);
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
						if(PROJECT_DebugInit(lproject))
                            _UIPROJECT.state=UIPROJECT_STATE_VRUNNER;
                        else
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
						if(PROJECT_RunInit(lproject))
                        _UIPROJECT.state=UIPROJECT_STATE_VRUNNER;
                        else
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
                        UI_palette_LoadF(files.paths[i]);
                        UI_sprite_LoadF(files.paths[i]);
                        puts("[EGBA] : done");
                    }
                    UnloadDroppedFiles(files);
                }
                UI_Sprite_Draw();
				UI_Palette_Draw(0,430,12);
			break;
			case UIPROJECT_STATE_VSCRIPT:
				if(UIBUTTON(5,5,"back",20,UICONFIG_COL2()))
				{
					_UIPROJECT.state=UIPROJECT_STATE_DEFAULT;
				}
				UI_Script_Draw();
			break;
			case UIPROJECT_STATE_VRUNNER:
				UI_Runner_Draw();
				if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
				{
					_UIPROJECT.state = UIPROJECT_STATE_DEFAULT;
                    puts("[EGBA][DEBUG/RUN END]");
				}
			break;
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

//-------- egba -----------------


void EGBA_EditorInit()
{
	_EGBA.ifrunner = false;
    UICONFIG_Init();
    UI_Palette_Init();
    UI_Sprite_Init();
    UI_Script_Init();
    UIPROJECT_LoadIcons();
    BROWSER_Init();

}
void EGBA_RunnerInit(char* arg)
{
    int size = GetFileLength(arg);
    FILE* fic = fopen(arg,"rb");
    struct sdata sdata;
    if(fic!=NULL)
    {
        fseek(fic,size-sizeof(struct sdata),0);
        fread(&sdata,sizeof(struct sdata),1,fic);
        fclose(fic);
        uirun.isdebug=0;
        UI_Runner();
        UI_Runner_LoadD(sdata);
    }
    _EGBA.ifrunner = true;
}
void EGBA_Init(int narg, char **sarg)
{
    Atlas_Init();
    _UIPROJECT.isactive=0;
    _EGBA.ifrunner=false;

    if(narg==1)
    {
        if(TextIsEqual( GetFileNameWithoutExt(sarg[0]) ,"egba"))
        {// init editor
            EGBA_EditorInit();
        }
        else 
        {// run game
            EGBA_RunnerInit(sarg[0]);
        }
    }
    else if(narg==2)
    {
		_EGBA.ifrunner = true;
        if(UI_Runner_Load(sarg[1]))
        {
        // runner init 
            
        }
        else
        {// runner fail -> init editor
            puts("[EGBA] : error runner fail");
            EGBA_EditorInit();
        }
    }
}

void EGBA_Draw()
{
	int browser_state=-1;

    if(_EGBA.ifrunner==false)
    {

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

    }
    else if(_EGBA.ifrunner==true)
    {// runner draw
        UI_Runner_Draw();
    }
}

void EGBA_Free()
{
	Atlas_Free();
    if(_EGBA.ifrunner==false)
    {// free editor
		UI_Sprite_Free();
		UIPROJECT_Free();
        UI_Runner_Free();
    }
    else if(_EGBA.ifrunner==true)
    {// free runner / game
        UI_Runner_Free();
    }
}
#include "EGBA.h"
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
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(UICONFIG_COL1());
        EGBA_Draw();
        EndDrawing();
    }
    
    EGBA_Free();
    CloseWindow();        // Close window and OpenGL
    return 0;
}

