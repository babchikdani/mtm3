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
    ListElement tmp_data=CopyE(new_data);
    if(tmp_data==NULL){
        free(Temp_Node);
        return NULL;
    }
    Temp_Node->data=tmp_data;
    Temp_Node->next=NULL;
    return Temp_Node;
}

static void DestroyNode(Node target, FreeListElement FreeE){
    assert(FreeE);
    FreeE(target->data);
    free(target);
    return;
}
//
static Node CopyNode(Node source, CopyListElement CopyE){
    Node destination=malloc(sizeof(*destination));
    if(destination==NULL){
        return NULL;
    }
    ListElement TempElement=CopyE(source);
    if(TempElement==NULL){
        free(destination);
        return NULL;
    }
    destination->data=TempElement;
    destination->next=NULL;
    return destination;

}
//
struct list_t {
    Node head;
    Node iterator;
    int size;
    CopyListElement CopyE;
    FreeListElement FreeE;
};

List listCreate(CopyListElement copyElement, FreeListElement freeElement){
    assert(copyElement && freeElement);
    if(copyElement ==NULL || freeElement==NULL){
        return NULL;
    }
    List list=malloc(sizeof(*list));
    if(list==NULL) {
        return NULL;
    }
    list->head=NULL;
    list->iterator=NULL;
    list->size=0;
    list->CopyE=copyElement;
    list->FreeE=freeElement;
    return list;
}

void listDestroy(List list){
    assert(list);
    if(list==NULL){
        return;
    }
    for(int j=0; j<list->size; j++){
        DestroyNode(&list->head[j], list->FreeE);                         // listGetFirst(list) or list->head?
    }
    free(list);
    return;
}

List listCopy(List list){
    assert(list);
    if(list==NULL){
        return NULL;
    }
    List tmp_list=listCreate(list->CopyE, list->FreeE);
    if(tmp_list==NULL) {
        return NULL;
    }
    for(int i=0; i<list->size; i++) {
        Node tmp_node=CopyNode(&list->head[i],list->CopyE);              // using head instead of iterator, use caution.
        if(tmp_node==NULL){
            listDestroy(tmp_list);
            return NULL;
        }
        if(i==0){
            list->head=tmp_node;
        }
        list->iterator=tmp_node;
        list->size++;

    }
    return LIST_SUCCESS;
}

int listGetSize(List list){
    if(list==NULL){
        return -1;
    }
    return list->size;
}

ListElement listGetFirst(List list){
    assert(list);
    if(list==NULL) {
        return NULL;
    }
    list->iterator=list->head;
    return list->head;
}

ListElement listGetNext(List list){
    assert(list);
    if(list==NULL || list->iterator==NULL || list->iterator->next==NULL) {
        return NULL;
    }
    list->iterator=list->iterator->next;
    return list->iterator->next->data;
}

ListResult listInsertFirst(List list, ListElement element){
    assert(list && element);
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    ListElement tmp_element=list->CopyE(element);
    if(tmp_element==NULL){
        return LIST_OUT_OF_MEMORY;
    }
    Node tmp_node=CreateNode(tmp_element, list->CopyE);
    if(tmp_node==NULL){
        free(tmp_element);
        return LIST_OUT_OF_MEMORY;
    }
    tmp_node->next=list->head;
    list->head=tmp_node;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertLast(List list, ListElement element){
    assert(list && element);
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    ListElement tmp_element=list->CopyE(element);
    if(tmp_element==NULL){
        return LIST_OUT_OF_MEMORY;
    }
    Node tmp_node=CreateNode(tmp_element, list->CopyE);           // the created node's 'next' field points to NULL.
    if(tmp_node==NULL){
        free(tmp_element);
        return LIST_OUT_OF_MEMORY;
    }
    list->head[list->size-1].next=tmp_node;          // Going to the last node and changing the 'next' field to the tmp_node
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element){
    assert(list && element);
    int i;                                                  // to be used later.
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if(list->iterator==NULL){
        return LIST_INVALID_CURRENT;
    }
    ListElement tmp_element=list->CopyE(element);
    if(tmp_element==NULL){
        return LIST_OUT_OF_MEMORY;
    }
    Node tmp_node=CreateNode(tmp_element, list->CopyE);           // the created node's 'next' field points to NULL.
    if(tmp_node==NULL){
        free(tmp_element);
        return LIST_OUT_OF_MEMORY;
    }
    if(list->iterator==list->head){
        tmp_node->next=list->iterator;                                  // Assuring that the BeforeTheCurrentOne exists.
        list->head=tmp_node;
    }
    else{
        tmp_node->next=list->iterator;
        for(i=0; i<list->size; i++){                            // finding the node before the current one.
            if(list->head[i].next==list->iterator){
                break;
            }
        }
        list->head[i].next=tmp_element;
    }
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element){
    assert(list && element);
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if(list->iterator==NULL){
        return LIST_INVALID_CURRENT;
    }
    ListElement tmp_element=list->CopyE(element);
    if(tmp_element==NULL){
        return LIST_OUT_OF_MEMORY;
    }
    Node tmp_node=CreateNode(tmp_element, list->CopyE);           // the created node's 'next' field points to NULL.
    if(tmp_node==NULL){
        free(tmp_element);
        return LIST_OUT_OF_MEMORY;
    }
    tmp_node->next=list->iterator->next;
    list->iterator->next=tmp_node;
    list->size++;
    return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list){
    assert(list);
    int i;                                                      // setting the i here so for will you use it twice.
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if(list->iterator==NULL){
        return LIST_INVALID_CURRENT;
    }
    if(list->iterator==list->head){                                 // if the iterator points to the first node.
       list->head=list->iterator->next;
       DestroyNode(list->iterator, list->FreeE);
    }
    else {
        if (list->iterator == &(list->head[list->size - 1])) {                   // if the iterator points to the last node.
            for (i = 0; i < list->size; i++) {
                if (list->head[i].next == list->iterator) {
                    break;
                }
            }
            list->head[i].next = NULL;
            DestroyNode(list->iterator, list->FreeE);
        } else {                                              // if the iterator points somewhere in the middle of the linked list
            for (i = 0; i < list->size; i++) {
                if (list->head[i].next == list->iterator) {
                    break;
                }
            }
            list->head[i].next=list->iterator->next;
            DestroyNode(list->iterator, list->FreeE);
        }
    }
    list->iterator=NULL;
    list->size--;
    return LIST_SUCCESS;
}

ListElement listGetCurrent(List list){                  // returns the data itself! Not the node containing the data.
    assert(list);
    if(list == NULL || list->iterator == NULL){   // Caution: if the list is NULL and we do list->iterator we may get SEG FAULT
        return NULL;
    }
    return list->iterator->data;
}
//
typedef int(*CompareListElements)(ListElement, ListElement);                // delet dis
//
ListResult listSort(List list, CompareListElements compareElement){
    assert(list && compareElement);
    int i;
    if(list == NULL || compareElement === NULL){
        return LIST_NULL_ARGUMENT;
    }
    for(i=0; i<list->size-1; i++){
        compareElement(list->head[i].data, list->head[i+1].data);
    }

}









