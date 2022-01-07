/* Implementar los siguientes métodos de Cola: 
- Insertar
- Eliminar
- Buscar
la cola contendrá como Dato un producto de coca-cola. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem_qeue
{
	char data[15];
	struct elem_qeue *next;
	
}elem_qeue;

int insert_elem_qeue(elem_qeue **start, char *P);
int delete_elem_qeue(elem_qeue **start, char *P);
int print_qeue(elem_qeue *start);
int search(elem_qeue *start, char *P);

int main(int argc, char const *argv[])
{
	elem_qeue *start = NULL;
	char soda[15];
	int op;

	do{
		printf(".========================.\n");
		printf("|| Insert your option:  ||\n");
		printf("||======================||\n");
		printf("||  [1]: Insert         ||\n");
		printf("||  [2]: Show           ||\n");
		printf("||  [3]: Search         ||\n");
		printf("||  [4]: Delete         ||\n");
		printf("||  [5]: Get Up         ||\n");
		printf(".========================.\n\n[]:> ");
		scanf("%d", &op);
		printf("\n");

		switch(op)
		{
			case 1:
			printf("\nInsert your name of product:\n[]:> ");
			scanf("%s", soda);

			insert_elem_qeue(&start, soda);
			system("cls || clear");
			break;

			case 2:
			printf("Elements of the cola: \n");
			print_qeue(start);
			break;

			case 3:
			printf("\nInsert your product to search:\n[]:> ");
			scanf("%s", soda);

			search(start, soda);  
			break;

			case 4:
			printf("\nInsert your product to delete:\n[]:> ");
			scanf("%s", soda);
			delete_elem_qeue(&start, soda);
			break;

			case 5:
			printf("\nThank You!!! \n\n");
			return 0;
			break;

			default:
			printf("\nTry Again \n\n");
			break;
		}

	}while(op != 1 || op != 2 || op != 3 || op != 4 || op != 5);
	
	return 0;
}

int insert_elem_qeue(elem_qeue **start, char *P)
{
	if(!(*start))
	{
		*start = (elem_qeue *) malloc(sizeof(elem_qeue));
		if (!(*start))
		{
			printf("\nCould not reserved memory \n");
			return 0;
		}
		strcpy((*start)->data, P);
		(*start)->next = NULL;
		return 1;
	}
	return insert_elem_qeue(&(*start)->next, P);
}

int print_qeue(elem_qeue *start)
{
	if(start == NULL)
	{
		printf("\nFinish of the qeue\n");
		return 0;
	}
	printf("[%s] \n", start->data);
	return print_qeue(start->next);
return 0;
}

int delete_elem_qeue(elem_qeue **start, char *P)
{
    elem_qeue *pActual = *start;
    if((*start) != NULL){
    	if ((strcmp((*start)->data, P)) == 0)
    	{
			*start = (*start)->next;
			printf("The product was deleted\n\n");
			free(pActual);
			return 1;
		}
		return delete_elem_qeue(&(*start)->next, P);
    }
    return 0;
	
}

int search(elem_qeue *start, char *P)
{
	if((start != NULL)){
    	if ((strcmp(start->data, P)) !=  0)
		{
		return search(start->next, P);
		}
	printf("We found it: %s \n\n", start->data);
	return 1;
}
	printf("Product not found \n\n");
	return 0;	
}