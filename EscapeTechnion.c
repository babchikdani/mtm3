//
// Created by Dani on 13-Jun-17.
//
                                      //TODO: free, cmp, copy function for rooms Set and companies Set and visitors List
#include "EscapeTechnion.h"



struct system_t{
    Set rooms;
    Set companies;
    List visitors;
};


System CreateSystem(copySetElements copyElement, freeSetElements freeElement, compareSetElements compareElements){
    if(copyElement==NULL || freeElement==NULL || compareElements==NULL){
        return NULL;
    }
    Set tmp_rooms=setCreate(copyElement, freeElement, compareElements);     // MALLOCING: Start
    if(tmp_rooms==NULL){
        return NULL;
    }
    Set tmp_companies=setCreate(copyElement, freeElement, compareElements);
    if(tmp_companies==NULL){
        free(tmp_rooms);
        return NULL;
    }
    List tmp_visitors=listCreate(copyElement, freeElement);
    if(tmp_visitors==NULL){
        free(tmp_companies);
        free(tmp_rooms);
        return NULL;
    }
    System tmp_system=malloc(sizeof(*tmp_system));
    if(tmp_system==NULL){
        free(tmp_visitors);
        free(tmp_companies);
        free(tmp_rooms);
        return NULL;
    }                                                               // MALLOCING: Finish.
    tmp_system->visitors=tmp_visitors;
    tmp_system->rooms=tmp_rooms;
    tmp_system->companies=tmp_companies;
                                                        // TODO: Is this all of the CreateSystem function?
    return tmp_system;
}

void DestroySystem(System systema){
    setDestroy(systema->companies);                // If the sent set is NULL nothing will be done. (according to header file)
    setDestroy(systema->rooms);
    listDestroy(systema->visitors);
    free(systema);
    return;
}

SystemResult AddCompany(System systema, char* CompanyEmail, TechnionFaculty faculty){
    if(CompanyEmail==NULL || systema==NULL){
        return SYS_NULL_PARAMETER;     // This won't happen cuz i will check the argument in the "upper main code" but still i must check
    }
    if(isValidEmail(CompanyEmail) || isValidFaculty(faculty)){
        return SYS_INVALID_PARAMETER;
    }
    char* tmp_email=malloc(strlen(CompanyEmail)+1);                // MALLOCING: Start
    if(tmp_email==NULL){
        return SYS_OUT_OF_MEMORY;
    }
    strcpy(tmp_email, CompanyEmail);                               // MALLOCING: Finish
    Company tmp_company=CreateCompany(tmp_email, faculty);
    if(tmp_company==NULL){                      // It checks the validity of the arguments. (?) BUT HOW DO I KNOW IF IT FAILED CUZ OF THE MALLOC OR THE VALIDITY?!
        return SYS_OUT_OF_MEMORY;
    }
    SetResult outcome=setAdd(systema->companies, tmp_company);              // CANNOT RETURN NULL ARG CUZ WE CHECKED IT BEFORE SETADD
    if(outcome==SET_OUT_OF_MEMORY){
        return SYS_OUT_OF_MEMORY;
    }
    if(outcome==SET_ITEM_ALREADY_EXISTS){
        return SYS_EMAIL_ALREADY_EXISTS;
    }
    return SYS_SUCCESS;
}

SystemResult RemoveCompany(System systema, char* company_email){
    if(company_email==NULL || systema==NULL){
        return SYS_NULL_PARAMETER;
    }
    if(isValidEmail(company_email)==false){
        return SYS_INVALID_PARAMETER;
    }
    char* tmp_email;
    SET_FOREACH(Company, iterator, systema->companies){
        tmp_email=CompanyGetEmail(iterator);
        if(tmp_email==NULL){
            return SYS_OUT_OF_MEMORY;
        }
        if(strcmp(company_email, tmp_email)==0){
            // TODO: check if there's a reservation for this company.
            if(isThereAnyReservation(iterator)==true){
                return SYS_RESERVATION_EXISTS;
            }
            assert(iterator->rooms_in_use);                             // USELESS
            SetResult result = setRemove(systema->companies, iterator);
            assert(iterator);
            if(result==SET_SUCCESS){
                return SYS_SUCCESS;
            }
        }
        free(tmp_email);
    }
    return SYS_COMPANY_EMAIL_DOES_NOT_EXIST;
}

SystemResult AddRoom(System systema, char* company_email, int id, int price, int num_ppl, char* working_hours, int difficulty){
    int garbageCan1;
    int garbageCan2;
    if(company_email==NULL || working_hours==NULL || isValidEmail(company_email)==false ||
       isValidFaculty((TechnionFaculty)(id))==false || systema==NULL || num_ppl<1 || price<1 ||
       price%4!=0 || difficulty>10 || difficulty<1 || StringToInt(working_hours, &garbageCan1, &garbageCan2)==false || id<1 ){
        return SYS_INVALID_PARAMETER;
    }
    int flag=0;
    char* tmp_pointer;
    SET_FOREACH(Company , Iterator, systema->companies){
        tmp_pointer=CompanyGetEmail(Iterator);
        if(tmp_pointer==NULL){
            return SYS_OUT_OF_MEMORY;
        }
        if(strcmp(tmp_pointer, company_email)==0){
            flag=1;
        }
        free(tmp_pointer);
    }
    if(flag==0){
        return SYS_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    SET_FOREACH(Room, iterator, systema->rooms ){
        if(RoomGetID(iterator)==id){
            return SYS_ID_ALREADY_EXIST;
        }
    }
    Room tmp_room=CreateRoom(company_email, id, price, difficulty, num_ppl, working_hours);
    if(tmp_room==NULL){
        return SYS_OUT_OF_MEMORY;
    }
    SetResult result=setAdd(systema->rooms, tmp_room);      // only the systema->rooms can be NULL here..
    if(result==SET_OUT_OF_MEMORY){
        return SYS_OUT_OF_MEMORY;  // The SetAdd cannot return that the element already exists cuz we checked that the ids are different.
    }
    return SYS_SUCCESS;
}

SystemResult RemoveRoom(System systema, TechnionFaculty faculty, int id) {
    if (systema == NULL || id < 1 || isValidFaculty(faculty) == false) {
        return SYS_INVALID_PARAMETER;
    }
    int room_exists = 0;
    int is_reserved = 0;
    SET_FOREACH(Room, iterator, systema->rooms) {
        if (RoomGetID(iterator) == id) {
            room_exists = 1;
            is_reserved = RoomGetReservedStatus(iterator);
        }
    }
    if (room_exists == 0) {
        return SYS_ID_DOES_NOT_EXIST;
    }
    if (is_reserved == 1) {
        return SYS_RESERVATION_EXISTS;
    }
    SET_FOREACH(Room, iterator, systema->rooms) {
        if (RoomGetID(iterator) == id) {
         setRemove(systema->rooms, iterator);        // return value ITEM_DOESNT_EXISTS CANNOT HAPPEN CUZ WE FOUND IT
        }
    }
    return SYS_SUCCESS;
}

//TODO: Resume from here.