#include "ui_palette.hpp"
#include "ui_sprite.hpp"
#include "ui_mainbar.hpp"
int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 240*4; //GetMonitorWidth(0);
    const int screenHeight = 136*4;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    SetTargetFPS(50);   // Set our game to run at 60 frames-per-second
    //Font f = LoadFont(".ttf");
    UI_MainBar uibar(0,0);
    UI_Palette uipal;
    UI_Sprite uispr;
 // probl:load json more one element
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //if(IsKeyDown(KEY_S))
       
        BeginDrawing();
        ClearBackground(BLUE);
        // uibar.DropLoad(&uipal,&uispr);
        // uibar.Save(uipal,uispr);
        // uibar.Draw();
        // switch(uibar.GetState())
        // {
        //     case statepalette:   
        //         uipal.Draw();
        //     break;
        //     case statesprite:
                uispr.Draw();
        //     break;
        //     default:;
        // }
        EndDrawing();
    }
   // UnloadModel(model);
    CloseWindow();        // Close window and OpenGL
    return 0;
}

