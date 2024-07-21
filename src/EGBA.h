#pragma once
#include <string.h>
#include "raylib.h"
#define EGBA_VERSION "a1.7"
#define EGBA_TITLE TextFormat("GBA engine ver %s by magnus oblerion",EGBA_VERSION)

#define EGBA_RUN_NAME "egba"
#define EGBA_EDIT_NAME "egba"

#define EGBA_MAX_PROJECT 100
#define EGBA_MAX_COLOR_PALETTE 32
#define EGBA_MAX_COLOR_SPRITE 256
#define EGBA_MAX_SPRITE 256
#define EGBA_MAX_PALETTE 5
#define EGBA_MAX_SCRIPTSIZE 64000

#define SAVING_MAX_BOOL 100
#define SAVING_MAX_NUMBER 50
#define SAVING_MAX_STRING 50

char UICONFIG_Timer();
Color UICONFIG_COL1();
Color UICONFIG_COL2();
char UICONFIG_GetActive();
void UICONFIG_SetActive(char c);
void UICONFIG_SetYellowTheme();
void UICONFIG_SetGreenTheme();
void UICONFIG_SetRedTheme();
void UICONFIG_SetBlueTheme();
void UICONFIG_SetWhiteTheme();
void UICONFIG_SetBlackTheme();
void UICONFIG_Save();
void UICONFIG_Load();

struct Palette
{
    char name[35];
    Color data[EGBA_MAX_COLOR_PALETTE];
};

struct Palette PaletteF(const char *pfile);
Image Palette_GetImg(struct Palette pal);

struct Sprite
{
    int width;
    int height;
    Color data[EGBA_MAX_COLOR_SPRITE];
};

struct Sprite Sprite();
void Sprite_SetData(struct Sprite* spr,int x,int y,Color col);
Image Sprite_GetImg(struct Sprite spr);

struct segba_saving
{
    char bools[SAVING_MAX_BOOL];
    int numbs[SAVING_MAX_NUMBER];
    char strs[SAVING_MAX_STRING][35];
};
struct segba_saving Saving_Get();
void Saving_Set(struct segba_saving saving);
void Saving_LoadSave(const char* name);
void Saving_WriteSave(const char* name,struct segba_saving saving);

struct segba_data
{
    struct Palette palettes[EGBA_MAX_PALETTE];
    int palette_nb;
    struct Sprite sprites[EGBA_MAX_SPRITE];
    char script[EGBA_MAX_SCRIPTSIZE];
    char islock;
};

struct segba_atlas
{
    Texture2D sprites;
    Texture2D palettes;
};

void Data_Palette_Init();
void Data_Palette_LoadF(const char* pfile);
void Data_Palette_LoadD(struct segba_data sdata);
void Data_Palette_DelPal(int id);
int Data_Palette_GetNd();
const char* Data_Palette_GetName(int n);
struct Palette Data_Palette_Get(int n);
void Data_Sprite_Init();
void Data_Sprite_LoadF(const char *pfile);
void Data_Sprite_LoadD(struct segba_data sdata);
struct Sprite Data_Sprite_Get(int id);
void Data_Script_Init();
void Data_Script_LoadF(const char* pfile);
void Data_Script_LoadD(struct segba_data sdata);
void Data_Script_Draw(int x,int y,Color color);
void Data_BuildEgba(const char* sfegba,char lock);
void Data_ExportSprite(const char* sfsprite);
void Data_ExportScript(const char* sfscript);

void Atlas_Init();
void Atlas_UpdatePalette(struct Palette* palettes);
void Atlas_UpdateSprite(struct Sprite* sprites);
void Atlas_DrawPalette(int id, int x, int y, int scale);
void Atlas_DrawSprite(int id,int x,int y,int scale);
void Atlas_Free();
