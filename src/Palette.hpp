#ifndef PALETTE_HPP
#define PALETTE_HPP
#include "raylib.h"
#include "JsonObject.hpp"
#include <vector>
#include <string>
#include "data_type.hpp"
class Palette
{
    private:
    Texture2D texture;
    std::vector<int> palette;
    std::string name;
    public:
    Palette(JsonObject json);
    Palette(const char* pfile);
    Palette(struct spalette spalette);
    ~Palette();
    Color Get(int id);
    std::string GetName();
    int GetHexa(int id);
    int Size();
    JsonObject GetJson();
    struct spalette GetStruct();
    void Draw(int x,int y);
};
#endif