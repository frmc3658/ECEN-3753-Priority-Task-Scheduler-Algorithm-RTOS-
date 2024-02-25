#include <stdlib.h>
#include "ctest.h"
#include "priority.h"


///-------------------------------------------------
/// @brief  Dataset for priority unit-test
///
/// @retval  None
///-------------------------------------------------
CTEST_DATA(priority)
{
    struct task_t task[3];
    int size;
};


///-------------------------------------------------
/// @brief  Setup the priority unit-test
//
/// @retval  None
///-------------------------------------------------
CTEST_SETUP(priority)
{
    int execution[] = {1, 2, 3};
    int priority[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}


///-------------------------------------------------
/// @brief  Validate the process IDs in the
///         sorted priority dataset
///
/// @retval  None
///-------------------------------------------------
CTEST2(priority, test_process)
{
    int sortedPID[] = {2, 1, 0};

    for (int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedPID[i], (int)data->task[i].process_id);
    }
}


/******************************
 *    CUSTOM UNIT TEST 1      *
 ******************************/


///-------------------------------------------------
/// @brief  Validate the final priority values
///         of the sorted priority dataset
///
/// @retval  None
///-------------------------------------------------
CTEST2(priority, sortPriority_process)
{
    int sortedPriority[] = {24, 16, 8};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedPriority[i], data->task[i].priority);
    }
}


/******************************
 *    CUSTOM UNIT TEST 2      *
 ******************************/

///-------------------------------------------------
/// @brief  Validate the execution times of the
///         sorted tasks
///
/// @retval  None
///-------------------------------------------------
CTEST2(priority, exeTime_process)
{
    int sortedExe[] = {3 , 2, 1};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedExe[i], data->task[i].execution_time);
    }
}


/******************************
 *    CUSTOM UNIT TEST 3      *
 ******************************/


///-------------------------------------------------
/// @brief  Validate the wait times of the
///         sorted tasks
///
/// @retval  None
///-------------------------------------------------
CTEST2(priority, waitTime_process)
{
    int sortedWaitTime[] = {2, 4, 1};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedWaitTime[i], data->task[i].waiting_time);
    }
}


/******************************
 *    CUSTOM UNIT TEST 4      *
 ******************************/


///-------------------------------------------------
/// @brief  Validate the turnaround times of the
///         sorted tasks
///
/// @retval  None
///-------------------------------------------------
CTEST2(priority, turnAroundTime_process)
{
    int sortedTurnAroundTimes[] = {5, 6, 2};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(sortedTurnAroundTimes[i], data->task[i].turnaround_time);
    }
}


/******************************
 *    CUSTOM UNIT TEST 5      *
 ******************************/


///-------------------------------------------------
/// @brief  Validate that the
///
/// @retval  None
///-------------------------------------------------
CTEST2(priority, leftToExecute_process)
{
    int leftToExecute[] = {0, 0, 0};

    for(int i = 0; i < data->size; i++)
    {
        ASSERT_EQUAL(leftToExecute[i], data->task[i].left_to_execute);
    }
}