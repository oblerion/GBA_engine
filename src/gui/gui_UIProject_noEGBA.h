/*******************************************************************************************
*
*   UIProjectNoEGBA v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UIPROJECT_NOEGBA_IMPLEMENTATION
*       #include "gui_UIProject_noEGBA.h"
*
*       INIT: GuiUIProjectNoEGBAState state = InitGuiUIProjectNoEGBA();
*       DRAW: GuiUIProjectNoEGBA(&state);
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

#ifndef GUI_UIPROJECT_NOEGBA_H
#define GUI_UIPROJECT_NOEGBA_H

typedef struct {
    bool WindowBox000Active;
    bool TextBoxNameEditMode;
    char TextBoxNameText[128];
    bool ButtonLuaPressed;
    bool ButtonSpritePressed;
    bool ButtonLoadPressed;
    bool ButtonHelpPressed;
    bool ButtonDebugPressed;

    Rectangle layoutRecs[10];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIProjectNoEGBAState;

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
GuiUIProjectNoEGBAState InitGuiUIProjectNoEGBA(void);
void GuiUIProjectNoEGBA(GuiUIProjectNoEGBAState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UIPROJECT_NOEGBA_H

/***********************************************************************************
*
*   GUI_UIPROJECT_NOEGBA IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UIPROJECT_NOEGBA_IMPLEMENTATION)

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
GuiUIProjectNoEGBAState InitGuiUIProjectNoEGBA(void)
{
    GuiUIProjectNoEGBAState state = { 0 };

    state.WindowBox000Active = true;
    state.TextBoxNameEditMode = false;
    strcpy(state.TextBoxNameText, "Name");
    state.ButtonLuaPressed = false;
    state.ButtonSpritePressed = false;
    state.ButtonLoadPressed = false;
    state.ButtonHelpPressed = false;
    state.ButtonDebugPressed = false;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 32, 40, 368, 24 };
    state.layoutRecs[2] = (Rectangle){ 24, 80, 384, 600 };
    state.layoutRecs[3] = (Rectangle){ 552, 80, 384, 600 };
    state.layoutRecs[4] = (Rectangle){ 48, 96, 336, 208 };
    state.layoutRecs[5] = (Rectangle){ 48, 368, 336, 208 };
    state.layoutRecs[6] = (Rectangle){ 432, 256, 96, 48 };
    state.layoutRecs[7] = (Rectangle){ 904, 0, 24, 24 };
    state.layoutRecs[8] = (Rectangle){ 48, 632, 336, 32 };
    state.layoutRecs[9] = (Rectangle){ 24, 32, 384, 40 };

    // Custom variables initialization

    return state;
}

void GuiUIProjectNoEGBA(GuiUIProjectNoEGBAState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Project");
        if (GuiTextBox(state->layoutRecs[1], state->TextBoxNameText, 128, state->TextBoxNameEditMode)) state->TextBoxNameEditMode = !state->TextBoxNameEditMode;
        GuiGroupBox(state->layoutRecs[2], "Debug");
        GuiGroupBox(state->layoutRecs[3], "Cartbridge");
        state->ButtonLuaPressed = GuiButton(state->layoutRecs[4], "LUA"); 
        state->ButtonSpritePressed = GuiButton(state->layoutRecs[5], "SPRITE"); 
        state->ButtonLoadPressed = GuiButton(state->layoutRecs[6], "#119#");//""- load ->"); 
        state->ButtonHelpPressed = GuiButton(state->layoutRecs[7], "#193#");//"?"); 
        state->ButtonDebugPressed = GuiButton(state->layoutRecs[8], "DEBUG"); 
        GuiGroupBox(state->layoutRecs[9], "Name");
    }
}

#endif // GUI_UIPROJECT_NOEGBA_IMPLEMENTATION
