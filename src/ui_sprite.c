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
        Atlas_DrawSprite(uispr.spratlas,btnspr.id_sprite,btnspr.x,btnspr.y,btnspr.scale);
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
    uispr.btnerase = UI_BUTTON(340,465,"erase",20,WHITE);
    for(int y=0;y<size;y++)
    for(int x=0;x<size;x++)
    {
        uispr.sprites[(size*y)+x] = Sprite();
        uispr.btncolor[(size*y)+x] = UI_BUTTONCOLOR(2+(x*uispr.btncol_size),
                                                    30+(y*uispr.btncol_size),
                                                    uispr.btncol_size,
                                                    (Color){0,0,0,0}); 
        uispr.btnspr[(size*y)+x] = UI_BUTTONSPRITE(440+(x*uispr.btnspr_size*16),
                                                    30+(y*uispr.btnspr_size*16),
                                                    uispr.btnspr_size,
                                                    (size*y)+x);
    }
    for(int j=0;j<2;j++)
    for(int i=0;i<16;i++)
    {// color picker
        uispr.btnpal[i+(j*16)] = UI_BUTTONCOLOR(5+(i*20),460+(j*20),20,BLACK);
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
    img = GenImageColor(256,256,BLACK);
    uispr.spratlas = LoadTextureFromImage(img);
    UnloadImage(img);
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
    Atlas_UpdateSprite(uispr->spratlas,uispr->sprites);
    for(int i=0;i<32;i++)
    {
        uispr->btnpal[i].color= GetColor(sdata.list_pal[0].data[i]);
    }
}

void UI_sprite_LoadF(struct UI_Sprite* uispr, const char *pfile)
{
    Image fullimg = LoadImage(pfile);
    if(fullimg.width==256 && fullimg.height==256)
    {
        Image img = GenImageColor(16,16,BLACK);
        for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
        {
            ImageDraw(&img,fullimg,
                    (Rectangle){j*16,i*16,16,16},
                    (Rectangle){0,0,16,16},WHITE);
            uispr->sprites[(i*16)+j].height=16;
            uispr->sprites[(i*16)+j].width=16;
            Color* lcol = LoadImageColors(img);
            for(int g=0;g<256;g++)
                uispr->sprites[(i*16)+j].ldata[g] = lcol[g];
           // uispr->sprites[(i*16)+j].texture = LoadTextureFromImage(img);
            UnloadImageColors(lcol);
        }
        Atlas_UpdateSprite(uispr->spratlas,uispr->sprites);
        UnloadImage(img);
    }
    UnloadImage(fullimg);
}

void UI_Sprite_LoadPalette(struct UI_Sprite* uispr,struct UI_Palette uipal)
{
    for(int i=0;i<32;i++)
    {
        uispr->btnpal[i].color= GetColor(uipal.palettes[uispr->curant_pal].palette[i]);
    }
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
    if((IsKeyDown(KEY_LEFT_CONTROL) || 
        IsKeyDown(KEY_RIGHT_CONTROL)) &&
        IsKeyPressed(KEY_E))
    {
        Image fullimg = GenImageColor(256,256,BLACK);
        for(int y=0;y<16;y++)
        for(int x=0;x<16;x++)
        {
            Image img = Sprite_GetImg(uispr->sprites[(y*16)+x]);
            Rectangle rso = {0,0,16,16};
            Rectangle rde = {x*16,y*16,16,16};
            ImageDraw(&fullimg,img,rso,rde,WHITE);
            UnloadImage(img);
        }
        ExportImage(fullimg,"save.png");
        UnloadImage(fullimg);
    }
    if(UI_SLIDEBAR_V_draw(&uispr->slidepalette))
    {
        uispr->curant_pal=uispr->slidepalette.pos;
        UI_Sprite_LoadPalette(uispr,uipal);
    }
    DrawTexture(uispr->sprfond,2,30,WHITE);
    for(int y=0;y<16;y++)
    for(int x=0;x<16;x++)
    {
        int id = (16*y)+x;
        if(UI_BUTTONSPRITE_Draw(uispr->btnspr[id],*uispr))
        {
            uispr->curant_spr=id;
        }
        // Sprite_Draw(uispr->sprites[uispr->curant_spr],2,30,uispr->btncol_size);
        Atlas_DrawSprite(uispr->spratlas,uispr->curant_spr,2,30,uispr->btncol_size);
        if(UI_BUTTONCOLOR_Update(&uispr->btncolor[id]))
        {
            Sprite_SetData(&uispr->sprites[uispr->curant_spr],x,y,uispr->curant_color);
            Atlas_UpdateSprite(uispr->spratlas,uispr->sprites);
        }
    }
    for(int i=0;i<32;i++)
    {
        if(UI_BUTTONCOLOR_Draw(&uispr->btnpal[i]))
            uispr->curant_color=uispr->btnpal[i].color;
    }
    if(UI_BUTTON_draw(&uispr->btnerase))
    {
        uispr->curant_color = (Color){0,0,0,0};
    }
    return ret;
}

void UI_Sprite_Free(struct UI_Sprite uispr)
{
    UnloadTexture(uispr.sprfond);
    UnloadTexture(uispr.spratlas);
    // for(int i=0;i<DT_MAX_SPRITE;i++)
    // {
    //     Sprite_Free(&uispr->sprites[i]);
    // }
}


