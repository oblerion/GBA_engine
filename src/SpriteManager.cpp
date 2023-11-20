#include "SpriteManager.hpp"

SpriteManager::SpriteManager()
{
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

void SpriteManager::Add(JsonObject json)
{
    Sprite spr(json);
    list.push_back(spr);
}

Sprite SpriteManager::Get(int id)
{
    if(id<0 && id>(signed int)list.size())
        return list[id];
    return Sprite();
}

JsonObject SpriteManager::GetJson()
{
    JsonObject json;
    for(int i=0;i<(signed int)list.size();i++)
    {
        json.SetObject(TextFormat("%d",i),list[i].GetJson());
    }
    return json;
}
