#include "raylib.h"
#include "ui_palette.h"
#include "ui_sprite.h"
#include "ui_mainbar.h"
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 240*4; //GetMonitorWidth(0);
    const int screenHeight = 136*4;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(50);   // Set our game to run at 60 frames-per-second
    struct UI_MainBar uibar = UI_MainBar(0,0);
    struct UI_Palette uipal = UI_Palette();
    struct UI_Sprite uispr = UI_Sprite();
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);
        UI_MainBar_DropLoad(&uibar,&uipal,&uispr);
        UI_MainBar_Save(&uibar,uipal,uispr);
        UI_MainBar_Draw(&uibar);
        switch(UI_MainBar_GetState(uibar))
        {
            case statepalette:   
                UI_Palette_Draw(&uipal);
            break;
            case statesprite:
                UI_Sprite_Draw(uispr);
            break;
            default:;
        }
        EndDrawing();
    }
    UI_Palette_Free(&uipal);
    CloseWindow();        // Close window and OpenGL
    return 0;
}

