#include "raylib.h"
#include "cimg.h"
#include "egba.h"
int main(int narg,char** sarg)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = (720*4)/3; //GetMonitorWidth(0);
    const int screenHeight = 720;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "GBA engine ver a0.1-2 by oblerion");
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    SetWindowIcon(icon);    

    struct EGBA egba = EGBA_Init(narg,sarg);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);
        EGBA_Draw(&egba);
        EndDrawing();
    }
    
    EGBA_Free(&egba);
    CloseWindow();        // Close window and OpenGL
    return 0;
}

