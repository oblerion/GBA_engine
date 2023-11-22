#include "Palette.hpp"

Palette::Palette(const char *pfile)
{
    texture = {0};
    const char* cext = GetFileExtension(pfile);
    name = GetFileNameWithoutExt(pfile);
    
    if(TextIsEqual(cext,".png"))
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

Palette::Palette(struct spalette spalette)
{
    name = spalette.name;
    for(int i=0;i<32;i++)
        palette.push_back(spalette.data[i]);
}

Color Palette::Get(int id)
{
    if(id<0 || id>(signed int)(palette.size())) return WHITE;
    return GetColor(palette[id]);
}

std::string Palette::GetName()
{
    return name;
}

int Palette::GetHexa(int id)
{
    if(id<0 || id>(signed int)palette.size()) return ColorToInt(WHITE);
    return palette[id];
}

int Palette::Size()
{
    return palette.size();
}

struct spalette Palette::GetStruct()
{
    struct spalette spalette;
    strcpy(spalette.name,name.c_str());
    for(int i=0;i<32;i++)
    {
        spalette.data[i]=palette[i];
    }
    return spalette;
}

void Palette::Draw(int x,int y)
{
    for(int i=0;i<(signed int)palette.size();i++)
    {
        DrawRectangle(x+(i*20),y,20,20,GetColor(palette[i]));
    }
}

Palette::~Palette()
{
    UnloadTexture(texture);
    palette.clear();
}
