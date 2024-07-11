#include "EGBA.h"
#include "Editor.h"
#include "Runner.h"

int main(int narg,char** sarg)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = (720*4)/3; //GetMonitorWidth(0);
    const int screenHeight = 720;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, EGBA_TITLE);
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    char isrun = 0;

    if(!Editor_Init(narg,sarg))
    {
        isrun=1;
        Runner_Init(narg,sarg);
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        if(isrun==0)
            Editor_Draw();
        else
            Runner_Draw();
        EndDrawing();
    }
    Editor_Free();
    Runner_Free();
    CloseWindow();        // Close window and OpenGL
    return 0;
}
