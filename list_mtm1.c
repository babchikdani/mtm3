#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include "list_mtm1.h"



typedef struct node* Node;
struct node {
    ListElement data;
    Node next;
};
// recives two pointers to nodes a and b, swaps the data that each of the node contains. The next field isn't affected.
static void swap(struct node* a, struct node *b);

static void swap(struct node *a, struct node *b) {
    ListElement temp = a->data;
    a->data = b->data;
    b->data = temp;
    return;
}

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

struct list_t {
    Node head;
    Node iterator;
    int size;
    CopyListElement CopyE;
    FreeListElement FreeE;
};

List listCreate(CopyListElement copyElement, FreeListElement freeElement){
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

    if(list->size==1){
        DestroyNode(list->head,list->FreeE);
        free(list);
        return;
    }
    Node ptr1= list->head;
    Node ptr2= ptr1->next;
    for(;ptr2->next!=NULL;ptr2=ptr2->next){        // Yesh po makom leshgiot!!!!!!!!!!!!!!!!!!!!!
        DestroyNode(ptr1,list->FreeE);
        ptr1=ptr2;
    }
    free(list);
    return;
}

List listCopy(List list){
    if(list==NULL){
        return NULL;
    }
    assert(list);
    List tmp_list=listCreate(list->CopyE, list->FreeE);
    if(tmp_list==NULL) {
        return NULL;
    }
    Node nodeptr=list->head;
    for (;  nodeptr!=NULL ; nodeptr=nodeptr->next) {
        ListElement tmp_element = list->CopyE(nodeptr->data);       // copying the current elemeent from the og list
        if (tmp_element == NULL) {
            listDestroy(tmp_list);                          // Should i destroy tmp_element aswell?
            return NULL;
        }
        if(nodeptr==list->head) {
            Node tmp_node = CreateNode(tmp_element, list->CopyE);
            if (tmp_node == NULL) {
                listDestroy(tmp_list);
                DestroyNode(tmp_node, list->FreeE);
                return NULL;
            }
            tmp_list->head = tmp_node;
        }
        else{
            if (nodeptr==list->iterator){
                Node tmp_node=CreateNode(tmp_element, list->CopyE);
                if(tmp_node==NULL){
                    listDestroy(tmp_list);
                    DestroyNode(tmp_node, list->FreeE);
                    return NULL;
                }
                tmp_list->iterator=tmp_node;
            }
            else{
                ListResult res = listInsertLast(tmp_list, nodeptr->data);
                if(res!=LIST_SUCCESS)
                {
                    listDestroy(tmp_list);
                    return NULL;
                }
            }
        }

    }
    tmp_list->size=list->size;
    return tmp_list;
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
    return list->head->data;
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
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    assert(list && element);
    ListElement tmp_element=list->CopyE(element);
    if(tmp_element==NULL){
        return LIST_OUT_OF_MEMORY;
    }
    Node tmp_node=CreateNode(tmp_element, list->CopyE);           // the created node's 'next' field points to NULL.
    if(tmp_node==NULL){
        free(tmp_element);
        return LIST_OUT_OF_MEMORY;
    }
    Node lastNodePtr=list->head;                    // from here we:
    for (int i = 0; i < list->size-1; i++) {
        lastNodePtr=lastNodePtr->next;
    }
    lastNodePtr->next=tmp_node;                       // Going to the last node and changing the 'next' field to the tmp_node
    list->size++;
    return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element){
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    assert(list && element);
    if(list->iterator==NULL){
        return LIST_INVALID_CURRENT;
    }
    ListElement tmp_element=list->CopyE(element);
    if(tmp_element==NULL){
        return LIST_OUT_OF_MEMORY;
    }
    Node tmp_node=CreateNode(tmp_element, list->CopyE);           // the created node's 'next' field points to NULL.
    free(tmp_element);                                            // Both CopyE and CreateNode allocate memory for the element.
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
        Node nodeptr=list->head;                          // finding the node before the current one
        while(nodeptr->next != list->iterator){
            nodeptr=nodeptr->next;
        }
        nodeptr->next=tmp_node;
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
    if(list==NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if(list->iterator==NULL){
        return LIST_INVALID_CURRENT;
    }
    Node nodeBeforeTheIterator=list->head;                          // finding the node before the current one
    while(nodeBeforeTheIterator->next != list->iterator){
        nodeBeforeTheIterator=nodeBeforeTheIterator->next;
    }
    if(list->iterator==list->head){                                 // if the iterator points to the first node.
       list->head=list->iterator->next;
       DestroyNode(list->iterator, list->FreeE);
    }
    else {
        nodeBeforeTheIterator->next=list->iterator->next;
        DestroyNode(list->iterator, list->FreeE);
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

ListResult listSort(List list, CompareListElements compareElement){
    assert(list && compareElement);
    if(list == NULL || compareElement == NULL){
        return LIST_NULL_ARGUMENT;
    }
    if(list->size==1 || list->size==0){            // what if size is zero? ***********************************************
        return LIST_SUCCESS;
    }
    int j=0;
    Node nodeptr1=list->head;                  // j - will contain the index of the current iterator index. head's index is 0;
    while(nodeptr1!=list->iterator){
        j++;
        nodeptr1=nodeptr1->next;
    }
    nodeptr1=list->head;
    Node nodeptr2=list->head->next;
    int n=listGetSize(list) - 1;
    while(n!=0) {                                                                       // BUBBLE SORT
        for (; nodeptr2->next!=NULL; nodeptr1=nodeptr1->next, nodeptr2=nodeptr2->next) {
            if (compareElement(nodeptr1->data, nodeptr2->data) < 0) {
                swap(nodeptr1->data, nodeptr2->data);
            }
        }
        n--;
        nodeptr1=list->head;
        nodeptr2=list->head->next;
    }                                                                                    // BUBBLE SORT
    list->iterator=list->head;
    while(j!=0){                                             // Setting the iterator to point to his original index.
        j--;
        list->iterator=list->iterator->next;
    }
    return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
    if(list==NULL || filterElement==NULL){                  // No need to check if the key is NULL. <- AKA to FAQ.
        return NULL;
    }
    List tmp_list=listCreate(list->CopyE, list->FreeE);                 // tmp_list's head, iterator and size are NULL/zero
    if(tmp_list==NULL){                                                 // don't forget to tmp_list->size++ everytime...
        return NULL;
    }
    for (Node nodeptr=list->head ; nodeptr!=NULL; nodeptr=nodeptr->next) {
        if(filterElement(nodeptr->data, key)){
            ListResult res=listInsertFirst(tmp_list, nodeptr->data);       // Will SURELY never recieve tmp_list as NULL arg.
            if(res==LIST_OUT_OF_MEMORY){
                return NULL;
            }                               // Here we sure know that it's ListSuccess!!!
        }
    }
    return tmp_list; // WARNING: tmp_list iterator is still set to NULL! FAQ said that listInsertFirst doesn't change the iterator
}

ListResult listClear(List list){
    if(list==NULL){
        return LIST_NULL_ARGUMENT;
    }
    Node nodeptr=list->head;
    DestroyNode(nodeptr, list->FreeE);
    return LIST_SUCCESS;
}








