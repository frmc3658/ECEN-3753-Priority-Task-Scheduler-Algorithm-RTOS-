#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include "priority.h"
#include "queue.h"


#define STATIC_QUANTUM 1

static inline int min(int x, int y){ return ((x < y) ? x : y); }

static void swapNodes(struct node_t* nodeA, struct node_t* nodeB);
static void swapTasks(struct task_t* taskA, struct task_t* taskB);
static void updateTasksPriority(struct node_t** head, int runTime);
static void sortTasksByPriority(struct task_t* task, int size);
static void sortQueueByPriority(struct node_t** head);


void init(struct task_t* task, int *execution, int* priority, int size)
{
    for(int i = 0; i < size; i++)
    {
        task[i].process_id = i;
        task[i].execution_time = execution[i];
        task[i].waiting_time = 0;
        task[i].turnaround_time = 0;
        task[i].priority = priority[i];
        task[i].left_to_execute = execution[i];
    }
}


void priority_schedule(struct task_t* task, int size)
{
    // Hints:
    // 1. Create Queue based on the task array in the correct order
    // 2. Each task can be processed for a time interval of 1 (i.e quantum time of 1)
    // 3. You can process by pushing and popping items from the queue
    // 4. You must recalculate the priorities after every turn

    int runTime = 0;
    int taskRuntime = 0;
    int lastTaskRan = INT_MAX;

    // Sort task buffer prior to queue creation
    sortTasksByPriority(task, size);

    // Create queue based on the task array
    struct node_t* queue = create_queue(task, size);

    // Execute the round robin algorithm
    while(!is_empty(&queue))
    {
        // "Execute" the first task
        struct task_t* currentTask = peek(&queue);

        taskRuntime = min(currentTask->left_to_execute, STATIC_QUANTUM);
        currentTask->left_to_execute -= taskRuntime;
        
        // Update runtime
        runTime += taskRuntime;

        // Calculate task wait time and turnaround time
        // NOTE: If the same task runs twice in a row
        //       don't update the wait-time
        if(lastTaskRan != currentTask->process_id)
        {
            currentTask->waiting_time = runTime - (currentTask->execution_time - currentTask->left_to_execute);
        }

        currentTask->turnaround_time = runTime;

        // Keep track of which task just ran
        lastTaskRan = currentTask->process_id;

        // If the current task needs to run more,
        // push it back onto the queue and sort
        // the queue
        if(currentTask->left_to_execute != 0)
        {
            push(&queue, currentTask);
        }

        pop(&queue);

        // Print times to console
        printf("\nTask[%d] Priority: %d\n", currentTask->process_id, currentTask->priority);
        printf("Task[%d] Time Left: %d\n", currentTask->process_id, currentTask->left_to_execute);
        printf("Task[%d] Wait Time: %d\n", currentTask->process_id, currentTask->waiting_time);
        printf("Task[%d] Turnaround Time: %d\n", currentTask->process_id, currentTask->turnaround_time);

        // Update task priorities and sort the queue
        updateTasksPriority(&queue, runTime);

        // Sort the queue by priority
        sortQueueByPriority(&queue);
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


static void updateTasksPriority(struct node_t** head, int runTime)
{
    struct node_t* queue = (*head);

    // Verify that the queue isn't empty
    if(is_empty(&queue))
    {
        return;
    }

    struct node_t* sentinel = queue;
    struct node_t* currentNode = sentinel->next;
    struct task_t* currentTask = currentNode->task;

    printf("updateTaskPriority at runtime: %d\n", runTime);
    
    // Traverse the queue
    while(currentNode != sentinel)
    {
        printf("Task[%d]\n", currentTask->process_id);

        // Update task priority
        if(currentTask->execution_time == runTime)
        {
            currentTask->priority = currentTask->priority * 4;
            printf("New Priority (*4): %d\n", currentTask->priority);
            
        }

        if(currentTask->left_to_execute == runTime)
        {
            currentTask->priority = currentTask->priority * 2;
            printf("New Priority (*2): %d\n", currentTask->priority);
        }

        // Move on to next node/task
        currentNode = currentNode->next;
        currentTask = currentNode->task;
    }
}


///-------------------------------------------------
/// @brief  Sorts the task array by priority
///         (descending). Leverages bubble sort.
///         Should be used once before creating the
///         queue.
///
/// @param[in] task The task array to sort
/// @param[in] size The number of elements in the
///                 task array
///
/// @return None
///-------------------------------------------------
static void sortTasksByPriority(struct task_t* task, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(task[j].priority < task[j + 1].priority)
            {
                swapTasks(&task[j], &task[j + 1]);      
            }
        }
    }
}


///-------------------------------------------------
/// @brief  Sorts the queue by priority (descending).
///         Should be used after a push operation.
///
/// @param[in] task The task array to sort
/// @param[in] size The number of elements in the
///                 task array
///
/// @return None
///-------------------------------------------------
static void sortQueueByPriority(struct node_t** head)
{
    struct node_t* queue = (*head);

    // Return if the queue is empty
    if(is_empty(&queue))
    {
        return;
    }

    bool swapped = true;
    struct node_t* sentinel = queue;

    while(swapped)
    {
        swapped = false;

        struct node_t* currentNode = sentinel->next;

        while((currentNode != sentinel) && (currentNode->next != sentinel))
        {
            struct task_t* currentTask = currentNode->task;
            struct task_t* nextTask = currentNode->next->task;

            if(currentTask->priority < nextTask->priority)
            {
                swapNodes(currentNode, currentNode->next);
                swapped = true;
            }

            currentNode = currentNode->next;
        }
    }
}


///-------------------------------------------------
/// @brief  Swap the position of two nodes in the queue
///
/// @param[in] nodeA Current node
/// @param[in] nodeB Next node
///
/// @return None
///-------------------------------------------------
static void swapNodes(struct node_t* nodeA, struct node_t* nodeB)
{
    if(nodeA == nodeB)
    {
        return;
    }

    struct node_t temp = *nodeA;
    *nodeA = *nodeB;
    *nodeB = temp;

    struct node_t* tempNext = nodeA->next;
    nodeA->next = nodeB->next;
    nodeB->next = tempNext;
}


static void swapTasks(struct task_t* taskA, struct task_t* taskB)
{
    if(taskA == taskB)
    {
        return;
    }

    struct task_t temp = *taskA;
    *taskA = *taskB;
    *taskB = temp;
}