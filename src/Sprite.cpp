#include "Sprite.hpp"

Sprite::Sprite(const char* pfile,Palette pal)
{
    Image img;
    const char* cext = GetFileExtension(pfile);
    if(TextIsEqual(cext,".png"))
    {
        img = LoadImage(pfile);
        Color* lcol = (Color*)img.data;
        for(int i=0;i<img.width*img.height;i++)
        {
            int icol = ColorToInt(lcol[i]);
            // compare id -> get list color
            for(int j=0;j<pal.Size();j++)
            {
                
            }
        }
        UnloadImage(img);
    }
}

Sprite::~Sprite()
{
    UnloadTexture(texture);
}

JsonObject Sprite::GetJson(const char *pfile)
{
    return JsonObject();
}
