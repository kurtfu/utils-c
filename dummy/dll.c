/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include <stdbool.h>
#include <stddef.h>

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define DLL_OK             0
#define DLL_NULL_PTR       (-1)
#define DLL_INVALID_CONFIG (-2)
#define DLL_BAD_ALLOCATION (-3)

struct dll_node
{
    int data;

    struct dll_node* prev;
    struct dll_node* next;
};

struct dll
{
    struct dll_node* head;
    struct dll_node* tail;

    void* (*allocator)(size_t);
    void (*deleter)(void*);

    size_t size;
};

static int dll_validate(struct dll* self)
{
    int result = DLL_OK;

    if (NULL == self)
    {
        result = DLL_NULL_PTR;
    }
    else if (NULL == self->allocator || NULL == self->deleter)
    {
        result = DLL_INVALID_CONFIG;
    }

    return result;
}

int dll_push_back(struct dll* self, int data)
{
    int result = dll_validate(self);
    struct dll_node* node = NULL;

    if (DLL_OK == result)
    {
        node = self->allocator(sizeof(struct dll_node));

        if (NULL == node)
        {
            result = DLL_BAD_ALLOCATION;
        }
    }

    if (DLL_OK == result)
    {
        node->data = data;

        node->prev = self->tail;
        node->next = NULL;

        if (0 == self->size)
        {
            self->head = node;
        }
        else
        {
            self->tail->next = node;
        }

        self->tail = node;
        self->size++;
    }

    return result;
}

int dll_pop_back(struct dll* self)
{
    int result = dll_validate(self);

    if (DLL_OK == result && 0 != self->size)
    {
        self->tail = self->tail->prev;

        if (1 == self->size)
        {
            self->deleter(self->head);
            self->head = self->tail;
        }
        else
        {
            self->deleter(self->tail->next);
        }

        self->size--;
    }

    return result;
}
