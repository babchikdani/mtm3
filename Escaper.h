//
// Created by Dani on 12-Jun-17.
//

#ifndef MTM3_ESCAPER_H
#define MTM3_ESCAPER_H

#include <stdbool.h>

typedef struct escaper* Escaper;

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
 * Creates a new escaper. Memory is allocated both for email field and the struct itself.
 * @param email - customer's email.
 * @param skill - customer's skill, ranges from 1 to 10.
 * @param faculty - customer's faculty.
 * @return a pointer to the new struct.
 */
Escaper CreateEscaper(char* email, int skill, TechnionFaculty faculty);

/**
 * frees the allocated memory.
 * @param player - the target.
 */
void DestroyEscaper(Escaper player);

/**
 * Copies the player's email to a newly allocated pointer.
 * @param player - the copy source.
 * @return a newly allocated struct with a newly allocated field for email and the same fields as player's.
 */
Escaper CopyEscaper(Escaper player);


#endif //MTM3_ESCAPER_H
