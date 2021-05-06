/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "hook.h"
#include <stdlib.h>

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

struct hook
{
    void (*event)(void* args);
    void* args;

    struct hook* prev;
    struct hook* next;
};

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int hook_attach(struct subject* subj, void (*event)(void* args), void* args)
{
    int result = HOOK_OK;
    struct hook* hook = NULL;

    if (NULL == subj || NULL == event)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        hook = malloc(sizeof(struct hook));

        if (NULL == hook)
        {
            result = HOOK_INVALID_HOOK;
        }
    }

    if (HOOK_OK == result)
    {
        hook->event = event;
        hook->args  = args;

        hook->prev = NULL;
        hook->next = subj->list;

        if (NULL != subj->list)
        {
            subj->list->prev = hook;
        }

        subj->list = hook;
    }

    return result;
}

int hook_detach(struct subject* subj, void (*event)(void* args))
{
    int result = HOOK_OK;

    if (NULL == subj || NULL == event)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        struct hook* hook = subj->list;

        while (NULL != hook && hook->event != event)
        {
            hook = hook->next;
        }

        if (NULL != hook)
        {
            if (hook == subj->list)
            {
                subj->list = hook->next;
                subj->list->prev = NULL;
            }
            else
            {
                hook->prev->next = hook->next;
                hook->next->prev = hook->prev;
            }

            free(hook);
        }
    }

    return result;
}

int hook_notify(struct subject* subj)
{
    int result = HOOK_OK;

    if (NULL == subj)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        struct hook* hook = subj->list;

        while (NULL != hook)
        {
            hook->event(hook->args);
            hook = hook->next;
        }
    }

    return result;
}
