/*******************************************************************************************
*
*   UISprite v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UISPRITE_IMPLEMENTATION
*       #include "gui_UISprite.h"
*
*       INIT: GuiUISpriteState state = InitGuiUISprite();
*       DRAW: GuiUISprite(&state);
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

#ifndef GUI_UISPRITE_H
#define GUI_UISPRITE_H

typedef struct {
    bool WindowBox000Active;
    bool ButtonSavePressed;

    Rectangle layoutRecs[2];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUISpriteState;

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
GuiUISpriteState InitGuiUISprite(void);
void GuiUISprite(GuiUISpriteState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_UISPRITE_H

/***********************************************************************************
*
*   GUI_UISPRITE IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UISPRITE_IMPLEMENTATION)

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
GuiUISpriteState InitGuiUISprite(void)
{
    GuiUISpriteState state = { 0 };

    state.WindowBox000Active = true;
    state.ButtonSavePressed = false;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 896, 0, 32, 24 };

    // Custom variables initialization

    return state;
}

void GuiUISprite(GuiUISpriteState *state)
{
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], "UI Sprite");
        state->ButtonSavePressed = GuiButton(state->layoutRecs[1], "#002#"); 
    }
}

#endif // GUI_UISPRITE_IMPLEMENTATION
