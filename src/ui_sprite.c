#include "ui_sprite.h"

struct UI_BUTTONSPRITE UI_BUTTONSPRITE(int x, int y,int scale,int id_sprite)
{
    struct UI_BUTTONSPRITE btnspr={x,y,scale,id_sprite,true};
    return btnspr;
}

int UI_BUTTONSPRITE_Draw(struct UI_BUTTONSPRITE btnspr,struct UI_Sprite uispr)
{
    int ret=0;
    if(btnspr.visible)
    {
        Atlas_DrawSprite(btnspr.id_sprite,btnspr.x,btnspr.y,btnspr.scale);
        int ix = GetMouseX();
        int iy = GetMouseY();
        if(MATH_collide(ix,iy,1,1,
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

struct UI_Sprite UI_Sprite()
{
    struct UI_Sprite uispr;
    uispr.slidepalette = UI_SLIDEBAR_V(420,460,10,50,5);
    const int size = 16;
    uispr.curant_spr=0;
    uispr.curant_color=BLACK;  
    uispr.curant_pal=0;
    uispr.btnspr_size = 2;
    uispr.btncol_size = 26;
    for(int y=0;y<size;y++)
    for(int x=0;x<size;x++)
    {
        uispr.sprites[(size*y)+x] = Sprite();
        uispr.btnspr[(size*y)+x] = UI_BUTTONSPRITE(440+(x*uispr.btnspr_size*16),
                                                    30+(y*uispr.btnspr_size*16),
                                                    uispr.btnspr_size,
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
    uispr.sprfond = LoadTextureFromImage(img);
    UnloadImage(itrangle);
    UnloadImage(img);
    // atlas
    // img = GenImageColor(256,256,BLACK);
    // uispr.spratlas = LoadTextureFromImage(img);
    // UnloadImage(img);
    return uispr;
}

struct Sprite UI_sprite_Get(struct UI_Sprite uispr,int id)
{
    return uispr.sprites[id];
}

void UI_Sprite_LoadD(struct UI_Sprite* uispr, struct sdata sdata)
{
    //uispr->sprman=SpriteManagerD(sdata,uispr->sprman.palman);
    for(int i=0;i<DT_MAX_SPRITE;i++)
    {
        uispr->sprites[i] = SpriteD(sdata.list_spr[i]);
    }
    Atlas_UpdateSprite(uispr->sprites);
}

void UI_sprite_LoadF(struct UI_Sprite* uispr, const char *pfile)
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
            uispr->sprites[(i*16)+j].ldata[col] = img_col[col];
            UnloadImage(img);
        }
        Atlas_UpdateSprite(uispr->sprites);
    }
    UnloadImage(fullimg);
}

void UI_Sprite_Save(struct UI_Sprite uispr, struct sdata *sdata)
{
    for(int i=0;i<DT_MAX_SPRITE;i++)
    {
        sdata->list_spr[i] = Sprite_GetStruct(uispr.sprites[i]);
    }
}

int UI_Sprite_Draw(struct UI_Sprite* uispr,struct UI_Palette uipal)
{
    int ret=0;
    DrawTexture(uispr->sprfond,2,30,WHITE);
    DrawRectangleLines(440,30,16*2*16,16*2*16,BLACK);
    for(int y=0;y<16;y++)
    for(int x=0;x<16;x++)
    {
        int id = (16*y)+x;
        if(UI_BUTTONSPRITE_Draw(uispr->btnspr[id],*uispr))
        {
            uispr->curant_spr=id;
        }
        Atlas_DrawSprite(uispr->curant_spr,2,30,uispr->btncol_size);
    }
    return ret;
}

void UI_Sprite_Free(struct UI_Sprite uispr)
{
    UnloadTexture(uispr.sprfond);
    //UnloadTexture(uispr.spratlas);
}


