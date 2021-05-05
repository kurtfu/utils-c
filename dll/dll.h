#ifndef DLL_H
#define DLL_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include <stdbool.h>

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define DLL_OK               0
#define DLL_NULL_PTR        -1
#define DLL_INVALID_CONFIG  -2
#define DLL_INVALID_NODE    -3

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

struct dll
{
    void* head;
    void* tail;

    void* (*node)(void);

    void (*mov)(void* node, void const* data);
    void (*del)(void* node);

    void** (*prev)(void const* node);
    void** (*next)(void const* node);

    int size;
};

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int dll_init   (struct dll* dll);

int dll_push   (struct dll* dll, void const* data);
int dll_pop    (struct dll* dll);

int dll_insert (struct dll* dll, void const* data);
int dll_erase  (struct dll* dll);

int dll_remove (struct dll* dll, void* node);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* DLL_H */
