#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <string.h>

#define Vec(T)                                                                 \
  struct {                                                                     \
    T *data;                                                                   \
    unsigned int size;                                                         \
    unsigned int capacity;                                                     \
    unsigned int data_size;                                                    \
    union {                                                                    \
      T buffer_value;                                                          \
      unsigned char value_bytes[sizeof(T)];                                    \
    } buffer;                                                                  \
  }

#define vec_attr(vec) (char **)(&(vec)->data), &(vec)->size, &(vec)->capacity

#define vec_data(vec) (vec)->data

#define vec_size(vec) (vec)->size

#define vec_capacity(vec) (vec)->capacity

#define vec_data_size(vec) (vec)->data_size

#define vec_init(vec)                                                          \
  do {                                                                         \
    (vec)->data = NULL;                                                        \
    (vec)->size = 0;                                                           \
    (vec)->capacity = 0;                                                       \
    (vec)->data_size = sizeof(*((vec)->data));                                 \
  } while (0)

#define vec_empty(vec) ((vec)->size == 0)

#define vec_push_back(vec, value)                                              \
  do {                                                                         \
    vector_expand(vec_attr(vec), vec_data_size(vec), 1);                       \
    (vec)->data[(vec)->size] = value;                                          \
    ++(vec)->size;                                                             \
  } while (0)

#define vec_push_values(vec, ptr_begin, ptr_end)                               \
  do {                                                                         \
    unsigned int nb_elem = ptr_end - ptr_begin;                                \
    vector_expand(vec_attr(vec), vec_data_size(vec), nb_elem);                 \
    for (unsigned int i = 0; i < nb_elem; ++i)                                 \
      vec_push_back(vec, *(ptr_begin + i));                                    \
  } while (0)

#define vec_insert(vec, value, position)                                       \
  do {                                                                         \
    vector_expand(vec_attr(vec), vec_data_size(vec), 1);                       \
    vector_insert_make_room((char **)(&(vec)->data), vec_size(vec),            \
                            vec_data_size(vec), 1, position);                  \
    (vec)->data[position] = value;                                             \
    ++(vec)->size;                                                             \
  } while (0)

#define vec_insert_array(vec, array, length, position)                         \
  do {                                                                         \
    vector_expand(vec_attr(vec), vec_data_size(vec), length);                  \
    vector_insert_array((char **)(&(vec)->data), &vec_size(vec),               \
                        vec_data_size(vec), (char *)array, length, position);  \
  } while (0)

#define vec_insert_string(vec, string, position)                               \
  do {                                                                         \
    vec_insert_array(vec, string, strlen(string), position);                   \
    if (vec_size(vec) > 0 && (vec)->data[vec_size(vec) - 1] != '\0')           \
      vec_push_back(vec, '\0');                                                \
  } while (0)

#define vec_insert_vec(vec_dest, vec_src, position)                            \
  vec_insert_array(vec_dest, vec_data(vec_src), vec_size(vec_src), position)

#define vec_pop_back(vec) --(vec)->size

#define vec_back(vec) (vec)->data[(vec)->size]

#define vec_front(vec) (vec)->data[0]

#define vec_at(vec, idx) (vec)->data[idx]

#define vec_prev(vec, idx) vec_at(vec, ((idx)-1))

#define vec_next(vec, idx) vec_at(vec, ((idx) + 1))

#define vec_fill(vec, value)                                                   \
  do {                                                                         \
    if (sizeof((vec)->data) == 1)                                              \
      memset((vec)->data, value, (vec)->size);                                 \
    else                                                                       \
      for (unsigned int i = 0; i < vec_size(vec); ++i)                         \
        (vec)->data[i] = (value);                                              \
  } while (0)

#define vec_reserve(vec, size)                                                 \
  vector_reserve((char **)(&(vec)->data), &(vec)->capacity,                    \
                 vec_data_size(vec), size)

#define vec_resize_1(vec, vec_size)                                            \
  do {                                                                         \
    vec_reserve(vec, vec_size);                                                \
    if ((vec)->size < vec_size) {                                              \
      (vec)->size = (vec_size);                                                \
    }                                                                          \
  } while (0)

#define vec_resize_2(vec, vec_size, value)                                     \
  do {                                                                         \
    vec_reserve(vec, vec_size);                                                \
    if ((vec)->size < vec_size) {                                              \
      (vec)->size = (vec_size);                                                \
    }                                                                          \
    vec_fill(vec, value);                                                      \
  } while (0)

#define distribute_vec_resize(vec, _1, _2, FUNC, ...) FUNC
#define vec_resize(vec, ...)                                                   \
  distribute_vec_resize(vec, __VA_ARGS__, vec_resize_2, vec_resize_1,          \
                        _NULL)(vec, __VA_ARGS__)

/*
** vec_erase(vec, position, [end])
** if end is specified position = begin
*/

#define vec_erase_2(vec, pos1, pos2)                                           \
  vector_erase(vec_attr(vec), vec_data_size(vec), pos1, pos2);

#define vec_erase_1(vec, pos)                                                  \
  vector_erase(vec_attr(vec), vec_data_size(vec), pos, (pos) + 1);

/*
** vec_erase(vec, 0)    -> distribute_vec_erase(vec, 0, vec_erase_2,
*vec_erase_1, [NULL]) -> vec_erase_1
** vec_erase(vec, 0, 1) -> distribute_vec_erase(vec, 0, 1, vec_erase_2,
*[vec_erase_1, NULL]) -> vec_erase_2
** NULL is used to suppress the warning about empty variadic macro
*/

#define distribute_vec_erase(vec, _1, _2, FUNC, ...) FUNC
#define vec_erase(vec, ...)                                                    \
  distribute_vec_erase(vec, __VA_ARGS__, vec_erase_2, vec_erase_1,             \
                       NULL)(vec, __VA_ARGS__)

#define vec_clear(vec) vec_erase_2(vec, 0, vec_size(vec));

#define vec_delete(vec) vector_delete(vec_attr(vec))

/*
** The comma operator is a binary operator that evaluates its first operand and
*discards the result,
** it then evaluates the second operand and returns this value.
*/

#define vec_foreach(vec, value)                                                \
  for (unsigned int i = 0;                                                     \
       i < vec_size(vec) && (((value) = (vec)->data[i]), 1); ++i)

#define vec_foreach_it(vec, value, it)                                         \
  for ((it) = 0; it < vec_size(vec) && (((value) = (vec)->data[it]), 1); ++it)

typedef Vec(char) String;
typedef Vec(short) VectorShort;
typedef Vec(int) VectorInt;
typedef Vec(float) VectorFloat;
typedef Vec(double) VectorDouble;

void vector_delete(char **data, unsigned int *size, unsigned int *capacity);
void vector_erase(char **data, unsigned int *size, unsigned int *capacity,
                  unsigned int data_size, unsigned int beg, unsigned int end);
int vector_expand(char **data, unsigned int *size, unsigned int *capacity,
                  unsigned int data_size, unsigned int expanded_size);
int vector_reserve(char **data, unsigned int *capacity, unsigned int data_size,
                   unsigned int new_capacity);
void vector_insert_array(char **data, unsigned int *size,
                         unsigned int data_size, char *array,
                         unsigned int length, unsigned int position);
void vector_insert_make_room(char **data, unsigned int size,
                             unsigned int data_size, unsigned int length,
                             unsigned int position);

#endif /* end of include guard: VEC_H_ */
