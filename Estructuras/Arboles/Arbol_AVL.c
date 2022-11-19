/*  
    Implementacion del balanceo en un arbol binario de busqueda.
    Arbol AVL.
*/
#include <stdio.h>
#include <stdlib.h>

struct arbol_avl
{
    int data;
    struct arbol_avl *left;
    struct arbol_avl *right;
};

typedef struct arbol_avl Tree;

void menu();

//  Funciones Basicas
Tree *create(int N);
int add(Tree **root, int N);
int in_orden(Tree *root);
Tree *search(Tree *root, int N);
Tree **more_to_right(Tree **root);
int delete(Tree **root, int N);
void father_child(Tree *root, int N);

//  Funciones para calcular valores
int max(int left, int right);
int height(Tree *root);
int cant_nodes(Tree *root);
int cant_leaf(Tree *root);
int balance_factor(Tree *root);

//  Funciones para el balanceo del arbol
int balance_tree(Tree **root);
void balance_left(Tree **root, Tree *node);
void balance_right(Tree **root, Tree *node);

int main(int argc, char const *argv[])
{
    Tree *avl_tree = NULL;
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
				add(&avl_tree, number);
				printf("\n");
				break;

			case 2:
                printf("\nItems of the avl tree:\n");
				in_orden(avl_tree);
				printf("\n\n");
				break;

			case 3:
				printf("Insert the number to search: ");
				scanf("%d", &number);
				
				Tree *item = search(avl_tree, number);
				if (item)
					printf("Founded: %d \n\n", item->data);
				else
					printf("No Exist!!! \n\n");
				break;
/*				
			case 4:
                printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (delete(&avl_tree, number) != 0)
					printf("Deleted \n\n");
				else
					printf("No delete!!!\n\n");
				break;					
*/			
			case 5:
                printf("Roots cant: %d \n\n", cant_nodes(avl_tree));
				break;

			case 6:
				printf("Leafs cant: %d \n\n", cant_leaf(avl_tree));
                break;

			case 7:
                printf("Height from avl tree: %d \n\n", height(avl_tree));
				break;

			case 8:
                printf("Insert the number to test: ");
                scanf("%d", &number);
                father_child(avl_tree, number);
				break;	

            case 9:
                printf("Balance factor from avl tree: %d \n\n", balance_factor(avl_tree));
				break;		

			case 0:
				printf("\nSee you later :D \n\n");
				return 0;
				break;	

			default:
				printf("\nTry Again!!! \n\n");
				break;	
		}
	}
    while(option != 0);

    return 0;
}

void menu()
{
	printf("Select your option to choose from the avl tree: \n\t");
	printf("[1]: Insert\n\t[2]: InOrden\n\t[3]: Search\n\t[4]: Delete\n\t[5]: Items\n\t[6]: Leafs\n\t[7]: Height\n\t[8]: Pather and Child\n\t[9]: Balance factor\n\t[0]: Exit\n> ");
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
    int value;
    if(!*root)
    {
        *root = create(N);
        if(*root)
            return 1;
        return 0;    
    }
    if((*root)->data > N)
        value = add(&(*root)->left, N);
    if((*root)->data < N)
        value = add(&(*root)->right, N); 
        
    balance_tree(root);
    return value;
}

int in_orden(Tree *root)
{
    if(root)
    {
        in_orden(root->left);
        printf("%d -> ", root->data);
        in_orden(root->right);   
    }
    return 0;
}

Tree *search(Tree *root, int N)
{
    if(!root)
        return NULL;
    if(N == root->data)
        return root;    
    if(N < root->data)
        return search(root->left, N);
    return search(root->right, N);        
}

Tree **more_to_right(Tree **root)
{
    if(!*root)
        return NULL;
    if(!(*root)->right)
        return root;
    return more_to_right(&(*root)->right);
}

int delete(Tree **root, int N)
{
    int value;
    Tree *aux, **p;
    if(!*root)
        return 0;
    if(N < (*root)->data)
        return delete(&(*root)->left, N);
    if(N > (*root)->data)
        return delete(&(*root)->right, N);  
    aux = *root;
    if(!aux->left)
        *root = aux->right;
    else
        if(!aux->right)
            *root = aux->left;  
        else
        {
            p = more_to_right(&aux->left);
            *root = *p;
            p = &((*p)->left);
            (*root)->left = aux->left;
            (*root)->right = aux->right;
        }
    free(aux);
//    balance_tree(root);
    return 1;
}

void father_child(Tree *root, int N)
{
    if(root->data == N) 
    {
        printf("Root: %d \n", root->data);
        return;
    }
    if(root->data > N)
    {
        if(!root->left) 
        {
            printf("\nItem not found\n");
            return;
        }
        if(root->left->data == N)
        {
            printf("Father: %d\nChild: %d \n", root->data, root->left->data);
            return;
        }
        else
            father_child(root->left, N);
    }
    if(root->data < N) 
    {
        if(!root->right)
        {
            printf("\nItem not found\n");
            return;
        }
        if(root->right->data == N) 
        {
            printf("Father: %d\nChild: %d \n", root->data, root->right->data);
            return;
        }
        else
            father_child(root->right, N);
    }
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

int cant_nodes(Tree *root)
{
    if(!root)
        return 0;
    return 1 + cant_nodes(root->left) + cant_nodes(root->right);        
}

int cant_leaf(Tree *root)
{
    if(!root)
        return 0;
    if(!root->left || !root->right)   
        return 1;
    return cant_leaf(root->left) + cant_leaf(root->right);     
}

int balance_factor(Tree *root)
{
    if(!root)
        return 0;
    return height(root->right) - height(root->left);    
}

void balance_left(Tree **root, Tree *node)
{
    if (node->right)
    {
        Tree *aux = node->right;
        node->right = aux->left;
        aux->left = node;
        (*root)->left = aux->right;
        aux->right = *root;
        *root = aux;
    }
    else
    {
        (*root)->left = node->right;
        node->right = *root;
        *root = node;
    }
}

void balance_right(Tree **root, Tree *node)
{
    if(node->left)
    {
        Tree *aux = node->left;
        node->left = aux->right;
        aux->right = node;
        (*root)->right = aux->left;
        aux->left = *root;
        *root = aux;
    }
    else
    {
        (*root)->right = node->left;
        node->left = *root;
        *root = node;
    }
}

int balance_tree(Tree **root)
{
    if(!*root)
        return 0;
    int factor = balance_factor(*root);
    if(factor < -1)
        balance_left(root, (*root)->left);
    else
        if(factor > 1)
            balance_right(root, (*root)->right);    
    return 1;           
}
