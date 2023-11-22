#include "SpriteManager.hpp"

SpriteManager::SpriteManager()
{
}

SpriteManager::SpriteManager(smsprite smsprite)
{
    list.clear();
    for(int i=0;i<smsprite.nb_sprite;i++)
    {
        Sprite spr(smsprite.list[i]);
        list.push_back(spr);
    }
}

SpriteManager::~SpriteManager()
{
    list.clear();
}

void SpriteManager::Add(const char *pfile,Palette pal)
{
    Sprite spr(pfile,pal);
    list.push_back(spr);
}

Sprite SpriteManager::Get(int id)
{
    if(id<0 && id>(signed int)list.size())
        return list[id];
    return Sprite();
}

struct smsprite SpriteManager::GetStruct()
{
    struct smsprite smsprite;
    smsprite.nb_sprite = (signed int)list.size();
    for(int i=0;i<smsprite.nb_sprite;i++)
    {
        smsprite.list[i] = list[i].GetStruct();
    }

    return smsprite;
}
