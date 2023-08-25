#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct persona
{
    char folio[15];
    char nombre[30];
    char apellido[50];
    char fecha_nac[12];
    char descripcion[150];
    int edad;
    float peso;
    int estatura;
};

struct avl_tree
{
    struct persona *datas;
    struct avl_tree *left;
    struct avl_tree *right;
};

typedef struct persona Paciente;
typedef struct avl_tree Tree;

void menu();

Paciente *create_patient();

int is_empty(Tree *root);
Tree *create_root(Paciente *pac);
int add(Tree **root, Paciente *pac);
int in_orden(Tree *root);
Tree *search(Tree *root, char *id);
Tree **right_most(Tree **root);
int delete(Tree **root, char *id);

int max(int left, int right);
int height(Tree *root);
int cant_nodes(Tree *root);
int cant_leafs(Tree *root);
int balance_factor(Tree *root);

int parent_child(Tree *root, int N);

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



    return 0;
}



Paciente *create_patient()
{
    Paciente *info = (Paciente *) malloc(sizeof(Paciente));
    if (!info)
        return NULL;

    printf("Ingresa el folio: ");
    scanf("%s", info->folio);
    printf("Ingresa el nombre: ");
    scanf("%s", info->nombre); 
    printf("Ingresa el apellido: ");
    scanf("%s", info->apellido);
    printf("Ingresa la fecha de nacimiento (yyyy-MM-dd): ");
    scanf("%s", info->fecha_nac);
    printf("Ingresa el sexo: ");
    scanf("%s", info->fecha_nac); 
    printf("Describe los sintomas: ");
    scanf(" %150[^\n]", info->descripcion); 
    printf("Ingresa la edad: ");
    scanf("%i", &info->edad); 
    printf("Ingresa el peso: ");
    scanf("%f", &info->peso); 
    printf("Ingresa la estatura: ");
    scanf("%i", &info->estatura); 

    return info;
}


void menu()
{
    printf("Select your option to choose from the avl tree: \n\t");
	printf("[1]: Insert\n\t[2]: InOrden\n\t[3]: Search\n\t[4]: Delete\n\t[5]: Items\n\t[6]: More information\n\t[7]: Parent and Child\n\t[0]: Exit\n> ");
}


int is_empty(Tree *root)
{
    return (root == NULL) ? 1 : 0;
}


Tree *create_root(Paciente *pac)
{
    Tree *node = (Tree *) malloc(sizeof(Tree));
	if(is_empty(node))
		return NULL;

	node->datas = (Paciente *) malloc(sizeof(Paciente));
	if(!node->datas)
	{
        free(node);
        return 0;
    }
	node->datas = pac;
	node->left = NULL;
	node->right = NULL;

	return node;
}


int add(Tree **root, Paciente *pac)
{
    if (is_empty(*root))
    {
        *root = create_root(pac);
        if(!is_empty(*root))
            return 1;
        return 0;
    }
    
    if (strcmp((*root)->datas->folio, pac->folio) > 0)
        return add(&(*root)->left, pac);
    return add(&(*root)->right, pac);

    return 1;
}


int in_orden(Tree *root)
{
    if (!is_empty(root))
    {
        in_orden(root->left);
        printf("Folio: %s \n", root->datas->folio);
        printf("Nombre: %s \n", root->datas->nombre);
        printf("Apellido: %s \n", root->datas->apellido);
        printf("--------------------\n");
        in_orden(root->right);

    }
    return 0;
}


Tree *search(Tree *root, char *id)
{
    if (is_empty(root))
        return NULL;
    if (strcmp(root->datas->folio, id) == 0)
        return root;
    if (strcmp(root->datas->folio, id))
        return search(root->left, id);
    return search(root->right, id);
}


Tree **right_most(Tree **root)
{
    if (is_empty(*root))
        return NULL;
    if (is_empty((*root)->right))
        return root;
    return right_most(&(*root)->right);
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
    return max(height(root->left), height(root->right));
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
    return 1 + cant_leafs(root->left) + cant_leafs(root->right);
}


int balance_factor(Tree *root)
{
    if (is_empty(root))
        return 0;
    return height(root->right) - height(root->left);
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