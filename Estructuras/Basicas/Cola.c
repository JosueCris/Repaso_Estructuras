/*
	Implementacion de una Cola Dinamica
*/
#include <stdio.h>
#include <stdlib.h>

struct Cola
{
	int data;
	struct Cola *next;	
};

typedef struct Cola Queue;

void menu();
int is_empty(Queue *start);
int add(Queue **start, int N);
int seek(Queue *start);
Queue *search(Queue *start, int N);
int delete(Queue **start, int N);

int main(int argc, char const *argv[])
{
	Queue *queue = NULL;
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
				add(&queue, number);
				printf("\n");
				break;

			case 2:
				printf("\nQUEUE: \n");
				seek(queue);
				printf("\n\n");
				break;		
			
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				Queue *item = search(queue, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!!\n\n");
				break;

			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (delete(&queue, number) == 1)
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
	printf("Select your option to choice from the queue: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

int is_empty(Queue *start)
{
	if (start == NULL)
		return 1;
	return 0;
}

int add(Queue **start, int N)
{
	if (is_empty(*start))
	{
		*start = (Queue *) malloc(sizeof(Queue));
		if (is_empty(*start))
			return 0;
		(*start)->data = N;
		(*start)->next = NULL;
		return 1;
	}
	return add(&(*start)->next, N);
}

int seek(Queue *start)
{
	if (is_empty(start))
		return 0;
	printf("[%d] -> ", start->data);
	seek(start->next);
	return 0;
}

Queue *search(Queue *start, int N)
{
	if (is_empty(start))
		return NULL;
	if (start->data == N)
		return start;
	return search(start->next, N);
}

int delete(Queue **start, int N)
{
	if (!is_empty(*start))
	{
		if ((*start)->data == N)
		{
			Queue *aux = *start;
			*start = (*start)->next;
			free(aux);
			return 1;
		}
		return delete(&(*start)->next, N);
	}
	return 0;
}