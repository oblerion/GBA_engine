#include "EGBA.h"
#include "clua.h"
//------------- runner -------------------
//#include "ui_runner.h"

char UIRun_isdebug=0;
int UIRun_paletteid=0;
struct segba_data UIRun_data;
struct segba_atlas UIRun_atlas;
struct CLUA UIRun_clua;

struct Palette GetPalette()
{
    return UIRun_data.palettes[UIRun_paletteid];
}
Image R_Palette_GetImg(struct Palette pal)
{
    Image img = GenImageColor(32,1,BLACK);
    for(int i=0;i<EGBA_MAX_COLOR_PALETTE;i++)
    {
        ImageDrawPixel(&img,i,0,pal.data[i]);
    }
    return img;
}
Image R_Sprite_GetImg(struct Sprite spr)
{
    Image img = GenImageColor(spr.width,spr.height,BLACK);
    for(int i=0;i<spr.width*spr.height;i++)
	{
        ImageDrawPixel(&img,i%spr.width,i/spr.width,spr.data[i]);
	}
    return img;
}
void R_Atlas_Init()
{
    Image img = GenImageColor(32,5,BLACK);
    UIRun_atlas.palettes = LoadTextureFromImage(img);
    UnloadImage(img);

    img = GenImageColor(256,256,BLACK);
    UIRun_atlas.sprites = LoadTextureFromImage(img);
    UnloadImage(img);
}
void R_Atlas_UpdatePalette(struct Palette* palettes)
{
    Image img = GenImageColor(32,5,BLACK);
    Image palimg;
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
    {
        palimg = R_Palette_GetImg(palettes[i]);
        ImageDraw(&img,palimg,(Rectangle){0,0,32,1},(Rectangle){0,i,32,1},WHITE);
    }
    UpdateTexture(UIRun_atlas.palettes,img.data);
    UnloadImage(palimg);
    UnloadImage(img);
}

void R_Atlas_UpdateSprite(struct Sprite* sprites)
{
    Image img = GenImageColor(256,256,(Color){0,0,0,0});
    for(int i=0;i<EGBA_MAX_SPRITE;i++)
    {
        Image imgspr = R_Sprite_GetImg(sprites[i]);
        ImageDraw(&img,imgspr,
            (Rectangle){0,0,16,16},
            (Rectangle){(i%16)*16,(i/16)*16,16,16},
            WHITE
        );
        UnloadImage(imgspr);
    }
    UpdateTexture(UIRun_atlas.sprites,img.data);
    UnloadImage(img);
}
void R_Atlas_DrawSprite(int id,int x,int y,int scale)
{
    DrawTexturePro(UIRun_atlas.sprites,
        (Rectangle){(id%16)*16,(id/16)*16,16,16},
        (Rectangle){x,y,16*scale,16*scale},(Vector2){0,0},0,WHITE);
}
void R_Atlas_Free()
{
    UnloadTexture(UIRun_atlas.palettes);
    UnloadTexture(UIRun_atlas.sprites);
}
void R_UI_Palette_Init(struct segba_data* data)
{
    for(int i=0;i<EGBA_MAX_PALETTE;i++)
        strcpy(data->palettes[i].name,"");
    data->palette_nb=0;
}
void R_UI_palette_LoadF(struct segba_data* data, const char* pfile)
{
    if(TextIsEqual(GetFileExtension(pfile),".png"))
    {
        Image img = LoadImage(pfile);
        if(img.width==256 && img.height==257)
        {
            for(int i=0;i<EGBA_MAX_PALETTE;i++)
            for(int j=0;j<EGBA_MAX_COLOR_PALETTE;j++)
            {
                //strcpy(data->palettes[i].name,TextFormat("%d",i));
                Color col = GetImageColor(img,i*32+j,256);
                data->palettes[i].data[j]=col;
            }
            R_Atlas_UpdatePalette(data->palettes);
            data->palette_nb=5;
        }
        UnloadImage(img);
    }
}
void R_UI_Palette_LoadD(struct segba_data* ddata,struct segba_data sdata)
{
    for(int j=0;j<EGBA_MAX_PALETTE;j++)
    {
        strcpy(ddata->palettes[j].name,
        sdata.palettes[j].name);
        for(int i=0;i<EGBA_MAX_COLOR_PALETTE;i++)
        {
            ddata->palettes[j].data[i] = sdata.palettes[j].data[i];
        }
    }
    R_Atlas_UpdatePalette(ddata->palettes);
    ddata->palette_nb=5;
}

void R_UI_sprite_LoadF(struct segba_data* data, const char *pfile)
{
    Image fullimg = LoadImage(pfile);
    if(fullimg.width==256 && fullimg.height==257)
    {
        Image imgspr = ImageFromImage(fullimg,(Rectangle){0,0,256,256});
        Color* lcol = (Color*)imgspr.data;
        UpdateTexture(UIRun_atlas.sprites,lcol);
        UnloadImage(imgspr);

        for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
        {
            Image img = GenImageColor(16,16,(Color){0,0,0,0});
            ImageDraw(&img,fullimg,
                    (Rectangle){j*16,i*16,16,16},
                    (Rectangle){0,0,16,16},WHITE);

            Color* img_col = (Color*)img.data;
            for(int col=0;col<256;col++)
            data->sprites[(i*16)+j].data[col] = img_col[col];
            UnloadImage(img);
        }
    }
    UnloadImage(fullimg);
}

void R_UI_Sprite_LoadD(struct segba_data* ddata,struct segba_data sdata)
{
    // for(int i=0;i<EGBA_MAX_SPRITE;i++)
    // for(int j=0;j<EGBA_MAX_COLOR_SPRITE;j++)
    // {
    //     int mapid = sdata.sprite_mapid[i][j];
    //     if(mapid<0)
    //         UI_Sprite.sprites[i].data[j] = (Color){0,0,0,0};
    //     else
    //         UI_Sprite.sprites[i].data[j] =  sdata.palette_data[mapid];
    // }
    for(int i=0;i<EGBA_MAX_SPRITE;i++)
    {
        ddata->sprites[i] = sdata.sprites[i];
    }
    R_Atlas_UpdateSprite(ddata->sprites);
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

    struct Palette pal = UIRun_data.palettes[UIRun_paletteid];
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
    R_Atlas_DrawSprite(id,x,y,scale);
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
void UI_Runner_LoadD(struct segba_data sdata)
{
    R_UI_Palette_LoadD(&UIRun_data, sdata);
    R_UI_Sprite_LoadD(&UIRun_data, sdata);
    strcpy(UIRun_data.script,sdata.script);
    CLUA_dostring(&UIRun_clua,sdata.script);
}

bool UI_Runner_Load(const char *pfile)
{
    const char* ext = GetFileExtension(pfile);
    if(TextIsEqual(ext,".egba"))
    {
        struct segba_data sdata;
        FILE* fic = fopen(pfile,"rb");
        if(fic!=NULL)
        {
            UI_Runner();
            UIRun_isdebug=0;
            fread(&sdata,sizeof(struct segba_data),1,fic);
            fclose(fic);
			UI_Runner_LoadD(sdata);
            return true;
        }
        else puts(TextFormat("[EGBA] : runner error : %s not found",pfile));
    }
    else if(TextIsEqual(ext,".lua"))
    {
        const char* fileext = TextFormat("%s.png",GetFileNameWithoutExt(pfile));
        if(FileExists(fileext))
        {
            UI_Runner();
            UIRun_isdebug=1;
            // if(_EGBA.ifrunner==true)
            // {
				R_UI_palette_LoadF(&UIRun_data,fileext);
				R_UI_sprite_LoadF(&UIRun_data, fileext);
            // }

            CLUA_dofile(&UIRun_clua,pfile);
            return true;
        }else puts(TextFormat("[EGBA] : runner error : %s not found",fileext));
    }
    return false;
}

void UI_Runner_Draw()
{
    if(CLUA_iferror(&UIRun_clua))
    {
        DrawText(CLUA_geterror(&UIRun_clua),23,23,20,BLACK);
    }
    else
        CLUA_callfunction(&UIRun_clua,"EGBA");
}

void UI_Runner_Free()
{
    CLUA_free(&UIRun_clua);
}

#include "Runner.h"
void Runner_Load(const char* sfile)
{
    R_Atlas_Init();
    UI_Runner();
    UI_Runner_Load(sfile);
}
void Runner_Init(int narg,char** sarg)
{
    R_Atlas_Init();
    UI_Runner();

    if(narg==1)
    {
        if(!TextIsEqual( GetFileNameWithoutExt(sarg[0]) ,EGBA_RUN_NAME))
        {
            int size = GetFileLength(sarg[0]);
            FILE* fic = fopen(sarg[0],"rb");
            struct segba_data sdata;
            if(fic!=NULL)
            {
                fseek(fic,size-sizeof(struct segba_data),0);
                fread(&sdata,sizeof(struct segba_data),1,fic);
                fclose(fic);
                UIRun_isdebug=0;
                UI_Runner();
                UI_Runner_LoadD(sdata);
            }
        }
    }
    if(narg==2)
    {
        if(UI_Runner_Load(sarg[1]))
        {
        // runner init
        }
        else
        {// runner fail -> init editor
            puts("[EGBA] : error runner fail");
        }
    }
}

char Runner_IsDown()
{
    if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) return 1;
    return 0;
}

void Runner_Draw()
{
    ClearBackground(WHITE);
    UI_Runner_Draw();
}

void Runner_Free()
{
    UI_Runner_Free();
    R_Atlas_Free();
}
// //------------------ main -------------------
// int main(int narg,char** sarg)
// {
//     // Initialization
//     //--------------------------------------------------------------------------------------
//    // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
//     const int screenWidth = (720*4)/3; //GetMonitorWidth(0);
//     const int screenHeight = 720;//GetMonitorHeight(0);
//     InitWindow(screenWidth, screenHeight, EGBA_TITLE);
//     SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
//     SetWindowIcon(icon);
//
//     Runner_Init(narg,sarg);
//
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
//             break;
//         BeginDrawing();
//         ClearBackground(WHITE);
//         Runner_Draw();
//         EndDrawing();
//     }
//     Runner_Free();
//     CloseWindow();        // Close window and OpenGL
//     return 0;
// }
