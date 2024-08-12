/*******************************************************************************************
*
*   UIHelp v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UIHELP_IMPLEMENTATION
*       #include "gui_UIHelp.h"
*
*       INIT: GuiUIHelpState state = InitGuiUIHelp();
*       DRAW: GuiUIHelp(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_UIHELP_H
#define GUI_UIHELP_H

typedef struct {
    bool WindowBox000Active;

    Rectangle layoutRecs[7];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIHelpState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiUIHelpState InitGuiUIHelp(void);
void GuiUIHelp(GuiUIHelpState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UIHELP_H

/***********************************************************************************
*
*   GUI_UIHELP IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UIHELP_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiUIHelpState InitGuiUIHelp(void)
{
    GuiUIHelpState state = { 0 };

    state.WindowBox000Active = true;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 32, 56, 896, 136 };
    state.layoutRecs[2] = (Rectangle){ 40, 64, 832, 24 };
    state.layoutRecs[3] = (Rectangle){ 40, 88, 832, 24 };
    state.layoutRecs[4] = (Rectangle){ 40, 112, 832, 24 };
    state.layoutRecs[5] = (Rectangle){ 40, 136, 832, 24 };
    state.layoutRecs[6] = (Rectangle){ 40, 160, 832, 24 };

    // Custom variables initialization

    return state;
}

void GuiUIHelp(GuiUIHelpState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Help");
        GuiGroupBox(state->layoutRecs[1], "shortcut");
        GuiLabel(state->layoutRecs[2], "[space] for start/end debug script");
        GuiLabel(state->layoutRecs[3], "[enter] for start/end run egba");
        GuiLabel(state->layoutRecs[4], "[ctrl] + [i] import sprite/script from EGBA");
        GuiLabel(state->layoutRecs[5], "[ctrl] + [e] export sprite/script to EGBA");
        GuiLabel(state->layoutRecs[6], "[ctrl] + [l] export sprite/script to lock EGBA");
    }
}

#endif // GUI_UIHELP_IMPLEMENTATION
