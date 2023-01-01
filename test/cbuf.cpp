/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "cbuf.h"

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

typedef struct
{
    int first;
    char second;
} cbuf_custom;

CBUF_DECLARE(cbuf_custom)
CBUF_DEFINE(cbuf_custom)

/*****************************************************************************/
/*  MODULE VARIABLES                                                         */
/*****************************************************************************/

constexpr std::size_t buffer_capacity = 4;

/*****************************************************************************/
/*  TEST CASES                                                               */
/*****************************************************************************/

TEST_CASE("Push[int]")
{
    cbuf_int buf[buffer_capacity] = {0};
    CBUF_CREATE(cbuf_int, cbuf, buf, buffer_capacity);

    cbuf_push(cbuf_int, &cbuf, 1);

    CHECK(cbuf.size == 1);
    CHECK(*cbuf.read == 1);
}

TEST_CASE("Pop[int]")
{
    cbuf_int buf[buffer_capacity] = {0};
    CBUF_CREATE(cbuf_int, cbuf, buf, buffer_capacity);

    cbuf_push(cbuf_int, &cbuf, 0);
    cbuf_pop(cbuf_int, &cbuf);

    CHECK(cbuf.size == 0);
    CHECK(cbuf.read == cbuf.write);
}

TEST_CASE("Overflow[int]")
{
    cbuf_int buf[buffer_capacity] = {0};
    CBUF_CREATE(cbuf_int, cbuf, buf, buffer_capacity);

    for (std::size_t value = 0; value < buffer_capacity + 1; ++value)
    {
        cbuf_push(cbuf_int, &cbuf, value);
    }

    CHECK(cbuf.size == buffer_capacity);
    CHECK(cbuf.read == cbuf.write);

    for (std::size_t value = 1; value < buffer_capacity + 1; ++value)
    {
        CHECK(*cbuf.read == value);
        cbuf_pop(cbuf_int, &cbuf);
    }
}

TEST_CASE("Clear[int]")
{
    cbuf_int buf[buffer_capacity] = {0};
    CBUF_CREATE(cbuf_int, cbuf, buf, buffer_capacity);

    for (std::size_t value = 0; value < buffer_capacity + 1; ++value)
    {
        cbuf_push(cbuf_int, &cbuf, value);
    }

    cbuf_clear(cbuf_int, &cbuf);

    CHECK(cbuf.size == 0);
    CHECK(cbuf.read == cbuf.write);
}

TEST_CASE("Push[custom]")
{
    cbuf_custom buf[buffer_capacity] = {};
    CBUF_CREATE(cbuf_custom, cbuf, buf, buffer_capacity);

    cbuf_custom data = {1, 'a'};
    cbuf_push(cbuf_custom, &cbuf, data);

    CHECK(cbuf.size == 1);

    CHECK(cbuf.read->first == 1);
    CHECK(cbuf.read->second == 'a');
}

TEST_CASE("Pop[custom]")
{
    cbuf_custom buf[buffer_capacity] = {};
    CBUF_CREATE(cbuf_custom, cbuf, buf, buffer_capacity);

    cbuf_custom data = {1, 'a'};

    cbuf_push(cbuf_custom, &cbuf, data);
    cbuf_pop(cbuf_custom, &cbuf);

    CHECK(cbuf.size == 0);
    CHECK(cbuf.read == cbuf.write);
}

TEST_CASE("Overflow[custom]")
{
    cbuf_custom buf[buffer_capacity] = {};
    CBUF_CREATE(cbuf_custom, cbuf, buf, buffer_capacity);

    cbuf_custom data = {1, 'a'};

    for (std::size_t i = 0; i < buffer_capacity + 1; ++i)
    {
        cbuf_push(cbuf_custom, &cbuf, data);

        data.first++;
        data.second++;
    }

    CHECK(cbuf.size == buffer_capacity);
    CHECK(cbuf.read == cbuf.write);

    cbuf_custom expected = {2, 'b'};

    for (std::size_t i = 0; i < buffer_capacity; ++i)
    {
        CHECK(cbuf.read->first == expected.first++);
        CHECK(cbuf.read->second == expected.second++);

        cbuf_pop(cbuf_custom, &cbuf);
    }
}

TEST_CASE("Clear[custom]")
{
    cbuf_custom buf[buffer_capacity] = {};
    CBUF_CREATE(cbuf_custom, cbuf, buf, buffer_capacity);

    for (std::size_t i = 0; i < buffer_capacity + 1; ++i)
    {
        cbuf_custom data = {};
        cbuf_push(cbuf_custom, &cbuf, data);
    }

    cbuf_clear(cbuf_custom, &cbuf);

    CHECK(cbuf.size == 0);
    CHECK(cbuf.read == cbuf.write);
}
