/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "cbuf.h"
#include "doctest/doctest.h"

/*****************************************************************************/
/*  FUNCTION DECLARATIONS                                                    */
/*****************************************************************************/

extern "C" { CBUF_DECLARE(int) }

/*****************************************************************************/
/*  MODULE VARIABLES                                                         */
/*****************************************************************************/

constexpr std::size_t buffer_capacity = 4;

/*****************************************************************************/
/*  TEST CASES                                                               */
/*****************************************************************************/

TEST_CASE("Push")
{
    int buf[buffer_capacity] = {0};
    CBUF_CREATE(int, cbuf, buf, buffer_capacity);

    cbuf_push(int, &cbuf, 1);

    CHECK(cbuf.size == 1);
    CHECK(*cbuf.read == 1);
}

TEST_CASE("Pop")
{
    int buf[buffer_capacity] = {0};
    CBUF_CREATE(int, cbuf, buf, buffer_capacity);

    cbuf_push(int, &cbuf, 0);
    cbuf_pop(int, &cbuf);

    CHECK(cbuf.size == 0);
    CHECK(cbuf.read == cbuf.write);
}

TEST_CASE("Overflow")
{
    int buf[buffer_capacity] = {0};
    CBUF_CREATE(int, cbuf, buf, buffer_capacity);

    for (std::size_t value = 0; value < buffer_capacity + 1; ++value)
    {
        cbuf_push(int, &cbuf, value);
    }

    CHECK(cbuf.size == buffer_capacity);
    CHECK(cbuf.read == cbuf.write);

    for (std::size_t value = 1; value < buffer_capacity + 1; ++value)
    {
        CHECK(*cbuf.read == value);
        cbuf_pop(int, &cbuf);
    }
}

TEST_CASE("Clear")
{
    int buf[buffer_capacity] = {0};
    CBUF_CREATE(int, cbuf, buf, buffer_capacity);

    for (std::size_t value = 0; value < buffer_capacity + 1; ++value)
    {
        cbuf_push(int, &cbuf, value);
    }

    cbuf_clear(int, &cbuf);

    CHECK(cbuf.size == 0);
    CHECK(cbuf.read == cbuf.write);
}
