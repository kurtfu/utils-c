#ifndef CBUF_H
#define CBUF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************************************/
/*  HEADER INCLUDES                                                          */
/*****************************************************************************/

#include <stddef.h>

/*****************************************************************************/
/*  DATA TYPES                                                               */
/*****************************************************************************/

enum
{
    CBUF_OK = 0,
    CBUF_NULL_PTR = -1,
    CBUF_INVALID_CAPACITY = -3
};

typedef char cbuf_char;
typedef char* cbuf_char_ptr;

typedef signed char cbuf_signed_char;
typedef signed char* cbuf_signed_char_ptr;

typedef unsigned char cbuf_unsigned_char;
typedef unsigned char* cbuf_unsigned_char_ptr;

typedef short cbuf_short;
typedef short* cbuf_short_ptr;

typedef unsigned short cbuf_unsigned_short;
typedef unsigned short* cbuf_unsigned_short_ptr;

typedef int cbuf_int;
typedef int* cbuf_int_ptr;

typedef unsigned int cbuf_unsigned_int;
typedef unsigned int* cbuf_unsigned_int_ptr;

typedef long cbuf_long;
typedef long* cbuf_long_ptr;

typedef unsigned long cbuf_unsigned_long;
typedef unsigned long* cbuf_unsigned_long_ptr;

typedef long long cbuf_long_long;
typedef long long* cbuf_long_long_ptr;

typedef unsigned int cbuf_unsigned_long_long;
typedef unsigned int* cbuf_unsigned_long_long_ptr;

typedef float cbuf_float;
typedef float* cbuf_float_ptr;

typedef double cbuf_double;
typedef double* cbuf_double_ptr;

typedef long double cbuf_long_double;
typedef long double* cbuf_long_double_ptr;

/*****************************************************************************/
/*  MACRO DEFINITIONS                                                        */
/*****************************************************************************/

#define CBUF_DECLARE(T)                               \
    struct cbuf_##T                                   \
    {                                                 \
        T* buffer;                                    \
                                                      \
        /* NOLINTBEGIN(bugprone-macro-parentheses) */ \
        T* read;                                      \
        T* write;                                     \
        /* NOLINTEND(bugprone-macro-parentheses) */   \
                                                      \
        size_t size;                                  \
        size_t capacity;                              \
    };                                                \
                                                      \
    int cbuf_push_##T(struct cbuf_##T* self, T data); \
    int cbuf_pop_##T(struct cbuf_##T* self);          \
    int cbuf_clear_##T(struct cbuf_##T* self);

#define CBUF_DEFINE(T)                                           \
    static int cbuf_validate_##T(struct cbuf_##T* self)          \
    {                                                            \
        int result = CBUF_OK;                                    \
                                                                 \
        if (NULL == self)                                        \
        {                                                        \
            result = CBUF_NULL_PTR;                              \
        }                                                        \
        else if (0 == self->capacity)                            \
        {                                                        \
            result = CBUF_INVALID_CAPACITY;                      \
        }                                                        \
                                                                 \
        return result;                                           \
    }                                                            \
                                                                 \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses)*/              \
    static void cbuf_advance_##T(struct cbuf_##T* self, T** ptr) \
    {                                                            \
        /* NOLINTBEGIN(bugprone-macro-parentheses) */            \
        T* first = &(self->buffer[0]);                           \
        T* last = &(self->buffer[self->capacity]);               \
        /* NOLINTEND(bugprone-macro-parentheses) */              \
                                                                 \
        if (++(*ptr) == last)                                    \
        {                                                        \
            *ptr = first;                                        \
        }                                                        \
    }                                                            \
                                                                 \
    int cbuf_push_##T(struct cbuf_##T* self, T data)             \
    {                                                            \
        int result = cbuf_validate_##T(self);                    \
                                                                 \
        if (CBUF_OK == result)                                   \
        {                                                        \
            *(self->write) = data;                               \
            cbuf_advance_##T(self, &self->write);                \
                                                                 \
            if (self->size == self->capacity)                    \
            {                                                    \
                self->read = self->write;                        \
            }                                                    \
            else                                                 \
            {                                                    \
                self->size++;                                    \
            }                                                    \
        }                                                        \
                                                                 \
        return result;                                           \
    }                                                            \
                                                                 \
    int cbuf_pop_##T(struct cbuf_##T* self)                      \
    {                                                            \
        int result = cbuf_validate_##T(self);                    \
                                                                 \
        if (CBUF_OK == result)                                   \
        {                                                        \
            self->size--;                                        \
            cbuf_advance_##T(self, &self->read);                 \
        }                                                        \
                                                                 \
        return result;                                           \
    }                                                            \
                                                                 \
    int cbuf_clear_##T(struct cbuf_##T* self)                    \
    {                                                            \
        int result = cbuf_validate_##T(self);                    \
                                                                 \
        if (CBUF_OK == result)                                   \
        {                                                        \
            self->read = self->buffer;                           \
            self->write = self->buffer;                          \
                                                                 \
            self->size = 0;                                      \
        }                                                        \
                                                                 \
        return result;                                           \
    }

#define CBUF_CREATE(T, name, buf, N) \
    struct cbuf_##T name             \
    {                                \
        /* .buffer   = */ (buf),     \
        /* .read     = */ (buf),     \
        /* .write    = */ (buf),     \
        /* .size     = */ 0,         \
        /* .capacity = */ (N),       \
    }

#define cbuf_push(T, self, data) cbuf_push_##T(self, data)
#define cbuf_pop(T, self)        cbuf_pop_##T(self)
#define cbuf_clear(T, self)      cbuf_clear_##T(self)

/*****************************************************************************/
/*  PUBLIC FUNCTION DECLARATIONS                                             */
/*****************************************************************************/

CBUF_DECLARE(cbuf_char)
CBUF_DECLARE(cbuf_char_ptr)

CBUF_DECLARE(cbuf_signed_char)
CBUF_DECLARE(cbuf_signed_char_ptr)

CBUF_DECLARE(cbuf_unsigned_char)
CBUF_DECLARE(cbuf_unsigned_char_ptr)

CBUF_DECLARE(cbuf_short)
CBUF_DECLARE(cbuf_short_ptr)

CBUF_DECLARE(cbuf_unsigned_short)
CBUF_DECLARE(cbuf_unsigned_short_ptr)

CBUF_DECLARE(cbuf_int)
CBUF_DECLARE(cbuf_int_ptr)

CBUF_DECLARE(cbuf_unsigned_int)
CBUF_DECLARE(cbuf_unsigned_int_ptr)

CBUF_DECLARE(cbuf_long)
CBUF_DECLARE(cbuf_long_ptr)

CBUF_DECLARE(cbuf_unsigned_long)
CBUF_DECLARE(cbuf_unsigned_long_ptr)

CBUF_DECLARE(cbuf_long_long)
CBUF_DECLARE(cbuf_long_long_ptr)

CBUF_DECLARE(cbuf_unsigned_long_long)
CBUF_DECLARE(cbuf_unsigned_long_long_ptr)

CBUF_DECLARE(cbuf_float)
CBUF_DECLARE(cbuf_float_ptr)

CBUF_DECLARE(cbuf_double)
CBUF_DECLARE(cbuf_double_ptr)

CBUF_DECLARE(cbuf_long_double)
CBUF_DECLARE(cbuf_long_double_ptr)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CBUF_H */
