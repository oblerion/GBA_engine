#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP
#include "raylib.h"
#include "Sprite.hpp"
#include "Palette.hpp"
#include <vector>
class SpriteManager
{
    private:
    std::vector<Sprite> list;
    public:
    SpriteManager();
    ~SpriteManager();
    void Add(const char* pfile,Palette pal);
    void Add(JsonObject json);
    Sprite Get(int id);
    JsonObject GetJson();
};
#endif