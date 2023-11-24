#include "Sprite.h"

struct Sprite SpriteD(struct ssprite ssprite)
{
    struct Sprite spr;
	spr.width = ssprite.width;
    spr.height = ssprite.height;
    for(int i=0;i<ssprite.width*ssprite.height;i++)
    {
        spr.ldata[i] = ssprite.data[i];
    }
    return spr;
}
struct Sprite Sprite()
{
	struct Sprite spr={0,16,16};
	for(int i=0;i<spr.width*spr.height;i++)
	{
		spr.ldata[i]=0;
	}
	return spr;
}
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col)
{
    spr->ldata[(y*spr->width)+x]=ColorToInt(col);
}
struct ssprite Sprite_GetStruct(struct Sprite spr)
{
    struct ssprite ssprite;
    ssprite.width=spr.width;
    ssprite.height=spr.height;
    
    for(int i=0;i<ssprite.width*ssprite.height;i++)
    {
        ssprite.data[i]=spr.ldata[i];
    }

    return ssprite;
}
void Sprite_Draw(struct Sprite spr,int x,int y,int scale)
{
    for(int i=0;i<spr.width*spr.height;i++)
    {
        Color col = GetColor(spr.ldata[i]);
        DrawRectangle(x+(i/spr.width)*scale,y+(i%spr.width)*scale,scale,scale,col);
    }
}
