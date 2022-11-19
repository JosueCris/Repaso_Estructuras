/* implemente las funciones en C de:
- insertar
- Borrar
- buscar
para una lista de colas. */
#include <stdio.h>
#include <stdlib.h>

struct cola
{
	int data;
	struct cola *next;
};

struct lista_colas
{
	struct cola *startQueue;
	struct lista_colas *next;
};

typedef struct cola Queue;
typedef struct lista_colas ListQ;

void menu();
int length(Queue *startQ);

// Funciones de la Cola
int addQ(Queue **startQ, int N);
int seekQ(Queue *startQ);
Queue *searchQ(Queue *startQ, int N);
int deleteQ(Queue **startQ, int N);

// Funciones de la Lista de Colas
int addL(ListQ **startL, int N);
int seekL(ListQ *startL);
Queue *searchL(ListQ *startL, int N);
int deleteL(ListQ **startL, int N);

int main(int argc, char const *argv[])
{
	ListQ *list = NULL;
	int option, number, buscar;

	do
	{
		menu();
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Insert the number: ");
				scanf("%d", &number);
				addL(&list, number);
				printf("\n");
				break;

			case 2:
				printf("\nItems of the list of queues:\n");
				seekL(list);
				printf("\n\n");
				break;		
			
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				
				Queue *item = searchL(list, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!!\n\n");
				break;

			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (deleteL(&list, number) == 1)
					printf("Deleted \n\n");
				else
					printf("No delete!!!\n\n");
				break;

			case 0:
				printf("\nSee you later :D \n\n");
				return 0;
				break;	

			default:
				printf("\nTry Again!!! \n\n");
				break;	
		}
	}while(option != 0);

	return 0;
}

void menu()
{
	printf("Select your option to choose from the list of queues: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

int length(Queue *startQ)
{
	if (!startQ)
		return 0;
	return 1 + length(startQ->next);
}

int addQ(Queue **startQ, int N)
{
	if(!(*startQ)) {
        (*startQ) = (Queue *) malloc(sizeof(Queue));
        if(!(*startQ))
            return 0;
        (*startQ)->data = N;
        (*startQ)->next = NULL;
        return 1;
    }
    return addQ(&(*startQ)->next, N);
}

int seekQ(Queue *startQ)
{
	if (!startQ)
		return 0;
	printf("[%d] -> ", startQ->data);
	return seekQ(startQ->next);
	return 0;
}

Queue *searchQ(Queue *startQ, int N)
{
    if(!startQ) 
        return 0;
    if(startQ->data != N)
        return searchQ(startQ->next, N);
    return startQ;        
}

int deleteQ(Queue **startQ, int N)
{
	if(!(*startQ))
        return 0;
    int value = (*startQ)->data;
    if(value != N)
        return deleteQ(&(*startQ)->next, N);
    Queue *aux = NULL;
    aux = (*startQ);
    (*startQ) = (*startQ)->next;
    free(aux);
    return 1;
}


int addL(ListQ **startL, int N)
{
	if(!*startL)
	{
		ListQ *new = (ListQ *) malloc(sizeof(ListQ));
		if(!new)
			return 0;
		new->next = *startL;
		new->startQueue = NULL;

		if(!addQ(&new->startQueue, N))
		{
			free(new);
			return 0;
		}
		*startL = new;
		return 1;
	}
	if(length((*startL)->startQueue) < 3)
	{
		if(!addQ(&((*startL)->startQueue), N))
			return 0;
		return 1;
	}
	return addL(&(*startL)->next, N);
}

int seekL(ListQ *startL)
{
	if (!startL)
		return 0;
	seekQ(startL->startQueue);
	printf("\n | \n V \n");
	return seekL(startL->next);

	return 0;
}

Queue *searchL(ListQ *startL, int N)
{
	if (!startL)
		return NULL;
	Queue *founded = searchQ(startL->startQueue, N);
	if (founded)
		return founded;
	return searchL(startL->next, N);
}

int deleteL(ListQ **startL, int N)
{
	if(!*startL)
		return 0;
	if (deleteQ(&(*startL)->startQueue, N) == 1)
	{
		if (!(*startL)->startQueue)
		{
			ListQ *aux = *startL;
			*startL = (*startL)->next;
			free(aux);
			return 1;
		}
	}
	else
		return deleteL(&(*startL)->next, N);
	return 0;
}