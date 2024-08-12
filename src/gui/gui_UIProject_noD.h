/*******************************************************************************************
*
*   UIProjectNoD v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UIPROJECT_NOD_IMPLEMENTATION
*       #include "gui_UIProject_noD.h"
*
*       INIT: GuiUIProjectNoDState state = InitGuiUIProjectNoD();
*       DRAW: GuiUIProjectNoD(&state);
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

#ifndef GUI_UIPROJECT_NOD_H
#define GUI_UIPROJECT_NOD_H

typedef struct {
    bool WindowBox000Active;
    bool TextBoxNameEditMode;
    char TextBoxNameText[128];
    bool ButtonEGBAPressed;
    bool ButtonImportPressed;
    bool ButtonHelpPressed;
    bool ButtonRunPressed;

    Rectangle layoutRecs[9];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIProjectNoDState;

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
GuiUIProjectNoDState InitGuiUIProjectNoD(void);
void GuiUIProjectNoD(GuiUIProjectNoDState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UIPROJECT_NOD_H

/***********************************************************************************
*
*   GUI_UIPROJECT_NOD IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UIPROJECT_NOD_IMPLEMENTATION)

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
GuiUIProjectNoDState InitGuiUIProjectNoD(void)
{
    GuiUIProjectNoDState state = { 0 };

    state.WindowBox000Active = true;
    state.TextBoxNameEditMode = false;
    strcpy(state.TextBoxNameText, "Name");
    state.ButtonEGBAPressed = false;
    state.ButtonImportPressed = false;
    state.ButtonHelpPressed = false;
    state.ButtonRunPressed = false;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 32, 40, 368, 24 };
    state.layoutRecs[2] = (Rectangle){ 24, 80, 384, 600 };
    state.layoutRecs[3] = (Rectangle){ 552, 80, 384, 600 };
    state.layoutRecs[4] = (Rectangle){ 576, 96, 336, 480 };
    state.layoutRecs[5] = (Rectangle){ 432, 368, 96, 48 };
    state.layoutRecs[6] = (Rectangle){ 904, 0, 24, 24 };
    state.layoutRecs[7] = (Rectangle){ 568, 632, 352, 32 };
    state.layoutRecs[8] = (Rectangle){ 24, 32, 384, 40 };

    // Custom variables initialization

    return state;
}

void GuiUIProjectNoD(GuiUIProjectNoDState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Project");
        if (GuiTextBox(state->layoutRecs[1], state->TextBoxNameText, 128, state->TextBoxNameEditMode)) state->TextBoxNameEditMode = !state->TextBoxNameEditMode;
        GuiGroupBox(state->layoutRecs[2], "Debug");
        GuiGroupBox(state->layoutRecs[3], "Cartbridge");
        state->ButtonEGBAPressed = GuiButton(state->layoutRecs[4], "EGBA"); 
        state->ButtonImportPressed = GuiButton(state->layoutRecs[5], "<- import -"); 
        state->ButtonHelpPressed = GuiButton(state->layoutRecs[6], "?"); 
        state->ButtonRunPressed = GuiButton(state->layoutRecs[7], "RUN"); 
        GuiGroupBox(state->layoutRecs[8], "Name");
    }
}

#endif // GUI_UIPROJECT_NOD_IMPLEMENTATION
