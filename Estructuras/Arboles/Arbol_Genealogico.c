#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct persona
{
    char nombre[20];
    char paterno[20];
    char materno[20];
};

struct arbol_genealogico
{
    struct persona *dato;
    struct arbol_genealogico *hijos;
    struct arbol_genealogico *hermanos;
};

typedef struct persona Familiar;
typedef struct arbol_genealogico Arbol;

void menu();
Familiar *llenar_registro();

Arbol *crear_nodo(Familiar *fam);
int add(Arbol **raiz, Familiar *fam);
int add_children(Arbol **raiz, Familiar *fam);
int imprime(Arbol *raiz); 
Arbol *dfs(Arbol *raiz, char *nom);

int main(int argc, char const *argv[])
{
    Arbol *arbol_gral = NULL;
    Familiar *familiar1 = llenar_registro();
    Familiar *familiar2 = llenar_registro();
    Familiar *familiar3 = llenar_registro();
    Familiar *familiar4 = llenar_registro();
    

    add(&arbol_gral, familiar1);
    add(&arbol_gral, familiar2);
    add(&arbol_gral, familiar3);
    add(&arbol_gral, familiar4);
    imprime(arbol_gral);


    return 0;
}

Familiar *llenar_registro()
{
    Familiar *fam = (Familiar *) malloc(sizeof(Familiar));
    if(!fam)
        return NULL;
    printf("Ingresa el nombre: ");
    scanf("%s", fam->nombre);
    printf("Ingresa el apellido paterno: ");
    scanf("%s", fam->paterno);
    printf("Ingresa el apellido materno: "); 
    scanf("%s", fam->materno); 

    return fam;  
}

Arbol *crear_nodo(Familiar *fam)
{
    Arbol *nuevo = (Arbol *) malloc(sizeof(Arbol));
    if(!nuevo)
        return NULL;
    nuevo->dato = (Familiar *) malloc(sizeof(Familiar));
    if(!nuevo->dato)
    {
        free(nuevo);
        return 0;
    }    
    nuevo->dato = fam;
    nuevo->hijos = NULL;
    nuevo->hermanos = NULL;

    return nuevo;
}

int add(Arbol **raiz, Familiar *fam)
{
    char nombre[20];
    if(!*raiz)
    {
        *raiz = crear_nodo(fam);
        if(*raiz)
            return 1;
        return 0;   
    }
    printf("Ingresa el nombre del familiar: ");
    scanf("%s", &nombre);
    Arbol *padre = dfs(*raiz, nombre);
    if(!padre)
    {
        printf("Error :( \n");
        return 1;
    }
    return add_children(&padre->hijos, fam);

}

int add_children(Arbol **raiz, Familiar *fam)
{
    if(!*raiz)
    {
        *raiz = crear_nodo(fam);
        if(*raiz)
            return 1;
        return 0;    
    }
    return add_children(&(*raiz)->hermanos, fam);
}

int imprime(Arbol *raiz)
{
    if(!raiz)
        return 0;
    printf("%s -> ", raiz->dato->nombre);
	imprime(raiz->hermanos);
    printf("\n | \n V \n");
	imprime(raiz->hijos);

    return 1;
}

Arbol *dfs(Arbol *raiz, char *nom)
{
    if(!raiz)
        return NULL;
    if(strcmp(raiz->dato->nombre, nom) == 0)    
        return raiz;
    Arbol *aux = dfs(raiz->hijos, nom);
    if(!aux)
        return dfs(raiz->hermanos, nom);   
    return aux;     
}

