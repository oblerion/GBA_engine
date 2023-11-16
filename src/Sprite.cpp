#include "Sprite.hpp"

Sprite::Sprite()
{
    name = "sprite";
    pos.x = 0;
    pos.y = 0;
    size.x = 16;
    size.y = 16;
    for(int i=0;i<16;i++)
    {
        ldata.push_back(0);
    }
}

Sprite::Sprite(JsonObject json)
{
    size.x = json.GetInt("width");
    size.y = json.GetInt("height");
    name = json.GetString("name");
    ldata = json.GetArray("data");
}

Sprite::Sprite(const char *pfile, Palette pal)
{
    Image img;
    pos.x = 0;
    pos.y = 0;
    const char* cext = GetFileExtension(pfile);
    name = GetFileNameWithoutExt(pfile);
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

Sprite::~Sprite()
{
    ldata.clear();
    UnloadTexture(texture);
}

JsonObject Sprite::GetJson()
{
    JsonObject jspr;
    jspr.SetInt("width",size.x);
    jspr.SetInt("height",size.y);
    jspr.SetString("name",name);
    jspr.SetArray("data",ldata);
    return jspr;
}

void Sprite::SetData(int x, int y, Color col)
{
    ldata[(y*size.x)+x]=ColorToInt(col);
}

void Sprite::UpdateTexture()
{

}
