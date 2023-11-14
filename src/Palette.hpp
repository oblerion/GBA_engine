#ifndef PALETTE_HPP
#define PALETTE_HPP
#include "raylib.h"
#include "JsonObject.hpp"
#include <vector>
class Palette
{
    private:
    std::vector<int> palette;
    public:
    Palette(const char* pfile);
    ~Palette();
    Color Get(int id);
    int Size();
    JsonObject GetJson(const char* pfile);
};
#endif