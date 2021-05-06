/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "hook.h"
#include <stddef.h>

/*****************************************************************************/
/*  PRIVATE FUNCTION INTERFACES                                              */
/*****************************************************************************/

static int hook_instance_check(struct subject* subj);

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int hook_init(struct subject* subj)
{
    int result = hook_instance_check(subj);

    if (HOOK_OK == result)
    {
        subj->list = NULL;
    }

    return result;
}

int hook_attach(struct subject* subj, void (*event)(void* args), void* args)
{
    int result = hook_instance_check(subj);
    struct hook* hook = NULL;

    if (NULL == event)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        hook = subj->hook();

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
    int result = hook_instance_check(subj);
    struct hook* hook = NULL;

    if (NULL == event)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        hook = subj->list;

        while (NULL != hook && hook->event != event)
        {
            hook = hook->next;
        }

        if (NULL == hook)
        {
            result = HOOK_INVALID_HOOK;
        }
    }

    if (HOOK_OK == result)
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

        subj->free(hook);
    }

    return result;
}

int hook_notify(struct subject* subj)
{
    int result = hook_instance_check(subj);

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

/*****************************************************************************/
/*  PRIVATE FUNCTIONS                                                        */
/*****************************************************************************/

static int hook_instance_check(struct subject* subj)
{
    int result;

    if (NULL == subj)
    {
        result = HOOK_NULL_PTR;
    }
    else if (NULL == subj->hook || NULL == subj->free)
    {
        result = HOOK_INVALID_CONFIG;
    }
    else
    {
        result = HOOK_OK;
    }

    return result;
}
