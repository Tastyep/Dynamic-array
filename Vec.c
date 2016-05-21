#include "Vec.h"

int vec_expand(char **data, size_t *size, size_t *capacity, unsigned int data_size) {
 if (*size + 1 > *capacity) {
   void *ptr;
   size_t new_capacity;
   
   new_capacity = (*capacity == 0 ? 1 : (*capacity) << 1);
   if ((ptr = realloc(*data, new_capacity * data_size)) == NULL)
    return -1;
    *data = ptr;
    *capacity = new_capacity;
 }
 return 0;
}