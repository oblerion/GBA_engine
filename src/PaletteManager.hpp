#ifndef PALETTEMANAGER_HPP
#define PALETTEMANAGER_HPP
#include "Palette.hpp"
#include <vector>
class PaletteManager
{
    private:
    std::vector<Palette> list; 
    public:
    PaletteManager();
    void Add(JsonObject json);
    void Add(const char* pfile);
    Palette Get(int id);
    void Del(int id);
    JsonObject GetJson();
    int Size();
    void Draw(int id,int x,int y);
    ~PaletteManager();
};

#endif