#include "Palette.h"

struct Palette PaletteF(const char *pfile)
{
    struct Palette pal;
    const char* cext = GetFileExtension(pfile);
    Image fullimage = GenImageColor(32*20,20,BLACK);
    if(TextIsEqual(cext,".png"))
    {
        strcpy(pal.name,GetFileNameWithoutExt(pfile));
        Image img = LoadImage(pfile);
        //palette.clear();
        for(int i=0;i<img.width;i++)
        {        
            Color col = GetImageColor(img,i,0);
            pal.palette[i]=ColorToInt(col);
            ImageDrawRectangle(&fullimage,i*20,0,20,20,col);
        } 
        UnloadImage(img);
    }
    pal.texture = LoadTextureFromImage(fullimage);
    UnloadImage(fullimage);
    return pal;
}

struct Palette PaletteD(struct spalette spalette)
{
    struct Palette pal;
    strcpy(pal.name,spalette.name);
    Image img = GenImageColor(32*20,20,BLACK);
    for(int i=0;i<32;i++)
    {
        pal.palette[i]=spalette.data[i];
        ImageDrawRectangle(&img,i*20,0,20,20,GetColor(spalette.data[i]));
    }
    pal.texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return pal;
}

Color Palette_Get(struct Palette pal, int id)
{
    if(id<0 || id>Palette_Size(pal)) return WHITE;
    return GetColor(pal.palette[id]);
}

const char *Palette_GetName(struct Palette pal)
{
    return TextFormat("%s",pal.name);
}

int Palette_GetHexa(struct Palette pal, int id)
{
    if(id<0 || id>Palette_Size(pal)) return ColorToInt(WHITE);
    return pal.palette[id];
}

int Palette_Size(struct Palette pal)
{
    return sizeof(pal.palette)/sizeof(int);
}

struct spalette Palette_GetStruct(struct Palette pal)
{
    struct spalette spalette;
    strcpy(spalette.name,pal.name);
    for(int i=0;i<32;i++)
    {
        spalette.data[i]=pal.palette[i];
    }
    return spalette;
}

void Palette_Draw(struct Palette pal, int x, int y)
{
    DrawTexture(pal.texture,x,y,WHITE);
}

void Palette_Free(struct Palette *pal)
{
    UnloadTexture(pal->texture);
}
