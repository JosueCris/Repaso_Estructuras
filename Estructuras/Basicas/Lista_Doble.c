/*
	Implementacion de una Lista Doblemente Enlazada
*/
#include <stdio.h>
#include <stdlib.h>

struct Lista_Doble
{
	int data;
	struct Lista_Doble *next;
	struct Lista_Doble *before;
};

typedef struct Lista_Doble DList;

void menu();
int length(DList *start);

int is_empty(DList *start);
DList *create(int N);
int add_front(DList **start, int N);
int add_final(DList **start, int N);
int seek_front(DList *start);
int seek_final(DList *start);
DList *search(DList *start, int N);
int delete(DList **start, int N);

int main(int argc, char const *argv[])
{
	DList *list = NULL;
	int option, option2, option3, number, buscar;
	
	do
	{
		menu();
		scanf("%d", &option);

		switch (option)
		{
			case 1:
				printf("Insert the number: ");
				scanf("%d", &number);
				printf("\tWhere do you want to insert?\n\t\t[1]: To Front\n\t\t[2]: To Final\n\t> ");
				scanf("%d", &option2);

				switch (option2)
				{
					case 1:
						add_front(&list, number);
						break;
					case 2:
						add_final(&list, number);
						break;			
				}
				break;

			case 2:
				printf("\tWhere do you want to start?\n\t\t[1]: Seek Front\n\t\t[2]: Seek Final\n\t> ");
				scanf("%d", &option3);

				switch (option3)
				{
					case 1:
						printf("\nDOUBLE LINKED LIST \nFront - Final: \n");
						seek_front(list);
						printf("\n\n");
						break;
					case 2:
						printf("\nDOUBLE LINKED LIST \nFinal - Front: \n");
						seek_final(list);
						printf("\n\n");
						break;
				}	
				break;
			
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				DList *item = search(list, number);
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
	printf("Select your option to choice from \nthe double linked list: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

int length(DList *start)
{
	if (is_empty(start))
		return 0;
	return 1 + length(start->next);
}

int is_empty(DList *start)
{
	if (!start)
		return 1;
	return 0;
}

DList *create(int N)
{
	DList *new = (DList *) malloc(sizeof(DList));
	if (is_empty(new))
		return 0;
	new->data = N;
	new->next = NULL;
	new->before = NULL;
	
	return new;
}

int add_front(DList **start, int N)
{
	DList *new = create(N);
	if (is_empty(new))
		return 0;
	if (!is_empty(*start))
		(*start)->before = new;
	new->next = *start;
	*start = new;

	return 1;

	// if (is_empty(*start))
	// {
	// 	new = (DList *) malloc(sizeof(DList));
	// 	if(is_empty(new))
	// 		return 0;
	// 	new->data = N;
	// 	new->next = *start;
	// 	new->before = *start;
	// 	*start = new;
	// 	return 1;
	// }
	// else
	// {
	// 	new = (DList *) malloc(sizeof(DList));
	// 	if(is_empty(new))
	// 		return 0;
	// 	new->data = N;
	// 	new->next = *start;
	// 	new->before = NULL;
	// 	(*start)->before = new;
	// 	*start = new;
	// }
	// return 1;
}

int add_final(DList **start, int N)
{
	if (is_empty(*start))
	{
		add_front(&(*start), N);
		return 1;
	}
	DList *aux = *start;
	DList *new = create(N);
	for (; aux->next; aux=aux->next);
	aux->next = new;
	new->before = aux;

	return 1;
}

int seek_front(DList *start)
{
	if (is_empty(start))
		return 0;
	printf("[%d] <=> ", start->data);
	seek_front(start->next);
}

int seek_final(DList *start)
{
	if (is_empty(start))
		return 0;
	for (; start->next; start=start->next);
	for (; start; start=start->before)
		printf("[%d] <=> ", start->data);
}

DList *search(DList *start, int N)
{
	if (is_empty(start))
		return NULL;
	if (start->data == N)
		return start;
	return search(start->next, N);
}

//	Falta terminar la eliminacion con el apuntador before
int delete(DList **start, int N)
{
	if (!is_empty(*start))
	{
		if ((*start)->data == N)
		{
			DList *aux = *start;
			// (*start)->next->before = *start;
			*start = (*start)->next;
			free(aux);
			return 1;
		}
		return delete(&(*start)->next, N);
	}
	return 0;
}