#include <stdio.h>
#include <stdlib.h>

#include "class.h"

struct SuperClass
{
    int msg;
};

struct A
{
    int msg;
};

struct B
{
    int msg;
};

// int main()
// {
//     class *c = new_class();
//     set_x(c, 2);
//     set_y(c, 3);
//     printf("%d\n", get_x(c));
//     printf("%d\n", get_sum(c));
//     return 0;
// }

void print_msg(void *self)
{
    struct SuperClass *new = self;
    printf("%d\n", new->msg);
}

int main()
{
    struct A *a = malloc(sizeof(struct A));
    struct B *b = malloc(sizeof(struct B));
    a->msg = 1;
    b->msg = 2;
    print_msg(a);
    print_msg(b);

    return 0;
}