// Insercion condicionada en si el dato es mayor o menor.
#include <stdio.h>
#include <stdlib.h>

struct lista
{
	int data;
	struct lista *next;
};

struct lista_listas
{
	int ref;
	struct lista *sList;
	struct lista_listas *next;
};

typedef struct lista List;
typedef struct lista_listas LiList;

void menu();

// Funciones de la lista normal
int insert(List **start, int N);
int seek(List *start);
List *search(List *start, int N);
int delete(List **start, int N);

// Funciones de la lista de listas
int insertL(LiList **startL, int N);
int seekL(LiList *startL);
List *searchL(LiList *startL, int N);
int deleteL(LiList **startL, int N);

int main(int argc, char const *argv[])
{
	LiList *list_of_lists = NULL;
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
				insertL(&list_of_lists, number);
				printf("\n");
				break;

			case 2:
				printf("\nItems of the list of lists:\n");
				seekL(list_of_lists);
				printf("\n\n");
				break;		
			
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				
				List *item = searchL(list_of_lists, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!!\n\n");
				break;

			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (deleteL(&list_of_lists, number) == 1)
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
	printf("Select your option to choose from the list of lists: \n\t");
	printf("[1]: Insert\n\t[2]: Show\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}

// Implementacion de las funciones de la lista normal
int insert(List **start, int N)
{
	List *new = (List *) malloc(sizeof(List));
	if (!new)
	{
		printf("\nCouldn't reserved memory!!!\n\n");
		return 0;
	}
	new->data = N;
	new->next = *start; 
	*start = new;

	return 1;
}

int seek(List *start)
{
	if(!start)
		return 0;
	printf("[%d] -> ", start->data);
	return seek(start->next);
	return 0;
}

List *search(List *start, int N)
{
	if (!start)
		return NULL;
	if (start->data != N)
		return search(start->next, N);
	return start;
}

int delete(List **start, int N)
{
	if (*start)
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


// Implementacion de las funciones de la lista de listas
int insertL(LiList **startL, int N)
{
	if(!*startL)
	{
		LiList *new = (LiList *) malloc(sizeof(LiList));
		if(!new)
			return 0;
		new->ref = N;
		new->next = *startL;
		new->sList = NULL;

		if(!insert(&new->sList, N))
		{
			free(new);
			return 0;
		}
		*startL = new;
		return 1;
	}
	if((*startL)->ref > N)
	{
		if(!insert(&((*startL)->sList), N))
			return 0;
		return 1;
	}
	return insertL(&(*startL)->next, N);
}

int seekL(LiList *startL)
{
	if(!startL)
		return 0;
	seek(startL->sList);
	printf("\n | \n V \n");
	return seekL(startL->next);

	return 0;
}

List *searchL(LiList *startL, int N)
{
	if (!startL)
		return NULL;
	List *founded = search(startL->sList, N);
	if (founded)
		return founded;
	return searchL(startL->next, N);
}

int deleteL(LiList **startL, int N)
{
	if (!*startL)	
		return 0;
	if (delete(&(*startL)->sList, N) == 1)
	{
		if (!(*startL)->sList)
		{
			LiList *aux = *startL;
			*startL = (*startL)->next;
			free(aux);
			return 1;
		}
	}
	else
		return deleteL(&(*startL)->next, N);
	return 0;
}

/*List *newList = (List *) malloc(sizeof(List));
		if(!newList)
		{
			free(new);
			return 0;
		}
		newList->data = N;
		newList->next = NULL;
		new->sList = newList;*/