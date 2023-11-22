#include "ui_palette.hpp"

// #include "raylib.h"
// #define RAYGUI_IMPLEMENTATION
// #include "raygui.h"
// int GuiButtonColor(Rectangle bounds, Color col)
// {
//     int result = 0;
//     GuiState state = guiState;

//     // Update control
//     //--------------------------------------------------------------------
//     if ((state != STATE_DISABLED) && !guiLocked && !guiSliderDragging)
//     {
//         Vector2 mousePoint = GetMousePosition();

//         // Check button state
//         if (CheckCollisionPointRec(mousePoint, bounds))
//         {
//             if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = STATE_PRESSED;
//             else state = STATE_FOCUSED;

//             if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) result = 1;
//         }
//     }
//     //--------------------------------------------------------------------

//     // Draw control
//     //--------------------------------------------------------------------
//     if(state == STATE_FOCUSED)
//         GuiDrawRectangle(bounds, 1, BLACK, {col.r,col.g,col.b,150});
//     else
//         GuiDrawRectangle(bounds, 1, BLACK, col);
//     if (state == STATE_FOCUSED) GuiTooltip(bounds);
//     //------------------------------------------------------------------

//     return result;      // Button pressed: result = 1
// }

void UI_Palette::_DropLoad()
{
    if(IsFileDropped())
    {
        FilePathList files = LoadDroppedFiles();
        for(unsigned int i=0;i<files.count;i++)
        {
            const char* ext = GetFileExtension(files.paths[i]);

            if(TextIsEqual(ext,".png"))
            {
                palman.Add(files.paths[i]);
            }
            else if(TextIsEqual(ext,".dat"))
            {
                struct sdata sdata;
                FILE* fic = fopen(files.paths[i],"rb");
                fread(&sdata,sizeof(struct sdata),1,fic);
                fclose(fic);
                palman.Clear();
                for(int j=0;j<5;j++)
                {
                    struct spalette pal = sdata.mpalette.list[j];
                    if(j<sdata.mpalette.nb_palette)
                    {
                        palman.Add(pal);
                    }
                }
            }
        }
        UnloadDroppedFiles(files);
    }
}

// void UI_Palette::_Save(const char *pfile)
// {
//     struct sdata sdata;
//     if(FileExists(pfile))
//     {   
//         FILE* fic = fopen(pfile,"rb");
//         fread(&sdata,sizeof(struct sdata),1,fic);
//         fclose(fic);
//     }
//     sdata.mpalette = palman.GetStruct();
//     FILE* fic = fopen(pfile,"wb");
//     fwrite(&sdata,sizeof(struct sdata),1,fic);
//     fclose(fic);
// }

UI_Palette::UI_Palette()
{
    btndelete = UI_BUTTON(19*32,0,"delete",18,BLACK);
    slider = UI_SLIDEBAR_V((float)GetScreenWidth()-20,10,5);
}


UI_Palette::~UI_Palette()
{

}

void UI_Palette::Load(const char *pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        palman.Add(pfile);
    }
}

void UI_Palette::Load(sdata sdata)
{
    palman.Clear();
    for(int j=0;j<5;j++)
    {
        struct spalette pal = sdata.mpalette.list[j];
        if(j<sdata.mpalette.nb_palette)
        {
            palman.Add(pal);
        }
    }
}

void UI_Palette::Save(sdata *sdata)
{
    sdata->mpalette = palman.GetStruct();
}

Palette UI_Palette::Get(int id)
{
    return palman.Get(id);
}

int UI_Palette::Draw()
{
    int ret=-1;
    const int yborder = 30;
    _DropLoad();
    // UI button,scroll

    if(palman.Size()>0)
    {
        UI_SLIDEBAR_V_draw(&slider);
        // idscroll = GuiScrollBar({(float)GetScreenWidth()-20,10,20,(float)GetScreenHeight()-20},idscroll,0,palman.Size());
        for(int j=slider.pos;j<palman.Size();j++)
        {
            int pos= j-slider.pos;
            if(pos<6 && pos>=0)
            {
                Palette cur_pal = palman.Get(j);
                cur_pal.Draw(23,yborder+23+(pos*45));
                DrawText(cur_pal.GetName().c_str(),5,yborder+(pos*45)+5,17,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(), {23,(float)yborder+23+(pos*45),32*20,20}))
                {
                    btndelete.y=yborder+21+(pos*45)+2;
                    if(UI_BUTTON_draw(&btndelete))
                    {
                        palman.Del(j);
                    }
                }
            }
        }
    }
    else
    {
        DrawText("Drop palette image file here",23,100,20,BLACK);
    }
    return ret;
}
