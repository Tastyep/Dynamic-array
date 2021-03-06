#include <stdlib.h>
#include <string.h>

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

static int alloc_vector_memory(char **data, unsigned int *capacity,
                               unsigned int data_size,
                               unsigned int new_capacity) {
  void *ptr;

  if ((ptr = realloc(*data, new_capacity * data_size)) == NULL)
    return -1;
  *data = ptr;
  *capacity = new_capacity;
  return 0;
}

int vector_expand(char **data, unsigned int *size, unsigned int *capacity,
                  unsigned int data_size, unsigned int expanded_size) {
  if (*size + expanded_size > *capacity) {
    unsigned int new_capacity = round_next_p_two(*capacity + expanded_size);

    return alloc_vector_memory(data, capacity, data_size, new_capacity);
  }
  return 0;
}

int vector_reserve(char **data, unsigned int *capacity, unsigned int data_size,
                   unsigned int new_capacity) {
  if (new_capacity > *capacity) {
    return alloc_vector_memory(data, capacity, data_size, new_capacity);
  }
  return 0;
}

void vector_delete(char **data, unsigned int *size, unsigned int *capacity) {
  free(*data);
  *data = NULL;
  *size = 0;
  *capacity = 0;
}

void vector_erase(char **data, unsigned int *size, unsigned int *capacity,
                  unsigned int data_size, unsigned int beg, unsigned int end) {
  unsigned int block_size = end - beg;

  if (block_size >= *size) {
    vector_delete(data, size, capacity);
    return;
  }
  if (end < *size) {
    memmove((*data + beg * data_size), (*data + end * data_size),
            (*size - end) * data_size);
  }
  *size -= block_size;
}

void vector_insert_make_room(char **data, unsigned int size,
                             unsigned int data_size, unsigned int length,
                             unsigned int position) {
  if (position < size) {
    memmove(*data + (position + length) * data_size,
            *data + position * data_size, (size - position) * data_size);
  }
}

void vector_insert_array(char **data, unsigned int *size,
                         unsigned int data_size, char *array,
                         unsigned int length, unsigned int position) {
  vector_insert_make_room(data, *size, data_size, length, position);
  memcpy(*data + position * data_size, array, length * data_size);
  *size += length;
}

int vector_find(char *data, unsigned int data_size, unsigned char *value,
                unsigned int beg, unsigned int end) {
  for (unsigned int i = beg; i < end; ++i) {
    if (memcmp(&data[i * data_size], value, data_size) == 0)
      return i;
  }
  return -1;
}

int vector_find_if(char *data, unsigned int data_size,
                   int (*cond_function)(const void *a), unsigned int beg,
                   unsigned int end) {
  for (unsigned int i = beg; i < end; ++i) {
    if (cond_function(&data[i * data_size]))
      return i;
  }
  return -1;
}

int vector_count(char *data, unsigned int data_size, unsigned char *value,
                 unsigned int beg, unsigned int end) {
  unsigned int count = 0;

  for (unsigned int i = beg; i < end; ++i) {
    if (memcmp(&data[i * data_size], value, data_size) == 0)
      ++count;
  }
  return count;
}

int vector_count_if(char *data, unsigned int data_size,
                    int (*cond_function)(const void *a), unsigned int beg,
                    unsigned int end) {
  unsigned int count = 0;

  for (unsigned int i = beg; i < end; ++i) {
    if (cond_function(&data[i * data_size]))
      ++count;
  }
  return count;
}
