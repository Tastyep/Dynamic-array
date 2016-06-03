#include "Vec.h"
#include "Vec_algorithm.h"
#include <stdio.h>

void basic_test() {
  printf("--- basic_test ---\n");
  VectorInt intVec;

  vec_init(intVec);
  printf("Is the initialized vector empty -> %s\n",
         (vec_empty(intVec) ? "Yes" : "No"));
  for (unsigned int i = 0; i < 25; ++i)
    vec_push_back(intVec, i);
  printf("Capacity: %u, Size: %u\n", vec_capacity(intVec), vec_size(intVec));
  for (unsigned int i = 0; i < vec_size(intVec); ++i) {
    printf("%d", vec_at(intVec, i));
    if (i + 1 != vec_size(intVec))
      printf(",");
  }
  printf("\n\n");
}

void capacity_test() {
  printf("--- capacity_test ---\n");
  VectorInt intVec;

  vec_init(intVec);
  vec_reserve(intVec, 40);
  vec_reserve(intVec, 30);

  vec_fill(intVec, 1);
  printf("Capacity: %u, Size: %u\n\n", vec_capacity(intVec), vec_size(intVec));
}

void resize_test() {
  printf("--- resize_test ---\n");
  VectorInt intVec;
  int value;

  vec_init(intVec);
  vec_resize(intVec, 40, 1);

  printf("Capacity: %u, Size: %u\n", vec_capacity(intVec), vec_size(intVec));
  vec_foreach(intVec, value) { printf("%d ", value); }
  printf("\n\n");
}

void erase_test() {
  printf("--- erase_test ---\n");
  VectorInt intVec;

  vec_init(intVec);
  for (unsigned int i = 0; i < 40; ++i)
    vec_push_back(intVec, i);

  printf("Capacity: %u, Size: %u\n", vec_capacity(intVec), vec_size(intVec));
  vec_erase(intVec, 0, 10);
  vec_erase(intVec, 0);
  vec_erase(intVec, 5);
  printf("Capacity: %u, Size: %u\n", vec_capacity(intVec), vec_size(intVec));
  for (unsigned int i = 0; i < vec_size(intVec); ++i) {
    printf("%d", vec_at(intVec, i));
    if (i + 1 != vec_size(intVec))
      printf(",");
  }
  printf("\n");
  vec_clear(intVec);
  printf("Capacity: %u, Size: %u\n", vec_capacity(intVec), vec_size(intVec));
  printf("\n\n");
}

void insertion_test() {
  printf("--- insertion_test ---\n");
  VectorInt intVec;
  VectorInt appendVec;
  String str;
  int tab[] = {105, 104, 103, 102, 101};

  vec_init(intVec);
  vec_init(appendVec);
  vec_init(str);

  vec_insert_array(appendVec, 0, tab, sizeof(tab) / sizeof(*tab));
  for (unsigned int i = 0; i < 15; ++i)
    vec_push_back(intVec, i);
  vec_insert(intVec, 0, 100);
  vec_insert(intVec, 10, 100);
  vec_insert_vec(intVec, 0, appendVec);
  printf("Capacity: %u, Size: %u\n", vec_capacity(intVec), vec_size(intVec));
  for (unsigned int i = 0; i < vec_size(intVec); ++i) {
    printf("%d", vec_at(intVec, i));
    if (i + 1 != vec_size(intVec))
      printf(",");
  }
  printf("\n");
  vec_insert_string(str, 0, "Hello World !");
  vec_insert_string(str, 6, "Beautiful ");
  printf("str: [%s]\n", vec_data(str));
  printf("\n");
}

int compare(const void *a, const void *b) {
  const int *a1 = a;
  const int *b1 = b;
  
  return *a1 > *b1;
}

void sort_test() {
  printf("--- sort_test ---\n");
  VectorInt intVec;
  int value;
  unsigned int it;

  vec_init(intVec);
  for (unsigned int i = 0; i < 25; ++i)
    vec_push_back(intVec, 25 - i);
  vec_foreach(intVec, value) {
    printf("%d ", value);
  }
  vec_sort(intVec, &compare);
  printf("\n");
  vec_foreach_it(intVec, value, it) {
    printf("%d", value);
    if (it + 1 != vec_size(intVec))
     printf(",");
  }
  printf("\n\n");
}

void find_test() {
  printf("--- find_test ---\n");
  VectorInt intVec;
  
  vec_init(intVec);
  for (unsigned int i = 0; i < 25; ++i)
    vec_push_back(intVec, i);
  printf("0 in vec: %d\n", vec_elem_found(vec_find(intVec, 0)));
  printf("15 in vec: %d\n", vec_elem_found(vec_find(intVec, 15)));
  printf("-1 in vec: %d\n", vec_elem_found(vec_find(intVec, -1)));
  printf("25 in vec: %d\n", vec_elem_found(vec_find(intVec, 25)));

  printf("0 in vec [beg = 5, end = vec_size]: %d\n", vec_elem_found(vec_find(intVec, 0, 5, vec_size(intVec))));
  printf("10 in vec [beg = 10, end = 11]: %d\n", vec_elem_found(vec_find(intVec, 10, 10, 11)));
  printf("\n\n");
}

void count_test() {
  printf("--- count_test ---\n");
  VectorInt intVec;
  
  vec_init(intVec);
  for (unsigned int i = 0; i < 25; ++i) {
    printf("%d ", i % 4);
    vec_push_back(intVec, i % 4);
  }
  printf("\n");
  printf("0 appears %d times\n", vec_count(intVec, 0));
  printf("3 appears %d times\n", vec_count(intVec, 3));
  printf("\n\n");
}

void readme_test() {
  printf("--- readme_test ---\n");
  // Declare a vector of int
  VectorInt vec;
  
  // Other variables used for this test
  int tab[] = {9,8,7,6,5,4,3,2,1,0};
  int find_pos;
  int value;
  
  // Initialize the vector's attributes
  vec_init(vec);

  // Push some values
  for (unsigned int i = 0; i < 25; ++i)
    vec_push_back(vec, i);

  // find the position of the value 10 in vec (-1 if not found)
  find_pos = vec_find(vec, 10);
  
  // insert the tab at the position 10 (position of 10 + 1)
  vec_insert_array(vec, find_pos + 1, tab, sizeof(tab) / sizeof(*tab));

  // insert the value -1 at the beginning of vec
  vec_insert(vec, 0, -1);
  
  // delete the last value
  vec_erase(vec, vec_size(vec) - 1);
  
  // Iterate over vec and print its content
  vec_foreach(vec, value)
    printf("%d ", value);
  printf("\n");
  
  // Delete the vector and free its memory
  // vec_delete(vec);
}

int main(void) {
  basic_test();
  capacity_test();
  resize_test();
  erase_test();
  insertion_test();
  sort_test();
  find_test();
  count_test();
  readme_test();
  return 0;
}