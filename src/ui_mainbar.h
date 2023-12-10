#ifndef UI_MAINBAR_H
#define UI_MAINBAR_H
#include <stdlib.h>
#include "raylib.h"
#include "ui.h"
#include "ui_palette.h"
#include "ui_sprite.h"
#include "ui_script.h"
#include "ui_runner.h"
#include "data_type.h"

enum UISTATE
{
    statepalette=0,
    statesprite=1,
    statescript=2
};

struct UI_MainBar
{
    struct UI_BUTTON btnpal;
    struct UI_BUTTON btnspr;
    struct UI_BUTTON btnscr;
    struct UI_BUTTON btnsave;
    struct UI_BUTTON btndoc;
    enum UISTATE state;
    char issave;
    bool isUpdate;
    char filename[50];
};

struct UI_MainBar UI_MainBar(int x,int y);
enum UISTATE UI_MainBar_GetState(struct UI_MainBar uibar);
void UI_MainBar_DropLoad(struct UI_MainBar* uibar,struct UI_Palette* uipal,struct UI_Sprite* uispr,struct UI_Script* uiscr);
void UI_MainBar_Save(struct UI_MainBar *uibar,struct UI_Palette uipal,struct UI_Sprite uispr,struct UI_Script uiscr);
void UI_MainBar_Build(struct UI_MainBar *uibar,const char* pfile);
void UI_MainBar_Draw(struct UI_MainBar *uibar);
#endif