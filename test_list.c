
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// Helper function to free items
void freeItem(void* pItem) {
    free(pItem);
}

// Helper function for comparison used in List_search
bool compareInts(void* pItem, void* pComparisonArg) {
    return *(int*)pItem == *(int*)pComparisonArg;
}

void testListCreate() {
    printf("Testing List_create...\n");
    List* myList = List_create();
    assert(myList != NULL);
    printf("List_create: Passed\n\n");
    List_free(myList, freeItem);
}

void testListCount() {
    printf("Testing List_count...\n");
    List* myList = List_create();
    assert(List_count(myList) == 0);

    int* data = malloc(sizeof(int));
    *data = 10;
    List_append(myList, data);
    assert(List_count(myList) == 1);

    printf("List_count: Passed\n\n");
    List_free(myList, freeItem);
}

void testListFirstAndLast() {
    printf("Testing List_first and List_last...\n");
    List* myList = List_create();
    int* data1 = malloc(sizeof(int));
    int* data2 = malloc(sizeof(int));
    *data1 = 10;
    *data2 = 20;

    List_append(myList, data1);
    assert(List_first(myList) == data1);
    assert(List_last(myList) == data1);

    List_append(myList, data2);
    assert(List_first(myList) == data1);
    assert(List_last(myList) == data2);

    printf("List_first and List_last: Passed\n\n");
    List_free(myList, freeItem);
}

void testListNextAndPrev() {
    printf("Testing List_next and List_prev...\n");
    List* myList = List_create();
    int* data1 = malloc(sizeof(int));
    int* data2 = malloc(sizeof(int));
    *data1 = 10;
    *data2 = 20;

    List_append(myList, data1);
    List_append(myList, data2);

    assert(List_first(myList) == data1);


    assert(List_next(myList) == data2);


    assert(List_prev(myList) == data1);

    printf("List_next and List_prev: Passed\n\n");
    List_free(myList, freeItem);
}

void testListInsertAfterAndBefore() {
    printf("Testing List_insert_after and List_insert_before...\n");
    List* myList = List_create();
    int* data1 = malloc(sizeof(int));
    int* data2 = malloc(sizeof(int));
    *data1 = 10;
    *data2 = 20;

    List_append(myList, data1); // List: data1
    List_insert_after(myList, data2); // List: data1 -> data2

    assert(List_count(myList) == 2);
    assert(List_last(myList) == data2);

    int* data3 = malloc(sizeof(int));
    *data3 = 30;
    List_first(myList); // Set curr to the beginning of the list
    List_insert_before(myList, data3); // List: data3 -> data1 -> data2

    assert(List_first(myList) == data3); // Now data3 should be the first item
    assert(List_count(myList) == 3); // The list should have three elements

    printf("List_insert_after and List_insert_before: Passed\n\n");
    List_free(myList, freeItem);
}

void testListRemove() {
    printf("Testing List_remove...\n");
    List* myList = List_create();
    int* data = malloc(sizeof(int));
    *data = 10;

    List_append(myList, data);
    void* removedItem = List_remove(myList);

    assert(removedItem == data);
    assert(List_count(myList) == 0);

    printf("List_remove: Passed\n\n");
    free(removedItem); // Manually free the removed item
    List_free(myList, freeItem);
}

void testListTrim() {
    printf("Testing List_trim...\n");
    List* myList = List_create();
    int* data = malloc(sizeof(int));
    *data = 10;

    List_append(myList, data);
    void* trimmedItem = List_trim(myList);

    assert(trimmedItem == data);
    assert(List_count(myList) == 0);

    printf("List_trim: Passed\n\n");
    free(trimmedItem); // Manually free the trimmed item
    List_free(myList, freeItem);
}

void testListConcat() {
    printf("Testing List_concat...\n");
    List* list1 = List_create();
    List* list2 = List_create();
    int* data1 = malloc(sizeof(int));
    int* data2 = malloc(sizeof(int));
    *data1 = 10;
    *data2 = 20;

    List_append(list1, data1);
    List_append(list1, data2);


    List_concat(list1, list2);
    assert(List_count(list1) == 2);
    assert(List_first(list1) == data1);
    assert(List_last(list1) == data2);

    printf("List_concat: Passed\n\n");
    List_free(list1, freeItem);
}

void testListSearch() {
    printf("Testing List_search...\n");
    List* myList = List_create();
    int* data1 = malloc(sizeof(int));
    int* data2 = malloc(sizeof(int));
    *data1 = 10;
    *data2 = 20;

    List_append(myList, data1);
    List_append(myList, data2);

    List_first(myList); // Set current to first item for search to work from the start
    assert(List_search(myList, compareInts, data2) == data2);

    int notFound = 30;
    assert(List_search(myList, compareInts, &notFound) == NULL);

    printf("List_search: Passed\n\n");
    List_free(myList, freeItem);
}



int main() {
    testListCreate();
    testListCount();
    testListFirstAndLast();
    testListNextAndPrev();
    testListInsertAfterAndBefore();
    testListRemove();
    testListTrim();
    testListConcat();
    testListSearch();

    printf("All tests passed successfully!\n");
    return 0;
}























// #include "list.h"
// #include <stdio.h>
// #include <stdlib.h>

// // Helper function to print the list contents (assuming the data is an int pointer)
// void printList(List* lst) {
//     if (lst == NULL) {
//         printf("List is NULL\n");
//         return;
//     }

//     int count = List_count(lst);
//     printf("List count: %d\n", count);

//     if (count == 0) {
//         printf("List is empty\n");
//         return;
//     }

//     void* item = List_first(lst);
//     while (item != NULL) {
//         printf("%d ", *(int*)item);
//         item = List_next(lst);
//     }
//     printf("\n");
// }

// void testListAppend() {
//     printf("Testing List_append...\n");
//     List* lst = List_create();
//     int data = 10;
//     List_append(lst, &data);

//     if (*(int*)List_first(lst) == 10) {
//         printf("List_append passed: Item appended successfully.\n");
//     } else {
//         printf("List_append failed.\n");
//     }
//     printList(lst);
// }

// void testListPrepend() {
//     printf("Testing List_prepend...\n");
//     List* lst = List_create();
//     int data = 20;
//     List_prepend(lst, &data);

//     if (*(int*)List_first(lst) == 20) {
//         printf("List_prepend passed: Item prepended successfully.\n");
//     } else {
//         printf("List_prepend failed.\n");
//     }
//     printList(lst);
// }

// void testListRemove() {
//     printf("Testing List_remove...\n");
//     List* lst = List_create();
//     int data = 30;
//     List_append(lst, &data);
//     List_remove(lst);

//     if (List_count(lst) == 0) {
//         printf("List_remove passed: Item removed successfully.\n");
//     } else {
//         printf("List_remove failed.\n");
//     }
//     printList(lst);
// }

// void testListTrim() {
//     printf("Testing List_trim...\n");
//     List* lst = List_create();
//     int data = 40;
//     List_append(lst, &data);
//     List_trim(lst);

//     if (List_count(lst) == 0) {
//         printf("List_trim passed: Item trimmed successfully.\n");
//     } else {
//         printf("List_trim failed.\n");
//     }
//     printList(lst);
// }

// void testListConcat() {
//     printf("Testing List_concat...\n");
//     List* lst1 = List_create();
//     List* lst2 = List_create();
//     int data1 = 50, data2 = 60;
//     List_append(lst1, &data1);
//     List_append(lst2, &data2);

//     // printf("List2 count before: %d\n", List_count(lst2));
//     // printf("List1 count before: %d\n", List_count(lst1));
//     // printf("%p pointer list1 \n", lst1->head->data);
//     // printf("%p pointer list1 tail \n", lst1->tail->data);

//     // printf("%p pointer list2 \n", lst2->head->data);
//     // printf("%p pointer list2 tail \n", lst2->tail->data);

//     List_concat(lst1, lst2);

//     // printf("%p after pointer list1 \n", lst1->head->data);
//     // printf("%p after pointer list1 tail \n", lst1->tail->data);
//     // printf("%p after pointer list1 head->next->data \n", lst1->head->next->data);

//     // printf("%p after pointer list2 \n", lst2->head->data);
//     // printf("%p after pointer list2 tail \n", lst2->tail->data);

//     // printf("List1 count after: %d\n", List_count(lst1));
//     // printf("List2 count after: %d\n", List_count(lst2));

//     if (List_count(lst1) == 2) {
//         printf("List_concat passed: Lists concatenated successfully.\n");
//     } else {
//         printf("List count: %d\n", List_count(lst1));
//         printf("List_concat failed.\n");
//     }
//     // printList(lst1);
// }
// void testListCreate() {
//     List* myList = List_create();
//     if (myList != NULL) {
//         printf("List_create passed\n");
//     } else {
//         printf("List_create failed\n");
//     }
//     // Add more checks and clean up
// }


// void testListInsertAndRemove() {
//     // Example for testing List_insert_after and List_remove
//     List* myList = List_create();
//     int data = 10;
//     if (List_insert_after(myList, &data) == LIST_SUCCESS) {
//         printf("List_insert_after passed\n");
//     } else {
//         printf("List_insert_after failed\n");
//     }
//     // Test List_remove and other functions similarly
//     // Clean up
// }


// int main() {
//     testListCreate();
//     testListInsertAndRemove();
//     testListAppend();
//     testListPrepend();
//     testListRemove();
//     testListTrim();
//     testListConcat();

//     // Add more tests for other functions here...

//     return 0;
// }








// ///////////////////
// #include "list.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>

// void freeData(void* pItem) {
//     free(pItem);
// }

// void testListCreate() {
//     List* myList = List_create();
//     assert(myList != NULL);
//     List_free(myList, freeData);  // Assume List_free handles NULL data correctly
//     printf("List_create: Passed\n");
// }

// void testListCount() {
//     List* myList = List_create();
//     int* data = malloc(sizeof(int));
//     *data = 10;
//     List_append(myList, data);
//     assert(List_count(myList) == 1);
//     List_free(myList, freeData);
//     printf("List_count: Passed\n");
// }

// void testListFirstAndLast() {
//     List* myList = List_create();
//     int* data1 = malloc(sizeof(int));
//     int* data2 = malloc(sizeof(int));
//     *data1 = 10;
//     *data2 = 20;
//     List_append(myList, data1);
//     List_append(myList, data2);
//     assert(List_first(myList) == data1);
//     assert(List_last(myList) == data2);
//     List_free(myList, freeData);
//     printf("List_first and List_last: Passed\n");
// }

// void testListNavigation() {
//     List* myList = List_create();
//     int* data1 = malloc(sizeof(int));
//     int* data2 = malloc(sizeof(int));
//     *data1 = 10;
//     *data2 = 20;
//     List_append(myList, data1);
//     List_append(myList, data2);

//     List_first(myList); // Set current to first item

//     // Test List_next
//     assert(List_next(myList) == data2); // Should move to the second item
   
//     // Reset current to first item
//     List_first(myList);

//     // Test List_prev
//     assert(List_prev(myList) == NULL); // Should return NULL as it's already at the start

//     List_free(myList, freeData);
//     printf("List_next and List_prev: Passed\n");
// }

// void testListInsertAndRemove() {
//     List* myList = List_create();
//     int* data = malloc(sizeof(int));
//     *data = 10;
//     assert(List_insert_after(myList, data) == 0);
//     assert(List_remove(myList) == data);
//     free(data); // Manually free since List_remove doesn't call the free function
//     List_free(myList, freeData);
//     printf("List_insert_after and List_remove: Passed\n");
// }

// void testListAppendPrependAndTrim() {
//     List* myList = List_create();
//     int* data1 = malloc(sizeof(int));
//     int* data2 = malloc(sizeof(int));
//     *data1 = 10;
//     *data2 = 20;
//     List_append(myList, data1);
//     List_prepend(myList, data2);
//     assert(List_trim(myList) == data1);
//     assert(List_remove(myList) == data2);
//     free(data1); // Manually free since List_trim doesn't call the free function
//     free(data2); // Manually free since List_remove doesn't call the free function
//     List_free(myList, freeData);
//     printf("List_append, List_prepend, and List_trim: Passed\n");
// }

// int main() {
//     testListCreate();
//     testListCount();
//     testListFirstAndLast();
//     testListNavigation();
//     testListInsertAndRemove();
//     testListAppendPrependAndTrim();
//     printf("All tests passed!\n");
//     return 0;
// }
