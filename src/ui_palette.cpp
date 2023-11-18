#include "ui_palette.hpp"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
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
            puts(files.paths[i]);
            palman.Add(files.paths[i]);
        }
        UnloadDroppedFiles(files);
    }
}

UI_Palette::UI_Palette()
{
    idscroll=0;
}

UI_Palette::UI_Palette(std::vector<std::string> lstfile)
{
    idscroll=0;
    for(int i=0;i<lstfile.size();i++)
    {
        palman.Add(lstfile[i].c_str());
    }
}

UI_Palette::~UI_Palette()
{

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
    if(GuiButton({5,5,50,30},"back"))
    {
        return 1;
    }
    

    if(palman.Size()>0)
    {
        idscroll = GuiScrollBar({(float)GetScreenWidth()-20,10,20,(float)GetScreenHeight()-20},idscroll,0,palman.Size());
        for(int j=idscroll;j<palman.Size();j++)
        {
            int pos= j-idscroll;
            if(pos<6 && pos>=0)
            {
                Palette cur_pal = palman.Get(j);
                cur_pal.Draw(23,yborder+23+(pos*45));
                DrawText(cur_pal.GetName().c_str(),5,yborder+(pos*45)+5,17,BLACK);
                if(CheckCollisionPointRec(GetMousePosition(), {23,(float)yborder+23+(pos*45),32*20,20}))
                {
                    if(GuiButton({(20*32),(float)yborder+21+(pos*45),45,25},"delete"))
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
