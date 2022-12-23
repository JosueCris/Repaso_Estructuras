/*
	Implementacion de una Cola Dinamica manejado con dos apuntadores
	Uno manipulando el frente y el otro el final de la estructura
*/
#include <stdio.h>
#include <stdlib.h>

struct Cola2
{
	int data;
	struct Cola2 *next;	
};

struct apuntadores
{
	int items;
	struct Cola2 *front;
	struct Cola2 *final;
};

typedef struct Cola2 Queue;
typedef struct apuntadores Limits;

void menu();
int add(Limits **start, int N);
int seek(Limits **start);
int search(Limits **start, int N);
int delete(Limits **start, int N);

int main(int argc, char const *argv[])
{
	Limits *queue = NULL;

	add(&queue, 1);
	add(&queue, 2);
	add(&queue, 3);

	printf("Elements of the queue: \n");
    seek(&queue);
    printf("\n");
}

int add(Limits **start, int N)
{
	if (!(*start))
	{
		*start = (Limits *) malloc(sizeof(Limits));
		if (!start)
			return 0;
		(*start)->front = NULL;
		(*start)->final = NULL;
	}
 	Queue *new = (Queue *) malloc(sizeof(Queue));
    if (!new)
	    return 0;
    new->data = N;
    new->next = NULL;

    if ((*start)->front == NULL)
    	(*start)->front = new;
    else
    	(*start)->final->next = new;
    (*start)->final = new;
    (*start)->items++;
	
	return 1;	
}

int seek(Limits **start)
{
	int count = 0;
    if (!(*start)->front)
        printf("\nThe queue is empty!!!\n");
    while (count < (*start)->items)
    {
        printf("[%d] -> ", (*start)->front->data);
        (*start)->front = (*start)->front->next;
        count++;
    } 
	return 0;
}