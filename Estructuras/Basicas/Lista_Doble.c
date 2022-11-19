#include <stdio.h>
#include <stdlib.h>

struct Lista_Doble
{
	int data;
	struct Lista_Doble *next;
	struct Lista_Doble *before;
};

typedef struct Lista_Doble DList;

int is_empty(DList *start);
int add(DList **start, int N);
int seek_front(DList *start);

int main(int argc, char const *argv[])
{
	DList *list = NULL;
	return 0;
}

int is_empty(DList *start)
{
	if(!start)
		return 1;
	return 0;
}

int add(DList **start, int N)
{
	DList *new = (DList *) malloc(sizeof(DList));
	if(is_empty(new))
		return 0;
	new->data = N;
	new->next = start;
	
}
int seek_front(DList *start);