/* implemente las funciones en C de:
- insertar
- Borrar
- buscar
para una lista de colas. */
#include <stdio.h>
#include <stdlib.h>

typedef struct elem_queue
{
	int data;
	struct elem_queue *next;
}eQueue;

typedef struct elem_list
{
	struct elem_queue *startQueue;
	struct elem_list *next;
}eList;

// Funciones de la Lista
int insert_list(eList **startL, int N);
int search_list(eList *startL, int N);
int delete_list(eList **startL, eQueue **startQ);

// Funciones de la cola
int lenght(eQueue *queue);
int insert_queue(eQueue **startQ, int N);
int search_queue(eQueue *startQ, int N);
int delete_queue(eQueue **startQ, int N);

int main(int argc, char const *argv[])
{
	eList *list = NULL;
	int numero;

	if (insert_list(&list, 6) == 1)
	{
		printf("Insertado\n");
	}
	else
		printf("No insertado\n");

	return 0;
}

int insert_queue(eQueue **startQ, int N)
{
	if(!(*startQ)) {
        (*startQ) = (eQueue *) malloc(sizeof(eQueue));
        if(!(*startQ))
            return 0;
        (*startQ)->data = N;
        (*startQ)->next = NULL;
        return 1;
    }
    return insert_queue(&(*startQ)->next, N);
}
int lenght(eQueue *queue)
{
	if (!queue)
	{
		return 0;
	}
	return 1+lenght(queue->next);
}

int insert_list(eList **startL, int N)
{
	if (!*startL)
	{
		eList *aux = (eList *) malloc(sizeof(eList));
		aux->startQueue = NULL;
		*startL = aux;
		insert_queue(&(*startL)->startQueue, N);
		return 1;
	}
	if (lenght((*startL)->startQueue) > 5)
	{
		eList *new_list = (eList *) malloc(sizeof(eList));
		if (!new_list)
		{
			return 0;
		}
		new_list->startQueue = NULL;
		*startL = new_list;
		insert_queue(&(*startL)->startQueue, N);
		return 1;
	}
	insert_queue(&(*startL)->startQueue, N);
	return 1;
}

int delete_queue(eQueue **startQ, int N)
{
	if(!(*startQ))
        return 0;
    int value = (*startQ)->data;
    if(value != N)
        return delete_queue(&(*startQ)->next, N);
    eQueue *aux = NULL;
    aux = (*startQ);
    (*startQ) = (*startQ)->next;
    free(aux);
    return 1;
}

int search_queue(eQueue *startQ, int N)
{ //retorna el valor buscado, si se encuentra en la cola
    if(!startQ) 
        return 0;
    if(startQ->data != N)
        return search_queue(startQ->next, N);
    return startQ->data;        
}
