#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "raylib.h"
#include "Palette.hpp"
#include <vector>
#include <string>
#include "data_type.hpp"
class Sprite
{
    private:
    // Texture2D texture;
    int palette_id;
    Vector2 pos;
    Vector2 size;
    std::vector<int> ldata;
    public:
    Sprite(const char* pfile,Palette pal);
    Sprite(struct ssprite ssprite);
    Sprite();
    ~Sprite();
    void SetData(int x,int y,Color col);
    struct ssprite GetStruct();
    // void UpdateTexture();
};
#endif