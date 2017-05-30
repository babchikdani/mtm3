#include "list_mtm1.h"
#include <stdlib.h>


typedef struct capsule* Capsule;
struct capsule {
    ListElement data;
    Capsule next;
};

struct list_h {
    Capsule head;
    Capsule iterator;
    int size;
    CopyListElement CopyE;          // function!
    FreeListElement FreeE;          // function!
    CompareListElements CompareE;   // function!
    FilterListElement FilterE;      // function!
};







/*
struct GenericList
{
    List reshima;

    ListElement CopyListElement (ListElement x)
    {
        // ...
    }
    // more functions
};
*/


/**
 * the copy function implementation.
 */
ListElement CopyElement(ListElement element)
{
ListElement tmp_element = malloc(sizeof(ListElement));
if(tmp_element == NULL)
{
return NULL;
}


}







