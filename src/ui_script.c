#include "ui_script.h"

struct UI_Script UI_Script()
{
    struct UI_Script uiscript={"\0","\0"};
    return uiscript;
}

void UI_Script_LoadF(struct UI_Script* uiscr,const char* pfile)
{
    FILE* fic = fopen(pfile,"r");
    if(fic!=NULL)
    {
        fseek(fic,SEEK_END,0);
        long pos = ftell(fic);
        fseek(fic,SEEK_SET,0);
        int p=0;
        strcpy(uiscr->script,"\0");
        if(pos<DT_MAX_SCRIPTSIZE){
     
            do
            {
                fscanf(fic,"%c",&uiscr->script[p]);
                p++;
            }
            while(feof(fic)==0);
        }
        strcpy(uiscr->source_script,".lua");
        fclose(fic);
    }
}

void UI_Script_LoadD(struct UI_Script* uiscript,struct sdata sdata)
{
    strcpy(uiscript->source_script,".dat");
    strcpy(uiscript->script,sdata.script);
}

void UI_Script_Save(struct UI_Script uiscript,struct sdata *sdata)
{
    strcpy(sdata->script,uiscript.script);
}

void UI_Script_Draw(struct UI_Script uiscript)
{
    DrawText(uiscript.script,15,30,18,BLACK);
}


