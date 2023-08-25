/*
    Implementacion de un arbol binario de busqueda (ABB / BST) con registros de pacientes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct persona
{
    char folio[15];
    char nombre[30];
    char apellido[50];
    char fecha_nac[12];
    char sexo[10];
    char descripcion[150];
    int edad;
    float peso;
    int estatura;
};

struct bs_tree
{
    struct persona *datas;
    struct bs_tree *left;
    struct bs_tree *right;
};

typedef struct persona Paciente;
typedef struct bs_tree Tree;

void menu();

Paciente *create_patient();

int is_empty(Tree *root);
Tree *create_root(Paciente *pac);
int add(Tree **root, Paciente *pac);
int in_orden(Tree *root);
Tree *search(Tree *root, char *id);
Tree **right_most(Tree **root);
int delete(Tree **root, char *id);


int main(int argc, char const *argv[])
{
    Tree *bs_tree = NULL;
    char id[15];
    int option;

	do
	{
		menu();
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Registre al paciente \n");
				if (add(&bs_tree, create_patient()))
                    printf("\nAgregado!!!\n\n");
				else
                    printf("\nError!!!\n\n");
				break;

			case 2:
				printf("\nPacientes:\n");
				in_orden(bs_tree);
				printf("\n\n");
				break;					
			
			case 3: 
				printf("Escriba la clave del paciente: \n");
				scanf("%s", id);
				
				Tree *item = search(bs_tree, id);
				if (item)
                {
					printf("\nNombre: %s \n", item->datas->nombre);
                    printf("Apellido: %s \n", item->datas->apellido);
                    printf("Fecha Nacimiento: %s \n", item->datas->fecha_nac);
                    printf("Sexo: %s \n", item->datas->sexo);
                    printf("Descripcion: %s \n", item->datas->descripcion);
                    printf("Edad: %i \n", item->datas->edad);
                    printf("Peso: %.2f \n", item->datas->peso);
                    printf("Estatura: %i \n\n", item->datas->estatura);
                }
				else
					printf("\nNo Existe!!! \n\n");
				break;

            case 4:
                printf("Ingrese la clave del paciente a eliminar\n");
                scanf("%s", id);
				if (delete(&bs_tree, id))
                    printf("\nEliminado!!!\n\n");
				else
                    printf("\nError!!!\n\n");
                break;
            
            case 0:
                printf("\nVuelva pronto :) !!!\n\n");
                return 0;
                break;

			default:
				printf("\nIntentalo de nuevo!!! \n\n");
				break;	
		}
	}
    while(option != 0);

    return 0;
}


void menu()
{
	printf("Select your option to choose from the binary search tree: \n\t");
	printf("[1]: Insert\n\t[2]: In-Orden\n\t[3]: Search\n\t[4]: Delete\n\t[0]: Exit\n> ");
}


Paciente *create_patient()
{
    Paciente *info = (Paciente *) malloc(sizeof(Paciente));
    if(!info)
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
    if(is_empty(*root))
    {
        *root = create_root(pac);
        if(!is_empty(*root))
            return 1;
        return 0;
    }
    
    if(strcmp(((*root)->datas->folio), (pac->folio)) > 0)
        return add(&(*root)->left, pac);
    return add(&(*root)->right, pac);
}


int in_orden(Tree *root)
{
    if(!is_empty(root))
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
    if(is_empty(root))
        return NULL;
    if(strcmp((root->datas->folio), id) == 0)
        return root;
    if(strcmp((root->datas->folio), id) > 0)
        return search(root->left, id);
    return search(root->right, id);
}


Tree **right_most(Tree **root)
{
    if(is_empty(*root))
        return 0;
    if(is_empty((*root)->right))
        return root;
    return right_most(&(*root)->right);
}


int delete(Tree **root, char *id) {
    if (is_empty(*root))
        return 0;

    if (strcmp((*root)->datas->folio, id) > 0) 
        return delete(&(*root)->left, id);
    if (strcmp((*root)->datas->folio, id) < 0)
        return delete(&(*root)->right, id);
    else {
        // Se encontró el nodo a eliminar
        if (is_empty((*root)->left) && is_empty((*root)->right)) 
        {
            // El nodo es una hoja, simplemente libera la memoria y establece la referencia en el padre a NULL
            free(*root);
            *root = NULL;
        } 
        else if (!is_empty((*root)->left) && !is_empty((*root)->right))
        {
            // El nodo tiene hijos en ambos lados
            Tree **rightmost = right_most(&(*root)->left);  // Encontrar el nodo más a la derecha en el subárbol izquierdo
            strcpy((*root)->datas->folio, (*rightmost)->datas->folio);  // Reemplazar el valor del nodo actual con el nodo más a la derecha
            return delete(rightmost, (*rightmost)->datas->folio);  // Eliminar el nodo más a la derecha recursivamente
        } 
        else 
        {
            // El nodo tiene solo un hijo
            Tree *child = (!is_empty((*root)->left)) ? (*root)->left : (*root)->right;
            free(*root);
            *root = child;
        }

        return 1;
    }
}