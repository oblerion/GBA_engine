#ifndef UI_SPRITE_HPP
#define UI_SPRITE_HPP
#include "raylib.h"
#include "ui.hpp"
#include "data_type.hpp"
#include "Sprite.hpp"
#include "SpriteManager.hpp"

class UI_Sprite
{
    private:
    SpriteManager sprman;
    struct UI_BUTTON btnspr[256];
    // void _DropLoad();
    public:
    UI_Sprite();
    ~UI_Sprite();
    Sprite Get(int id);
    void Load(struct sdata sdata);
    void Load(const char* pfile);
    void Save(struct sdata* sdata);
    int Draw();
};
#endif