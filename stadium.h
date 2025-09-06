#ifndef STADIUM_H_
#define STADIUM_H_

#ifndef STADIUM_STAND_CAPACITY
#define STADIUM_STAND_CAPACITY (10*1024)
#endif // STADIUM_STAND_CAPACITY

#ifndef STADIUM_MAX_STANDS
#define STADIUM_MAX_STANDS (50)
#endif // STADIUM_MAX_STANDS

#include <assert.h>
#include <string.h>

typedef struct {
    size_t allocated;
} Stand;

typedef struct {
    size_t end;
    Stand stands[STADIUM_MAX_STANDS];
    unsigned char data[STADIUM_STAND_CAPACITY*STADIUM_MAX_STANDS];
} Stadium;

void* stadium_alloc(Stadium* stadium, size_t size);
void stadium_free(Stadium* stadium, void* ptr, size_t size);
void stadium_clear(Stadium* stadium);

#ifdef STADIUM_IMPLEMENTATION

void* stadium_alloc(Stadium* stadium, size_t size)
{
    int offset = -1;
    for (size_t i = 0; i < stadium->end; ++i)
    {
        if (stadium->stands[i].allocated + size > STADIUM_STAND_CAPACITY) continue;

        offset = i * STADIUM_STAND_CAPACITY + stadium->stands[i].allocated;
        stadium->stands[i].allocated += size;
        break;
    }

    if (offset == -1)
    {
        stadium->stands[++stadium->end] = (Stand)
        {
            .allocated = size
        };

        offset = stadium->end * STADIUM_STAND_CAPACITY;
    }

    assert(offset >= 0);
    return (void*) stadium->data + offset;
}

// it's important to free stuff in the reverse order of allocation
void stadium_free(Stadium* stadium, void* ptr, size_t size)
{
    assert(ptr >= (void*) stadium->data);

    size_t stand = (int) ((unsigned char*) ptr - stadium->data) / STADIUM_STAND_CAPACITY;
    assert(stadium->stands[stand].allocated >= size);

    stadium->stands[stand].allocated -= size;
    if (stadium->stands[stand].allocated == 0 && stand == stadium->end)
        stadium->end--;
}

void stadium_clear(Stadium* stadium)
{
    stadium->end = 0;
    memset(stadium->stands, 0, sizeof(stadium->stands));
}

#endif // STADIUM_IMPLEMENTATION

#endif // STADIUM_H_