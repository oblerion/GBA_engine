#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP
#include "raylib.h"
#include "Sprite.hpp"
#include "Palette.hpp"
#include <vector>
#include "data_type.hpp"
class SpriteManager
{
    private:
    std::vector<Sprite> list;
    public:
    SpriteManager();
    SpriteManager(struct smsprite smsprite);
    ~SpriteManager();
    void Add(const char* pfile,Palette pal);
    Sprite Get(int id);
    struct smsprite GetStruct();
};
#endif