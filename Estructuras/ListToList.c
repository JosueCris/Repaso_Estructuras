#include <stdio.h>
#include <stdlib.h>

typedef struct elem_list
{
    int data;
    struct elem_list *next;
    struct elem_list *before;
}eList;

typedef struct elem_lislist
{
    int num;
    struct elem_list *startList;
    struct elem_lislist *next;
    struct elem_lislist *before;
}elisList;

// Funciones de la lista interna
int insert_list(eList **start, int N);
int seek_list(eList *start);
eList *search_list(eList *start, int N);
int delete_list(eList **start, int N);

// Funciones de la lista de listas
int insert_listL(elisList **startL, int N);
int seek_listL(elisList *startL);
eList *search_listL(elisList *startL, int N);
int delete_listL(elisList **startL, int N);

int main(int argc, char const *argv[])
{
    elisList *lisList = NULL;
    int number, op;

    insert_listL(&lisList, 3);
    insert_listL(&lisList, 2);
    insert_listL(&lisList, 1);

    insert_list(&lisList->startList, 5);
    insert_list(&lisList->startList, 4);
    insert_list(&lisList->startList, 3);
    insert_list(&lisList->startList, 2);
    insert_list(&lisList->next->startList, 8);
    insert_list(&lisList->next->startList, 6);
    insert_list(&lisList->next->startList, 4);
    insert_list(&lisList->next->next->startList, 9);
    insert_list(&lisList->next->next->startList, 6);
    
    printf("Items of the list: \n");
    seek_listL(lisList);
    printf("\n");
     
}

int insert_list(eList **start, int N)
{
    eList *new_eList = (eList *) malloc(sizeof(eList));
    if (!new_eList)
    {
        printf("Couldn't reserved the memory!!! \n");
        return 0;
    }
    new_eList->data = N;
    new_eList->before = NULL;

    if (!*start)
    {
        new_eList->next = NULL;
        *start = new_eList;
        return 0;
    }
    (*start)->before = new_eList;
    new_eList->next = *start;
    *start = new_eList;
    return 1;
}

int seek_list(eList *start)
{
     if (!start)
    {
        return 0;
    }
    printf("[%d]=>", start->data);
    return seek_list(start->next);

    return 0;
}

eList *search_list(eList *start, int N)
{
    if (!start)
        return NULL;
    if (start->data != N)
        return search_list(start->next, N);
    return start;
    
}

int delete_list(eList **start, int N)
{
    eList *aux = *start;
    if (*start)
    {
        if ((*start)->data == N)
        {
            *start = (*start)->next;
            free(aux);
            return 1;
        }
        return delete_list(&(*start)->next, N);
    }
    return 0;
}

int insert_listL(elisList **startL, int N)
{
    elisList *new_list = (elisList *) malloc(sizeof(elisList));
    if (!new_list)
    {
        return 0;
    }
    new_list->startList = NULL;
    new_list->num = N;
    new_list->before = NULL;

    if (!*startL)
    {
        new_list->next = NULL;
        *startL = new_list;
        return 1;
    }
    (*startL)->before = new_list;
    new_list->next = *startL;
    *startL = new_list;
    return 1;
}

int seek_listL(elisList *startL)
{
    if (!startL)
    {
        return 0;
    }
    printf("[%d] -> ", startL->num);
    seek_list(startL->startList);
    printf("\n||\n\\/\n");
    seek_listL(startL->next);

    return 0;
}