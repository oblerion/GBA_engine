#include "raylib.h"
#include "ui_palette.h"
#include "ui_sprite.h"
#include "ui_script.h"
#include "ui_runner.h"
#include "ui_mainbar.h"
// #include "Sprite.h"
int main(int narg,char** sarg)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = (720*4)/3; //GetMonitorWidth(0);
    const int screenHeight = 720;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "GBA engine ver a0.1 by oblerion");
    bool runnermode=false;
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    
    struct UI_MainBar uibar;
    struct UI_Palette uipal;
    struct UI_Sprite uispr;
    struct UI_Script uiscr;
    if(narg==1)
    {
        uibar=UI_MainBar(0,0);
        uipal=UI_Palette();
        uispr=UI_Sprite();
        uiscr=UI_Script();
        struct sdata sdata;
        int size = GetFileLength(sarg[0]);
        if(!TextIsEqual( GetFileNameWithoutExt(sarg[0]) ,"egba"))
        {
            FILE* fic = fopen(sarg[0],"rb");
            if(fic!=NULL)
            {
                fseek(fic,size-sizeof(struct sdata),0);
                fread(&sdata,sizeof(struct sdata),1,fic);
                fclose(fic);
                UI_Runner();
                UI_Runner_LoadD(sdata);
                runnermode=true;
            }
        }
    }
    else if(narg==2)
    {
        UI_Runner();
        UI_Runner_Load(sarg[1]);
    }
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);
        if(narg==1 && runnermode==false)
        {
            UI_MainBar_DropLoad(&uibar,&uipal,&uispr,&uiscr);
            UI_MainBar_Save(&uibar,uipal,uispr,uiscr);
            UI_MainBar_Draw(&uibar);
            if(uibar.isUpdate)
            {
                UI_Sprite_LoadPalette(&uispr,uipal);
            }
            if(IsKeyDown(KEY_RIGHT_CONTROL) &&
                IsKeyPressed(KEY_B))
            {
                UI_MainBar_Build(&uibar,sarg[0]);
            }

            switch(UI_MainBar_GetState(uibar))
            {
                case statepalette:   
                    UI_Palette_Draw(&uipal);
                break;
                case statesprite:
                    UI_Sprite_Draw(&uispr,uipal);
                break;
                case statescript:
                    UI_Script_Draw(uiscr);
                default:;
            }
        }
        else if(narg==2 || runnermode==true)
        {
            UI_Runner_Draw();
        }
        EndDrawing();
    }

    if(narg==1 && runnermode==false)
    {
        UI_Palette_Free(uipal);
        UI_Sprite_Free(uispr);
    }
    else if(narg==2 || runnermode==true)
    {
        UI_Runner_Free();
    }
    CloseWindow();        // Close window and OpenGL
    return 0;
}

