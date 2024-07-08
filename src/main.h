#pragma once
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cimg.h"

#include "EGBA.h"

struct Palette
{
    char name[35];
    Color data[EGBA_MAX_COLOR_PALETTE];
};


struct Sprite
{
    int width;
    int height;
    Color data[256];
};

#define SAVING_MAX_BOOL 20
#define SAVING_MAX_NUMBER 20
#define SAVING_MAX_STRING 10
struct ssaving
{
    char bools[SAVING_MAX_BOOL];
    int numbs[SAVING_MAX_NUMBER];
    char strs[SAVING_MAX_STRING][35];
};
struct sdata
{
    char palette_name[EGBA_MAX_PALETTE][35];
    Color palette_data[EGBA_MAX_PALETTE*EGBA_MAX_COLOR_PALETTE];
    int palette_nb;
    char sprite_mapid[EGBA_MAX_SPRITE][EGBA_MAX_COLOR_SPRITE];
    char script[EGBA_MAX_SCRIPTSIZE];
    char islock;
    struct ssaving saving;
};

struct UI_SLIDEBAR_V
{
    int x;
    int y;
    int size_cursor;
    int nb_pos_max;
    int pos;
    Color color;
    int width;
    int height;
    bool visible;
};

struct satlas
{
    Texture2D sprites;
    Texture2D palettes;
}Atlas;

struct UI_BUTTONSPRITE
{
    int x;
    int y;
    int scale;
    int id_sprite;
    bool visible;
};

struct UI_Sprite
{
    Texture2D sprfond;
    struct UI_BUTTONSPRITE btnspr[EGBA_MAX_SPRITE];
    struct UI_SLIDEBAR_V slidepalette;
    Color curant_color;
    int curant_spr;
    int curant_pal;
    struct Sprite sprites[EGBA_MAX_SPRITE];
    int btnspr_size;
    int btncol_size;
}UI_Sprite;

struct UI_Palette
{
    //struct UI_BUTTON btndelete;
    struct Palette palettes[EGBA_MAX_PALETTE];
    int palette_nb;
}UI_Palette;

struct UI_Script
{
    char source_script[40];
    char script[EGBA_MAX_SCRIPTSIZE];
}UI_Script;

#include "clua.h"
struct UI_Runner
{
    struct CLUA clua;
    char palette_id;
    char isload;
    char isdebug;
}uirun;

struct sproject
{
	char name[50];
	char islua;
	char isegba;
	char ispng;
};
typedef struct sproject Project;



#define BROWSER_PROJECT_MAX_H 24
struct sbrowser
{
	Project list[EGBA_MAX_PROJECT];
	int project_nb;
	float timer;

};
typedef struct sbrowser Browser;
Browser _BROWSER;

enum UIPROJECT_STATE
{
	UIPROJECT_STATE_DEFAULT=0,
	UIPROJECT_STATE_VSPRITE,
	UIPROJECT_STATE_VSCRIPT,
	UIPROJECT_STATE_VRUNNER
};

struct suiproject
{
	int id;
	enum UIPROJECT_STATE state;
	char isactive;
    float timer;
    // texture img ui
    Texture spr;
    Texture lua;
    Texture egba;
    char islock;
}_UIPROJECT;

struct sconfig
{
    Color color1;
    Color color2;
};

struct suiconfig
{
    struct sconfig config;
    char isactive;
    float timer;
}_UICONFIG;

#define UICONFIG_COL1() (_UICONFIG.config.color1)
#define UICONFIG_COL2() (_UICONFIG.config.color2)

struct EGBA
{
    bool ifrunner;
}_EGBA;
