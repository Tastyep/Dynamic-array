#include "Vec.h"

static int alloc_vector_memory(char **data, size_t *capacity, unsigned int data_size, size_t new_capacity) {
 void *ptr;

 if ((ptr = realloc(*data, new_capacity * data_size)) == NULL)
  return -1;
  *data = ptr;
  *capacity = new_capacity;
  return 0;
}

int vector_expand(char **data, size_t *size, size_t *capacity, unsigned int data_size) {
 if (*size + 1 > *capacity) {
  size_t new_capacity;
  
  new_capacity = (*capacity == 0 ? 1 : (*capacity) << 1);
  return alloc_vector_memory(data, capacity, data_size, new_capacity);
 }
 return 0;
}

int vector_reserve(char **data, size_t *capacity, unsigned int data_size, size_t new_capacity) {
  if (new_capacity > *capacity) {
   return alloc_vector_memory(data, capacity, data_size, new_capacity);
  }
  return 0;
}

void vector_erase(char **data, size_t *size, size_t *capacity, unsigned int data_size, size_t beg, size_t end) {
  size_t block_size = end - beg;
  
  if (block_size >= *size) {
   free(*data);
   *data = NULL;
   *size = 0;
   *capacity = 0;
  }
  if (end < *size) {
   memcpy((*data + beg * data_size), (*data + end * data_size), (*size - end) * data_size);
  }
  *size -= block_size;
}
