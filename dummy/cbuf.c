/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include <stddef.h>

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define CBUF_OK               (0)
#define CBUF_NULL_PTR         (-1)
#define CBUF_INVALID_CAPACITY (-2)

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

struct cbuf
{
    int* buffer;

    int* read;
    int* write;

    size_t size;
    size_t capacity;
};

/*****************************************************************************/
/*  FUNCTION DEFINITIONS                                                     */
/*****************************************************************************/

static int cbuf_validate(struct cbuf* self)
{
    int result = CBUF_OK;

    if (NULL == self)
    {
        result = CBUF_NULL_PTR;
    }
    else if (0 == self->capacity)
    {
        result = CBUF_INVALID_CAPACITY;
    }

    return result;
}

static void cbuf_advance(struct cbuf* self, int** ptr)
{
    int* first = &(self->buffer[0]);
    int* last = &(self->buffer[self->capacity]);

    if (++(*ptr) == last)
    {
        *ptr = first;
    }
}

int cbuf_push(struct cbuf* self, int data)
{
    int result = cbuf_validate(self);

    if (CBUF_OK == result)
    {
        *(self->write) = data;
        cbuf_advance(self, &self->write);

        if (self->size == self->capacity)
        {
            self->read = self->write;
        }
        else
        {
            self->size++;
        }
    }

    return result;
}

int cbuf_pop(struct cbuf* self)
{
    int result = cbuf_validate(self);

    if (CBUF_OK == result)
    {
        self->size--;
        cbuf_advance(self, &self->read);
    }

    return result;
}

int cbuf_clear(struct cbuf* self)
{
    int result = cbuf_validate(self);

    if (CBUF_OK == result)
    {
        self->read = self->buffer;
        self->write = self->buffer;

        self->size = 0;
    }

    return result;
}
