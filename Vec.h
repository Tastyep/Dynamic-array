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

#define vec_init(vec)\
(vec).data = NULL; (vec).size = 0; (vec).capacity = 0;

#define vec_attr(vec)\
(char **)(&(vec).data), &(vec).size, &(vec).capacity

#define data_size(vec)\
sizeof(*((vec).data))

#define vec_push_back(vec, value)\
    vec_expand(vec_attr(vec), data_size(vec));\
    (vec).data[(vec).size] = value;\
    ++(vec).size;

#define vec_pop_back(vec)\
    --(vec).size;

#define vec_back(vec)\
    (vec).data[(vec).size]

#define vec_at(vec, idx)\
    (vec).data[idx]

#define vec_size(vec)\
    (vec).size

int vec_expand(char **data, size_t *size, size_t *capacity, unsigned int data_size);


#endif /* end of include guard: VEC_H_ */
