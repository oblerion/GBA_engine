#include "egba.h"
#include "ui_runner.h"
struct EGBA EGBA_Init(int narg, char **sarg)
{
    Atlas_Init();
    struct EGBA egba = (struct EGBA){false};
    if(narg==1)
    {
        if(TextIsEqual( GetFileNameWithoutExt(sarg[0]) ,"egba"))
        {// init editor
            egba.uibar= UI_MainBar(0,0);
            egba.uipal= UI_Palette(12);
            egba.uispr= UI_Sprite();
            egba.uiscr= UI_Script();
        }
        else 
        {// run game
            int size = GetFileLength(sarg[0]);
            FILE* fic = fopen(sarg[0],"rb");
            struct sdata sdata;
            if(fic!=NULL)
            {
                fseek(fic,size-sizeof(struct sdata),0);
                fread(&sdata,sizeof(struct sdata),1,fic);
                fclose(fic);
                UI_Runner();
                UI_Runner_LoadD(sdata);
            }
            egba.ifrunner = true;
        }
    }
    else if(narg==2)
    {
        if(UI_Runner_Load(sarg[1]))
        // runner init 
            egba.ifrunner = true;
        else
        {// runner fail -> init editor
            puts("error : runner fail");
            egba.uibar= UI_MainBar(0,0);
            egba.uipal= UI_Palette(12);
            egba.uispr= UI_Sprite();
            egba.uiscr= UI_Script();
        }
    }
    return egba;
}

void EGBA_Draw(struct EGBA *egba)
{
    if(egba->ifrunner==false)
    {// editor update/draw
        UI_MainBar_DropLoad(
            &egba->uibar,
            &egba->uipal,
            &egba->uispr,
            &egba->uiscr);
        UI_MainBar_Save(
            &egba->uibar,
            egba->uipal,
            egba->uispr,
            egba->uiscr);
        UI_MainBar_Draw(&egba->uibar);
    
        if(IsKeyDown(KEY_RIGHT_CONTROL) &&
            IsKeyPressed(KEY_B))
        {
            UI_MainBar_Build(&egba->uibar);
        }

        switch(UI_MainBar_GetState(egba->uibar))
        {
            case statesprite:
                UI_MainBar_ExportSprite(
                    egba->uibar,
                    egba->uispr,
                    egba->uipal);
                UI_Sprite_Draw(&egba->uispr,egba->uipal);
                UI_Palette_Draw(&egba->uipal,0,430,12);
            break;
            case statescript:
                UI_Script_Draw(egba->uiscr);
            default:;
        }
    }
    else if(egba->ifrunner==true)
    {// runner draw
        UI_Runner_Draw();
    }
}

void EGBA_Free(struct EGBA *egba)
{
    if(egba->ifrunner==false)
    {// free editor
        Atlas_Free();
    }
    else if(egba->ifrunner==true)
    {// free runner / game
        UI_Runner_Free();
    }

}
