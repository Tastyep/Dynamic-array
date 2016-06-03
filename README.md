#CV: Generic Dynamic arrays in C

##<a name="overview"></a>Overview

CV is a standalone and lightweight library written in C, for C developers, aiming at emulating the behavior of C++'s vector.
It also makes available the most used functions from the algorithm library such as find, copy, count ...

###Types

For convenience the following types are already declared:

| Contained Type  | Type name     |
|-----------------|---------------|
| char            | String        |
| short           | VectorShort   |
| int             | VectorInt     |
| float           | VectorFloat   |
| double          | VectorDouble  |

###Usage

```c
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
  
  //prints: -1 0 1 2 3 4 5 6 7 8 9 10 9 8 7 6 5 4 3 2 1 0 11 12 13 14 15 16 17 18 19 20 21 22 23
  
  // Delete the vector and free its memory
  vec_delete(vec);
```

###Available functions

TODO
