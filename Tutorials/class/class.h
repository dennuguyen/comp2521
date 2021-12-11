#ifndef CLASS_H
#define CLASS_H

typedef struct _class class;

class *new_class();
int get_x(class *);
void set_x(class *, int);
int get_sum(class *);

#endif // CLASS_H