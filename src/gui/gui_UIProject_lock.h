/*******************************************************************************************
*
*   UIProjectLock v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UIPROJECT_LOCK_IMPLEMENTATION
*       #include "gui_UIProject_lock.h"
*
*       INIT: GuiUIProjectLockState state = InitGuiUIProjectLock();
*       DRAW: GuiUIProjectLock(&state);
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

#ifndef GUI_UIPROJECT_LOCK_H
#define GUI_UIPROJECT_LOCK_H

typedef struct {
    bool WindowBox000Active;
    bool ButtonLuaPressed;
    bool ButtonSpritePressed;
    bool ButtonEGBAPressed;
    bool ButtonLoadPressed;
    bool ButtonHelpPressed;
    bool ButtonDebugPressed;
    bool ButtonRunPressed;
    char LabelTextName[50];

    Rectangle layoutRecs[13];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIProjectLockState;

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
GuiUIProjectLockState InitGuiUIProjectLock(void);
void GuiUIProjectLock(GuiUIProjectLockState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UIPROJECT_LOCK_H

/***********************************************************************************
*
*   GUI_UIPROJECT_LOCK IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UIPROJECT_LOCK_IMPLEMENTATION)

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
GuiUIProjectLockState InitGuiUIProjectLock(void)
{
    GuiUIProjectLockState state = { 0 };

    state.WindowBox000Active = true;
    state.ButtonLuaPressed = false;
    state.ButtonSpritePressed = false;
    state.ButtonEGBAPressed = false;
    state.ButtonLoadPressed = false;
    state.ButtonHelpPressed = false;
    state.ButtonDebugPressed = false;
    state.ButtonRunPressed = false;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 24, 80, 384, 600 };
    state.layoutRecs[2] = (Rectangle){ 552, 80, 384, 600 };
    state.layoutRecs[3] = (Rectangle){ 48, 96, 336, 208 };
    state.layoutRecs[4] = (Rectangle){ 48, 368, 336, 208 };
    state.layoutRecs[5] = (Rectangle){ 576, 96, 336, 480 };
    state.layoutRecs[6] = (Rectangle){ 432, 256, 96, 48 };
    state.layoutRecs[7] = (Rectangle){ 904, 0, 24, 24 };
    state.layoutRecs[8] = (Rectangle){ 48, 632, 336, 32 };
    state.layoutRecs[9] = (Rectangle){ 568, 632, 352, 32 };
    state.layoutRecs[10] = (Rectangle){ 24, 32, 384, 40 };
    state.layoutRecs[11] = (Rectangle){ 464, 384, 64, 24 };
    state.layoutRecs[12] = (Rectangle){ 32, 40, 368, 24 };

    // Custom variables initialization

    return state;
}

void GuiUIProjectLock(GuiUIProjectLockState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Project");
        GuiGroupBox(state->layoutRecs[1], "Debug");
        GuiGroupBox(state->layoutRecs[2], "Cartbridge");
        state->ButtonLuaPressed = GuiButton(state->layoutRecs[3], "LUA"); 
        state->ButtonSpritePressed = GuiButton(state->layoutRecs[4], "SPRITE"); 
        state->ButtonEGBAPressed = GuiButton(state->layoutRecs[5], "EGBA"); 
        state->ButtonLoadPressed = GuiButton(state->layoutRecs[6], "#119#"); 
        state->ButtonHelpPressed = GuiButton(state->layoutRecs[7], "#193#"); 
        state->ButtonDebugPressed = GuiButton(state->layoutRecs[8], "DEBUG"); 
        state->ButtonRunPressed = GuiButton(state->layoutRecs[9], "RUN"); 
        GuiGroupBox(state->layoutRecs[10], "Name");
        GuiLabel(state->layoutRecs[11], "Lock");
        GuiLabel(state->layoutRecs[12], state->LabelTextName);
    }
}

#endif // GUI_UIPROJECT_LOCK_IMPLEMENTATION
