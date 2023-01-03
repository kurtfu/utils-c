/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include "dll.h"
#include "doctest/doctest.h"

#include <cstdlib>

/*****************************************************************************/
/*  FUNCTION DECLARATIONS                                                    */
/*****************************************************************************/

extern "C" { DLL_DECLARE(int) }

/*****************************************************************************/
/*  TEST CASES                                                               */
/*****************************************************************************/

TEST_CASE("Push Back")
{
    DLL_CREATE(int, malloc, free, list);

    dll_push_back(int, &list, 1);
    dll_push_back(int, &list, 2);

    CHECK(list.size == 2);

    CHECK(list.head->data == 1);
    CHECK(list.tail->data == 2);
}

TEST_CASE("Push Back Single")
{
    DLL_CREATE(int, malloc, free, list);

    dll_push_back(int, &list, 1);
    dll_pop_back(int, &list);

    CHECK(list.size == 0);

    CHECK(list.head == nullptr);
    CHECK(list.tail == nullptr);
}

TEST_CASE("Push Back Multiple")
{
    DLL_CREATE(int, malloc, free, list);

    dll_push_back(int, &list, 1);
    dll_push_back(int, &list, 2);
    dll_push_back(int, &list, 3);

    dll_pop_back(int, &list);

    CHECK(list.size == 2);

    CHECK(list.head->data == 1);
    CHECK(list.tail->data == 2);
}
