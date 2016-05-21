#include "Vec.h"
#include <stdio.h>

int main(void) {
 Vec(int) intVec;
 
 vec_init(intVec);
 vec_push_back(intVec, 5);
 
 for (unsigned int i = 0; i < vec_size(intVec); ++i) {
  printf("%d\n", vec_at(intVec, i));
 }
 return 0;
}