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

//  Funciones Basicass
Tree *create(int N);
int add(Tree **root, int N);
int in_orden(Tree *root);
Tree *search(Tree *root, int N);
void father_child(Tree *root, int N);

//  Funciones para calcular valores
int max(int left, int right);
int height(Tree *root);
int cant_nodes(Tree *root);
int cant_leaf(Tree *root);
int balance_factor(Tree *root);

//  Funciones para el balanceo del arbol
int rotate_left(Tree **root);
int rotate_right(Tree **root);
int rotate_left_right(Tree **root);
int rotate_right_left(Tree **root);
int balance_tree(Tree **root);

int main(int argc, char const *argv[])
{
    Tree *avl_tree = NULL;

    add(&avl_tree, 10);
//    add(&avl_tree, 5);
//    add(&avl_tree, 33);
    add(&avl_tree, 20);
    add(&avl_tree, 19);
//    add(&avl_tree, 21);
//    add(&avl_tree, 22);

    in_orden(avl_tree);
    printf("\n\n");
//    father_child(avl_tree, 42);
    
    printf("Altura Arbol: %d \n", height(avl_tree));
    printf("Altura Izquierda: %d \n", height(avl_tree->left));
    printf("Altura Derecha: %d \n", height(avl_tree->right));
    printf("Factor de Equilibrio: %d \n", balance_factor(avl_tree));
    printf("Cantidad Nodos: %d \n", cant_nodes(avl_tree));
    printf("Cantidad Hojas: %d \n", cant_leaf(avl_tree));

//    rotate_left(&avl_tree);
//    rotate_right(&avl_tree);
//    rotate_left_right(&avl_tree);
//    rotate_right_left(&avl_tree);
    balance_tree(&avl_tree);
    printf("\n");
    

//    BREAKPOINT DE REFERENCIA JEJE
    in_orden(avl_tree);
    printf("\n\n");
//    father_child(avl_tree, 42);

    printf("Altura Arbol: %d \n", height(avl_tree));
    printf("Altura Izquierda: %d \n", height(avl_tree->left));
    printf("Altura Derecha: %d \n", height(avl_tree->right));
    printf("Factor de Equilibrio: %d \n", balance_factor(avl_tree));
    printf("Cantidad Nodos: %d \n", cant_nodes(avl_tree));
    printf("Cantidad Hojas: %d \n", cant_leaf(avl_tree));

    return 0;
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

int rotate_left(Tree **root)
{
    if(!*root)
        return 0;
    if(balance_factor((*root)) < 0)
        return rotate_left_right(root);    
    Tree *aux = (*root)->right;
    (*root)->right = aux->left;
    aux->left = *root;
    *root = aux;

    return 1;
}

int rotate_right(Tree **root)
{
    if(!*root)
        return 0;
    if(balance_factor((*root)) > 0)
        return rotate_right_left(root);
    Tree *aux = (*root)->left;
	(*root)->left = aux->right;
	aux->right = *root;
	*root = aux;
    return 1;
}

int rotate_left_right(Tree **root)
{
    Tree *aux1, *aux2;
    if(!*root)
		return 0;
	aux1 = (*root)->left;
	aux2 = aux1->right;
	aux1->right = aux2->left;
	(*root)->left = aux2->right;
    aux2->left = aux1;
//    (*root)->left = aux1->right;    // Aun no se donde exactamente apuntar este
	aux2->right = *root;
	*root = aux2;

	return 1;
}

int rotate_right_left(Tree **root)
{
    Tree *aux1, *aux2;
    if(!*root)
        return 0;
    aux1 = (*root)->right;
    aux2 = aux1->left;
    aux1->left = aux2->right,
    (*root)->right = aux2->left;
    aux2->right = aux1;
    aux2->left = *root;
    *root = aux2;

    return 1;
}


//  Aun no se acaba la cosa
int balance_tree(Tree **root)
{
    if(!*root)
        return 0;
    int factor = balance_factor(*root);
    if(factor < -1)
        balance_tree(&(*root)->left); 
    if(factor > 1)
        balance_tree(&(*root)->right);   
    if(factor < 0)
        return rotate_right(root); 
    if(factor > 0)
        return rotate_left(root);    
    return 1;                
}
