#pragma once
#include "raylib.h"
#define EGBA_VERSION "a1.5-2"
#define EGBA_TITLE TextFormat("GBA engine ver %s by magnus oblerion",EGBA_VERSION)

#define EGBA_RUN_NAME "egba"
#define EGBA_EDIT_NAME "egba"

#define EGBA_MAX_PROJECT 100
#define EGBA_MAX_COLOR_PALETTE 32
#define EGBA_MAX_COLOR_SPRITE 256
#define EGBA_MAX_SPRITE 256
#define EGBA_MAX_PALETTE 5
#define EGBA_MAX_SCRIPTSIZE 64000

#define SAVING_MAX_BOOL 20
#define SAVING_MAX_NUMBER 20
#define SAVING_MAX_STRING 10

struct Palette
{
    char name[35];
    Color data[EGBA_MAX_COLOR_PALETTE];
};

struct Sprite
{
    int width;
    int height;
    Color data[EGBA_MAX_COLOR_SPRITE];
};

struct segba_saving
{
    char bools[SAVING_MAX_BOOL];
    int numbs[SAVING_MAX_NUMBER];
    char strs[SAVING_MAX_STRING][35];
};

struct segba_data
{
    // char palette_name[EGBA_MAX_PALETTE][35];
    // Color palette_data[EGBA_MAX_PALETTE*EGBA_MAX_COLOR_PALETTE];
    struct Palette palettes[EGBA_MAX_PALETTE];
    int palette_nb;
    struct Sprite sprites[EGBA_MAX_SPRITE];
    // char sprite_mapid[EGBA_MAX_SPRITE][EGBA_MAX_COLOR_SPRITE];
    char script[EGBA_MAX_SCRIPTSIZE];
    char islock;
    struct segba_saving saving;
};

struct segba_atlas
{
    Texture2D sprites;
    Texture2D palettes;
};
