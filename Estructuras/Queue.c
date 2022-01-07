#include <stdio.h>
#include <stdlib.h>

typedef struct elem_queue
{
    int data;
    struct elem_queue *next;
}eQueue;

int insert(eQueue **start, int N);
int seek(eQueue *start);
eQueue *search(eQueue *start, int N);
int delete(eQueue **start, int N);

int main(int argc, char const *argv[])
{
    eQueue *queue = NULL;
    int op, number;

    insert(&queue, 8);
    insert(&queue, 5);
    insert(&queue, 0);
    printf("Items of the queue: \n");
    seek(queue);
    printf("\n");

    /*if (!search(queue, 8))
        printf("\nItem not found \n");
    else
        printf("\nThe item [%d] was found \n", search(queue, 8)->data);*/
    delete(&queue, 5);
    seek(queue);
    printf("\n");

    return 0;
}

int empty_queue(eQueue *start)
{
    if (start == NULL)
        return 1;
    return 0;
}

int insert(eQueue **start, int N)
{
	if(!(*start))
	{
		*start = (eQueue *) malloc(sizeof(eQueue));
		if (!(*start))
		{
			printf("\nCould not reserved memory \n");
			return 0;
		}
		(*start)->data = N;
		(*start)->next = NULL;
		return 1;
	}
	return insert(&(*start)->next, N);
}

int seek(eQueue *start)
{
    if (!start)
        return 0;
    printf("[%d]\t", start->data);
    return seek(start->next);
return 0;
}

eQueue *search(eQueue *start, int N)
{
    if (!start)
        return NULL;
    if (start->data != N)
        return search(start->next, N);
    return start;
}

int delete(eQueue **start, int N)
{
    eQueue *aux = *start;
    if (!*start)
        return 0;
    if ((*start)->data != N)
        return delete(&(*start)->next, N);
    else
    {
        *start = (*start)->next;
        free(aux);
        return 1;
    }
    return 0;
}