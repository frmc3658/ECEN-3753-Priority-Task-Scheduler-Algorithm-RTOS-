#include "sjf.h"
#include "queue.h"
#include <stdio.h>

static void swap(struct task_t* taskA, struct task_t* taskB);
static void sortTasksByExecutionTime(struct task_t* task, int size);


///-------------------------------------------------
/// @brief  Initializes the task array
///
/// @param[in] task The task queue array
/// @param[in] execution Array containing the
///                      execution times of each
///                      task
/// @param[in] size Size of the task queue array
///
/// @return Average wait time of all tasks in 
///         the queue
///-------------------------------------------------
void init(struct task_t* task, int *execution, int size)
{
    for(int i = 0; i < size; i++)
    {
        task[i].process_id = i;
        task[i].execution_time = execution[i];
        task[i].waiting_time = 0;
        task[i].turnaround_time = 0;    
    }
}


void shortest_job_first(struct task_t* task, int size)
{
    // Hints:
    // 1. Create Queue based on the task array in the correct order
    // 2. Process each "task" until completion
    // 3. You can process by popping items from the queue

    // Sort the task queue based on execution time (ascending order)
    sortTasksByExecutionTime(task, size);

    // Track scheduler runtime
    int runTime = 0;

    // Construct a task queue from the task array
    struct node_t* queue = create_queue(task, size);
    struct task_t* currentTask;

    while(!is_empty(&queue))
    {
        // "Execute" the first task
        currentTask = peek(&queue);
        currentTask->waiting_time = runTime;
        runTime += currentTask->execution_time;
        currentTask->turnaround_time = runTime;

        pop(&queue);

        // Print times to console
        printf("\nTask[%d] Execution Time: %d\n", currentTask->process_id, currentTask->execution_time);
        printf("Task[%d] Wait Time: %d\n", currentTask->process_id, currentTask->waiting_time);
        printf("Task[%d] Turnaround Time: %d\n", currentTask->process_id, currentTask->turnaround_time);
    }
    
    // Calculate average times
    float avgWaitTime = calculate_average_wait_time(task, size);
    float avgTurnaroundTime = calculate_average_turn_around_time(task, size);

    // Print average times
    printf("Average Wait Time: %f\n", avgWaitTime);
    printf("Average Turnaround Time: %f\n", avgTurnaroundTime);

    // Cleanup
    free(queue->next);
    free(queue);

}


float calculate_average_wait_time(struct task_t* task, int size)
{
    // return 0.0 so it compiles
    return 0.0;
}


float calculate_average_turn_around_time(struct task_t* task, int size)
{
    // return 0.0 so it compiles
    return 0.0;
}


///-------------------------------------------------
/// @brief  Sorts the task array by execution time
///         (ascending). Leverages bubble sort.
///
/// @param[in] task The task array to sort
/// @param[in] size The number of elements in the
///                 task array
///
/// @return None
///-------------------------------------------------
static void sortTasksByExecutionTime(struct task_t* task, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(task[j].execution_time > task[j + 1].execution_time)
            {
                swap(&task[j], &task[j + 1]);      
            }
        }
    }
}


///-------------------------------------------------
/// @brief  Swap two tasks within the task array
///
/// @param[in] taskA First task
/// @param[in] taskB Second task
///
/// @return None
///-------------------------------------------------
static void swap(struct task_t* taskA, struct task_t* taskB)
{
    struct task_t temp = *taskA;
    *taskA = *taskB;
    *taskB = temp;
}