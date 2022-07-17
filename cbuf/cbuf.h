#ifndef CBUF_H
#define CBUF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include <stdbool.h>

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define CBUF_OK               0
#define CBUF_NULL_PTR         -1
#define CBUF_INVALID_CONFIG   -2
#define CBUF_INVALID_CAPACITY -3

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

struct cbuf
{
    void* buf;

    void (*put)(struct cbuf const* cbuf, void const* data);
    void* (*get)(struct cbuf const* cbuf);

    int read;
    int write;

    int cap;
    int size;

    bool full;
};

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int cbuf_init(struct cbuf* cbuf);
void cbuf_flush(struct cbuf* cbuf);
int cbuf_put(struct cbuf* cbuf, void const* data);
void* cbuf_get(struct cbuf* cbuf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CBUF_H */
