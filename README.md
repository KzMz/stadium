# stadium allocator
Single header simple Arena allocator written in C

## usage
```c
#define STADIUM_IMPLEMENTATION
#include "stadium.h"

...
Stadium stadium;
char* my_string = (char*) stadium_alloc(&stadium, 10 * sizeof(char));
...
stadium_free(&stadium, my_string, 10 * sizeof(char));
...
stadium_clear(&stadium);
```
It's important to free memory in reverse order if it's required to re-use it.