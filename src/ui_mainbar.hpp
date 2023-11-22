#ifndef UI_MAINBAR_HPP
#define UI_MAINBAR_HPP
#include "raylib.h"
#include "ui.hpp"
#include "ui_palette.hpp"
#include "ui_sprite.hpp"
#include "data_type.hpp"
enum UISTATE
{
    statepalette=0,
    statesprite=1
};

class UI_MainBar
{
    private:
        struct UI_BUTTON btnpal;
        struct UI_BUTTON btnspr;

        struct UI_BUTTON btnsave;
        bool issave;
        UISTATE state;
    public:
    UI_MainBar(int x,int y);
    ~UI_MainBar();
    UISTATE GetState();
    void DropLoad(UI_Palette* uipal,UI_Sprite* uispr);
    void Save(UI_Palette uipal,UI_Sprite uispr);
    
    void Draw();
};
#endif