#include "ui_runner.h"
struct UI_Runner
{
    struct CLUA clua;
    struct Sprite spr[DT_MAX_SPRITE];
    struct Palette pal[DT_MAX_PALETTE];
}uirun;

int rlua_trace(clua_state* L)
{
    const char* pstr = lua_tostring(L,1);
    puts(pstr);
    return 0;
}

int rlua_cls(clua_state* L)
{
    int id = lua_tointeger(L,1);
    Color col = uirun.pal[0].palette[id];
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),col);
    return 0;
}

int rlua_drawtext(clua_state* L)
{
    // extern struct UI_Runner uirun;
    const char* cstr = lua_tostring(L,1);
    int x = lua_tonumber(L,2);
    int y = lua_tonumber(L,3);
 
    Color col = uirun.pal[0].palette[(int)lua_tonumber(L,4)];
    int scale = lua_tointeger(L,5);
    if(scale==0) scale=16;
    DrawText(cstr,x,y,scale,col);
    //lua_pop(L,4);
    return 0;
}

int rlua_drawsprite(clua_state* L)
{
    int id = lua_tointeger(L,1);
    int x = lua_tonumber(L,2);
    int y = lua_tonumber(L,3);
    int scale = lua_tointeger(L,4);
    if(scale == 0) scale = 2;
    Atlas_DrawSprite(id,x,y,scale);
    return 0;
}

int rlua_drawrect(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);;
    Color col = uirun.pal[0].palette[(int)lua_tonumber(L,5)];
    DrawRectangle(x,y,w,h,col);
    return 0;
}

int rlua_drawrectb(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);;
    Color col = uirun.pal[0].palette[(int)lua_tonumber(L,5)];
    DrawRectangleLines(x,y,w,h,col);
    return 0;
}

int rlua_btn(clua_state* L)
{
    int id = lua_tointeger(L,1);
    switch(id)
    {
        case 0: 
            if(IsKeyDown(KEY_UP)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 1: 
            if(IsKeyDown(KEY_DOWN)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 2: 
            if(IsKeyDown(KEY_LEFT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 3: 
            if(IsKeyDown(KEY_RIGHT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        default:;
    }
    lua_pushboolean(L,0);
    return 1;
}

int rlua_btnp(clua_state* L)
{
    int id = lua_tointeger(L,1);
    switch(id)
    {
        case 0: 
            if(IsKeyPressed(KEY_UP)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 1: 
            if(IsKeyPressed(KEY_DOWN)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 2: 
            if(IsKeyPressed(KEY_LEFT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        case 3: 
            if(IsKeyPressed(KEY_RIGHT)){ 
                lua_pushboolean(L,1);
                return 1;
            }
        break;
        default:;
    }
    lua_pushboolean(L,0);
    return 1;
}

int rlua_mouse(clua_state* L)
{
    lua_pushinteger(L,GetMouseX());
    lua_pushinteger(L,GetMouseY());
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_LEFT));
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_MIDDLE));
    lua_pushboolean(L,IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
    return 5;
}

void _UI_Runner_functionpush(int (*pfunc)(clua_state*),const char* name)
{
    CLUA_setfunction(&uirun.clua,pfunc,name);
}

void UI_Runner()
{
    uirun.clua = CLUA();
    _UI_Runner_functionpush(rlua_cls,"cls");
    _UI_Runner_functionpush(rlua_drawtext,"print");
    _UI_Runner_functionpush(rlua_drawsprite,"spr");
    _UI_Runner_functionpush(rlua_drawrect,"rect");
    _UI_Runner_functionpush(rlua_drawrectb,"rectb");
    _UI_Runner_functionpush(rlua_btn,"btn");
    _UI_Runner_functionpush(rlua_btnp,"btnp");
    _UI_Runner_functionpush(rlua_mouse,"mouse");
    _UI_Runner_functionpush(rlua_trace,"trace");
}


bool UI_Runner_Load(const char *pfile)
{
    const char* ext = GetFileExtension(pfile);
    if(TextIsEqual(ext,".egba"))
    {
        struct sdata sdata;
        FILE* fic = fopen(pfile,"rb");
        if(fic!=NULL)
        {
            UI_Runner();
            fread(&sdata,sizeof(struct sdata),1,fic);
            fclose(fic);
            for(int i=0;i<DT_MAX_PALETTE;i++)
                uirun.pal[i]=PaletteD(sdata.list_pal[i]);
            Atlas_UpdatePalette(uirun.pal);
            for(int i=0;i<DT_MAX_SPRITE;i++)
                uirun.spr[i]=SpriteD(sdata.list_spr[i]);
            Atlas_UpdateSprite(uirun.spr);
            CLUA_dostring(&uirun.clua,sdata.script);
            return true;
        }

    }
    else if(TextIsEqual(ext,".lua"))
    {
        struct sdata sdata;
        const char* fileext = TextFormat("%s.egba",GetFileNameWithoutExt(pfile));
        FILE* fic = fopen(fileext,"rb");
        if(fic!=NULL)
        {
            UI_Runner();
            fread(&sdata,sizeof(struct sdata),1,fic);
            fclose(fic);
            for(int i=0;i<DT_MAX_PALETTE;i++)
                uirun.pal[i]=PaletteD(sdata.list_pal[i]);
            Atlas_UpdatePalette(uirun.pal);
            for(int i=0;i<DT_MAX_SPRITE;i++)
                uirun.spr[i]=SpriteD(sdata.list_spr[i]);
            Atlas_UpdateSprite(uirun.spr);
            CLUA_dofile(&uirun.clua,pfile);
            return true;
        }else puts(TextFormat("runner error : %s not found",fileext));
    }
    return false;
}
bool UI_Runner_LoadD(struct sdata sdata)
{;
    for(int i=0;i<DT_MAX_PALETTE;i++)
        uirun.pal[i]=PaletteD(sdata.list_pal[i]);
    Atlas_UpdatePalette(uirun.pal);
    for(int i=0;i<DT_MAX_SPRITE;i++)
        uirun.spr[i]=SpriteD(sdata.list_spr[i]);
    Atlas_UpdateSprite(uirun.spr);
    CLUA_dostring(&uirun.clua,sdata.script);
    return true;
        
}
void UI_Runner_Draw()
{
    if(CLUA_iferror(&uirun.clua))
    {
        DrawText(CLUA_geterror(&uirun.clua),23,23,20,BLACK);
    }
    else
        CLUA_callfunction(&uirun.clua,"EGBA");
}

void UI_Runner_Free()
{
    CLUA_free(&uirun.clua);
}
