#include <stdio.h>
#include <stdlib.h>

typedef struct elem_queue
{
    int data;
    struct elem_queue *next;
    struct elem_queue *before;
}eQueue;

typedef struct limits
{
    int elements;
    struct elem_queue *front;
    struct elem_queue *final;
}limits;

int insert(limits **start, int N);
int seek(limits **start);
eQueue *search(limits *start, int N);
int delete(eQueue **limits, int N);

int main(int argc, char const *argv[])
{
    limits *queue = NULL;
    int op, number;

        insert(&queue, 9);
        insert(&queue, 7);
        insert(&queue, 2);
        printf("Elements of the queue: \n");
        seek(&queue);
        printf("\n");

    return 0;
}

int insert(limits **start, int N)
{
    if (!(*start))
    {
        *start = (limits *) malloc(sizeof(limits));
        if (!start)
            return 0;
        (*start)->front = NULL;
        (*start)->final = NULL;  
    }
    eQueue *new_eQueue = (eQueue *) malloc(sizeof(eQueue));
    if (!new_eQueue)
    {
        printf("\nCould not reserved memory!!!\n\n");
        return 0;
    }
    new_eQueue->data = N;
    new_eQueue->next = NULL;
    
    if ((*start)->front == NULL)
        (*start)->front = new_eQueue;
    else
        (*start)->final->next = new_eQueue;
    (*start)->final = new_eQueue;
    (*start)->elements++;
    
    return 1;    
}

int seek(limits **start)
{
    int count = 0;
    if (!(*start)->front)
        printf("\nThe queue is empty!!!\n");
    while (count<(*start)->elements)
    {
        printf("[%d]\t", (*start)->front->data);
        (*start)->front = (*start)->front->next;
        count++;
    } 
return 0;
}

/*eQueue *search(limits *start, int N)
{
    int count = 0;
   // eQueue *aux = (*start)->front;
    if (!(start->front))
        return 0;
    while (count<(*start)->elements)
    {
        if (start->front->data == N)
        {
            
        }
        
    }*/
    
    return 0; 
}