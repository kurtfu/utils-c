/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "hook.h"

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/
/*  MODULE VARIABLES                                                         */
/*****************************************************************************/

struct subject call_counter = {
    .alloc = malloc,
    .free = free,
};

/*****************************************************************************/
/*  MODULE FUNCTIONS                                                         */
/*****************************************************************************/

void func(void)
{
    hook_notify(&call_counter);
}

void callback(void* args)
{
    int* count = args;
    printf("func called count: %d\n", ++(*count));
}

/*****************************************************************************/
/*  MAIN APPLICATION                                                         */
/*****************************************************************************/

int main(void)
{
    hook_init(&call_counter);

    int call_count = 0;
    hook_attach(&call_counter, callback, &call_count);

    func();
    func();
    func();

    return 0;
}
