#include "clua.h"

struct CLUA CLUA()
{
    struct CLUA clua;
    clua.L = luaL_newstate();
    clua.error=0;
    luaL_openlibs(clua.L);
    return clua;
}

short CLUA_dofile(struct CLUA *clua, const char *scrfile)
{
    if(luaL_dofile(clua->L,scrfile)== LUA_OK)
    {
        return 1;
    }
    clua->error=1;
    strcpy(clua->error_str,lua_tostring(clua->L, -1));
    return 0;
}

short CLUA_dostring(struct CLUA *clua, const char *sscript)
{
    if(luaL_dostring(clua->L,sscript)== LUA_OK)
    {
        return 1;
    }
    clua->error=1;
    strcpy(clua->error_str,lua_tostring(clua->L, -1));
    return 0;
}

double CLUA_getnumber(struct CLUA *clua, const char *name)
{
    lua_getglobal(clua->L,name);
    double red = lua_tonumber(clua->L,-1);
    lua_pop(clua->L,1);
    return red;
}

double CLUA_getnumberI(struct CLUA *clua, int id)
{
    double d = lua_tonumber(clua->L,id);
    lua_pop(clua->L,1);
    return d;
}

void CLUA_setnumber(struct CLUA *clua, const char *name, double num)
{
    lua_pushnumber(clua->L,num);
    lua_setglobal(clua->L,name);
}

const char *CLUA_getstring(struct CLUA *clua, const char *name)
{
    lua_getglobal(clua->L,name);
    const char* res = lua_tostring(clua->L,-1); //(clua->L,-1);
    lua_pop(clua->L,1);
    return res;
}

const char *CLUA_getstringI(struct CLUA *clua, int id)
{
    const char* s = lua_tostring(clua->L,id);
    lua_pop(clua->L,1);
    return s;
}

void CLUA_setstring(struct CLUA *clua, const char *name, char *val)
{
    lua_pushstring(clua->L,val);
    lua_setglobal(clua->L,name);
}

void CLUA_setfunction(struct CLUA *clua, int (*fun_ptr)(clua_state *), const char *name)
{
    lua_pushcfunction(clua->L,fun_ptr);
    lua_setglobal(clua->L,name);// set global name
}

void CLUA_callfunction(struct CLUA *clua, const char *name)
{
    lua_getglobal(clua->L,name);
    if(lua_isfunction(clua->L,-1))
    {
        lua_pcall(clua->L,0,0,0);
    }
}

char *CLUA_geterror(struct CLUA *clua)
{
    if(clua->error)
        return clua->error_str;
    return "";
}

short CLUA_iferror(struct CLUA *clua)
{
    return clua->error;
}

void CLUA_free(struct CLUA* clua)
{
    lua_close(clua->L);
}
