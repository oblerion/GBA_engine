#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "raylib.h"
#include "Palette.hpp"
#include <vector>
#include <string>
class Sprite
{
    private:
    Texture2D texture;
    Vector2 pos;
    Vector2 size;
    std::vector<int> ldata;
    public:
    std::string name;
    Sprite(const char* pfile,Palette pal);
    Sprite(JsonObject json);
    Sprite();
    ~Sprite();
    JsonObject GetJson();
    void SetData(int x,int y,Color col);
    void UpdateTexture();
};
#endif