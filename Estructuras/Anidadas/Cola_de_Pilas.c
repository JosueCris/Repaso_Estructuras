#include <stdio.h>
#include <stdlib.h>
#define cant 3

struct pila
{
	int data;
	struct pila *next;
};

struct cola_pilas
{
	struct pila *startStack;
	struct cola_pilas *next;
};

typedef struct pila Stack;
typedef struct cola_pilas QueueS;

void menu();
int length(Stack *startS);

// Funciones de la Pila
int push(Stack **startS, int N);
Stack *pop(Stack **startS);
Stack *top(Stack **startS);
int move(Stack **startS, Stack **final);
int searchS(Stack **startS, Stack *aux, int N);
int seekS(Stack **startS, Stack *aux);
int deleteS(Stack **startS, Stack *aux, int N);

// Funciones de la Cola de Pilas
int addQ(QueueS **startQ, int N);
int seekQ(QueueS **startQ);
int searchQ(QueueS **startQ, int N);
int deleteQ(QueueS **startQ, int N);


int main(int argc, char const *argv[])
{
	QueueS *queue = NULL;
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
				addQ(&queue, number);
				printf("\n");
				break;

			case 2:
				printf("\nItems of the list of queues:\n");
				seekQ(&queue);
				printf("\n\n");
				break;		

// La busqueda esta media rara falta mejorarla
// Ya vi jeje imprime si existe o no el numero en cada elemento cola
// Por eso los mensajes multiples
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				searchQ(&queue, number);
				break;

// No me elimina ningun elemento
			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				deleteQ(&queue, number);
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
	printf("Select your option to choose from the queue of stacks: \n\t");
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


// Implementacion de las fuciones de la Cola de Pilas
int addQ(QueueS **startQ, int N)
{
	if(!*startQ)
	{
		QueueS *new = (QueueS *) malloc(sizeof(QueueS));
		if(!new)
			return 0;
		new->next = *startQ;
		new->startStack = NULL;

		if(!push(&new->startStack, N))
		{
			free(new);
			return 0;
		}
		*startQ = new;
		return 1;
	}
	if(length((*startQ)->startStack) < cant)
	{
		if(!push(&((*startQ)->startStack), N))
			return 0;
		return 1;
	}
	return addQ(&(*startQ)->next, N);
}

int seekQ(QueueS **startQ)
{
	if(!*startQ)
		return 0;
	seekS(&(*startQ)->startStack, NULL);
	printf("\n | \n V \n");
	return seekQ(&(*startQ)->next);

	return 0;
}

// Falta mejorar esta funcion porque sale dos impresiones
int searchQ(QueueS **startQ, int N)
{
	if (!*startQ)
		return 0;
	if (searchS(&(*startQ)->startStack, NULL, N) == 1)
		return 1;
	return searchQ(&(*startQ)->next, N);
}

// Este de plano no me elimina nada
int deleteQ(QueueS **startQ, int N)
{
	if(!*startQ)
		return 0;
	if(deleteS(&(*startQ)->startStack, NULL, N) == 1)
	{
		if (!(*startQ)->startStack)
		{
			QueueS *aux = *startQ;
			*startQ = (*startQ)->next;
			free(aux);
			return 1;
		}
	}	
	else
		return deleteQ(&(*startQ)->next, N);
	return 0;	
}