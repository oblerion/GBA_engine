#include "ui_mainbar.hpp"

UI_MainBar::UI_MainBar(int x,int y)
{
    btnpal = UI_BUTTON(x+5,y+5,"palette",20,BLACK);
    btnspr = UI_BUTTON(x+88,y+5,"sprite",20,BLACK);
    btnsave = UI_BUTTON(x+160,y+5,"save",20,BLACK);
    state=statepalette;
    issave=false;
}

UI_MainBar::~UI_MainBar()
{
}

UISTATE UI_MainBar::GetState()
{
    return state;
}

void UI_MainBar::DropLoad(UI_Palette *uipal, UI_Sprite *uispr)
{
    if(IsFileDropped())
    {
        FilePathList files = LoadDroppedFiles();
        for(int i=0;i<files.count;i++)
        {
            const char* ext = GetFileExtension(files.paths[i]);
            if(TextIsEqual(ext,".dat"))
            {
                struct sdata sdata;
                FILE* fic = fopen(files.paths[i],"rb");
                fread(&sdata,sizeof(struct sdata),1,fic);
                fclose(fic);
                uipal->Load(sdata);
                uispr->Load(sdata);
            }
            else if(TextIsEqual(ext,".png"))
            {
                switch(state)
                {
                    case statepalette:
                       uipal->Load(files.paths[i]);
                    break;
                    case statesprite:
                    break;
                    default:;
                }
            }
        }
        UnloadDroppedFiles(files);
    }
}

void UI_MainBar::Save(UI_Palette uipal, UI_Sprite uispr)
{
    if(issave)
    {
        struct sdata sdata;
        uipal.Save(&sdata);
        uispr.Save(&sdata);
        FILE* fic = fopen("save.dat","wb");
        fwrite(&sdata,sizeof(struct sdata),1,fic);
        fclose(fic);
        issave=false;
    }
}

void UI_MainBar::Draw()
{
    if(state==statepalette)
        DrawRectangle(btnpal.x-4,btnpal.y-2,btnpal.width,btnpal.height,WHITE);
    if(state==statesprite)
        DrawRectangle(btnspr.x-4,btnspr.y-2,btnspr.width,btnspr.height,WHITE);
    if(UI_BUTTON_draw(&btnpal))
        state=statepalette;
    if(UI_BUTTON_draw(&btnspr))
        state=statesprite;
    if(UI_BUTTON_draw(&btnsave))
        issave=true;
}
