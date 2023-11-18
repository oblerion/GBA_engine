#ifndef UI_PALETTE_HPP
#define UI_PALETTE_HPP

#include "PaletteManager.hpp"
#include <vector>
#include <string>
class UI_Palette
{
    private:
    PaletteManager palman;
    int idscroll;
    void _DropLoad();
    public:
    UI_Palette();
    UI_Palette(std::vector<std::string> lstfile);
    ~UI_Palette();
    Palette Get(int id);
    int Draw();
};
#endif