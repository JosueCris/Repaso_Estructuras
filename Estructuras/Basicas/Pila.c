/*
	Implementacion de una Pila Dinamica
*/
#include <stdio.h>
#include <stdlib.h>

struct Pila
{
	int data;
	struct Pila *next;	
};

typedef struct Pila Stack;

void menu();
int is_empty(Stack *start);
int push(Stack **start, int N);
Stack *pop(Stack **start);
Stack *top(Stack **start);
int move(Stack **start, Stack **final);
int search(Stack **start, Stack *aux, int N);
int seek(Stack **start, Stack *aux);
int delete(Stack **start, Stack *aux, int N);

int main(int argc, char const *argv[])
{
	Stack *stack = NULL;
	int option, number, buscar;
	
	do
	{
		menu();
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Insert the number in the stack: ");
				scanf("%d", &number);
				push(&stack, number);
				printf("\n");
				break;

			case 2:
				printf("\nSTACK: \n");
				seek(&stack, NULL);
				printf("\n\n");
				break;		
			
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
//				Stack *item = search(&stack, NULL, number);
				search(&stack, NULL, number);
/*				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!!\n\n");
*/
				break;

			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (delete(&stack, NULL, number) == 1)
					printf("Deleted \n\n");
				else
					printf("No delete!!!\n\n");
				break;

			case 0:
				printf("\nSee you later :D \n\n");
				return 0;
				break;	

			default:
				printf("Try Again!!!");
				break;	
		}
	}while(option != 0);

	return 0;
}

void menu()
{
	printf("Select your option to choice from the stack: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

int is_empty(Stack *start)
{
	if (start == NULL)
		return 1;
	return 0;
}

int push(Stack **start, int N)
{
	Stack *new = (Stack *) malloc(sizeof(Stack));
	if (is_empty(new))
	{
		printf("Empty Stack!!!\n");
		return 0;
	}
	new->data = N;
	new->next = *start;
	*start = new;

	return 1;
}

Stack *pop(Stack **start)
{
	if (is_empty(*start))
		return NULL;
	Stack *aux = *start;
	*start = (*start)->next;

	return aux;			
}

Stack *top(Stack **start)
{
	if (is_empty(*start))
		return NULL;
	return *start;
}

int move(Stack **start, Stack **final)
{
	if (is_empty(*start))
		return 0;
	(*start)->next = *final;
	*final = *start;
	return 1;
}

int seek(Stack **start, Stack *aux)
{
	if (is_empty(*start))
		return 0;
	Stack *saca = pop(&(*start));
	move(&saca, &aux);
	printf("[%d] \n |\n V \n", aux->data);
	seek(&(*start), aux);

	Stack *saca2 = pop(&aux);
	return move(&saca2, &(*start));
}

int search(Stack **start, Stack *aux, int N)
{
	if (is_empty(*start))
	{
		printf("No Exist!!! \n\n");
		return 0;
	}
	Stack *saca = pop(start);
	move(&saca, &aux);
	if (aux->data == N)
	{
		saca = pop(&aux);
		move(&saca, start);
		printf("Founded!!! \n\n");
		return 1;
	}
	search(start, aux, N);
	saca = pop(&aux);
	move(&saca, start);

	return 0;
}

int delete(Stack **start, Stack *aux, int N)
{
	if (!is_empty(*start))
	{	
		Stack *saca = pop(start);
		move(&saca, &aux);
		if (aux->data == N)
		{
			Stack *temp = pop(&aux);
			free(temp);
			return 1;
		}
		delete(start, aux, N);
		Stack *saca2 = pop(&aux);
	
		return move(&saca2, start);
	}
	return 0;
}

