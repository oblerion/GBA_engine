#include "SpriteManager.h"

struct SpriteManager SpriteManager()
{
    struct SpriteManager sprman;
    sprman.nb_sprite=0;
    return sprman;
}
struct SpriteManager SpriteManagerD(struct smsprite smsprite)
{
    struct SpriteManager sprman;
    sprman.nb_sprite=0;
    for(int i=0;i<smsprite.nb_sprite;i++)
    {
        sprman.list[i]=Sprite(smsprite.list[i]);
    }
    return sprman;
}
void SpriteManager_AddF(struct SpriteManager* sprman,const char* pfile,struct Palette pal)
{
    if(sprman->nb_sprite+1<255)
    {
        sprman->nb_sprite++;
        sprman->list[sprman->nb_sprite] = Sprite(pfile,pal);
    }
}
void SpriteManager_AddD(struct SpriteManager* sprman,struct ssprite ssprite)
{
    if(sprman->nb_sprite+1<255)
    {
        sprman->nb_sprite++;
        sprman->list[sprman->nb_sprite] = SpriteD(ssprite);
    }
}
struct Sprite SpriteManager_Get(struct SpriteManager sprman,int id)
{
    if(id>-1 && id<sprman.nb_sprite)
        return sprman.list[id];
    return Sprite();
}
struct smsprite SpriteManager_GetStruct(struct SpriteManager sprman)
{
    struct smsprite smsprite;
    smsprite.nb_sprite = sprman.nb_sprite;
    for(int i=0;i<smsprite.nb_sprite;i++)
    {
        smsprite.list[i] = Sprite_GetStruct(sprman.list[i]);
    }
    return smsprite;
}