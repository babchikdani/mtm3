//
// Created by Dani on 13-Jun-17.
//

#ifndef MTM3_ESCAPETECHNION_H
#define MTM3_ESCAPETECHNION_H

#include "set.h"
#include "list.h"
#include "mtm_ex3.h"
#include "Company.h"
#include "Room.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

/**
 * typedef for the the system type.
 */
typedef struct system_t* System;

typedef enum{
    SYS_OUT_OF_MEMORY,  //
    SYS_INVALID_COMMAND_LINE_PARAMETERS, //
    SYS_CANNOT_OPEN_FILE, //
    SYS_NULL_PARAMETER,
    SYS_INVALID_PARAMETER,
    SYS_EMAIL_ALREADY_EXISTS,
    SYS_COMPANY_EMAIL_DOES_NOT_EXIST,
    SYS_CLIENT_EMAIL_DOES_NOT_EXIST,
    SYS_ID_ALREADY_EXIST,
    SYS_ID_DOES_NOT_EXIST,
    SYS_CLIENT_IN_ROOM,
    SYS_ROOM_NOT_AVAILABLE,
    SYS_RESERVATION_EXISTS,
    SYS_NO_ROOMS_AVAILABLE,
    SYS_SUCCESS,
}SystemResult;
//TODO: documentation.






/**
 *
 * @param copyElement
 * @param freeElement
 * @param compareElements
 * @return
 */
System CreateSystem(copySetElements copyElement, freeSetElements freeElement, compareSetElements compareElements);

/**
 *
 * @param systema
 */
void DestroySystem(System systema);

/**
 *
 * @param systema
 * @param CompanyEmail
 * @param faculty
 * @return
 */
SystemResult AddCompany(System systema, char* CompanyEmail, TechnionFaculty faculty);

/**
 *
 * @param systema
 * @param company_email
 * @return
 */
SystemResult RemoveCompany(System systema, char* company_email);

/**
 *
 * @param systema
 * @param company_email
 * @param id
 * @param price
 * @param num_ppl
 * @param working_hours
 * @param difficulty
 * @return
 */
SystemResult AddRoom(System systema, char* company_email, int id, int price, int num_ppl, char* working_hours, int difficulty);

/**
 *
 * @param systema
 * @param faculty
 * @param id
 * @return
 */
SystemResult RemoveRoom(System systema, TechnionFaculty faculty, int id);

#endif //MTM3_ESCAPETECHNION_H
