// Schedule ADT implementation

#include <stdio.h>
#include <stdlib.h>

#include "Schedule.h"
#include "Time.h"
#include "Tree.h"

struct schedule
{
    Tree times;
    int count;
};

// Creates a new schedule
Schedule ScheduleNew(void)
{
    Schedule s = malloc(sizeof(*s));
    if (s == NULL)
    {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    s->times = TreeNew();
    s->count = 0;
    return s;
}

// Frees all memory associated with a given schedule
void ScheduleFree(Schedule s)
{
    TreeFree(s->times);
    free(s);
}

// Gets the number of times added to the schedule
int ScheduleCount(Schedule s)
{
    return s->count;
}

// Attempts to schedule a new landing time. Returns true if the time was
// successfully added, and false otherwise.
//
// TimeCmp does not consider the difference in minutes over two consecutive days
bool ScheduleAdd(Schedule s, Time t)
{
    if (s == NULL || t == NULL)
        return false;

    if (ScheduleCount(s) == 0)
    {
        TreeInsert(s->times, t);
        s->count++;
        return true;
    }

    Time lower = TimeSubtractMinutes(t, 10);
    Time upper = TimeAddMinutes(t, 10);
    Time floor = TreeFloor(s->times, t);
    Time ceiling = TreeCeiling(s->times, t);

    if (floor == NULL && ceiling == NULL)
        return false;

    // printf("T: ");
    // TimeShow(t);
    // printf("\tLOWER: ");
    // TimeShow(lower);
    // printf("\tUPPER: ");
    // TimeShow(upper);
    // if (floor)
    // {
    //     printf("\tFLOOR: ");
    //     TimeShow(floor);
    // }
    // if (ceiling)
    // {
    //     printf("\tCEILING: ");
    //     TimeShow(ceiling);
    // }
    // printf("\n\n");

    if (floor != NULL && ceiling != NULL)
        if (TimeCmp(floor, lower) < 0 && TimeCmp(ceiling, upper) > 0)
        {
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }

    if (floor != NULL && ceiling == NULL)
        if (TimeCmp(floor, lower) < 0)
        {
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }

    if (floor == NULL && ceiling != NULL)
        if (TimeCmp(ceiling, upper) > 0)
        {
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }

    return false;
}

// Shows  all  the landing times in the schedule. If mode is 1, only the
// times are shown. If mode is 2, the underlying data structure is shown
// as well.
void ScheduleShow(Schedule s, int mode)
{
    if (mode == 1)
    {
        TreeList(s->times);
    }
    else if (mode == 2)
    {
        TreeShow(s->times);
    }
}
