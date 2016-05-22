#include "Vec.h"
#include <stdio.h>

int main(void) {
  Vec(int)intVec;

  vec_init(intVec);
  for (unsigned int i = 0; i < 25; ++i) {
    vec_push_back(intVec, i);
  }

  printf("Capacity: %lu, Size: %lu\n", vec_capacity(intVec), vec_size(intVec));
  for (unsigned int i = 0; i < vec_size(intVec); ++i) {
    printf("%d\n", vec_at(intVec, i));
  }
  return 0;
}