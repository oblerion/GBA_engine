#ifndef PALETTEMANAGER_HPP
#define PALETTEMANAGER_HPP
#include "Palette.hpp"
#include <vector>
#include "data_type.hpp"
class PaletteManager
{
    private:
    std::vector<Palette> list; 
    public:
    PaletteManager();
    void Add(const char* pfile);
    void Add(struct spalette);
    Palette Get(int id);
    void Del(int id);
    struct smpalette GetStruct();
    int Size();
    void Clear();
    void Draw(int id,int x,int y);
    ~PaletteManager();
};

#endif