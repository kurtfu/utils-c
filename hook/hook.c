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
    int (*event)(void* args);
    void* args;

    struct hook* next;
};

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int hook_attach(struct subject* subject, int (*hook)(void* args), void* args)
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

int hook_detach(struct subject* subject, int (*hook)(void* args))
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
            int op = node->event(node->args);

            if (HOOK_OP_END != op)
            {
                node = node->next;
            }
            else
            {
                struct hook* next = node->next;

                hook_detach(subject, node->event);
                node = next;
            }
        }
    }

    return result;
}
