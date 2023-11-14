#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "raylib.h"
#include "Palette.hpp"
class Sprite
{
    private:
    Texture2D texture;
    public:
    Sprite(const char* pfile,Palette pal);
    ~Sprite();
    JsonObject GetJson(const char* pfile);
};
#endif