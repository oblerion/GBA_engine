#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include "raylib.h"
#include "Sprite.h"
#include "Palette.h"
#include "data_type.h"
struct SpriteManager
{
    int nb_sprite;
    struct Sprite list[255];
};
struct SpriteManager SpriteManager();
struct SpriteManager SpriteManagerD(struct smsprite smsprite);
void SpriteManager_AddF(struct SpriteManager* sprman,const char* pfile,struct Palette pal);
void SpriteManager_AddD(struct SpriteManager* sprman,struct ssprite ssprite);
struct Sprite SpriteManager_Get(struct SpriteManager sprman,int id);
struct smsprite SpriteManager_GetStruct(struct SpriteManager sprman);
#endif