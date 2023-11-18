#ifndef UI_SPRITE_HPP
#define UI_SPRITE_HPP
#include "raylib.h"
#include "Sprite.hpp"
#include "SpriteManager.hpp"
class UI_Sprite
{
    private:
    SpriteManager sprman;
    public:
    UI_Sprite();
    ~UI_Sprite();
    Sprite Get(int id);
    int Draw();
};
#endif