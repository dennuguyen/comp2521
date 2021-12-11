#include <stdlib.h>
#include <assert.h>

#include "class.h"

struct _class
{
    int x;
    void *(*ctor)(void *self, int x);
    void *(*dtor)(void *self);
    void *(*clone)(const void *self);
};

class *new_class()
{
    class *c = malloc(sizeof(class));
    assert(c);
    return c;
}

int get_x(class *self)
{
    return self->x;
}

void set_x(class *self, int x)
{
    self->x = x;
}
