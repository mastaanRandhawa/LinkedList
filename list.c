#include "list.h"
#include <assert.h>
#include <stdlib.h>

// Define a static pool for list nodes and heads
static Node nodePool[LIST_MAX_NUM_NODES];
static List listPool[LIST_MAX_NUM_HEADS];

// Variables to track the usage of nodes and heads
static int numFreeNodes = LIST_MAX_NUM_NODES;
static int numFreeHeads = LIST_MAX_NUM_HEADS;
static int poolsInitialized = 0; // Keep track of whether pools have been initialized
static int headpoolsInitialized = 0; // Keep track of whether head pools have been initialized

// Stack to keep track of free nodes
static int freeNodeStack[LIST_MAX_NUM_NODES];
static int StackTopINdx = -1; // Initialize stack top to -1 to indicate empty stack

static int freeListStack[LIST_MAX_NUM_HEADS];
static int listStackTopINdx = -1; // Initialize stack top to -1 to indicate empty stack

// Updated function to initialize the static node pool and free node stack
static void initializeNodePool() {
    for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
        nodePool[i].next = NULL;
        nodePool[i].prev = NULL;
        nodePool[i].data = NULL;
        // Push the node index stack 
        freeNodeStack[i] = i;
    }
    StackTopINdx = LIST_MAX_NUM_NODES - 1; // Set the top of the stack to the last index
}

//FUnction to make sure the node pool is initalized only once
static void initializePoolsIfNeeded() {
    if (!poolsInitialized) {
        initializeNodePool();
        poolsInitialized = 1;
    }
}
// Function to initialize the static list head pool
static void initializeListPool() {
    for (int i = 0; i < LIST_MAX_NUM_HEADS; i++) {
        listPool[i].head = NULL;
        listPool[i].tail = NULL;
        listPool[i].curr = NULL;
        listPool[i].size = 0;
        listPool[i].oob_start = false;
        listPool[i].oob_end = false;

        //push free head into the empty stack
        freeListStack[i] = i;
    }
    listStackTopINdx = LIST_MAX_NUM_HEADS - 1; // Set the top of the stack to the last index
}

//FUnction to make sure the node pool is initalized only once
static void initializeHeadPoolsIfNeeded() {
    if (!headpoolsInitialized) {
        initializeListPool();
        headpoolsInitialized = 1;
    }
}

// function to find and allocate a free node in O(1) time
static Node* allocateNode() {
    if (StackTopINdx < 0) {
        return NULL; // No free nodes available
    }
    // Pop a node index off the stack of free nodes
    int nodeIndex = freeNodeStack[StackTopINdx--];
    numFreeNodes--;
    return &nodePool[nodeIndex];
}

// function to free a node in O(1) time
static void freeNode(Node* node) {

    if (node != NULL) {
        node->data = NULL;
        node->next = NULL;
        node->prev = NULL;
        // Push the node index onto the stack of free nodes
        int nodeIndex = node - nodePool; // Calculate index based on pointer arithmetic
        freeNodeStack[++StackTopINdx] = nodeIndex;
        numFreeNodes++;
    } 
}

//######################################################################################################################
//######################################################################################################################

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){

    //Initialize the node pool
    initializePoolsIfNeeded();
    // Initialize the list head pool if it hasn't been initialized yet
    initializeHeadPoolsIfNeeded();

    if (listStackTopINdx < 0) {
        return NULL; // No free list heads available
    }
    // Pop a list head index off the stack of free list heads
    int listIndex = freeListStack[listStackTopINdx];
    listStackTopINdx--;
    numFreeHeads--;

    return &listPool[listIndex];
}

// Returns the number of items in pList.
int List_count(List* pList){
    return pList->size;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    assert(pList != NULL);

    pList->curr = pList->head;//sets the first item the current item
    if (pList->curr == NULL) {
        return NULL;
    }
    return pList->curr->data;// void pointer to the item
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
    assert(pList != NULL);

    pList->curr = pList->tail;//sets the last item the current item
    if (pList->curr == NULL) {
        return NULL;
    }
    return pList->curr->data;// void pointer to the item
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){

    assert(pList != NULL);

    // Check if the list is empty or if we are already out of bounds at the end
    if (pList->curr == NULL || pList->oob_end) {
        // already at the end and trying to move forward, set the flag
        pList->oob_end = true;
        return NULL;
    }

    // Move the current pointer forward
    pList->curr = pList->curr->next;
   
    // Check if we have moved out of bounds at the end
    if (pList->curr == NULL) {
        pList->oob_end = true;
        return NULL;
    }

    // successfully moved forward, reset out-of-bounds flags
    pList->oob_end = false;
    return pList->curr->data;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){

    assert(pList != NULL);

    // Check if the list is empty or if we are already out of bounds at the start
    if (pList->curr == NULL || pList->oob_start) {
        // already at the start and trying to move back, set the flag
        pList->oob_start = true;
        return NULL;
    }

    // Move the current pointer back
    pList->curr = pList->curr->prev;
    
    // Check if we have moved out of bounds at the start
    if (pList->curr == NULL) {
        pList->oob_start = true;
        return NULL;
    }

    // successfully moved back, reset out-of-bounds flags
    pList->oob_start = false;
    return pList->curr->data;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
    assert(pList != NULL);

    return pList->curr->data;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem){
   assert(pList != NULL);

    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return -1; // Allocation failed
    }
    newNode->data = pItem;

    // If the list is empty, add to the start, which is also the end.
    if (pList->head == NULL) {
        pList->head = newNode;
        pList->tail = newNode;
        pList->curr = newNode; // Set current to the new node
    }
    // If curr is beyond the end, add to the end.
    else if (pList->curr == NULL || pList->oob_end) {
        pList->tail->next = newNode;
        newNode->prev = pList->tail;
        pList->tail = newNode;
        pList->curr = newNode; // Set current to the new node
    }
    // If curr is not NULL, add after curr.
    else {
        newNode->next = pList->curr->next;
        newNode->prev = pList->curr;
        if (pList->curr->next == NULL) { // curr was at the end
            pList->tail = newNode;
        } else { // curr was not at the end
            pList->curr->next->prev = newNode;
        }
        pList->curr->next = newNode;
        pList->curr = newNode; // set current to new node
    }

    pList->size++;
    return 0;

}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem){
    assert(pList != NULL);

    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return -1;
    }
    newNode->data = pItem;

    // If the list is empty, add to start.
    if (pList->head == NULL) {
        pList->head = newNode;
        pList->tail = newNode;
    }
    // If curr is before the start, add to start.
    else if (pList->curr == NULL || pList->oob_start) {
        newNode->next = pList->head;
        pList->head->prev = newNode;
        pList->head = newNode;
    }
    // If curr is not NULL, add before curr.
    else {
        newNode->next = pList->curr;
        newNode->prev = pList->curr->prev;
        if (pList->curr->prev != NULL) {
            pList->curr->prev->next = newNode;
        }
        else { // curr was at the head
            pList->head = newNode;
        }
        pList->curr->prev = newNode;
    }
    pList->size++;
    pList->curr = newNode;
    return 0;

}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    assert(pList != NULL);

    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return -1;
    }
    newNode->data = pItem;

    if (pList->tail == NULL) { // List is empty
        pList->head = newNode;
        pList->tail = newNode;
    } 
    else {
        pList->tail->next = newNode;
        newNode->prev = pList->tail;
        pList->tail = newNode;
    }
    pList->size++;
    pList->curr = newNode;
    return 0;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    assert(pList != NULL);

    Node* newNode = allocateNode();
    if (newNode == NULL) {
        return -1;
    }
    newNode->data = pItem;

    if(pList->tail == NULL){
        pList->head = newNode;
        pList->tail = newNode;
    }
    else {
        newNode->next = pList->head;
        pList->head->prev = newNode;
        pList->head = newNode;
    } 
    pList->size++;
    pList->curr = newNode;
    return 0;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    assert(pList != NULL);

    // Return NULL if before start or beyond end of the list
    if (pList->curr == NULL) {
        return NULL;
    }

    Node* nodeToRemove = pList->curr;
    void* item = nodeToRemove->data;

    // If it's the only node in the list
    if (pList->head == pList->tail) {//////////////////
        pList->head = NULL;
        pList->tail = NULL;
        pList->curr = NULL;
    }
    // If the node to remove is the head
    else if (nodeToRemove == pList->head) {
        pList->head = nodeToRemove->next;
        if (pList->head != NULL) {
            pList->head->prev = NULL;
        }
        pList->curr = pList->head;
    }
    // If the node to remove is the tail
    else if (nodeToRemove == pList->tail) {
        pList->tail = nodeToRemove->prev;
        pList->tail->next = NULL;
        pList->curr = NULL; // Since there's no next node
    }
    // Removing a middle node
    else {
        nodeToRemove->prev->next = nodeToRemove->next;
        nodeToRemove->next->prev = nodeToRemove->prev;
        pList->curr = nodeToRemove->next;
    }

    // Update list size and free the node
    pList->size--;
    freeNode(nodeToRemove);
    return item;
}


// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    assert(pList != NULL);

    if (pList->tail == NULL) {
        return NULL;
    }
    Node* nodeToRemove = pList->tail;
    void* item = nodeToRemove->data;

    pList->tail = nodeToRemove->prev;
    if (pList->tail != NULL) {
        pList->tail->next = NULL;
    } else {
        // The list is now empty
        pList->head = NULL;
    }

    if (pList->curr == nodeToRemove) {
        pList->curr = pList->tail;
    }

    pList->size--;
    freeNode(nodeToRemove);
    return item;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2) { 
    assert(pList1 != NULL && pList2 != NULL);

    if (pList2->head == NULL) {
        return; // pList2 is empty, nothing to do
    }

    // If pList1 is not empty, link its last node to pList2's first node
    if (pList1->tail != NULL) {
        pList1->tail->next = pList2->head;
        pList2->head->prev = pList1->tail;
    } 
    else {
        // If pList1 is empty, just set its head to pList2's head
        pList1->head = pList2->head;
    }

    // Update the tail of pList1 to be the tail of pList2
    pList1->tail = pList2->tail;

    pList1->size = pList2->size + pList1->size;
    // Reset pList2
    int listIndex = pList2 - listPool; // Calculate index based on pointer arithmetic
    freeListStack[listStackTopINdx] = listIndex;
    listStackTopINdx++;
    numFreeHeads++;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn){
    assert(pList != NULL);
    assert(pItemFreeFn != NULL);

    // Iterate through each node in the list
    Node* currentNode = pList->head;
    while (currentNode != NULL) {
        Node* tempNode = currentNode;
        currentNode = currentNode->next;

        // Free the data in the node using the provided function
        pItemFreeFn(tempNode->data);

        freeNode(tempNode);
    }

    // Reset the list structure
    pList->head = NULL;
    pList->tail = NULL;
    pList->curr = NULL;
    pList->size = 0;
    pList->oob_start = false;
    pList->oob_end = false;

    // Add the list head back to the pool of available list heads
    int listIndex = pList - listPool; // Correct reference to listPool
    listStackTopINdx++;
    freeListStack[listStackTopINdx] = listIndex;
    numFreeHeads++;
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    assert(pList != NULL && pComparator != NULL);

    Node* currentNode = pList->curr;

    // Reset out-of-bounds flags
    pList->oob_start = false;
    pList->oob_end = false;

    // If the current pointer is before the start of the pList, start from the head
    if (currentNode == NULL) {
        currentNode = pList->head;
    }

    while (currentNode != NULL) {
        if (pComparator(currentNode->data, pComparisonArg)) {
            pList->curr = currentNode;
            return currentNode->data;
        }
        currentNode = currentNode->next;
    }

    // Set the out-of-bounds end flag if no match was found
    pList->oob_end = true;
    pList->curr = NULL; // Ensuring the current pointer is NULL to indicate end of list
    return NULL; // No match found
}







