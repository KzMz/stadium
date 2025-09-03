#include <stdio.h>

#define STADIUM_IMPLEMENTATION
#include "../stadium.h"

int main(void)
{
    Stadium stadium;
    int* ints_ptr = (int*) stadium_alloc(&stadium, sizeof(int) * 3);

    ints_ptr[0] = 1;
    ints_ptr[1] = 2;
    ints_ptr[2] = 3;

    for (int i = 0; i < 3; ++i)
        printf("%d\n", ints_ptr[i]);

    char* chars_ptr = (char*) stadium_alloc(&stadium, sizeof(char) * 3);

    chars_ptr[0] = 'a';
    chars_ptr[1] = 'b';
    chars_ptr[2] = 0;

    printf("%s\n", chars_ptr);

    stadium_free(&stadium, chars_ptr, sizeof(char) * 3);
    stadium_free(&stadium, ints_ptr, sizeof(int) * 3);

    stadium_clear(&stadium);
}