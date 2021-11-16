/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "hook.h"

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

struct hook
{
    void (*event)(void* args);
    void* args;

    struct hook* next;
};

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

    if (NULL == event)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        struct hook* hook = subj->alloc(sizeof(struct hook));

        if (NULL == hook)
        {
            result = HOOK_INVALID_HOOK;
        }

        if (HOOK_OK == result)
        {
            hook->event = event;
            hook->args  = args;

            hook->next = subj->list;
            subj->list = hook;
        }
    }

    return result;
}

int hook_detach(struct subject* subj, void (*event)(void* args))
{
    int result = hook_instance_check(subj);

    if (NULL == event)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        struct hook* hook = subj->list;
        struct hook* prev = subj->list;

        while (NULL != hook && hook->event != event)
        {
            prev = hook;
            hook = hook->next;
        }

        if (NULL == hook)
        {
            result = HOOK_INVALID_HOOK;
        }

        if (HOOK_OK == result)
        {
            if (hook == subj->list)
            {
                subj->list = hook->next;
            }

            prev->next = hook->next;
            subj->free(hook);
        }
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
            struct hook* next = hook->next;

            hook->event(hook->args);
            hook = next;
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
    else if (NULL == subj->alloc || NULL == subj->free)
    {
        result = HOOK_INVALID_CONFIG;
    }
    else
    {
        result = HOOK_OK;
    }

    return result;
}
