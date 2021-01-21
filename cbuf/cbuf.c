/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "cbuf.h"
#include <stddef.h>

/*****************************************************************************/
/*  PRIVATE FUNCTION INTERFACES                                              */
/*****************************************************************************/

static int  cbuf_instance_check (struct cbuf* cbuf);
static void cbuf_advance        (struct cbuf* cbuf);
static void cbuf_retreat        (struct cbuf* cbuf);

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
        cbuf->read  = 0;
        cbuf->write = 0;

        cbuf->full = false;
    }
}

bool cbuf_empty(struct cbuf* cbuf)
{
    bool empty;

    if (NULL != cbuf)
    {
        empty = (false == cbuf->full && (cbuf->write == cbuf->read));
    }

    return empty;
}

int cbuf_put(struct cbuf* cbuf, void* data)
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
    void* data   = NULL;
    int   result = cbuf_instance_check(cbuf);

    if (CBUF_OK == result)
    {
        data = cbuf->get(cbuf);
        cbuf_retreat(cbuf);
    }

    return data;
}

/*****************************************************************************/
/*  PRIVATE FUNCTIONS                                                        */
/*****************************************************************************/

static int cbuf_instance_check(struct cbuf* cbuf)
{
    int result;

    if (NULL == cbuf)
    {
        result = CBUF_NULL_PTR;
    }
    else if (NULL == cbuf->put)
    {
        result = CBUF_INVALID_PUT;
    }
    else if (NULL == cbuf->get)
    {
        result = CBUF_INVALID_GET;
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
    if (NULL != cbuf)
    {
        if (cbuf->full)
        {
            cbuf->read = (cbuf->read == cbuf->cap - 1) ? 0 : cbuf->read + 1;
        }

        cbuf->write = (cbuf->write == cbuf->cap - 1) ? 0 : cbuf->write + 1;
        cbuf->full  = (cbuf->write == cbuf->read);
    }
}

static void cbuf_retreat(struct cbuf* cbuf)
{
    if (NULL != cbuf)
    {
        cbuf->full = false;
        cbuf->read = (cbuf->read == cbuf->cap - 1) ? 0 : cbuf->read + 1;
    }
}
