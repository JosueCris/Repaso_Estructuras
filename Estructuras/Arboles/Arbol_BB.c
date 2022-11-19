/*  
    Implementacion de un arbol donde los valores menores a la raiz se alojan a la izquierda y los mayores a la derecha.
    Arbol Binario de Busqueda. 
*/
#include <stdio.h>
#include <stdlib.h>

struct arbol_bb
{
	int data;
	struct arbol_bb *left;
	struct arbol_bb *right;	
};

typedef struct arbol_bb Tree;

void menu();

Tree *create(int N);
int add(Tree **root, int N);
int pre_orden(Tree *root);
int in_orden(Tree *root);
int post_orden(Tree *root);
Tree *search(Tree *root, int N);
Tree **more_to_rigth(Tree **root);
int delete(Tree **root, int N);
int cant_nodes(Tree *root);
int max(int left, int right);
int height(Tree *root);

int main(int argc, char const *argv[])
{
	Tree *bs_tree = NULL;
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
				add(&bs_tree, number);
				printf("\n");
				break;

			case 2:
				printf("\nItems of the binary search tree:\n");
				pre_orden(bs_tree);
				printf("\n\n");
				break;	

			case 3:
				printf("\nItems of the binary search tree:\n");
				in_orden(bs_tree);
				printf("\n\n");
				break;
				
			case 4:
				printf("\nItems of the binary search tree:\n");
				post_orden(bs_tree);
				printf("\n\n");
				break;					
			
			case 5: 
				printf("Insert the number to search: ");
				scanf("%d", &number);
				
				Tree *item = search(bs_tree, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!! \n\n");
				break;
/*
			case 6:
				printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (deleteL(&list, number) == 1)
					printf("Deleted \n\n");
				else
					printf("No delete!!!\n\n");
				break;
*/

			case 7:
				printf("Roots cant: %d \n\n", cant_nodes(bs_tree));
				break;

			case 8:
				printf("Hight from binary search tree: %d \n\n", height(bs_tree));		
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
	printf("Select your option to choose from the binary search tree: \n\t");
	printf("[1]: Insert\n\t[2]: PreOrden\n\t[3]: InOrden\n\t[4]: PostOrden\n\t[5]: Search\n\t[6]: Delete\n\t[7]: Items\n\t[8]: Height\n\t[0]: Exit\n> ");
}

Tree *create(int N)
{
	Tree *new = (Tree *) malloc(sizeof(Tree));
	if(!new)
		return NULL;
	new->data = N;
	new->left = NULL;
	new->right = NULL;

	return new;
}

int add(Tree **root, int N)
{
	if(!*root)
	{
		*root = create(N);
		if(*root)
			return 1;
		return 0;
	}
		
	if((*root)->data > N)
		return add(&(*root)->left, N);
	return add(&(*root)->right, N);
}

int pre_orden(Tree *root)
{
	/*
	printf("%d -> ", root->data);
    if(root->left != NULL)
    	pre_orden(root->left);
    if(root->right != NULL)
    	pre_orden(root->right);
    */
	
	if(root)
	{
		printf("%d -> ", root->data);
		pre_orden(root->left);
		pre_orden(root->right);
	}
	return 0;
}

int in_orden(Tree *root)
{
	/*
	if(root->left != NULL)
		in_orden(root->left);
    printf("%d -> ", root->data);
    if(root->right != NULL)
       	in_orden(root->right);
	*/
	
	if(root)
	{
		in_orden(root->left);
		printf("%d -> ", root->data);
		in_orden(root->right);
	}
	return 0;
}

int post_orden(Tree *root)
{
	/*
    if(root->left != NULL)
    	post_orden(root->left);
    if(root->right != NULL)
    	post_orden(root->right);
    printf("%d -> ", root->data);
    */
	
	if(root)
	{
		post_orden(root->left);
		post_orden(root->right);
		printf("%d -> ", root->data);
	}
	
	return 0;
}

Tree *search(Tree *root, int N)
{
	if (!root)
		return NULL;
	if(N == root->data)
		return root;
	if (N < root->data)
		return search(root->left, N);
	return search(root->right, N);
}

Tree **more_to_rigth(Tree **root)
{
	if (!*root)
		return NULL;
	if (!(*root)->right)
		return root;
	return more_to_rigth(&(*root)->right);
}

int delete(Tree **root, int N)
{
	Tree *aux, **p;
	if(!*root)
		return 0;
	if((*root)->data > N)
		delete(&(*root)->left, N);
	if((*root)->data < N)
		delete(&(*root)->right, N);

	aux = *root;

	if(!aux->left)
		*root = aux->right;
	else
		if(!aux->right)
			*root = aux->left;
		else
			

	return 1;
}

int cant_nodes(Tree *root)
{
	if (!root)
		return 0;
	return 1 + cant_nodes(root->left) + cant_nodes(root->right);
}

int max(int left, int right)
{
	if(left > right)
		return left;
	return right;
}

int height(Tree *root)
{
	if(!root)
		return 0;
	if(!root->left && !root->right)
		return 1;
	return 1 + max(height(root->left), height(root->right));
}