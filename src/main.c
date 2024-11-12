#include "EGBA.h"
#include "Editor.h"
#include "Runner.h"
#include <stdio.h>

const char* GetEntryPoint()
{
    char str[50];
    FilePathList files = LoadDirectoryFiles(".");
    for(int i=0;i<files.count;i++)
    {
        if(TextIsEqual(GetFileExtension(files.paths[i]),".entry"))
        {
            strcpy(str,files.paths[i]);
            break;
        }
    }
    UnloadDirectoryFiles(files);
    return TextFormat("%s",str);
}
char EntryPoint(char* isrun)
{
   const char* sentry = GetEntryPoint();
    if(Runner_Load(
        TextFormat("%s.lua",
                    GetFileNameWithoutExt(sentry)))
    )
    {
        *isrun=1;
        return 1;
    }
    else if(Runner_Load(
        TextFormat("%s.egba",
                    GetFileNameWithoutExt(sentry))))
    {
        *isrun=1;
        return 1;
    }
    return 0;
}

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
    Music_Init();
    Music_LoadDir("asset");
    if(!EntryPoint(&isrun))
    {
        if(!Editor_Init(narg,sarg))
        {
            isrun=1;
            Runner_Init(narg,sarg);
        }
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
    Music_Free();
    CloseWindow();   // Close window and OpenGL
    return 0;
}
