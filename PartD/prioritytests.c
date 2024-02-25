#include <stdlib.h>
#include "ctest.h"
#include "priority.h"

CTEST_DATA(priority) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(priority)
{
    int execution[] = {1, 2, 3};
    int priority[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}

CTEST2(priority, test_process)
{
    int sortedPID[] = {2, 1, 0};

    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedPID[i], (int)data->task[i].process_id);
    }
}


CTEST2(priority, sortPriority_process)
{
    int sortedPriority[] = {24, 16, 8};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedPriority[i], data->task[i].priority);
    }
}

#ifdef DEBUG
CTEST_DATA(sorted)
{
    struct task_t task[10];
    int size;
};


CTEST_SETUP(sorted)
{
    int execution[] = {4, 7, 1, 6, 9, 10, 2, 8, 5, 3};
    int priority[] = {5, 7, 10, 9, 1, 3, 4, 8, 2, 6};
    data->size = sizeof(priority) / sizeof(priority[0]);

    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}


CTEST2(sorted, sortedByPriority_process)
{
    int sortedPriority[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedPriority[i], data->task[i].priority);
    }
}
#endif