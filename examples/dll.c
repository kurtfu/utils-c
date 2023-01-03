/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "dll.h"

#include <stdlib.h>
#include <stdio.h>

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define LIST_SIZE 4

/*****************************************************************************/
/*  SAMPLE FUNCTIONS                                                         */
/*****************************************************************************/

DLL_DECLARE(int)
DLL_DEFINE(int)

/*****************************************************************************/
/*  MAIN APPLICATION                                                         */
/*****************************************************************************/

int main(void)
{
    DLL_CREATE(int, malloc, free, list);

    for (int i = 0; i < LIST_SIZE; ++i)
    {
        printf("Pushing %d to the list\n", i);
        dll_push_back(int, &list, i);
    }

    printf("\nThe size of the list after push: %llu\n\n", list.size);

    while (0 != list.size)
    {
        printf("Popping %d to the list\n", list.tail->data);
        dll_pop_back(int, &list);
    }

    printf("\nThe size of the list after pop: %llu\n", list.size);
    return 0;
}
