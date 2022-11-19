#include <stdio.h>
#include <stdlib.h>
#define cant 3

struct pila
{
	int data;
	struct pila *next;
};

struct lista_pilas
{
	struct pila *startStack;
	struct lista_pilas *next;
};

typedef struct pila Stack;
typedef struct lista_pilas ListS;

void menu();
int length(Stack *startS);

// Funciones de la Pila
int push(Stack **startS, int N);
Stack *pop(Stack **startS);
Stack *top(Stack **startS);
int move(Stack **startS, Stack **final);
//int searchS(Stack **startS, Stack *aux, int N);
Stack *searchS(Stack **startS, Stack *aux, int N);
int seekS(Stack **startS, Stack *aux);
int deleteS(Stack **startS, Stack *aux, int N);

// Funciones de la Lista de Pilas
int insertL(ListS **startL, int N);
int seekL(ListS **startL);
//int searchL(ListS **startL, int N);
Stack *searchL(ListS **startL, int N);
int deleteL(ListS **startL, int N);


int main(int argc, char const *argv[])
{
    ListS *list = NULL;
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
				insertL(&list, number);
				printf("\n");
				break;

			case 2:
				printf("\nItems of the list of queues:\n");
				seekL(&list);
				printf("\n\n");
				break;		

// La busqueda esta media rara falta mejorarla
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				//searchL(&list, number);
				Stack *item = searchL(&list, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!!\n\n");
				break;

// No me elimina ningun elemento
			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				deleteL(&list, number);
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
	printf("Select your option to choose from the list of stacks: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

int length(Stack *startS)
{
	if(!startS)
		return 0;
	return 1 + length(startS->next);
}

// Implementacion de las funciones de la Pila
int push(Stack **startS, int N)
{
	Stack *new = (Stack *) malloc(sizeof(Stack));
	if (!new)
	{
		printf("Empty Stack!!!\n");
		return 0;
	}
	new->data = N;
	new->next = *startS;
	*startS = new;

	return 1;
}

Stack *pop(Stack **startS)
{
	if (!*startS)
		return NULL;
	Stack *aux = *startS;
	*startS = (*startS)->next;

	return aux;			
}

Stack *top(Stack **startS)
{
	if (!*startS)
		return NULL;
	return *startS;
}

int move(Stack **startS, Stack **final)
{
	if (!*startS)
		return 0;
	(*startS)->next = *final;
	*final = *startS;
	return 1;
}

int seekS(Stack **startS, Stack *aux)
{
	if (!*startS)
		return 0;
	Stack *saca = pop(&(*startS));
	move(&saca, &aux);
	printf("[%d] -> ", aux->data);
	seekS(&(*startS), aux);

	Stack *saca2 = pop(&aux);
	return move(&saca2, &(*startS));
}

/*
int searchS(Stack **startS, Stack *aux, int N)
{
	if (!*startS)
	{
		printf("No Exist!!! \n\n");
		return 0;
	}
	Stack *saca = pop(&(*startS));
	move(&saca, &aux);
	if (aux->data == N)
	{
		saca = pop(&aux);
		move(&saca, &(*startS));
		printf("Founded!!! \n\n");
		return 1;
	}
	searchS(&(*startS), aux, N);
	saca = pop(&aux);
	move(&saca, &(*startS));

	return 0;
}
*/

Stack *searchS(Stack **startS, Stack *aux, int N)
{
	if (!*startS)
		return 0;
	Stack *saca = pop(&(*startS));
	move(&saca, &aux);
	if (aux->data == N)
	{
		saca = pop(&aux);
		move(&saca, &(*startS));
		return aux;
	}
	searchS(&(*startS), aux, N);
	saca = pop(&aux);
	move(&saca, &(*startS));

	return NULL;
}

int deleteS(Stack **startS, Stack *aux, int N)
{
	if (!*startS)
	{	
		Stack *saca = pop(&(*startS));
		move(&saca, &aux);
		if (aux->data == N)
		{
			Stack *temp = pop(&aux);
			free(temp);
			return 1;
		}
		deleteS(&(*startS), aux, N);
		Stack *saca2 = pop(&aux);
	
		return move(&saca2, &(*startS));
	}
	return 0;
}

// Implementacion de las funciones de la Lista de Pilas
int insertL(ListS **startL, int N)
{
	if(!*startL)
	{
		ListS *new = (ListS *) malloc(sizeof(ListS));
		if(!new)
			return 0;
		new->next = *startL;
		new->startStack = NULL;

		if(!push(&new->startStack, N))
		{
			free(new);
			return 0;
		}
		*startL = new;
		return 1;
	}
	if(length((*startL)->startStack) < cant)
	{
		if(!push(&((*startL)->startStack), N))
			return 0;
		return 1;
	}
	return insertL(&(*startL)->next, N);
}

int seekL(ListS **startL)
{
	if(!*startL)
		return 0;
	seekS(&(*startL)->startStack, NULL);
	printf("\n | \n V \n");
	return seekL(&(*startL)->next);

	return 0;
}

Stack *searchL(ListS **startL, int N)
{
	if (!*startL)
		return NULL;
	Stack *founded = searchS(&(*startL)->startStack, NULL, N);
	if (founded)
		return founded;
	return searchL(&(*startL)->next, N);
}

int deleteL(ListS **startL, int N)
{
	if (!*startL)	
		return 0;
	if (deleteS(&(*startL)->startStack, NULL, N) == 1)
	{
		if (!(*startL)->startStack)
		{
			ListS *aux = *startL;
			*startL = (*startL)->next;
			free(aux);
			return 1;
		}
	}
	else
		return deleteL(&(*startL)->next, N);
	return 0;
}