#ifndef CLUA_H
#define CLUA_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
// clua ver 0.1
#define clua_state lua_State
struct CLUA
{
    clua_state* L;
    int error;
    char error_str[50];
};
struct CLUA CLUA();
short CLUA_dofile(struct CLUA* clua,const char* scrfile);
short CLUA_dostring(struct CLUA* clua,const char* sscript);
double CLUA_getnumber(struct CLUA* clua,const char* name);
double CLUA_getnumberI(struct CLUA* clua,int id);
void CLUA_setnumber(struct CLUA* clua,const char* name,double num);
const char* CLUA_getstring(struct CLUA* clua,const char* name);
const char* CLUA_getstringI(struct CLUA* clua,int id);
void CLUA_setstring(struct CLUA* clua,const char* name,char* val);
void CLUA_setfunction(struct CLUA* clua,int (*fun_ptr)(clua_state*),const char* name);
void CLUA_callfunction(struct CLUA* clua,const char* name);
char* CLUA_geterror(struct CLUA* clua);
short CLUA_iferror(struct CLUA* clua);
void CLUA_free(struct CLUA* clua);
#endif