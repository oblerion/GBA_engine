#ifndef UI_PALETTE_HPP
#define UI_PALETTE_HPP
#include <cstdio>
#include "PaletteManager.hpp"
#include <vector>
#include <string>
class UI_Palette
{
    private:
    PaletteManager palman;
    public:
    UI_Palette(std::vector<std::string> lstfile);
    ~UI_Palette();
    void Draw();
};
#endif