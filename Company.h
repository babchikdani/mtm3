//
// Created by Dani on 12-Jun-17.
//

#ifndef MTM3_COMPANY_H
#define MTM3_COMPANY_H

#include <stdbool.h>
#include "mtm_ex3.h"


typedef struct company* Company;

/**
 * static function that determines if the faculty is valid within the given enum bank.
 * @param faculty - the given faculty.
 * @return 'true' - if the faculty exists in the enum bank, 'false' else.
 */
bool isValidFaculty(TechnionFaculty faculty);

/**
 *  the function checks if th given email is a valid one. A valid email has only one '@'.
 * @param email - the given email
 * @return true if the '@' is only once.
 */
bool isValidEmail(char* email);

/**
 * Creates a new company. Returns the new company with the sent arguments.
 * @param email - company's email.
 * @param faculty - the faculty to which the company belongs to.
 * @return Returns the new company with the sent arguments. NULL if there was a problem alloacating memory, or one or both of the arguments
 * is not valid.
 */
Company CreateCompany(char* email, TechnionFaculty faculty);

/**
 * Frees the the company's email field and the company itself.
 * @param comp - the target.
 */
void DestroyCompany(Company comp);

/**
 * Copies the given company to a newly allowcated ompany, including the newly alocated email field.
 * @param comp - the copy source.
 * @return a newly allocated company with newly allocated fields.
 */
Company CopyCompany(Company comp);

/**
 * the function gets a company and copies to a NEWLY ALLOCATED string the company email.
 * @param comp - the company which we desire to get the email.
 * @return NULL in case of a memory problem or a NULL argument. Else a newly allocated string with the company's email.
 */
char* CompanyGetEmail(Company comp);

/**
 *
 * @param comp
 * @return
 */
bool isThereAnyReservation(Company comp);


#endif //MTM3_COMPANY_H
