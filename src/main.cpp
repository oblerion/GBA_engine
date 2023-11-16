#include "raylib.h"
#include "ui_palette.hpp"

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 240*3; //GetMonitorWidth(0);
    const int screenHeight = 160*3;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //Font f = LoadFont(".ttf");
    UI_Palette uipal({"asset/nanner-32-1x.png","asset/sheltzy32-1x.png"});
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //if(IsKeyDown(KEY_S))
       
        BeginDrawing();
        ClearBackground(BLUE);
        uipal.Draw();
        
        EndDrawing();
    }
   // UnloadModel(model);
    CloseWindow();        // Close window and OpenGL
    return 0;
}

