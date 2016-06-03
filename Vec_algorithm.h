#ifndef VEC_ALGORITHM_H_
#define VEC_ALGORITHM_H_

#include <stdlib.h>

#define _NULL(...) {}

#define vec_elem_found(it)\
    ((it) == -1 ? 0 : 1)

/*
** vec_find(vec, value [beg, end])
*/

#define vec_find_1(vec, value)\
    vec_find_3(vec, value, 0, (vec).size)

#define vec_find_3(vec, value, beg, end)\
    ((vec).buffer_value = value,\
     vector_find((char *)vec_data(vec), vec_data_size(vec), (vec).value_bytes, beg, end))
    
#define distribute_vec_find(vec,_1,_2,_3,FUNC,...) FUNC
#define vec_find(vec, ...) distribute_vec_find(vec, __VA_ARGS__, vec_find_3, _NULL, vec_find_1, _NULL)(vec, __VA_ARGS__)

/*
** vec_find_if(vec, condition_function, [beg, end])
*/

#define vec_find_if_1(vec, cond_func)\
    vec_find_if_3(vec, cond_func, 0, vec_size(vec))

#define vec_find_if_3(vec, cond_func, beg, end)\
    vector_find_if((char *)vec_data(vec), vec_data_size(vec), cond_func, beg, end)
    
#define distribute_vec_find_if(vec,_1,_2,_3,FUNC,...) FUNC
#define vec_find_if(vec, ...) distribute_vec_find_if(vec, __VA_ARGS__, vec_find_if_3, _NULL, vec_find_if_1, _NULL)(vec, __VA_ARGS__)

/*
** vec_count(vec, value [beg, end])
*/

#define vec_count_1(vec, value)\
    ((vec).buffer_value = value,\
     vector_count((char *)vec_data(vec), vec_data_size(vec), (vec).value_bytes, 0, vec_size(vec)))

#define vec_count_3(vec, value, beg, end)\
    ((vec).buffer_value = value,\
     vector_count((char *)vec_data(vec), vec_data_size(vec), (vec).value_bytes, beg, end))
    
#define distribute_vec_count(vec,_1,_2,_3,FUNC,...) FUNC
#define vec_count(vec, ...) distribute_vec_count(vec, __VA_ARGS__, vec_count_3, _NULL, vec_count_1, _NULL)(vec, __VA_ARGS__)

/*
** vec_count_if(vec, condition_function, [beg, end])
*/

#define vec_count_if_1(vec, cond_func)\
    vec_count_if_3(vec, cond_func, 0, vec_size(vec))

#define vec_count_if_3(vec, cond_func, beg, end)\
    vector_count_if((char *)vec_data(vec), vec_data_size(vec), cond_func, beg, end)
    
#define distribute_vec_count_if(vec,_1,_2,_3,FUNC,...) FUNC
#define vec_count_if(vec, ...) distribute_vec_count_if(vec, __VA_ARGS__, vec_count_if_3, _NULL, vec_count_if_1, _NULL)(vec, __VA_ARGS__)

/*
** vec_sort(vec, function_ptr)
** function ptr: int compare(const void *a, const void *b)
** returns 0 if sorted, else 1
*/

#define vec_sort(vec, compar)\
  qsort(vec_data(vec), vec_size(vec), vec_data_size(vec), compar)

int vector_find(char *data, unsigned int data_size, unsigned char* value, unsigned int beg, unsigned int end);
int vector_find_if(char *data, unsigned int data_size, int (*cond_function)(const void *a), unsigned int beg, unsigned int end);
int vector_count(char *data, unsigned int data_size, unsigned char* value, unsigned int beg, unsigned int end);
int vector_count_if(char *data, unsigned int data_size, int (*cond_function)(const void *a), unsigned int beg, unsigned int end);

#endif /* end of include guard: VEC_ALGORITHM_H_ */
