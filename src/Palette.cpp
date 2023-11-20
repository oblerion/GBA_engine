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
        palette.push_back(ColorToInt({0,0,0,0}));
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
    for(int i=0;i<33;i++)
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

JsonObject Palette::GetJson()
{
    JsonObject jobj;
    puts(name.c_str());
    jobj.SetString("name",name);
    jobj.SetArray("data",palette);
    jobj.Print();
    return jobj;
}

struct spalette Palette::GetStruct()
{
    struct spalette spalette;
    strcpy(spalette.name,name.c_str());
    spalette.data[0]=ColorToInt({0,0,0,0});
    for(int i=1;i<33;i++)
    {
        spalette.data[i]=palette[i-1];
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
