/*  
    Implementacion de un arbol donde la raiz tiene n cantidad de hijos y de hermanos.
    Arbol General.
*/
#include <stdio.h>
#include <stdlib.h>

struct arbol_general
{
    int data;
    struct arbol_general *childs;
    struct arbol_general *brothers;
};

typedef struct arbol_general Tree;

void menu();

Tree *create_node(int N);
int add(Tree **root, int N);
int add_children(Tree **root, int N);
Tree *dfs(Tree *root, int code);
int seek(Tree *root);
int number_nodes(Tree *root);


int main(int argc, char const *argv[])
{
    Tree *gral_tree = NULL;
    int option, code, number;

	do
	{
		menu();
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Insert the number: ");
                scanf("%d", &number);
                add(&gral_tree, number);
				printf("\n");
				break;

			case 2:
				printf("\nItems of the general tree:\n");
				seek(gral_tree);
				printf("\n\n");
				break;					

			
			case 3: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				
				Tree *item = dfs(gral_tree, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!! \n\n");
				break;
				
/*
			case 4:
				printf("Insert the number to delete: ");
				scanf("%d", &code);
				if (delete(&gral_tree, code) == 1)
					printf("Deleted \n\n");
				else
					printf("No deletet!!!\n\n");
				break;
*/
			case 5:
				printf("Number of nodes: %d\n\n", number_nodes(gral_tree));
				break;
                
/*
			case 6:
				printf("Ingresa el codigo del empleado a buscar: ");
				scanf("%d", &codigo);
				printf("Numero de hijos: %d\n\n", cant_hijos(arbol_gral, codigo));
*/				break;	

			case 0:
				printf("\nGood bye asshole :P \n\n");
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
    printf("Select your option to choose from the general tree: \n\t");
	printf("[1]: Insert\n\t[2]: Seek\n\t[3]: Search\n\t[4]: Delete\n\t[5]: Items\n\t[6]: Number Childs\n\t[0]: Exit\n> ");
}

Tree *create_node(int N)
{
    Tree *new = (Tree *) malloc(sizeof(Tree));
    if(!new)
        return NULL;
    new->data = N;
    new->childs = NULL;
    new->brothers = NULL;

    return new;
}
int add(Tree **root, int N)
{
    int code;
    if(!*root)
	{
		if(*root = create_node(N))
			return 1;
		return 0;	
	}
	printf("Enter the phater: ");
	scanf("%d", &code);
	Tree *phater = dfs(*root, code);
	if (!phater)
	{
		printf("Fault :( \n");
		return 1;
	}
	return add_children(&phater->childs, N);
}

int add_children(Tree **root, int N)
{
    if(!*root)
	{
		if(*root = create_node(N))
			return 1;
		return 0;	
	}
	return add_children(&(*root)->brothers, N);       
}

Tree *dfs(Tree *root, int code)
{
    if(!root)
		return NULL;
	if(code == root->data)
		return root;
	Tree *aux = dfs(root->childs, code);
	if (!aux)
        aux = dfs(root->brothers, code);
    return aux;	    
}

int seek(Tree *root)
{
    if(!root)
        return 0;
    printf("%d -> ", root->data);
    seek(root->brothers);
    printf("\n | \n V \n");
    seek(root->childs);

    return 1;
}

int number_nodes(Tree *root)
{
    if(!root)
        return 0;
    return 1 + number_nodes(root->childs) + number_nodes(root->brothers);    
}
