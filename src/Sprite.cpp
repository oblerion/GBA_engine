#include "Sprite.hpp"

Sprite::Sprite()
{
    palette_id=0;
    pos.x = 0;
    pos.y = 0;
    size.x = 16;
    size.y = 16;
    for(int i=0;i<size.x*size.y;i++)
    {
        ldata.push_back(0);
    }
}

Sprite::Sprite(const char *pfile, Palette pal)
{
    Image img;
    pos.x = 0;
    pos.y = 0;
    const char* cext = GetFileExtension(pfile);
    if(TextIsEqual(cext,".png"))
    {
        img = LoadImage(pfile);
        size.x = img.width;
        size.y = img.height;
        Color* lcol = (Color*)img.data;
        for(int i=0;i<img.width*img.height;i++)
        {
            int icol = ColorToInt(lcol[i]);
            // compare id -> get list color
            for(int j=0;j<pal.Size();j++)
            {
                if(pal.GetHexa(j)==icol)
                {
                    ldata.push_back(j);
                    break;
                }
                else if(j==pal.Size()-1)
                {
                    ldata.push_back(0);
                }
            }
        }
        UnloadImage(img);
    }
}

Sprite::Sprite(struct ssprite ssprite)
{
    size.x = ssprite.width;
    size.y = ssprite.height;
    pos.x=0;
    pos.y=0;
    ldata.clear();
    for(int i=0;i<ssprite.width*ssprite.height;i++)
    {
        ldata.push_back(ssprite.data[i]);
    }
}

Sprite::~Sprite()
{
    ldata.clear();
    // UnloadTexture(texture);
}


void Sprite::SetData(int x, int y, Color col)
{
    ldata[(y*size.x)+x]=ColorToInt(col);
}

struct ssprite Sprite::GetStruct()
{
    struct ssprite ssprite;
    ssprite.width=size.x;
    ssprite.height=size.y;
    
    for(int i=0;i<(signed int)ldata.size();i++)
    {
        ssprite.data[i]=ldata[i];
    }

    return ssprite;

}

