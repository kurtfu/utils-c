/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "cbuf.h"
#include <stddef.h>

/*****************************************************************************/
/*  PRIVATE FUNCTION INTERFACES                                              */
/*****************************************************************************/

static int cbuf_instance_check(struct cbuf const* cbuf);
static void cbuf_advance(struct cbuf* cbuf);
static void cbuf_retreat(struct cbuf* cbuf);

/*****************************************************************************/
/*  PUBLIC FUNCTIONS                                                         */
/*****************************************************************************/

int cbuf_init(struct cbuf* cbuf)
{
    int result = cbuf_instance_check(cbuf);

    if (CBUF_OK == result)
    {
        cbuf_flush(cbuf);
    }

    return result;
}

void cbuf_flush(struct cbuf* cbuf)
{
    if (NULL != cbuf)
    {
        cbuf->read = 0;
        cbuf->write = 0;

        cbuf->size = 0;
    }
}

int cbuf_put(struct cbuf* cbuf, void const* data)
{
    int result = cbuf_instance_check(cbuf);

    if (CBUF_OK == result)
    {
        cbuf->put(cbuf, data);
        cbuf_advance(cbuf);
    }

    return result;
}

void* cbuf_get(struct cbuf* cbuf)
{
    void* data = NULL;
    int result = cbuf_instance_check(cbuf);

    if (CBUF_OK == result && 0 != cbuf->size)
    {
        data = cbuf->get(cbuf);
        cbuf_retreat(cbuf);
    }

    return data;
}

/*****************************************************************************/
/*  PRIVATE FUNCTIONS                                                        */
/*****************************************************************************/

static int cbuf_instance_check(struct cbuf const* cbuf)
{
    int result;

    if (NULL == cbuf)
    {
        result = CBUF_NULL_PTR;
    }
    else if (NULL == cbuf->put || NULL == cbuf->get)
    {
        result = CBUF_INVALID_CONFIG;
    }
    else if (cbuf->cap <= 0)
    {
        result = CBUF_INVALID_CAPACITY;
    }
    else
    {
        result = CBUF_OK;
    }

    return result;
}

static void cbuf_advance(struct cbuf* cbuf)
{
    if (cbuf->size == cbuf->cap)
    {
        cbuf->read = (cbuf->read == cbuf->cap - 1) ? 0 : cbuf->read + 1;
    }
    else
    {
        cbuf->size++;
    }

    cbuf->write = (cbuf->write == cbuf->cap - 1) ? 0 : cbuf->write + 1;
}

static void cbuf_retreat(struct cbuf* cbuf)
{
    cbuf->read = (cbuf->read == cbuf->cap - 1) ? 0 : cbuf->read + 1;
    cbuf->size--;
}
