#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <string.h>

#define Vec(T)\
struct {\
    T *data;\
    unsigned int size;\
    unsigned int capacity;\
}

#define vec_attr(vec)\
    (char **)(&(vec).data), &(vec).size, &(vec).capacity

#define data_size(vec)\
    sizeof(*((vec).data))

#define vec_init(vec)\
    (vec).data = NULL; (vec).size = 0; (vec).capacity = 0

#define vec_data(vec)\
    ((char *)(vec).data)

#define vec_push_back(vec, value)\
do {\
    vector_expand(vec_attr(vec), data_size(vec), 1);\
    (vec).data[(vec).size] = value;\
    ++(vec).size;\
} while (0)

#define vec_insert(vec, position, value)\
do {\
    vector_expand(vec_attr(vec), data_size(vec), 1);\
    vector_insert_make_room((char **)(&(vec).data), vec_size(vec), data_size(vec), 1, position);\
    (vec).data[position] = value;\
    ++(vec).size;\
} while (0)

#define vec_insert_array(vec, position, array, length)\
do {\
    vector_expand(vec_attr(vec), data_size(vec), length);\
    vector_insert_array((char **)(&(vec).data), &vec_size(vec), data_size(vec), (char *)array, length, position);\
} while (0)

#define vec_insert_string(vec, position, string)\
do {\
    vec_insert_array(vec, position, string, strlen(string));\
    if (vec_size(vec) > 0 && (vec).data[vec_size(vec) - 1] != '\0')\
        vec_push_back(vec, '\0');\
} while (0)

#define vec_insert_vec(vec_dest, position, vec_src)\
    vec_insert_array(vec_dest, position, (vec_src).data, (vec_src).size)

#define vec_pop_back(vec)\
    --(vec).size

#define vec_back(vec)\
    (vec).data[(vec).size]

#define vec_front(vec)\
    (vec).data[0]

#define vec_at(vec, idx)\
    (vec).data[idx]

#define vec_size(vec)\
    (vec).size

#define vec_capacity(vec)\
    (vec).capacity
    
#define vec_empty(vec)\
    ((vec).size == 0)

#define vec_fill(vec, value)\
    if (sizeof((vec).data) == 1)\
        memset((vec).data, value, (vec).size);\
    else\
        for (unsigned int i = 0; i < vec_size(vec); ++i)\
            (vec).data[i] = value;

#define vec_reserve(vec, size)\
    vector_reserve((char **)(&(vec).data), &(vec).capacity, data_size(vec), size)
    
#define vec_resize(vec, vec_size, value)\
    vec_reserve(vec, vec_size);\
    if ((vec).size < vec_size) {\
        (vec).size = vec_size;\
    }\
    vec_fill(vec, value)

#define vec_erase_2(vec, pos1, pos2)\
    vector_erase(vec_attr(vec), data_size(vec), pos1, pos2);

#define vec_erase_1(vec, pos)\
    vector_erase(vec_attr(vec), data_size(vec), pos, pos + 1);
    
#define distribute_vec_erase(_1,_2,_3,FUNC,...) FUNC
#define vec_erase(...) distribute_vec_erase(__VA_ARGS__, vec_erase_2, vec_erase_1)(__VA_ARGS__)

#define vec_clear(vec)\
    vec_erase_2(vec, 0, vec_size(vec));

void vector_erase(char **data, unsigned int *size, unsigned int *capacity, unsigned int data_size, unsigned int beg, unsigned int end);
int vector_expand(char **data, unsigned int *size, unsigned int *capacity, unsigned int data_size, unsigned int expanded_size);
int vector_reserve(char **data, unsigned int *capacity, unsigned int data_size, unsigned int new_capacity);
void vector_insert_array(char **data, unsigned int *size, unsigned int data_size,
                         char *array, unsigned int length, unsigned int position);
void vector_insert_make_room(char **data, unsigned int size, unsigned int data_size, unsigned int position, unsigned int length);


typedef Vec(char) String;

#endif /* end of include guard: VEC_H_ */
