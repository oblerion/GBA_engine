#include "Palette.hpp"

Palette::Palette(const char *pfile)
{
    const char* cext = GetFileExtension(pfile);
    if(TextIsEqual(cext,".json"))
    {
        JsonObject jpalette(pfile);
        palette.clear();
        palette = jpalette.GetArray("palette");
    }
    else if(TextIsEqual(cext,".png"))
    {
        Image img = LoadImage(pfile);
        palette.clear();
        for(int i=0;i<img.width;i++)
        {        
            Color col = GetImageColor(img,i,0);
            palette.push_back(ColorToInt(col));
        }
        UnloadImage(img);
    }
}

Color Palette::Get(int id)
{
    if(id<0 || id>palette.size()) return WHITE;
    return GetColor(palette[id]);
}

int Palette::Size()
{
    return palette.size();
}

JsonObject Palette::GetJson(const char* pfile)
{
    JsonObject jobj(pfile);
    jobj.SetArray("palette",palette);
    return jobj;
}

Palette::~Palette()
{
    palette.clear();
}
