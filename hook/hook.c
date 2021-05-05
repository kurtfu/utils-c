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

    struct hook* next;
};

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int hook_attach(struct subject* subject, void (*hook)(void* args), void* args)
{
    int result = HOOK_OK;

    if (NULL == subject || NULL == hook)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        struct hook* node = malloc(sizeof(struct hook));

        if (NULL == node)
        {
            result = HOOK_ATTACH_FAILED;
        }
        else
        {
            node->event = hook;
            node->args  = args;

            node->next    = subject->list;
            subject->list = node;
        }
    }

    return result;
}

int hook_detach(struct subject* subject, void (*hook)(void* args))
{
    int result = HOOK_OK;

    if (NULL == subject || NULL == hook)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        struct hook* node = subject->list;
        struct hook* prev = subject->list;

        while (NULL != node && node->event != hook)
        {
            prev = node;
            node = node->next;
        }

        if (NULL != node)
        {
            if (node == subject->list)
            {
                subject->list = node->next;
            }
            else
            {
                prev->next = node->next;
            }

            free(node);
        }
    }

    return result;
}

int hook_notify(struct subject* subject)
{
    int result = HOOK_OK;

    if (NULL == subject)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        struct hook* node = subject->list;

        while (NULL != node)
        {
            node->event(node->args);
            node = node->next;
        }
    }

    return result;
}
