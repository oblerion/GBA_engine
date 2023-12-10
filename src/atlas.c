#include "atlas.h"

void Atlas_DrawPalette(Texture2D texture,int id, int x,int y,int scale)
{
    if(id>-1 && id<6)
    DrawTexturePro(texture,(Rectangle){0,id,32,1},(Rectangle){x,y,32*scale,scale},(Vector2){0,0},0,WHITE);
}
void Atlas_UpdatePalette(Texture2D texture,struct Palette* palettes)
{
    Image img = GenImageColor(32,5,BLACK);
//LoadImageFromTexture(uipal->texture);
    Image palimg;
    for(int i=0;i<DT_MAX_PALETTE;i++)
    {
        palimg = Palette_GetImg(palettes[i]);
        ImageDraw(&img,palimg,(Rectangle){0,0,32,1},(Rectangle){0,i,32,1},WHITE);
    }
    UpdateTexture(texture,img.data);
    UnloadImage(palimg);
    UnloadImage(img);
}
void Atlas_DrawSprite(Texture2D texture,int id,int x,int y,int scale)
{
    DrawTexturePro(texture,
        (Rectangle){(id%16)*16,(id/16)*16,16,16},
        (Rectangle){x,y,16*scale,16*scale},(Vector2){0,0},0,WHITE);
}
void Atlas_UpdateSprite(Texture2D texture,struct Sprite* sprites)
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
    UpdateTexture(texture,img.data);
    
    UnloadImage(img);
}