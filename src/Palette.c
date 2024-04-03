#include "Palette.h"

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
    // pal.texture = LoadTextureFromImage(fullimage);
    // UnloadImage(fullimage);
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
    // pal.texture = LoadTextureFromImage(img);
    // UnloadImage(img);
    return pal;
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

// int Palette_GetHexa(struct Palette pal, int id)
// {
//     if(id<0 || id>Palette_Size(pal)) return ColorToInt(WHITE);
//     return pal.palette[id];
// }

int Palette_Size(struct Palette pal)
{
    return sizeof(pal.palette)/sizeof(int);
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

// void Palette_Draw(struct Palette pal, int x, int y)
// {
//     DrawTexture(pal.texture,x,y,WHITE);
// }

// void Palette_Free(struct Palette *pal)
// {
//     UnloadTexture(pal->texture);
// }
