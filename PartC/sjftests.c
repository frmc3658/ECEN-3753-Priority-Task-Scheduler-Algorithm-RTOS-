#include <stdlib.h>
#include "ctest.h"
#include "sjf.h"
#include <time.h>


///-------------------------------------------------
/// @brief  Dataset for the shortestjobfirst
///         unit-test
///
/// @retval  None
///-------------------------------------------------
CTEST_DATA(shortestjobfirst)
{
    struct task_t task[3];
    int size;
};


///-------------------------------------------------
/// @brief  Setup the shortestjobfirst unit-test
//
/// @retval  None
///-------------------------------------------------
CTEST_SETUP(shortestjobfirst)
{
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}


///-------------------------------------------------
/// @brief  Validate the process IDs in the
///         shortestjobfirst dataset
///
/// @retval  None
///-------------------------------------------------
CTEST2(shortestjobfirst, test_process)
{
    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}


/******************************
 *    CUSTOM UNIT TEST 1      *
 ******************************/


///-------------------------------------------------
/// @brief  Validate the wait times in the
///         shortestjobfirst dataset
///  
/// @retval  None
///-------------------------------------------------
CTEST2(shortestjobfirst, wait_time_process)
{
    int waitTimes[] = {0, 1, 3};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(waitTimes[i], data->task[i].waiting_time);
    }
}


/******************************
 *    CUSTOM UNIT TEST 2      *
 ******************************/


///-------------------------------------------------
/// @brief  Validate the turnaround times in the
///         shortestjobfirst dataset
///
/// @retval  None
///-------------------------------------------------
CTEST2(shortestjobfirst, turnaround_time_process)
{
    int turnaroundTimes[] = {1, 3, 6};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(turnaroundTimes[i], data->task[i].turnaround_time);
    }
}


/******************************
 *    CUSTOM UNIT TEST 3      *
 ******************************/


///-------------------------------------------------
/// @brief  Validate that the PIDs are unique in the
///         shortestjobfirst dataset
///
/// @retval  None
///-------------------------------------------------
CTEST2(shortestjobfirst, uniquePID_process)
{
    int PIDs[3];

    // Get the process_id of each task
    for(int i = 0; i < data->size; i++)
    {
        PIDs[i] = data->task[i].process_id;
    }

    // Assert that each PID is unique
    for(int i = 0; i < data->size - 1; i++)
    {
        for(int j = i + 1; j < data->size; j++)
        {
            ASSERT_NOT_EQUAL(PIDs[i], PIDs[j]);
        }
    }
}


/******************************
 *    CUSTOM UNIT TEST 4      *
 ******************************/

///-------------------------------------------------
/// @brief  Dataset for the sorted unit-test
///
/// @retval  None
///-------------------------------------------------
CTEST_DATA(sorted)
{
    struct task_t task[10];
    int size;
};


///-------------------------------------------------
/// @brief  Setup the sorted unit-test
//
/// @retval  None
///-------------------------------------------------
CTEST_SETUP(sorted)
{
    int execution[] = {4, 7, 1, 6, 9, 10, 2, 8, 5, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}


///-------------------------------------------------
/// @brief  Validate the sorted Execution times
///         given a larger dataset
//
/// @retval  None
///-------------------------------------------------
CTEST2(sorted, sortedByExecTime_process)
{
    int sortedExecTimes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedExecTimes[i], data->task[i].execution_time);
    }
}


/******************************
 *    CUSTOM UNIT TEST 5      *
 ******************************/


///-------------------------------------------------
/// @brief  Dataset for the customSJF unit-test
///
/// @retval  None
///-------------------------------------------------
CTEST_DATA(customeSJF)
{
    struct task_t task[10];
    int size;
};


///-------------------------------------------------
/// @brief  Setup the customSJF unit-test
//
/// @retval  None
///-------------------------------------------------
CTEST_SETUP(customeSJF)
{
    int execution[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}


///-------------------------------------------------
/// @brief   Validate the wait and turnaround times
///          given a NULL queue, given a larger
///          dataset.
///
/// @retval  None
///-------------------------------------------------
CTEST2(customeSJF, nullQueue_process)
{
    // Hand-calculated wait and turnaround times for the given dataset
    int waitTime[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int turnaroundTime[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Validate the dataset
    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(waitTime[i], data->task[i].waiting_time);
        ASSERT_EQUAL(turnaroundTime[i], data->task[i].turnaround_time);
        ASSERT_EQUAL(i, data->task[i].process_id);
    }
}