/*******************************************************************************************
*
*   UIScript v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UISCRIPT_IMPLEMENTATION
*       #include "gui_UIScript.h"
*
*       INIT: GuiUIScriptState state = InitGuiUIScript();
*       DRAW: GuiUIScript(&state);
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
#include "../egba.h"
#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_UISCRIPT_H
#define GUI_UISCRIPT_H

typedef struct {
    bool WindowBox000Active;
    int ListView001ScrollIndex;
    int ListView001Active;
    char ListText[EGBA_MAX_SCRIPTSIZE];

    Rectangle layoutRecs[2];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIScriptState;

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
GuiUIScriptState InitGuiUIScript(void);
void GuiUIScript(GuiUIScriptState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UISCRIPT_H

/***********************************************************************************
*
*   GUI_UISCRIPT IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UISCRIPT_IMPLEMENTATION)

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
GuiUIScriptState InitGuiUIScript(void)
{
    GuiUIScriptState state = { 0 };

    state.WindowBox000Active = true;
    state.ListView001ScrollIndex = 0;
    state.ListView001Active = 0;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 24, 40, 912, 656 };

    // Custom variables initialization

    return state;
}

void GuiUIScript(GuiUIScriptState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Script");
        GuiListView(state->layoutRecs[1], state->ListText, &state->ListView001ScrollIndex, &state->ListView001Active);
    }
}

#endif // GUI_UISCRIPT_IMPLEMENTATION
