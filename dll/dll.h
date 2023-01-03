#ifndef DLL_H
#define DLL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include <stdbool.h>
#include <stddef.h>

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

enum
{
    DLL_OK = 0,
    DLL_NULL_PTR = -1,
    DLL_INVALID_CONFIG = -2,
    DLL_BAD_ALLOCATION = -3
};

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define DLL_DECLARE(T)                                  \
    struct dll_node_##T                                 \
    {                                                   \
        T data;                                         \
                                                        \
        struct dll_node_##T* prev;                      \
        struct dll_node_##T* next;                      \
    };                                                  \
                                                        \
    struct dll_##T                                      \
    {                                                   \
        struct dll_node_##T* head;                      \
        struct dll_node_##T* tail;                      \
                                                        \
        void* (*allocator)(size_t);                     \
        void (*deleter)(void*);                         \
                                                        \
        size_t size;                                    \
    };                                                  \
                                                        \
    int dll_push_back_##T(struct dll_##T* dll, T data); \
    int dll_pop_back_##T(struct dll_##T* dll);

#define DLL_DEFINE(T)                                              \
    static int dll_validate_##T(struct dll_##T* self)              \
    {                                                              \
        int result = DLL_OK;                                       \
                                                                   \
        if (NULL == self)                                          \
        {                                                          \
            result = DLL_NULL_PTR;                                 \
        }                                                          \
        else if (NULL == self->allocator || NULL == self->deleter) \
        {                                                          \
            result = DLL_INVALID_CONFIG;                           \
        }                                                          \
                                                                   \
        return result;                                             \
    }                                                              \
                                                                   \
    int dll_push_back_##T(struct dll_##T* self, T data)            \
    {                                                              \
        int result = dll_validate_##T(self);                       \
        struct dll_node_##T* node = NULL;                          \
                                                                   \
        if (DLL_OK == result)                                      \
        {                                                          \
            node = self->allocator(sizeof(struct dll_node_##T));   \
                                                                   \
            if (NULL == node)                                      \
            {                                                      \
                result = DLL_BAD_ALLOCATION;                       \
            }                                                      \
        }                                                          \
                                                                   \
        if (DLL_OK == result)                                      \
        {                                                          \
            node->data = data;                                     \
                                                                   \
            node->prev = self->tail;                               \
            node->next = NULL;                                     \
                                                                   \
            if (0 == self->size)                                   \
            {                                                      \
                self->head = node;                                 \
            }                                                      \
            else                                                   \
            {                                                      \
                self->tail->next = node;                           \
            }                                                      \
                                                                   \
            self->tail = node;                                     \
            self->size++;                                          \
        }                                                          \
                                                                   \
        return result;                                             \
    }                                                              \
    int dll_pop_back_##T(struct dll_##T* self)                     \
    {                                                              \
        int result = dll_validate_##T(self);                       \
                                                                   \
        if (DLL_OK == result && 0 != self->size)                   \
        {                                                          \
            self->tail = self->tail->prev;                         \
                                                                   \
            if (1 == self->size)                                   \
            {                                                      \
                self->deleter(self->head);                         \
                self->head = self->tail;                           \
            }                                                      \
            else                                                   \
            {                                                      \
                self->deleter(self->tail->next);                   \
            }                                                      \
                                                                   \
            self->size--;                                          \
        }                                                          \
                                                                   \
        return result;                                             \
    }

#define DLL_CREATE(T, Allocator, Deleter, name) \
    struct dll_##T name                         \
    {                                           \
        /* .head      = */ NULL,                \
        /* .tail      = */ NULL,                \
        /* .allocator = */ (Allocator),         \
        /* .deleter   = */ (Deleter),           \
        /* .size      = */ 0                    \
    }

#define dll_push_back(T, self, data) dll_push_back_##T(self, data)
#define dll_pop_back(T, self)        dll_pop_back_##T(self)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DLL_H */
