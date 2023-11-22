#include "PaletteManager.hpp"

PaletteManager::PaletteManager()
{
}

void PaletteManager::Add(const char *pfile)
{
    Palette pa(pfile);
    list.push_back(pa);
}

void PaletteManager::Add(struct spalette spalette)
{
    Palette pa(spalette);
    list.push_back(pa);
}

Palette PaletteManager::Get(int id)
{
    if(id>-1 && id<(signed int)list.size())
    {
        return list[id];
    }
    return Palette("");
}

void PaletteManager::Del(int id)
{
    list.erase(list.begin()+id);
}

void PaletteManager::Clear()
{
    list.clear();
}

struct smpalette PaletteManager::GetStruct()
{
    struct smpalette smpalette;
    smpalette.nb_palette=(signed int)list.size();
    for(int i=0;i<5;i++)
    {
        if(i< smpalette.nb_palette)
            smpalette.list[i] = list[i].GetStruct();
    }
    return smpalette;
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
