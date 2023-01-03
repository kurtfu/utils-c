/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "cbuf.h"
#include <stdio.h>

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define BUFFER_SIZE 4

/*****************************************************************************/
/*  SAMPLE FUNCTIONS                                                         */
/*****************************************************************************/

CBUF_DECLARE(int)
CBUF_DEFINE(int)

/*****************************************************************************/
/*  MAIN APPLICATION                                                         */
/*****************************************************************************/

int main(void)
{
    int buf[BUFFER_SIZE] = {0};
    CBUF_CREATE(int, cbuf, buf, BUFFER_SIZE);

    printf("Capacity of the circular buffer: %llu\n\n", cbuf.capacity);

    for (int i = 0; i < BUFFER_SIZE + 1; ++i)
    {
        printf("Pushing %d to the circular buffer\n", i);
        cbuf_push(int, &cbuf, i);
    }

    printf("\nCircular buffer size after push: %llu\n\n", cbuf.size);

    while (0 != cbuf.size)
    {
        printf("Popping %d to the circular buffer\n", *cbuf.read);
        cbuf_pop(int, &cbuf);
    }

    printf("\nThe size of the circular buffer after pop: %llu\n", cbuf.size);
    return 0;
}
