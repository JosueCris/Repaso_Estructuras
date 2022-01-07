#include <stdio.h>
#include <stdlib.h>

typedef struct elem_list
{
    int data;
    struct elem_list *next;
}eList;

typedef struct elem_lislist
{
    int num;
    struct elem_list *startList;
    struct elem_lislist *next;
}elisList;

// Funciones de la lista interna
int empty_list(eList *start);
int insert(eList **start, int N);
int seek(eList *start);
eList *search(eList *start, int N);
int delete(eList **start, int N);
//int buscar(eList **start, int N);

// Funciones de la lista de listas
int insertL(elisList **startL, int N);
int seekL(elisList *start);
eList *searchL(elisList *start, int N);
int deleteL(elisList **start, int N);
//int buscarL(elisList **start, int N);

int main(int argc, char const *argv[])
{
    eList *list = NULL;
    elisList *lisList = NULL;
    int op, number;

    if (insertL(&lisList, 8) == 1)
        printf("Item INSERTED \n");
    else
        printf("Item NOT INSERTED \n");
    

    return 0;
}

int empty_list(eList *start)
{
    if(!start)
        return 1;
    return 0;
}

int insert(eList **start, int N)
{
    eList *new_eList = (eList *) malloc(sizeof(eList));
    if (!new_eList)
    {
        printf("Couldn't reserved the memory!!! \n");
        return 0;
    }
    new_eList->data = N;
    new_eList->next = *start;
    *start = new_eList;
    
    return 1;
}

int seek(eList *start)
{
    if (!start)
    {
        return 0;
    }
    printf("[%d] \t", start->data);
    return seek(start->next);

    return 0;
}

eList *search(eList *start, int N)
{
    if (empty_list(start))
        return NULL;
    if (start->data != N)
        return search(start->next, N);
    return start;
}

int delete(eList **start, int N)
{
    eList *aux = *start;
    if (!empty_list(*start))
    {
        if ((*start)->data == N)
        {
            *start = (*start)->next;
            free(aux);
            return 1;
        }
        return delete(&(*start)->next, N);
    }
    return 0;
}

int insertL(elisList **startL, int N)
{
    if(!(*startL))
	{
		elisList *new_elisList = (elisList *) malloc(sizeof(elisList));
		if (!new_elisList)
			return 0;
		new_elisList->num = N;
		new_elisList->next = NULL;
		new_elisList->startList = NULL;

		if (!insert(&new_elisList->startList, N))
		{
			free(new_elisList);
			return 0;
		}

		*startL = new_elisList;
		return 1;
	}
	if ((*startL)->num == N)
	{
		if (!insertL(&((*startL)->startList), N))
			return 0;
		return 1;
	}
	return insertL(&((*startL)->next), N);
}
/*int buscar(eList **start, int N)
{
    if (empty_list(*start))
        return 0;
    if ((*start)->data != N)
        return buscar(&(*start)->next, N);
    return (*start)->data;
}*/