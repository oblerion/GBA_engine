/*******************************************************************************************
*
*   UIBrowser v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_UIBROWSER_IMPLEMENTATION
*       #include "gui_UIBrowser.h"
*
*       INIT: GuiUIBrowserState state = InitGuiUIBrowser();
*       DRAW: GuiUIBrowser(&state);
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

#ifndef GUI_UIBROWSER_H
#define GUI_UIBROWSER_H

typedef struct {
    int ListViewNameScrollIndex;
    int ListViewNameActive;
    bool ButtonConfigPressed;
    bool ButtonDocPressed;
    bool ButtonDeletePressed;
    bool ButtonLoadPressed;
    bool ButtonNewPressed;
    bool ButtonOpenDirPressed;

    Rectangle layoutRecs[11];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiUIBrowserState;

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
GuiUIBrowserState InitGuiUIBrowser(void);
void GuiUIBrowser(GuiUIBrowserState *state,const char* cstrn);

#ifdef __cplusplus
}
#endif

#endif // GUI_UIBROWSER_H

/***********************************************************************************
*
*   GUI_UIBROWSER IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_UIBROWSER_IMPLEMENTATION)

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
GuiUIBrowserState InitGuiUIBrowser(void)
{
    GuiUIBrowserState state = { 0 };

    state.ListViewNameScrollIndex = 0;
    state.ListViewNameActive = 0;
    state.ButtonConfigPressed = false;
    state.ButtonDocPressed = false;
    state.ButtonDeletePressed = false;
    state.ButtonLoadPressed = false;
    state.ButtonNewPressed = false;
    state.ButtonOpenDirPressed = false;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 960, 720 };
    state.layoutRecs[1] = (Rectangle){ 8, 48, 944, 664 };
    state.layoutRecs[2] = (Rectangle){ 40, 104, 712, 576 };
    state.layoutRecs[3] = (Rectangle){ 784, 16, 80, 24 };
    state.layoutRecs[4] = (Rectangle){ 880, 16, 72, 24 };
    state.layoutRecs[5] = (Rectangle){ 792, 168, 128, 40 };
    state.layoutRecs[6] = (Rectangle){ 40, 80, 712, 24 };
    state.layoutRecs[7] = (Rectangle){ 792, 104, 128, 40 };
    state.layoutRecs[8] = (Rectangle){ 376, 80, 120, 24 };
    state.layoutRecs[9] = (Rectangle){ 792, 232, 128, 40 };
    state.layoutRecs[10] = (Rectangle){ 688, 16, 80, 24 };

    // Custom variables initialization

    return state;
}

void GuiUIBrowser(GuiUIBrowserState *state,const char* cstrn)
{
    GuiPanel(state->layoutRecs[0], NULL);
    GuiGroupBox(state->layoutRecs[1], "UI Browser");
    GuiListView(state->layoutRecs[2], cstrn, &state->ListViewNameScrollIndex, &state->ListViewNameActive);
   	state->ButtonConfigPressed = GuiButton(state->layoutRecs[3], "#142#"); 
    state->ButtonDocPressed = GuiButton(state->layoutRecs[4], "doc"); 
    state->ButtonDeletePressed = GuiButton(state->layoutRecs[5], "#009#"); 
    GuiPanel(state->layoutRecs[6], NULL);
    state->ButtonLoadPressed = GuiButton(state->layoutRecs[7], "#013#"); 
    GuiLabel(state->layoutRecs[8], "Project");
    state->ButtonNewPressed = GuiButton(state->layoutRecs[9], "#008#"); 
    state->ButtonOpenDirPressed = GuiButton(state->layoutRecs[10], "#001#"); 
}

#endif // GUI_UIBROWSER_IMPLEMENTATION
