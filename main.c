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
  vec_delete(intVec);
}

void capacity_test() {
  printf("--- capacity_test ---\n");
  VectorInt intVec;

  vec_init(intVec);
  vec_reserve(intVec, 40);
  vec_reserve(intVec, 30);

  vec_fill(intVec, 1);
  printf("Capacity: %u, Size: %u\n\n", vec_capacity(intVec), vec_size(intVec));
  vec_delete(intVec);
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
  vec_delete(intVec);
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
  vec_delete(intVec);
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

  vec_insert_array(appendVec, tab, sizeof(tab) / sizeof(*tab), 0);
  for (unsigned int i = 0; i < 15; ++i)
    vec_push_back(intVec, i);
  vec_insert(intVec, 100, 0);
  vec_insert(intVec, 100, 10);
  vec_insert_vec(appendVec, intVec, 0);
  printf("Capacity: %u, Size: %u\n", vec_capacity(intVec), vec_size(intVec));
  for (unsigned int i = 0; i < vec_size(intVec); ++i) {
    printf("%d", vec_at(intVec, i));
    if (i + 1 != vec_size(intVec))
      printf(",");
  }
  printf("\n");
  vec_insert_string(str, "Hello World !", 0);
  vec_insert_string(str, "Beautiful ", 6);
  printf("str: [%s]\n", vec_data(str));
  printf("\n");
  vec_delete(intVec);
  vec_delete(appendVec);
  vec_delete(str);
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
  vec_foreach(intVec, value) { printf("%d ", value); }
  vec_sort(intVec, &compare);
  printf("\n");
  vec_foreach_it(intVec, value, it) {
    printf("%d", value);
    if (it + 1 != vec_size(intVec))
      printf(",");
  }
  printf("\n\n");
  vec_delete(intVec);
}

int is_odd(const void *i) {
  int v = *(const int *)i;

  return ((v % 2) == 1);
}

void find_test() {
  printf("--- find_test ---\n");
  VectorInt intVec;

  vec_init(intVec);
  for (unsigned int i = 0; i < 10; ++i) {
    vec_push_back(intVec, i);
    printf("%d ", i);
  }
  printf("\n-- find:\n");
  printf("Is 0 in vec: %d\n", vec_elem_found(vec_find(intVec, 0)));
  printf("Is 9 in vec: %d\n", vec_elem_found(vec_find(intVec, 9)));
  printf("Is -1 in vec: %d\n", vec_elem_found(vec_find(intVec, -1)));
  printf("Is 10 in vec: %d\n", vec_elem_found(vec_find(intVec, 10)));

  printf("Is 0 in vec [beg = 5, end = vec_size]: %d\n",
         vec_elem_found(vec_find(intVec, 0, 5, vec_size(intVec))));
  printf("Is 5 in vec [beg = 3, end = 8]: %d\n",
         vec_elem_found(vec_find(intVec, 5, 3, 8)));

  vec_clear(intVec);
  vec_push_back(intVec, 10);
  vec_push_back(intVec, 25);
  vec_push_back(intVec, 40);
  vec_push_back(intVec, 55);

  printf("\n-- find_if:\n");
  printf("[10,25,40,55] The first odd value is %d\n",
         vec_at(intVec, vec_find_if(intVec, is_odd)));
  printf("[10,25,40,55][begin = 2] The first odd value is %d\n",
         vec_at(intVec, vec_find_if(intVec, is_odd, 2, vec_size(intVec))));
  printf("\n\n");
  vec_delete(intVec);
}

void count_test() {
  printf("--- count_test ---\n");
  VectorInt intVec;

  vec_init(intVec);
  for (unsigned int i = 0; i < 10; ++i) {
    printf("%d ", i % 4);
    vec_push_back(intVec, i % 4);
  }
  printf("\n-- count:\n");
  printf("0 appears %d times\n", vec_count(intVec, 0));
  printf("3 appears %d times\n", vec_count(intVec, 3));

  printf("\n-- count_if:\n");
  printf("Number of odd values: %d\n", vec_count_if(intVec, is_odd));
  printf("[begin = 2, end = 5] Number of odd values: %d\n",
         vec_find_if(intVec, is_odd, 2, 5));
  printf("\n\n");
  vec_delete(intVec);
}

void readme_test() {
  printf("--- readme_test ---\n");
  // Declare a vector of int
  VectorInt vec;

  // Other variables used for this test
  int tab[] = {5, 4, 3, 2, 1, 0};
  int find_pos;
  int value;

  // Initialize the vector's attributes
  vec_init(vec);

  // Push some values
  for (unsigned int i = 0; i < 10; ++i)
    vec_push_back(vec, i);

  // find the position of the value 6 in vec (-1 if not found)
  find_pos = vec_find(vec, 6);

  // insert the tab at the position of 6
  vec_insert_array(vec, tab, sizeof(tab) / sizeof(*tab), find_pos);

  // insert the value -1 at the beginning of vec
  vec_insert(vec, -1, 0);

  // delete the last value
  vec_erase(vec, vec_size(vec) - 1);

  // Iterate over vec and print its content
  vec_foreach(vec, value) printf("%d ", value);

  // Delete the vector and free its memory
  vec_delete(vec);
  printf("\n\n");
}

void square_num(void *i) {
  int *value = i;

  (*value) *= (*value);
}

void for_each_test() {
  printf("--- for_each_test ---\n");
  VectorInt intVec;
  int value;

  vec_init(intVec);
  for (unsigned int i = 0; i < 10; ++i)
    vec_push_back(intVec, i);
  vec_foreach(intVec, value) printf("%2d ", value);
  printf("\n");
  vec_for_each(intVec, square_num);
  vec_foreach(intVec, value) printf("%2d ", value);
  printf("\n\n");
  vec_delete(intVec);
}

void replace_test() {
  printf("--- replace_test ---\n");
  VectorInt intVec;
  int value;
  int tab[] = {10, 20, 30, 30, 20, 10, 10, 20};

  vec_init(intVec);
  vec_push_values(intVec, tab, tab + 8);
  printf("Before:\n");
  vec_foreach(intVec, value) printf("%2d ", value);
  printf("\nAfter:\n");
  vec_replace(intVec, 20, 99);
  vec_foreach(intVec, value) printf("%2d ", value);
  printf("\n\n");
  vec_delete(intVec);
}

typedef struct {
  char *name;
  int age;
} Person;

int is_jack(const void *ptr) {
  const Person *person = ptr;

  return (strcmp(person->name, "Jack") == 0);
}

void struct_test() {
  printf("--- struct_people__test ---\n");

  Vec(Person) people;
  Person person;
  int jack_pos;

  vec_init(people);
  vec_push_back(people, ((Person){.name = "willie", .age = 10}));
  vec_push_back(people, ((Person){.name = "Henry", .age = 35}));
  vec_push_back(people, ((Person){.name = "Bessie", .age = 15}));
  vec_push_back(people, ((Person){.name = "Stephanie", .age = 64}));
  vec_foreach(people, person)
      printf("Hi, I'm %s and I'm %d years old\n", person.name, person.age);
  vec_insert(people, ((Person){.name = "Jack", .age = 75}), 2);
  jack_pos = vec_find_if(people, is_jack);
  printf("\nHi, I'm %s and I'm inserted between %s and %s\n",
         vec_at(people, jack_pos).name, vec_prev(people, jack_pos).name,
         vec_next(people, jack_pos).name);
  vec_delete(people);
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
  for_each_test();
  replace_test();
  struct_test();

  return 0;
}