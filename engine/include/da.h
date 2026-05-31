#include <stdlib.h>

#define IS_TYPE_OF(T, V) _Generic((V), T: 1, default: 0)

#define da_init(da, T, C)                                                                                                  \
  do                                                                                                                   \
  {                                                                                                                    \
    da->data = malloc(C * sizeof(T*)); \
    da->capacity = C;\
    da->size = 0;\
  } while (0)

#define da_append(T, da, x)                                                                                            \
  do                                                                                                                   \
  {                                                                                                                    \
    if (da->size >= da->capacity)                                                                                      \
    {                                                                                                                  \
      if (da->capacity == 0)                                                                                           \
        da->capacity = 256;                                                                                            \
      else                                                                                                             \
        da->capacity *= 2;                                                                                             \
      static_assert(IS_TYPE_OF(T *, *v->data), "V must be of type T");                                                 \
      da->data = realloc(da->data, da->capacity * sizeof(*da->data));                                                  \
      da->data[da->size++] = data;                                                                                     \
    }                                                                                                                  \
    while (0)
