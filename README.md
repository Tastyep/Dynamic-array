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
##### Basic example
```c
  // Declare a vector of int
  VectorInt vec;
  
  // Other variables used for this test
  int tab[] = {5,4,3,2,1,0};
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
  vec_foreach(vec, value)
    printf("%d ", value);
  printf("\n");
  
  // Delete the vector and free its memory
  vec_delete(vec);
```

Outputs:

```
  -1 0 1 2 3 4 5 5 4 3 2 1 0 6 7 8 
```

##### Advanced example

```c
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
         vec_at(people, jack_pos).name,
         vec_prev(people, jack_pos).name,
         vec_next(people, jack_pos).name);
  
  vec_delete(people);
```

Outputs:

```
  Hi, I'm willie and I'm 10 years old
  Hi, I'm Henry and I'm 35 years old
  Hi, I'm Bessie and I'm 15 years old
  Hi, I'm Stephanie and I'm 64 years old
  
  Hi, I'm Jack and I'm inserted between Henry and Bessie
```


###Available functions
#####Capacity:
| Function          | Parameters                   | Descrption                                |
|-------------------|------------------------------|-------------------------------------------|
| vec_size          | (v)                          | Return size                               |
| vec_resize        | (v, size, [value])           | Change size                               |
| vec_capacity      | (v)                          | Return size of allocated storage capacity |
| vec_empty         | (v)                          | Test whether vector is empty              |
| vec_reserve       | (v, size)                    | Request a change in capacity              |

#####Element access:
| Function          | Parameters                   | Description                               |
|-------------------|------------------------------|-------------------------------------------|
| vec_at            | (v, idx)                     | Access element                            |
| vec_front         | (v)                          | Access first element                      |
| vec_back          | (v)                          | Access last element                       |
| vec_data          | (v)                          | Access data                               |

#####Modifiers:
| Function          | Parameters                   | Description                               |
|-------------------|------------------------------|-------------------------------------------|
| vec_push_back     | (v, value)                   | Add element at the end                    |
| vec_pop_back      | (v)                          | Delete last element                       |
| vec_insert        | (v, value, position)         | Insert elements                           |
| vec_insert_array  | (v, array, length, position) | Insert an array of elements               |
| vec_insert_string | (v, string, position)        | Insert a string and check for \0          |
| vec_erase         | (v, position, [end])         | Erase elements                            |
| vec_clear         | (v)                          | Clear content                             |
| vec_delete        | (v)                          | Clear content                             |
