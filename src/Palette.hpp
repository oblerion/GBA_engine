#ifndef PALETTE_HPP
#define PALETTE_HPP
#include "raylib.h"
#include <vector>
#include <string>
#include <cstring>
#include "data_type.hpp"
class Palette
{
    private:
    Texture2D texture;
    std::vector<int> palette;
    std::string name;
    public:
    Palette(const char* pfile);
    Palette(struct spalette spalette);
    ~Palette();
    Color Get(int id);
    std::string GetName();
    int GetHexa(int id);
    int Size();
    struct spalette GetStruct();
    void Draw(int x,int y);
};
#endif