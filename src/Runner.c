#include "EGBA.h"
#include "clua.h"
#include "Runner.h"
//------------- runner -------------------
//#include "ui_runner.h"

char UIRun_isload=0;
char UIRun_isdebug=0;
int UIRun_paletteid=0;
char UIRun_ext[5];
char UIRun_name[50];
struct CLUA UIRun_clua;

struct Palette GetPalette()
{
    return Data_Palette_Get(UIRun_paletteid);
}

// interverse
int rlua_run(clua_state* L)
{
    const char* cstr = lua_tostring(L,1);
    if(Runner_Load(cstr))
    {

    }
    return 0;
}
struct segba_saving _rlua_GetSave(const char* cname)
{
    struct segba_saving ssave={0};
    FILE* fic= fopen(TextFormat("%s.sav",cname),"rb");
    if(fic!=NULL)
    {
        fread(&ssave,sizeof(struct segba_saving),1,fic);
        fclose(fic);
    }
    return ssave;
}

int rlua_rsave_string_ext(clua_state* L)
{
    const char* cname = lua_tostring(L,1);
    int id = lua_tointeger(L,2);
    if(id>-1 && id<SAVING_MAX_STRING)
    {
        struct segba_saving saving = _rlua_GetSave(cname);
        lua_pushstring(L,saving.strs[id]);
    }
    return 1;
}

int rlua_rsave_bool_ext(clua_state* L)
{
    const char* cname = lua_tostring(L,1);
    int id = lua_tointeger(L,2);
    if(id>-1 && id<SAVING_MAX_BOOL)
    {
        struct segba_saving saving = _rlua_GetSave(cname);
        lua_pushboolean(L,(int)saving.bools[id]);
    }
    return 1;
}

int rlua_rsave_numb_ext(clua_state* L)
{
    const char* cname = lua_tostring(L,1);
    int id = lua_tointeger(L,2);
    if(id>-1 && id<SAVING_MAX_NUMBER)
    {
        struct segba_saving saving = _rlua_GetSave(cname);
        lua_pushnumber(L,saving.numbs[id]);
    }
    return 1;
}

//--------------------------------------

int rlua_wsave_bool(clua_state* L)
{
    int id = lua_tointeger(L,1);
    int b = lua_toboolean(L,2);
    if(id>-1 && id<SAVING_MAX_BOOL)
    {
        struct segba_saving saving = Saving_Get();
        saving.bools[id] = b;
        const char* cstr = TextFormat("%s%s",UIRun_name,UIRun_ext);
        Saving_WriteSave(cstr,saving);
    }
    return 0;
}

int rlua_rsave_bool(clua_state* L)
{
    int id = lua_tointeger(L,1);
    if(id>-1 && id<SAVING_MAX_BOOL)
    {
        struct segba_saving saving = Saving_Get();
        lua_pushboolean(L,(int)saving.bools[id]);
    }
    return 1;
}

int rlua_wsave_string(clua_state* L)
{
    int id = lua_tointeger(L,1);
    const char* str = lua_tostring(L,2);
    if(id>-1 && id<SAVING_MAX_STRING)
    {
        struct segba_saving saving = Saving_Get();
        strcpy(saving.strs[id],str);
        const char* cstr = TextFormat("%s%s",UIRun_name,UIRun_ext);
        Saving_WriteSave(cstr,saving);
    }
    return 0;
}

int rlua_rsave_string(clua_state* L)
{
    int id = lua_tointeger(L,1);
    if(id>-1 && id<SAVING_MAX_STRING)
    {
        struct segba_saving saving = Saving_Get();
        lua_pushstring(L,saving.strs[id]);
    }
    return 1;
}

int rlua_wsave_numb(clua_state* L)
{
    int id = lua_tointeger(L,1);
    int n = lua_tonumber(L,2);
    if(id>-1 && id<SAVING_MAX_NUMBER)
    {
        struct segba_saving saving = Saving_Get();
        saving.numbs[id]=n;
        const char* cstr = TextFormat("%s%s",UIRun_name,UIRun_ext);
        Saving_WriteSave(cstr,saving);
    }
    return 0;
}

int rlua_rsave_numb(clua_state* L)
{
    int id = lua_tointeger(L,1);
    if(id>-1 && id<SAVING_MAX_NUMBER)
    {
        struct segba_saving saving = Saving_Get();
        lua_pushnumber(L,saving.numbs[id]);
    }
    return 1;
}

int rlua_trace(clua_state* L)
{
	if(UIRun_isdebug)
	{
		const char* pstr = lua_tostring(L,1);
		printf("[EGBA](TRACE)=>%s\n",pstr);
    }
    return 0;
}

int rlua_pal(clua_state* L)
{
    int id = lua_tointeger(L,1);
    if(id>-1 && id<EGBA_MAX_PALETTE) UIRun_paletteid=id;
    return 0;
}

int rlua_cls(clua_state* L)
{
    int id = lua_tointeger(L,1);
    struct Palette pal = GetPalette();
    Color col = pal.data[id];
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),col);
    return 0;
}

int rlua_drawtext(clua_state* L)
{
    // extern struct UI_Runner uirun;
    const char* cstr = lua_tostring(L,1);
    int x = lua_tonumber(L,2);
    int y = lua_tonumber(L,3);

    struct Palette pal = Data_Palette_Get(UIRun_paletteid);
    Color col = pal.data[(int)lua_tonumber(L,4)];
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

int rlua_drawpix(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    struct Palette pal = GetPalette();
    Color col = pal.data[(int)lua_tonumber(L,3)];
    DrawPixel(x,y,col);
    return 0;
}

int rlua_drawrect(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);
    struct Palette pal = GetPalette();
    Color col = pal.data[(int)lua_tonumber(L,5)];
    DrawRectangle(x,y,w,h,col);
    return 0;
}

int rlua_drawrectb(clua_state* L)
{
    int x = lua_tonumber(L,1);
    int y = lua_tonumber(L,2);
    int w = lua_tointeger(L,3);
    int h = lua_tointeger(L,4);
    struct Palette pal = GetPalette();
    Color col = pal.data[(int)lua_tonumber(L,5)];
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
        case 4:
        if(IsKeyDown(KEY_X)){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        case 5:
        if(IsKeyDown(KEY_C)){
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
        case 4:
        if(IsKeyPressed(KEY_X)){
            lua_pushboolean(L,1);
            return 1;
        }
        break;
        case 5:
        if(IsKeyPressed(KEY_C)){
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
    CLUA_setfunction(&UIRun_clua,pfunc,name);
}

void UI_Runner()
{
    UIRun_clua = CLUA();
    _UI_Runner_functionpush(rlua_rsave_bool_ext,"rsave_bool_ext");
    _UI_Runner_functionpush(rlua_rsave_string_ext,"rsave_string_ext");
    _UI_Runner_functionpush(rlua_rsave_numb_ext,"rsave_numb_ext");
    _UI_Runner_functionpush(rlua_run,"run");

    _UI_Runner_functionpush(rlua_rsave_bool,"rsave_bool");
    _UI_Runner_functionpush(rlua_wsave_bool,"wsave_bool");
    _UI_Runner_functionpush(rlua_rsave_string,"rsave_string");
    _UI_Runner_functionpush(rlua_wsave_string,"wsave_string");
    _UI_Runner_functionpush(rlua_rsave_numb,"rsave_numb");
    _UI_Runner_functionpush(rlua_wsave_numb,"wsave_numb");
    _UI_Runner_functionpush(rlua_cls,"cls");
    _UI_Runner_functionpush(rlua_drawtext,"text");
    _UI_Runner_functionpush(rlua_drawsprite,"spr");
    _UI_Runner_functionpush(rlua_drawrect,"rect");
    _UI_Runner_functionpush(rlua_drawrectb,"rectb");
    _UI_Runner_functionpush(rlua_btn,"btn");
    _UI_Runner_functionpush(rlua_btnp,"btnp");
    _UI_Runner_functionpush(rlua_mouse,"mouse");
    _UI_Runner_functionpush(rlua_trace,"trace");
    _UI_Runner_functionpush(rlua_pal,"pal");
    _UI_Runner_functionpush(rlua_drawpix,"pix");
	//uirun.isload=1;
}
// void UI_Runner_LoadD(struct segba_data sdata)
// {
//
// }

bool UI_Runner_Load(const char *pfile)
{
    if(FileExists(pfile))
    {
         const char* ext = GetFileExtension(pfile);
        if(TextIsEqual(ext,".egba"))
        {
            strcpy(UIRun_ext,ext);
            strcpy(UIRun_name,GetFileNameWithoutExt(pfile));
            struct segba_data sdata;
            FILE* fic = fopen(pfile,"rb");
            if(fic!=NULL)
            {
                UI_Runner();
                UIRun_isdebug=0;
                fread(&sdata,sizeof(struct segba_data),1,fic);
                fclose(fic);
                Data_Palette_LoadD(sdata);
                Data_Sprite_LoadD(sdata);
                Data_Script_LoadD(sdata);
                CLUA_dostring(&UIRun_clua,sdata.script);
                Saving_LoadSave(pfile);
                return true;
            }
            else puts(TextFormat("[EGBA] : runner error : %s not found",pfile));
        }
        else if(TextIsEqual(ext,".lua"))
        {
            strcpy(UIRun_ext,ext);
            strcpy(UIRun_name,GetFileNameWithoutExt(pfile));
            const char* fileext = TextFormat("%s.png",GetFileNameWithoutExt(pfile));
            if(FileExists(fileext))
            {
                UI_Runner();
                UIRun_isdebug=1;
                Data_Palette_LoadF(fileext);
                Data_Sprite_LoadF(fileext);
                Data_Script_LoadF(pfile);
                Saving_LoadSave(pfile);
                CLUA_dofile(&UIRun_clua,pfile);
                return true;
            }else puts(TextFormat("[EGBA] : runner error : %s not found",fileext));
        }
    }
    return false;
}


bool Runner_Load(const char* sfile)
{
    Atlas_Init();
    UI_Runner();
    UIRun_isload=1;
    return UI_Runner_Load(sfile);
}
void Runner_Init(int narg,char** sarg)
{
    if(narg==1)
    {

    }
    if(narg==2)
    {
        if(Runner_Load(sarg[1]))
        {
        // runner init
        }
        else
        {// runner fail -> init editor
            puts("[EGBA] : error runner fail");
        }
    }
}
const char* Runner_GetExt()
{
    return UIRun_ext;
}
const char* Runner_GetName()
{
    return UIRun_name;
}
char Runner_IsDebug()
{
    return UIRun_isdebug;
}
char Runner_IsDown()
{
    if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) return 1;
    return 0;
}

void Runner_Draw()
{
    ClearBackground(UICONFIG_COL1());
    if(CLUA_iferror(&UIRun_clua))
    {
        DrawText(CLUA_geterror(&UIRun_clua),23,23,20,BLACK);
    }
    else
        CLUA_callfunction(&UIRun_clua,"EGBA");
}

void Runner_Free()
{
    if(UIRun_isload)
    {
        CLUA_free(&UIRun_clua);
        Atlas_Free();
    }

}
