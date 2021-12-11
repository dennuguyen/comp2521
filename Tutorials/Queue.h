/**
 * Template queue implementation using linked lists.
 * 
 * Author: Dan Nguyen
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define DefineQueue(TYPE)                                    \
                                                             \
    /* Definition of Queue */                                \
    typedef struct queue##TYPE *Queue##TYPE;                 \
    typedef struct queue##TYPE                               \
    {                                                        \
        TYPE *data;                                          \
        struct queue##TYPE *next;                            \
    } queue##TYPE;                                           \
                                                             \
    /* Definition of Function Prototypes */                  \
    queue##TYPE *QueueNew##TYPE()                            \
    {                                                        \
        return NULL;                                         \
    }                                                        \
                                                             \
    void QueueFree##TYPE(queue##TYPE **q)                    \
    {                                                        \
        if (*q == NULL)                                      \
            return;                                          \
        QueueFree(&((*q)->next));                            \
        free(*q);                                            \
        *q = NULL;                                           \
    }                                                        \
                                                             \
    void Enqueue##TYPE(queue##TYPE **q, TYPE##TYPE *data)    \
    {                                                        \
        queue *head = malloc(sizeof(queue));                 \
                                                             \
        if (head == NULL)                                    \
        {                                                    \
            fprintf(stderr, "Failed to allocate memory.\n"); \
            exit(1);                                         \
        }                                                    \
                                                             \
        head->data = data;                                   \
        head->next = *q;                                     \
        *q = head;                                           \
    }                                                        \
                                                             \
    void Dequeue##TYPE(queue##TYPE **q)                      \
    {                                                        \
        if (*q == NULL)                                      \
            return;                                          \
                                                             \
        queue *prev = NULL, *curr = *q;                      \
        while (curr->next != NULL)                           \
        {                                                    \
            prev = curr;                                     \
            curr = curr->next;                               \
        }                                                    \
                                                             \
        if (prev == NULL)                                    \
            QueueFree##TYPE(q);                              \
        else                                                 \
        {                                                    \
            prev->next = NULL;                               \
            free(curr);                                      \
        }                                                    \
    }                                                        \
                                                             \
    void QueueRemove##TYPE(queue##TYPE **q, TYPE *data)      \
    {                                                        \
        if (*q == NULL)                                      \
            return;                                          \
                                                             \
        queue *prev = NULL, *curr = *q;                      \
        while (curr->next != NULL)                           \
        {                                                    \
            prev = curr;                                     \
            curr = curr->next;                               \
        }                                                    \
                                                             \
        if (prev == NULL)                                    \
            QueueFree##TYPE(q);                              \
        else                                                 \
        {                                                    \
            prev->next = NULL;                               \
            free(curr);                                      \
        }                                                    \
    }                                                        \
                                                             \
    int QueueIsEmpty##TYPE(queue##TYPE *q)                   \
    {                                                        \
        return q == NULL;                                    \
    }                                                        \
                                                             \
    void QueueShow##TYPE(queue##TYPE **q)                    \
    {                                                        \
        if (*q == NULL)                                      \
            return;                                          \
                                                             \
        printf("[");                                         \
                                                             \
        queue *curr = *q;                                    \
        while (curr != NULL)                                 \
        {                                                    \
            if (curr->next == NULL)                          \
                printf("%d", curr->data);                    \
            else                                             \
                printf("%d, ", curr->data);                  \
            curr = curr->next;                               \
        }                                                    \
                                                             \
        printf("]");                                         \
    }

#define Queue(TYPE) \
    queue##TYPE

#define QueueNew(TYPE) \
    QueueNew##TYPE()

#endif // QUEUE_H_
