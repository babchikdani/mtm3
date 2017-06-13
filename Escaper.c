//
// Created by Dani on 12-Jun-17.
//
#include "mtm_ex3.h"
#include <malloc.h>
#include <string.h>
#include "Escaper.h"

struct escaper{
    char* email;
    int skill;
    TechnionFaculty faculty;
};

bool isValidFaculty(TechnionFaculty faculty){
    return ((int)faculty>=(int)(CIVIL_ENGINEERING) && (int)faculty<(int)UNKNOWN);
}

bool isValidEmail(char* email){
    int shtrudel=0;
    for(int i = 0; i < strlen(email); i++) {
        if (email[i] == '@') {
            shtrudel++;
        }
    }
    return (shtrudel==1);
}

Escaper CreateEscaper(char* email, int skill, TechnionFaculty faculty){
    if(email==NULL || isValidEmail(email) || skill>10 || skill <1 || isValidFaculty(faculty)==false){
        return NULL;
    }
    Escaper tmp_escaper=malloc(sizeof(*tmp_escaper));
    if(tmp_escaper==NULL){
        return NULL;
    }
    char* tmp_email=malloc(strlen(email)+1);        // Is this the right way to to do this? strlen return wothout the EOF
    if(tmp_email==NULL){
        free(tmp_escaper);
        return NULL;
    }
    strcpy(tmp_email, email);
    tmp_escaper->faculty=faculty;
    tmp_escaper->email=tmp_email;
    tmp_escaper->skill=skill;
    return tmp_escaper;
}

void DestroyEscaper(Escaper player){
    if(player==NULL){
        return;
    }
    free(player->email);
    free(player);
    return;
}

Escaper CopyEscaper(Escaper player){
    if(player==NULL){
        return NULL;
    }
    Escaper tmp_escaper=malloc(sizeof(*tmp_escaper));
    if(tmp_escaper==NULL){
        return NULL;
    }
    char* tmp_email=malloc(strlen(player->email)+1);
    if(tmp_email==NULL){
        free(tmp_escaper);
        return NULL;
    }
    strcpy(tmp_email, player->email);
    tmp_escaper->skill=player->skill;

    tmp_escaper->faculty=player->faculty;
    return tmp_escaper;
}
