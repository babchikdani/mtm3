//
// Created by Dani on 12-Jun-17.
//

#ifndef MTM3_ROOM_H
#define MTM3_ROOM_H

typedef struct room* Room;

/**
 *  the function checks if th given email is a valid one. A valid email has only one '@'.
 * @param email - the given email
 * @return true if the '@' is only once.
 */
bool isValidEmail(char* email);

/**
 * this function converts the given string (aka content) into two intergers which represent the opening and closing hours.
 * this function uses both atoi() and strtok(); PROCEED WITH EXTRA CAUTION.
 * @param content - the string from which we'll read the integers.
 * @param open_hrs - OUTPUT arguement for the opening hours.
 * @param close_hrs - OUTPUT argument for the closing hours.
 * @return the function returns: * true if the operation was successful.
 *                               * false if the content points to NULL or the hours are illegal (not in the 00-24 range).
 */
bool StringToInt(char *content, int *open_hrs, int *close_hrs);

/**
 *
 * @param company_email - the email of the room owner company
 * @param id - room id. A positive number. No two rooms with the same id.
 * @param price - price per person. positive integer, dividable by 4.
 * @param difficulty - rooms difficulty. Ranges from 1 to 10.
 * @param num_ppl - recommended number of people in the room, positive number.
 * @param working_hours - room's working hours. A string in the formet of "xx-yy". 'xx' - opening hour. 'yy' - closing hour.
 * 'yy' MUST BE greater than 'xx'. Both 'xx' and 'yy' ranges from 00 to 24.
 * @return A newly allocated room with newly allocated field for working hours and company email. else - NULL.
 */
Room CreateRoom(char* company_email, int id, int price, int difficulty, int num_ppl, char* working_hours);

/**
 * Destroys an unwanted room.
 * @param target - the unwanted Room.
 */
void DestroyRoom(Room target);

/**
 *  returns the id of the room.
 * @param roomie - the target room.
 * @return the id of the room
 */
int RoomGetID(Room roomie);

/**
 *  This function uses the 'reserved' field of the Room structure.
 * @param roomie - the struct.
 * @return if the 'reserved' status is 0 which says that there are NO reservation by far it returns 0. It returns 1 else.
 */
int RoomGetReservedStatus(Room roomie);

#endif //MTM3_ROOM_H
