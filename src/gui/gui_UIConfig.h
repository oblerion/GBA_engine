/*******************************************************************************************
*
*   UIConfig v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UICONFIG_IMPLEMENTATION
*       #include "gui_UIConfig.h"
*
*       INIT: GuiUIConfigState state = InitGuiUIConfig();
*       DRAW: GuiUIConfig(&state);
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

#ifndef GUI_UICONFIG_H
#define GUI_UICONFIG_H

typedef struct {
    bool WindowBox000Active;
    int ComboBox001Active;
    int ComboBox003Active;

    Rectangle layoutRecs[5];
    char gamepad_name[100];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIConfigState;

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
GuiUIConfigState InitGuiUIConfig(void);
void GuiUIConfig(GuiUIConfigState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UICONFIG_H

/***********************************************************************************
*
*   GUI_UICONFIG IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UICONFIG_IMPLEMENTATION)

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
GuiUIConfigState InitGuiUIConfig(void)
{
    GuiUIConfigState state = { 0 };

    state.gamepad_name[0] = '\0';
    state.WindowBox000Active = true;
    state.ComboBox001Active = 0;
    state.ComboBox003Active = 0;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 72, 56, 848, 24 };
    state.layoutRecs[2] = (Rectangle){ 456, 32, 48, 24 };
    state.layoutRecs[3] = (Rectangle){ 72, 112, 848, 24 };
    state.layoutRecs[4] = (Rectangle){ 456, 88, 64, 24 };

    // Custom variables initialization

    return state;
}

void GuiUIConfig(GuiUIConfigState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Config");
        GuiComboBox(state->layoutRecs[1], "default;Jungle;Candy;Lavanda;Cyber;Terminal;Ashes;Bluish;Dark;Cherry;Sunny;Enefete", &state->ComboBox001Active);
        GuiLabel(state->layoutRecs[2], "Theme :");
        GuiComboBox(state->layoutRecs[3], state->gamepad_name, &state->ComboBox003Active);
        GuiLabel(state->layoutRecs[4], "Gamepad :");
    }
}

#endif // GUI_UICONFIG_IMPLEMENTATION
