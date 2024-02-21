#include "queue.h"


static int isInvalidNode(struct node_t* node, const char* caller);


///-------------------------------------------------
/// @brief  Given an array of tasks, construct a
///         singly-linked task queue
///
/// @param[in] task Array of tasks to create task
///                 nodes from
/// @param[in] size The number of tasks nodes to
///                 create
///
/// @return The sentinel node of the queue
///-------------------------------------------------
struct node_t* create_queue(struct task_t* task, int size)
{
    // Validate parameters
    if((task == NULL) ||(size < 1))
    {
        return NULL;
    }

    // Create the sentinel node at the base of the queue
    struct node_t* sentinel = create_new_node(NULL);

    // Verify that malloc didn't fail
    if(isInvalidNode(sentinel, __func__))
    {
        return NULL;
    }

    // Create and link nodes together to form the queue
    // NOTE: The first "true" node in the queue is linked to the sentinel
    for(int i = 0; i < size; i++)
    {
        push(&sentinel, &(task[i]));
    }

    return sentinel;
}


///-------------------------------------------------
/// @brief  Construct a new task node
///
/// @param[in] task Task to attach to a node
///
/// @return The newly created task node
///-------------------------------------------------
struct node_t* create_new_node(struct task_t* task)
{
    // Dynamically allocate memory for the new node
    struct node_t* newNode = (struct node_t*)malloc(sizeof(struct node_t));
    
    // Verify that malloc didn't fail
    if(isInvalidNode(newNode, __func__))
    {
        return NULL;
    }

    // Initialize node data members
    newNode->task = task;
    newNode->next = NULL;

    return newNode;
}


///-------------------------------------------------
/// @brief Returns the top-most task for the queue
///
/// @param[in] head The head of the task queue
/// 
/// @return The top-most task
///-------------------------------------------------
struct task_t* peek(struct node_t** head)
{
    if(is_empty(head))
    {
        return NULL;
    }

    // NOTE: The base of the queue is a sentinel
    //       therefore the first task node is
    //       linked to it
    struct node_t* topNode = (*head)->next;

    // Return the top-most task
    return topNode->task;
}


///-------------------------------------------------
/// @brief  Pop the top-most task off the queue
///
/// @param[in] head The head of the queue
///-------------------------------------------------
void pop(struct node_t** head)
{
    // Check if the queue is empty
    if(is_empty(head))
    {
        return;
    }

    // Pop the old head
    struct node_t* oldHead = *head;
    *head = (*head)->next;

    // Free the memory allocated for the popped head
    free(oldHead);
}


///-------------------------------------------------
/// @brief  Push a new task onto the queue
///
/// @param[in] head The head of the task queue
/// @param[in] task The task to push onto the queue
///-------------------------------------------------
void push(struct node_t** head, struct task_t* task)
{
    // Verify that the queue is initialized properly
    if(isInvalidNode(*head, __func__) || (task == NULL))
    {
        return;
    }

    struct node_t* sentinel = *head;

    // Check if the queue is empty
    if(is_empty(&sentinel))
    {
        // Link the new node to the sentinel
        sentinel->next = create_new_node(task);
    }
    else
    {
        struct node_t* nextNode = sentinel->next;
        struct node_t* currentNode;

        // Traverse queue until you find the sentinel
        while(nextNode != NULL)
        {
            currentNode = nextNode;
            nextNode = nextNode->next;
        }

        // Insert new node at the end of the task queue
        struct node_t* newNode = create_new_node(task);
        currentNode->next = newNode;
    }
}


///-------------------------------------------------
/// @brief  Check if the queue is empty
///
/// @param[in] head The head of the task queue
///
/// @return True/False
///-------------------------------------------------
int is_empty(struct node_t** head)
{
    return ((*head)->next == NULL);
}


///-------------------------------------------------
/// @brief  Traverse the queue and free all memory
///         aside from the the sentinel
///
/// @param[in] head The head of the queue to empty
///-------------------------------------------------
void empty_queue(struct node_t** head)
{
    // Check if the queue is empty
    if(is_empty(head))
    {
        return;
    }

    struct node_t* currentNode = *head;
    struct node_t* nextNode;

    // Traverse the queue and free each node
    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }

    *head = NULL;
}


///-------------------------------------------------
/// @brief  Validates that a node was constructed
///
/// @param[in] node The node to validate
/// @param[in] caller Should always pass in __func__
///
/// @return 1: Invalid node; 0: Valid node
///-------------------------------------------------
static int isInvalidNode(struct node_t* node, const char* caller)
{
    if(node == NULL)
    {
        fprintf(stderr, "%s() ERROR: Couldn't create node!\n", caller);
        return 1;
    }

    return 0;
}