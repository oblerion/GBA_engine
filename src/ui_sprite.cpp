#include "ui_sprite.hpp"

// void UI_Sprite::_DropLoad()
// {
//     if(IsFileDropped())
//     {
//         FilePathList files = LoadDroppedFiles();
//         for(int i=0;i<files.count;i++)
//         {
//             const char* ext = GetFileExtension(files.paths[i]);
//             if(TextIsEqual(ext,".dat"))
//             {
//                 struct sdata sdata;
//                 FILE* fic = fopen(files.paths[i],"rb");
//                 fread(&sdata,sizeof(struct sdata),1,fic);
//                 fclose(fic);
//                 //sdata.msprite
//                 sprman = SpriteManager(sdata.msprite);
//             }
//         }
//         UnloadDroppedFiles(files);
//     }
// }
UI_Sprite::UI_Sprite()
{
    int size = 16;
    for(int y=0;y<16;y++)
    for(int x=0;x<16;x++)
    {
        btnspr[(16*y)+x] = UI_BUTTON(x*(size*2),y*(size*2),TextFormat(" %3d ", (16*y)+x),size,BLACK); 
    }
}

UI_Sprite::~UI_Sprite()
{
}

Sprite UI_Sprite::Get(int id)
{
    return sprman.Get(id);
}

void UI_Sprite::Load(struct sdata sdata)
{
    sprman = SpriteManager(sdata.msprite);
}

void UI_Sprite::Load(const char *pfile)
{
}

void UI_Sprite::Save(struct sdata *sdata)
{
    sdata->msprite = sprman.GetStruct();
}

int UI_Sprite::Draw()
{
    int ret=0;
    for(int y=0;y<16;y++)
    for(int x=0;x<16;x++)
    {
        UI_BUTTON_draw(&btnspr[(16*y)+x]);
    }
    return ret;
}
