/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "dll.h"
#include <stddef.h>

/*****************************************************************************/
/*  PRIVATE FUNCTION INTERFACES                                              */
/*****************************************************************************/

static int  dll_instance_check (struct dll const* dll);
static bool dll_contains       (struct dll const* dll, void const* node);

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int dll_init(struct dll* dll)
{
    int result = dll_instance_check(dll);

    if (DLL_OK == result)
    {
        dll->head = NULL;
        dll->tail = NULL;

        dll->size = 0;
    }

    return result;
}

int dll_push(struct dll* dll, void const* data)
{
    int   result = dll_instance_check(dll);
    void* node   = NULL;

    if (DLL_OK == result)
    {
        node = dll->node();

        if (NULL == node)
        {
            result = DLL_NULL_PTR;
        }
    }

    if (DLL_OK == result)
    {
        dll->mov(node, data);

        *dll->prev(node) = dll->head;
        *dll->next(node) = NULL;

        if (NULL == dll->head)
        {
            dll->tail = node;
        }
        else
        {
            *dll->next(dll->head) = node;
        }

        dll->head = node;
        dll->size++;
    }

    return result;
}

int dll_pop(struct dll* dll)
{
    int result = dll_instance_check(dll);

    if (DLL_OK == result && NULL != dll->head)
    {
        void* node = dll->head;

        if (dll->head == dll->tail)
        {
            dll->head = NULL;
            dll->tail = NULL;
        }
        else
        {
            dll->head = *dll->prev(dll->head);
            *dll->next(dll->head) = NULL;
        }

        dll->del(node);
        dll->size--;
    }

    return result;
}

int dll_insert(struct dll* dll, void const* data)
{
    int   result = dll_instance_check(dll);
    void* node   = NULL;

    if (DLL_OK == result)
    {
        node = dll->node();

        if (NULL == node)
        {
            result = DLL_NULL_PTR;
        }
    }

    if (DLL_OK == result)
    {
        dll->mov(node, data);

        *dll->prev(node) = NULL;
        *dll->next(node) = dll->tail;

        if (NULL == dll->tail)
        {
            dll->head = node;
        }
        else
        {
            *dll->prev(dll->tail) = node;
        }

        dll->tail = node;
        dll->size++;
    }

    return result;
}

int dll_erase(struct dll* dll)
{
    int result = dll_instance_check(dll);

    if (DLL_OK == result && NULL != dll->tail)
    {
        struct dll_node* node = dll->tail;

        if (dll->tail == dll->head)
        {
            dll->head = NULL;
            dll->tail = NULL;
        }
        else
        {
            dll->tail = *dll->next(dll->tail);
            *dll->prev(dll->tail) = NULL;
        }

        dll->del(node);
        dll->size--;
    }

    return result;
}

int dll_remove(struct dll* dll, void* node)
{
    int result = dll_instance_check(dll);

    if (DLL_OK == result && NULL == node)
    {
        result = DLL_NULL_PTR;
    }

    if (DLL_OK == result && false == dll_contains(dll, node))
    {
        result = DLL_INVALID_NODE;
    }

    if (DLL_OK == result)
    {
        if (node == dll->head)
        {
            dll_pop(dll);
        }
        else if (node == dll->tail)
        {
            dll_erase(dll);
        }
        else
        {
            void* prev = *dll->prev(node);
            void* next = *dll->next(node);

            *dll->next(prev) = next;
            *dll->prev(next) = prev;

            dll->del(node);
            dll->size--;
        }
    }

    return result;
}

/*****************************************************************************/
/*  PRIVATE FUNCTIONS                                                        */
/*****************************************************************************/

static int dll_instance_check(struct dll const* dll)
{
    int result;

    if (NULL == dll)
    {
        result = DLL_NULL_PTR;
    }
    else if (NULL == dll->node)
    {
        result = DLL_INVALID_CONFIG;
    }
    else if (NULL == dll->mov || NULL == dll->del)
    {
        result = DLL_INVALID_CONFIG;
    }
    else if (NULL == dll->prev || NULL == dll->next)
    {
        result = DLL_OK;
    }
    else
    {
        result = DLL_OK;
    }

    return result;
}

static bool dll_contains(struct dll const* dll, void const* node)
{
    bool  found = false;
    void* curr  = dll->tail;

    while (false == found && NULL != curr)
    {
        if (curr == node)
        {
            found = true;
        }
        else
        {
            curr = *dll->next(curr);
        }
    }

    return found;
}
