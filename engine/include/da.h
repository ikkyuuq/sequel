#include <stdlib.h>

#define DA_DEFAULT_CAPACITY 32
#define DA_DOUBLE_STRATEGY 2
#define IS_TYPE_OF(T, V) _Generic((V), T: 1, default: 0)

#define da_init(da, T, C)                                                                                              \
  do                                                                                                                   \
  {                                                                                                                    \
    da->data = malloc(C * sizeof(T *));                                                                                \
    da->capacity = C;                                                                                                  \
    da->size = 0;                                                                                                      \
  } while (0)

#define da_append(T, da, x)                                                                                            \
  do                                                                                                                   \
  {                                                                                                                    \
    if (da->size >= da->capacity)                                                                                      \
    {                                                                                                                  \
      if (da->capacity == 0)                                                                                           \
        da->capacity = DA_DEFAULT_CAPACITY;                                                                            \
      else                                                                                                             \
        da->capacity *= DA_DOUBLE_STRATEGY;                                                                            \
      static_assert(IS_TYPE_OF(T *, *da->data), "V must be of type T");                                                \
      da->data = realloc(da->data, da->capacity * sizeof(T *));                                                        \
      da->data[da->size++] = x;                                                                                        \
    }                                                                                                                  \
  } while (0)

#define da_clear(da)                                                                                                   \
  do                                                                                                                   \
  {                                                                                                                    \
    da->capacity = DA_DEFAULT_CAPACITY;                                                                                \
    da->size = 0;                                                                                                      \
    da->data = calloc(da->capacity, sizeof(*da->data));                                                                \
  } while (0)
