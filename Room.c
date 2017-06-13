//
// Created by Dani on 12-Jun-17.
//
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Room.h"

struct room {
    char* company_email;             // TODO:REMINDER: COMPANY's! email. The email of the company which owns the room!
    int id;                 // room id, a positive number. Never there shall be two rooms with the same ids.
    int price;              // price per person
    int difficulty;         // ranges from 1-10
    int num_ppl;            // recommended ppl in a room.
    char* working_hours;
    int opening_hour;
    int closing_hour;
    int reserved;           // 1 - there is a reservation. 0 - else.
}; // Should I have had added a field of Overallvisits?

int RoomGetReservedStatus(Room roomie){
    return roomie->reserved;
}
int RoomGetID(Room roomie){
    return roomie->id;
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

bool StringToInt(char *content, int *open_hrs, int *close_hrs){ // USE CAUTION WITH THIS FUNCTION!
    if(content==NULL){                          // will atoi change "01" to 1 or to 01? I assumed that it changes to 1.
        return false;
    }
    *open_hrs=atoi(strtok(content, "-"));   //  from the internet.
    *close_hrs=atoi(strtok(NULL, "-"));     // Passing NULL in order to continue form the last string you parsed.
    if(*open_hrs>=*close_hrs || *open_hrs<0 || *close_hrs>24){
        return false;
    }
    return true;
}

Room CreateRoom(char* company_email, int id, int price, int difficulty, int num_ppl, char* working_hours) {
    int garbageCan1;
    int garbageCan2;            // Both are for the initial use of StringToInt.
    if(difficulty>10 || difficulty<1 || working_hours==NULL || company_email==NULL || isValidEmail(company_email) ||
            StringToInt(working_hours, &garbageCan1, &garbageCan2) || price<1 || price%4!=0 || num_ppl<1 || id<1){
        return NULL;
    }
    Room tmp_room = malloc(sizeof(*tmp_room));
    if (tmp_room == NULL) {
        return NULL;
    }
    char *tmp_email = malloc(strlen(company_email) + 1);
    if (tmp_email == NULL) {
        free(tmp_room);
        return NULL;
    }
    char *tmp_working_hours = malloc(strlen(working_hours) + 1);
    bool validWorkingHours = StringToInt(working_hours, &tmp_room->opening_hour, &tmp_room->closing_hour);
    if (tmp_working_hours == NULL || validWorkingHours==false) {
        free(tmp_room);     // this mean either the malloc failed or the working hours aren't in order
        free(tmp_email);
        return NULL;
    }
    strcpy(tmp_email, company_email);
    strcpy(tmp_working_hours, working_hours);
    tmp_room->company_email = tmp_email;
    tmp_room->working_hours = tmp_working_hours;
    tmp_room->difficulty = difficulty;
    tmp_room->id = id;
    tmp_room->num_ppl = num_ppl;
    tmp_room->price = price;
    tmp_room->reserved=0;
    return tmp_room;
}

void DestroyRoom(Room target){
    if(target==NULL){
        return;
    }
    free(target->working_hours);
    free(target->company_email);
    free(target);
    return;
}

Room CopyRoom(Room source){
    if(source==NULL){                               // Argument check
        return NULL;
    }
    Room tmp_room=malloc(sizeof(*tmp_room));        // MALLOCING: Start
    if(tmp_room==NULL){
        return NULL;
    }
    char* tmp_email=malloc(sizeof(*tmp_email));
    if(tmp_email==NULL){
        free(tmp_room);
        return NULL;
    }
    char* tmp_working_hours=malloc(sizeof(*tmp_working_hours));
    if(tmp_working_hours==NULL){
        free(tmp_email);
        free(tmp_room);
        return NULL;
    }                                              // MALLOCING: Finish
    strcpy(tmp_email, source->company_email);
    strcpy(tmp_working_hours, source->working_hours);
    tmp_room->company_email=tmp_email;
    tmp_room->working_hours=tmp_working_hours;
    tmp_room->opening_hour=source->opening_hour;
    tmp_room->closing_hour=source->closing_hour;
    tmp_room->price=source->price;
    tmp_room->num_ppl=source->num_ppl;
    tmp_room->id=source->id;
    tmp_room->difficulty=source->difficulty;
    tmp_room->reserved=source->reserved;
    return tmp_room;
}

