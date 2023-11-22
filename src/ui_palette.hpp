#ifndef UI_PALETTE_HPP
#define UI_PALETTE_HPP
#include "raylib.h"
#include "ui.hpp"
#include "Palette.hpp"
#include "PaletteManager.hpp"
#include "data_type.hpp"
#include <vector>
#include <string>
class UI_Palette
{
    private:
    PaletteManager palman;
    struct UI_BUTTON btndelete;
    struct UI_SLIDEBAR_V slider;
    void _DropLoad();
    // void _Save(const char* pfile);
    public:
    UI_Palette();
    ~UI_Palette();
    void Load(const char* pfile);
    void Load(struct sdata sdata);
    void Save(struct sdata* sdata);
    Palette Get(int id);
    int Draw();
};
#endif