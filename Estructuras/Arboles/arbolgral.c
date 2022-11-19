#include <stdio.h>
#include <stdlib.h>

struct arbol 
{
    int valor;
    struct arbol *hijos;
    struct arbol *hermanos;
};

typedef struct arbol arbol;

int insertar_dato(int hijo, arbol **raiz);
arbol *alojar_nodo(int dato);
arbol *dfs(arbol *raiz, int valor);
int print(arbol *raiz);

int main(int argc, char const *argv[])
{
    arbol *root = NULL;
    insertar_dato(7, &root);
    arbol *padre = NULL;
    char opt = 'x';
    int p, h;
    while(opt != 'e')
    {
        printf("Ingrese el valor del padre: ");
        scanf("%i", &p);
        padre = dfs(root, p);
        if (!padre)
        {
            printf("ERROR\n");
            break;
        }
        printf("Ingrese el valor de hijo: ");
        scanf("%i", &h);
        insertar_dato(h, &padre);
        printf("Si desea salir, presione e, si no presione cualquier tecla: ");
        scanf("%s", &opt);
    }
    print(root);
    return 0;
}

arbol *alojar_nodo(int dato)
{
    arbol *tmp = (arbol *) malloc(sizeof(arbol));
    if(!tmp)
    {
        return NULL;
    }
    tmp->valor = dato;
    tmp->hermanos = NULL;
    tmp->hijos = NULL;
    return tmp;
}

int insertar_dato(int hijo, arbol **raiz)
{
    if(!(*raiz))
    {
        if((*raiz = alojar_nodo(hijo)))
        {
            return 1;
        }
        return 0;
    }
    if(!(*raiz)->hijos)
    {
        return insertar_dato(hijo, &(*raiz)->hijos);
    }
    return insertar_dato(hijo, &(*raiz)->hijos->hermanos);
}

arbol *dfs(arbol *raiz, int valor) // DFS = Depth First Search == Busqueda Primero en Profundidad
{
    if (!raiz)
        return NULL;
    if (raiz->valor == valor)
        return raiz;
    arbol *temp = dfs(raiz->hijos, valor);
    if (!temp)
        temp = dfs(raiz->hermanos, valor);
    return temp;
}

int print(arbol *raiz)
{
    if (!raiz)
        return 0;
    printf("%i ->", raiz->valor);
    print(raiz->hermanos);
    printf("\nV\n");
    print(raiz->hijos);
    return 1;
}