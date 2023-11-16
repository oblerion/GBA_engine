#include "PaletteManager.hpp"

PaletteManager::PaletteManager()
{
}

void PaletteManager::Add(JsonObject json)
{
    Palette pal(json);
    list.push_back(pal);
}

void PaletteManager::Add(const char *pfile)
{
    Palette pa(pfile);
    list.push_back(pa);
}

Palette PaletteManager::Get(int id)
{
    if(id>-1 && id<list.size())
    {
        return list[id];
    }
    return Palette("");
}

JsonObject PaletteManager::GetJson()
{
    JsonObject json;
    for(int i=0;i<list.size();i++)
    {
        json.SetObject(TextFormat("%d",i),list[i].GetJson());
    }
    return json;
}

int PaletteManager::Size()
{
    return list.size();
}

void PaletteManager::Draw(int id, int x, int y)
{
    Get(id).Draw(x,y);
}

PaletteManager::~PaletteManager()
{
    list.clear();
}
