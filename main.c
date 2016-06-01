#include "Vec.h"
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
}

int main(void) {
  basic_test();
  capacity_test();
  resize_test();
  erase_test();
  insertion_test();
  sort_test();
  return 0;
}