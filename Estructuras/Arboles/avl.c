#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct avl_tree
{
    int data;
    struct avl_tree *left;
    struct avl_tree *right;
};

typedef struct avl_tree Tree;

void menu();

int is_empty(Tree *root);
int add(Tree **root, int N);
int in_orden(Tree *root);
Tree *search(Tree *root, int N);
Tree **right_most(Tree **root);
int delete(Tree **root, int N);

int max(int left, int right);
int height(Tree *root);
int cant_nodes(Tree *root);
int cant_leafs(Tree *root);
int balance_factor(Tree *root);

Tree *get_parent(Tree *root, int N);

int srl(Tree **root);
int crl(Tree **root);
int srr(Tree **root);
int crr(Tree **root);
int balance_left(Tree **root, Tree *branch);
int balance_right(Tree **root, Tree *branch);
int balance_tree(Tree **root);

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
				if (add(&avl_tree, number))
                    printf("Added!!! \n\n");
                else
                    printf("Error!!! \n\n");
				printf("\n");
                system("clear || cls");
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
				
			case 4:
                printf("Insert the number to delete: ");
				scanf("%d", &number);
				if (delete(&avl_tree, number))
					printf("Deleted!!! \n\n");
				else
					printf("Error!!!\n\n");
				break;					

			case 5:
                printf("About AVL Tree . . . \n");
                printf("Nodes: %d \n", cant_nodes(avl_tree));
                printf("Leafs: %d \n", cant_leafs(avl_tree));
                printf("Height: %d \n", height(avl_tree));
                printf("Balance Factor: %d \n\n", balance_factor(avl_tree));
				break;

			case 6:
                printf("Insert the number to test: ");
                scanf("%d", &number);
                Tree *parent = get_parent(avl_tree, number);
                if (parent == NULL)
                    printf("Root: %d \n\n", avl_tree->data);
                else
                {
                    printf("Parent: %d \n", parent->data);
                    printf("Child: %d \n\n", number);
                }
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
	printf("[1]: Insert\n\t[2]: InOrden\n\t[3]: Search\n\t[4]: Delete\n\t[5]: Information\n\t[6]: Parent - Child\n\t[0]: Exit\n> ");
}


int is_empty(Tree *root)
{
    return (root == NULL) ? 1 : 0;
}


Tree *create_root(int N)
{
    Tree *node = (Tree *) malloc(sizeof(Tree));
	if(is_empty(node))
		return NULL;
	node->data = N;
	node->left = NULL;
	node->right = NULL;

	return node;
}


int add(Tree **root, int N)
{
    int value;
    if (is_empty(*root))
    {
        *root = create_root(N);
        if(!is_empty(*root))
            return 1;
        return 0;
    }
    
    if ((*root)->data > N)
        value = add(&(*root)->left, N);
    if ((*root)->data < N)
        value = add(&(*root)->right, N);

    balance_tree(root);
    return value;
}


int in_orden(Tree *root)
{
    if (!is_empty(root))
    {
        in_orden(root->left);
        printf("%i \n", root->data);
        in_orden(root->right);

    }
    return 0;
}


Tree *search(Tree *root, int N)
{
    if (is_empty(root))
        return NULL;
    if (root->data == N)
        return root;
    if (root->data > N)
        return search(root->left, N);
    return search(root->right, N);
}


Tree **right_most(Tree **root)
{
    if (is_empty(*root))
        return NULL;
    if (is_empty((*root)->right))
        return root;
    return right_most(&(*root)->right);
}


int delete(Tree **root, int N)
{
    if (is_empty(*root))
        return 0; // No se encontró el elemento a eliminar
    if (N < (*root)->data)
        return delete(&(*root)->left, N);
    if (N > (*root)->data)
        return delete(&(*root)->right, N);

    // Si encontramos el nodo a eliminar
    if (is_empty((*root)->left))
    {
        Tree *temp = (*root)->right;
        free(*root);
        *root = temp;
    }
    else if (is_empty((*root)->right))
    {
        Tree *temp = (*root)->left;
        free(*root);
        *root = temp;
    }
    else
    {
        // Si el nodo tiene dos hijos, buscamos el sucesor inmediato
        Tree **successor = right_most(&(*root)->left);
        (*root)->data = (*successor)->data;
        delete(successor, (*successor)->data);
    }
    balance_tree(root);
    return 1;
}


int max(int left, int right)
{
    return (left > right) ? left : right;
}


int height(Tree *root)
{
    if (is_empty(root))
        return 0;
    if (is_empty(root->left) && is_empty(root->right))
        return 1;
    return 1 + max(height(root->left), height(root->right));
}


int cant_nodes(Tree *root)
{
    if (is_empty(root))
        return 0;
    return 1 + cant_nodes(root->left) + cant_nodes(root->right);
}


int cant_leafs(Tree *root)
{
    if (is_empty(root))
        return 0;
    if (is_empty(root->left) || is_empty(root->right))
        return 1;
    return cant_leafs(root->left) + cant_leafs(root->right);
}


int balance_factor(Tree *root)
{
    if (is_empty(root))
        return 0;
    return height(root->right) - height(root->left);
}


Tree *get_parent(Tree *root, int N)
{
    if (is_empty(root))
        return NULL; // No se encontró el elemento a eliminar
    if ((root->left && root->left->data == N) || (root->right && root->right->data == N))
        return root;
    if (N < root->data)
        return get_parent(root->left, N);
    else
        return get_parent(root->right, N);
}


int srl(Tree **root)
{
    if (is_empty(*root))
        return 0;
    Tree *aux = (*root)->right;
    (*root)->right = aux->left;
    aux->left = *root;
    *root = aux;

    return 1;
}


int crl(Tree **root)
{
    if (is_empty(*root))
        return 0;
    Tree *aux1 = (*root)->right;
    Tree *aux2 = aux1->left;
    aux1->left = aux2->right;
    aux2->right = aux1;
    (*root)->right = aux1->left;
    aux2->left = *root;
    *root = aux2;

    return 1;
}


int srr(Tree **root)
{
    if (is_empty(*root))
        return 0;
    Tree *aux = (*root)->left;
	(*root)->left = aux->right;
	aux->right = *root;
	*root = aux;

    return 1;
}


int crr(Tree **root)
{
    if (is_empty(*root))
        return 0;
    Tree *aux1 = (*root)->left;
    Tree *aux2 = aux1->right;
    aux1->right = aux2->left;
    aux2->left = aux1;
    (*root)->left = aux1->right;
    aux2->right = *root;
    *root = aux2;

    return 1;
}


int balance_left(Tree **root, Tree *branch)
{
    if (is_empty(*root))
        return 0;
    if (is_empty(branch->right))
        srr(root);
    else
        crr(root);
    return 1;
}


int balance_right(Tree **root, Tree *branch)
{
    if (is_empty(*root))
        return 0;

    if (is_empty(branch->left))
        srl(root);
    else
        crl(root);
    return 1;
}


int balance_tree(Tree **root)
{
    if (is_empty(*root))
        return 0;
    int result = balance_factor(*root);
    if(result < -1)
        return balance_left(root, (*root)->left);
    if(result > 1)
        return balance_right(root, (*root)->right);
    return 1;
}