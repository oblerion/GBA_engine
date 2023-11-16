#include "Palette.hpp"

Palette::Palette(JsonObject json)
{
    texture = {0};
    name = json.GetString("name");
    palette = json.GetArray("data");
}

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

Color Palette::Get(int id)
{
    if(id<0 || id>palette.size()) return WHITE;
    return GetColor(palette[id]);
}

std::string Palette::GetName()
{
    return name;
}

int Palette::GetHexa(int id)
{
    if(id<0 || id>palette.size()) return ColorToInt(WHITE);
    return palette[id];
}

int Palette::Size()
{
    return palette.size();
}

JsonObject Palette::GetJson()
{
    JsonObject jobj;
    jobj.SetString("name",name);
    jobj.SetArray("data",palette);
    return jobj;
}

void Palette::Draw(int x,int y)
{
    for(int i=0;i<palette.size();i++)
    {
        DrawRectangle(x+(i*20),y,20,20,GetColor(palette[i]));
    }
}

Palette::~Palette()
{
    UnloadTexture(texture);
    palette.clear();
}
