#include "Sprite.h"

struct Sprite SpriteD(struct ssprite ssprite)
{
    struct Sprite spr={ssprite.width,ssprite.height};
    for(int i=0;i<spr.width*spr.height;i++)
    {
        spr.ldata[i] = ssprite.data[i];
    }
    // Image img = GenImageColor(spr.width,spr.height,BLACK);
    // spr.texture = LoadTextureFromImage(img);
    // UpdateTexture(spr.texture,spr.ldata);
    // UnloadImage(img);
    return spr;
}
struct Sprite Sprite()
{
	struct Sprite spr={16,16};
	for(int i=0;i<spr.width*spr.height;i++)
	{
		spr.ldata[i]=BLACK;
	}
    // Image img = GenImageColor(spr.width,spr.height,BLACK);
    // spr.texture = LoadTextureFromImage(img);
    // UnloadImage(img);
	return spr;
}
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col)
{
    spr->ldata[(y*spr->width)+x]=col;
    // UpdateTexture(spr->texture,&spr->ldata);
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
// void Sprite_Draw(struct Sprite spr,int x,int y,int scale)
// {
//     Rectangle rso = {0,0,spr.width,spr.height};
//     Rectangle rde = {x,y,spr.width*scale,spr.height*scale};
//     Vector2 vor = {0,0};
//     DrawTexturePro(spr.texture,rso,rde,vor,0,WHITE);
// }

// void Sprite_Free(struct Sprite* spr)
// {
//     UnloadTexture(spr->texture);
// }