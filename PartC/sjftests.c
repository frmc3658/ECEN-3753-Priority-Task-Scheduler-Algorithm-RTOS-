#include <stdlib.h>
#include "ctest.h"
#include "sjf.h"
#include <time.h>


CTEST_DATA(shortestjobfirst)
{
    struct task_t task[3];
    int size;
};


CTEST_SETUP(shortestjobfirst)
{
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}


CTEST2(shortestjobfirst, test_process)
{
    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}


CTEST_DATA(sorted)
{
    struct task_t task[10];
    int size;
};


CTEST_SETUP(sorted)
{
    int execution[] = {4, 7, 1, 6, 9, 10, 2, 8, 5, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}


CTEST2(sorted, sortedByExecTime_process)
{
    int sortedExecTimes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedExecTimes[i], data->task[i].execution_time);
    }
}
