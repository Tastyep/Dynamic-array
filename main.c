#include "Vec.h"
#include <stdio.h>

void intTest() {
 printf("--- intTest ---\n");
 Vec(int) intVec;

 vec_init(intVec);
 for (unsigned int i = 0; i < 25; ++i)
   vec_push_back(intVec, i);
 printf("Capacity: %lu, Size: %lu\n", vec_capacity(intVec), vec_size(intVec));
 for (unsigned int i = 0; i < vec_size(intVec); ++i) {
   printf("%d", vec_at(intVec, i));
   if (i + 1 != vec_size(intVec))
    printf(",");
 }
 printf("\n\n");
}

void capacityTest() {
 printf("--- capacityTest ---\n");
 Vec(int) intVec;

 vec_init(intVec);
 vec_reserve(intVec, 40);
 vec_reserve(intVec, 30);

 vec_fill(intVec, 1);
 printf("Capacity: %lu, Size: %lu\n", vec_capacity(intVec), vec_size(intVec));
 for (unsigned int i = 0; i < vec_size(intVec); ++i) {
   printf("%d", vec_at(intVec, i));
   if (i + 1 != vec_size(intVec))
    printf(",");
 }
 printf("\n\n");
}

void resizeTest() {
 printf("--- resizeTest ---\n");
 Vec(int) intVec;

 vec_init(intVec);
 vec_resize(intVec, 40, 1);

 printf("Capacity: %lu, Size: %lu\n", vec_capacity(intVec), vec_size(intVec));
 for (unsigned int i = 0; i < vec_size(intVec); ++i) {
   printf("%d", vec_at(intVec, i));
   if (i + 1 != vec_size(intVec))
    printf(",");
 }
 printf("\n\n");
}

void eraseTest() {
 printf("--- eraseTest ---\n");
 Vec(int) intVec;

 vec_init(intVec);
 for (unsigned int i = 0; i < 40; ++i)
  vec_push_back(intVec, i);

 printf("Capacity: %lu, Size: %lu\n", vec_capacity(intVec), vec_size(intVec));
 vec_erase(intVec, 0, 10);
 vec_erase(intVec, 0);
 vec_erase(intVec, 5);
 printf("Capacity: %lu, Size: %lu\n", vec_capacity(intVec), vec_size(intVec));
 for (unsigned int i = 0; i < vec_size(intVec); ++i) {
   printf("%d", vec_at(intVec, i));
   if (i + 1 != vec_size(intVec))
    printf(",");
 }
 printf("\n");
 vec_clear(intVec);
 printf("Capacity: %lu, Size: %lu\n", vec_capacity(intVec), vec_size(intVec)); 
 printf("\n\n");
}

int main(void) {
  intTest();
  capacityTest();
  resizeTest();
  eraseTest();
  return 0;
}