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

int hook_attach(struct subject* subject, void (*hook)(void* args), void* args)
{
    int result = HOOK_OK;
    struct hook* node = NULL;

    if (NULL == subject || NULL == hook)
    {
        result = HOOK_NULL_PTR;
    }

    if (HOOK_OK == result)
    {
        node = malloc(sizeof(struct hook));

        if (NULL == node)
        {
            result = HOOK_ATTACH_FAILED;
        }
    }

    if (HOOK_OK == result)
    {
        node->event = hook;
        node->args  = args;

        node->prev = NULL;
        node->next = subject->list;

        if (NULL != subject->list)
        {
            subject->list->prev = node;
        }

        subject->list = node;
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

        while (NULL != node && node->event != hook)
        {
            node = node->next;
        }

        if (NULL != node)
        {
            if (node == subject->list)
            {
                subject->list = node->next;
                subject->list->prev = NULL;
            }
            else
            {
                node->prev->next = node->next;
                node->next->prev = node->prev;
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
