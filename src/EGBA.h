#pragma once
#include <string.h>
#include "raylib.h"
#define EGBA_VERSION "a1.8"
#define EGBA_TITLE TextFormat("EGBA engine ver %s by magnus oblerion",EGBA_VERSION)

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
char UICONFIG_GetActive();
void UICONFIG_SetActive(char c);
void UICONFIG_SetTheme(int itheme);
int UICONFIG_GetTheme();
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
const char* Data_Script_Get();
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
void Atlas_DrawSprite(int id,int x,int y,int scale,int rot);
void Atlas_Free();

#define EGBA_MAX_SOUND 20
#define EGBA_MAX_MUSIC 20
struct segba_music
{
    Sound sounds[EGBA_MAX_SOUND];
    char sounds_name[EGBA_MAX_SOUND][35];
    Music musics[EGBA_MAX_MUSIC];
    char musics_name[EGBA_MAX_MUSIC][35];
    int music_id_play;
};
void Music_Init();
int Music_GetNewSound();
int Music_GetNewMusic();
void Music_LoadSound(const char* ssound);
void Music_LoadMusic(const char* smusic);
void Music_PlaySound(const char* sid);
void Music_PlaySound_id(int i);
void Music_PlayMusic(const char* sid);
void Music_PlayMusic_id(int i);
void Music_UpdateMusic();
void Music_PauseMusic();
void Music_StopMusic();
void Music_Free();
void Music_LoadDir(const char* sdir);
// Music m = LoadMusicStream();
// Sound s = LoadSoundFromWave()
