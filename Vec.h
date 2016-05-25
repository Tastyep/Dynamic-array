#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <string.h>

#define Vec(T)\
struct {\
    T *data;\
    size_t size;\
    size_t capacity;\
}

#define vec_attr(vec)\
    (char **)(&(vec).data), &(vec).size, &(vec).capacity

#define data_size(vec)\
    sizeof(*((vec).data))
    
#define vec_init(vec)\
    (vec).data = NULL; (vec).size = 0; (vec).capacity = 0

#define vec_push_back(vec, value)\
{\
    vector_expand(vec_attr(vec), data_size(vec));\
    (vec).data[(vec).size] = value;\
    ++(vec).size; \
}

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
    
#define distribute_erase(_1,_2,_3,FUNC,...) FUNC
#define vec_erase(...) distribute_erase(__VA_ARGS__, vec_erase_2, vec_erase_1)(__VA_ARGS__)

void vector_erase(char **data, size_t *size, size_t *capacity, unsigned int data_size, size_t beg, size_t end);
int vector_expand(char **data, size_t *size, size_t *capacity, unsigned int data_size);
int vector_reserve(char **data, size_t *capacity, unsigned int data_size, size_t new_capacity);


#endif /* end of include guard: VEC_H_ */
