/*
	Implementacion de una Lista Enlazada
*/
#include <stdio.h>
#include <stdlib.h>

struct Lista
{
	int data;
	struct Lista *next;	
};

typedef struct Lista List;

void menu();
int is_empty(List *start);
int add(List **start, int N);
int seek(List *start);
List *search(List *start, int N);
int delete(List **start, int N);

int main(int argc, char const *argv[])
{
	List *list = NULL;
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
				add(&list, number);
				printf("\n");
				break;

			case 2:
				printf("\nLIST: \n");
				seek(list);
				printf("\n\n");
				break;		
			
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				List *item = search(list, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!!\n\n");
				break;

			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (delete(&list, number) == 1)
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
	printf("Select your option to choice: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

int is_empty(List *start)
{
	if (start == NULL)
		return 1;
	return 0;
}

int add(List **start, int N)
{
	List *new = (List *) malloc(sizeof(List));
	if (is_empty(new))
		return 0;
	new->data = N;
	new->next = *start;
	*start = new;

	return 1;
}

int seek(List *start)
{
	if (is_empty(start))
		return 0;
	printf("[%d] -> ", start->data);
	seek(start->next);
	return 0;
}

List *search(List *start, int N)
{
	if (is_empty(start))
		return NULL;
	if (start->data != N)
		return search(start->next, N);
	return start;
}

int delete(List **start, int N)
{
	if (!is_empty(*start))
	{
		if ((*start)->data == N)
		{
			List *aux = *start;
			*start = (*start)->next;
			free(aux);
			return 1;
		}
		return delete(&(*start)->next, N);
	}
	return 0;
}