#include "Vec.h"

static unsigned int round_next_p_two(unsigned int n) {
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n++;
  return n;
}

static int alloc_vector_memory(char **data, size_t *capacity,
                               unsigned int data_size, size_t new_capacity) {
  void *ptr;

  if ((ptr = realloc(*data, new_capacity * data_size)) == NULL)
    return -1;
  *data = ptr;
  *capacity = new_capacity;
  return 0;
}

int vector_expand(char **data, size_t *size, size_t *capacity,
                  unsigned int data_size, unsigned int expanded_size) {
  if (*size + expanded_size > *capacity) {
    size_t new_capacity = round_next_p_two(*capacity + expanded_size);

    return alloc_vector_memory(data, capacity, data_size, new_capacity);
  }
  return 0;
}

int vector_reserve(char **data, size_t *capacity, unsigned int data_size,
                   size_t new_capacity) {
  if (new_capacity > *capacity) {
    return alloc_vector_memory(data, capacity, data_size, new_capacity);
  }
  return 0;
}

void vector_erase(char **data, size_t *size, size_t *capacity,
                  unsigned int data_size, size_t beg, size_t end) {
  size_t block_size = end - beg;

  if (block_size >= *size) {
    free(*data);
    *data = NULL;
    *size = 0;
    *capacity = 0;
    return;
  }
  if (end < *size) {
    memmove((*data + beg * data_size), (*data + end * data_size),
            (*size - end) * data_size);
  }
  *size -= block_size;
}

void vector_insert_make_room(char **data, size_t size, unsigned int data_size, unsigned int position, unsigned int length) {
 if (position < size)
 {
     memmove(*data + (position + length) * data_size,
     *data + position * data_size,
     (size - position) * data_size);
 } 
}

void vector_insert_array(char **data, size_t *size, unsigned int data_size,
                         char *array, unsigned int length, unsigned int position) {
 vector_insert_make_room(data, *size, data_size, position, length);
 memcpy(*data + position * data_size, array, length * data_size);
 *size += length;
}

