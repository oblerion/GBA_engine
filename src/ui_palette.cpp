#include "ui_palette.hpp"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
int GuiButtonColor(Rectangle bounds, Color col)
{
    int result = 0;
    GuiState state = guiState;

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && !guiLocked && !guiSliderDragging)
    {
        Vector2 mousePoint = GetMousePosition();

        // Check button state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = STATE_PRESSED;
            else state = STATE_FOCUSED;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) result = 1;
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    if(state == STATE_FOCUSED)
        GuiDrawRectangle(bounds, 1, BLACK, {col.r,col.g,col.b,150});
    else
        GuiDrawRectangle(bounds, 1, BLACK, col);
    if (state == STATE_FOCUSED) GuiTooltip(bounds);
    //------------------------------------------------------------------

    return result;      // Button pressed: result = 1
}

UI_Palette::UI_Palette(std::vector<std::string> lstfile)
{
    for(int i=0;i<lstfile.size();i++)
    {
        palman.Add(lstfile[i].c_str());
    }
}

UI_Palette::~UI_Palette()
{

}

void UI_Palette::Draw()
{
    for(int j=0;j<palman.Size();j++)
    {
        Palette cur_pal = palman.Get(j);
        cur_pal.Draw(23,23+(j*45));
        DrawText(cur_pal.GetName().c_str(),5,(j*45)+5,17,BLACK);
    }
}
