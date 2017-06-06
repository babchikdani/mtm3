#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include "list_mtm1.h"


typedef struct node* Node;
struct node {
    ListElement data;
    Node next;
};

static Node CreateNode(ListElement new_data, CopyListElement CopyE){
    assert(CopyE);
    Node Temp_Node=malloc(sizeof(*Temp_Node));
    if(Temp_Node==NULL){
        return NULL;
    }
    Temp_Node->next=NULL;
    ListElement tmp_data=CopyE(new_data);
    if(tmp_data==NULL){
        free(Temp_Node);
        return NULL;
    }
    Temp_Node->data=tmp_data;
    return Temp_Node;
}

static void DestroyNode(Node target, CopyListElement CopyE, FreeListElement FreeE){
    assert(FreeE);
    FreeE(target->data);
    free(target);
    return;
}

struct list_h {
    Node head;                   // Shall NOT be changed
    Node iterator;
    int size;
    CopyListElement CopyE;          // function!
    FreeListElement FreeE;          // function!
};









