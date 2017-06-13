//
// Created by Dani on 12-Jun-17.
//
#include <malloc.h>
#include <string.h>
#include "Company.h"


struct company {
    char* email;
    TechnionFaculty faculty;
    int rooms_in_use;
    int total_rooms_number;
};

bool isValidFaculty(TechnionFaculty faculty){
    return ((int)faculty<(int)UNKNOWN && (int)faculty>=(int)(CIVIL_ENGINEERING));
}

Company CreateCompany(char* email, TechnionFaculty faculty) {
    if(email==NULL || isValidEmail(email) || isValidFaculty(faculty)==false) {
        return NULL;
    }
    Company tmp_company;     // WE ASSUME THAT THERES ALWAYS ENOGUH MEMORY! -S. Panzieri
    tmp_company=malloc(sizeof(*tmp_company));
    if(tmp_company==NULL) {
        return NULL;
    }
    char* tmp_email=malloc(strlen(email)+1);
    if(tmp_email==NULL) {
        free(tmp_company);
        return NULL;
    }
    strcpy(tmp_email, email);
    tmp_company->email=tmp_email;
    tmp_company->faculty=faculty;
    tmp_company->rooms_in_use=0;
    tmp_company->total_rooms_number=0;
    return tmp_company;
}

void DestroyCompany(Company comp){
    if(comp==NULL){
        return;
    }
    free(comp->email);
    free(comp);
    return;
}

Company CopyCompany(Company comp){
    if(comp==NULL){
        return NULL;
    }
    Company tmp_company=malloc(sizeof(*tmp_company));
    if(tmp_company==NULL){
        return NULL;
    }
    char* tmp_email=malloc(strlen(comp->email)+1);
    if(tmp_email==NULL){
        free(tmp_company);
        return NULL;
    }
    strcpy(tmp_email, comp->email);
    tmp_company->email=tmp_email;
    tmp_company->faculty=comp->faculty;
    tmp_company->rooms_in_use=comp->rooms_in_use;
    tmp_company->total_rooms_number=comp->total_rooms_number;
    return tmp_company;
}

// TODO: Delete these if is not needed.
bool isThereAnyReservation(Company comp){
    return (comp->rooms_in_use!=0);
}
char* CompanyGetEmail(Company comp){
    if(comp==NULL){
        return NULL;
    }
    char* tmp_email=malloc(strlen(comp->email)+1);
    if(tmp_email==NULL){
        return NULL;
    }
    strcpy(tmp_email, comp->email);
    return tmp_email;
}

                                //TODO: Check if the function below is necessery.

