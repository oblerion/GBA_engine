/*******************************************************************************************
*
*   UIProjectNoDL v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UIPROJECT_NODL_IMPLEMENTATION
*       #include "gui_UIProject_noDL.h"
*
*       INIT: GuiUIProjectNoDLState state = InitGuiUIProjectNoDL();
*       DRAW: GuiUIProjectNoDL(&state);
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

#ifndef GUI_UIPROJECT_NODL_H
#define GUI_UIPROJECT_NODL_H

typedef struct {
    bool WindowBox000Active;
    bool ButtonEGBAPressed;
    bool ButtonHelpPressed;
    bool ButtonRunPressed;
    char LabelTextName[50];

    Rectangle layoutRecs[9];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIProjectNoDLState;

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
GuiUIProjectNoDLState InitGuiUIProjectNoDL(void);
void GuiUIProjectNoDL(GuiUIProjectNoDLState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UIPROJECT_NODL_H

/***********************************************************************************
*
*   GUI_UIPROJECT_NODL IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UIPROJECT_NODL_IMPLEMENTATION)

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
GuiUIProjectNoDLState InitGuiUIProjectNoDL(void)
{
    GuiUIProjectNoDLState state = { 0 };

    state.WindowBox000Active = true;
    state.ButtonEGBAPressed = false;
    state.ButtonHelpPressed = false;
    state.ButtonRunPressed = false;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 24, 80, 384, 600 };
    state.layoutRecs[2] = (Rectangle){ 552, 80, 384, 600 };
    state.layoutRecs[3] = (Rectangle){ 576, 96, 336, 480 };
    state.layoutRecs[4] = (Rectangle){ 904, 0, 24, 24 };
    state.layoutRecs[5] = (Rectangle){ 568, 632, 352, 32 };
    state.layoutRecs[6] = (Rectangle){ 24, 32, 384, 40 };
    state.layoutRecs[7] = (Rectangle){ 464, 384, 64, 24 };
    state.layoutRecs[8] = (Rectangle){ 32, 40, 368, 24 };

    // Custom variables initialization

    return state;
}

void GuiUIProjectNoDL(GuiUIProjectNoDLState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Project");
        GuiGroupBox(state->layoutRecs[1], "Debug");
        GuiGroupBox(state->layoutRecs[2], "Cartbridge");
        state->ButtonEGBAPressed = GuiButton(state->layoutRecs[3], "EGBA"); 
        state->ButtonHelpPressed = GuiButton(state->layoutRecs[4], "#193#");
        state->ButtonRunPressed = GuiButton(state->layoutRecs[5], "RUN"); 
        GuiGroupBox(state->layoutRecs[6], "Name");
        GuiLabel(state->layoutRecs[7], "Lock");
        GuiLabel(state->layoutRecs[8], state->LabelTextName);
    }
}

#endif // GUI_UIPROJECT_NODL_IMPLEMENTATION
