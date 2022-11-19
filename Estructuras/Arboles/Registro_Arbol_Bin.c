// Estructura de empleados en un Arbol Binario.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona
{
	int id;
	char nombre[20];
	char apellido[20];
	char puesto[20];
};

struct Arbol_Bin
{
	struct Persona *datos;
	struct Arbol_Bin *izquierda;
	struct Arbol_Bin *derecha;
};

typedef struct Persona Empleado;
typedef struct Arbol_Bin Arbol;

Empleado *llenar_registro();

void menu();
Arbol *crear_raiz(Empleado *esclavo);
int insertar(Arbol **raiz, Empleado *esclavo);
int pre_orden(Arbol *raiz);
int in_orden(Arbol *raiz);
int post_orden(Arbol *raiz);
Arbol *buscar(Arbol *raiz, int codigo);
Arbol **mas_a_la_derecha(Arbol **raiz);
int eliminar(Arbol **raiz, int codigo);
int cantidad(Arbol *raiz);
int max(int izquierda, int derecha);
int altura(Arbol *raiz);

int main(int argc, char const *argv[])
{
	Arbol *arbol_bin = NULL;

	insertar(&arbol_bin, llenar_registro());
	insertar(&arbol_bin, llenar_registro());
	insertar(&arbol_bin, llenar_registro());
	pre_orden(arbol_bin);
	printf("\n");
	in_orden(arbol_bin);
	printf("\n");
	post_orden(arbol_bin);

	Arbol *elem = buscar(arbol_bin, 10);
	if (elem)
		printf("\nEncontrado: %s \n", elem->datos->nombre);
	else
		printf("\nNo existe \n");
	

	return 0;
}

void menu()
{
	
}

Empleado *llenar_registro()
{
	Empleado *info = (Empleado *) malloc(sizeof(Empleado));
	if(!info)
		return NULL;
	printf("Ingresa el codigo: ");
	scanf("%d", &info->id);
	printf("Ingresa el nombre: ");
	scanf("%s", info->nombre);
	printf("Ingresa el apellido: ");
	scanf("%s", info->apellido);
	printf("Ingresa el puesto: ");
	scanf("%s", info->puesto);

	return info;
}

Arbol *crear_raiz(Empleado *esclavo)
{
	Arbol *nuevo = (Arbol *) malloc(sizeof(Arbol));
	if(!nuevo)
		return NULL;

	nuevo->datos = (Empleado *) malloc(sizeof(Empleado));
	if(!nuevo->datos)
	{
        free(nuevo);
        return 0;
    }
	nuevo->datos = esclavo;
	nuevo->izquierda = NULL;
	nuevo->derecha = NULL;

	return nuevo;
}

int insertar(Arbol **raiz, Empleado *esclavo)
{
	if(!*raiz)
	{
		*raiz = crear_raiz(esclavo);
		if(*raiz)
			return 1;
		return 0;
	}
		
	if((*raiz)->datos->id > esclavo->id)
		return insertar(&(*raiz)->izquierda, esclavo);
	return insertar(&(*raiz)->derecha, esclavo);
}

int pre_orden(Arbol *raiz)
{
	if(raiz)
	{
		printf("Nombre: %s \n", raiz->datos->nombre);
		pre_orden(raiz->izquierda);	
		pre_orden(raiz->derecha);
	}
	return 0;
}

int in_orden(Arbol *raiz)
{
	if(raiz)
	{
		in_orden(raiz->izquierda);
		printf("Nombre: %s \n", raiz->datos->nombre);	
		in_orden(raiz->derecha);
	}
	return 0;
}

int post_orden(Arbol *raiz)
{
	if(raiz)
	{
		post_orden(raiz->izquierda);	
		post_orden(raiz->derecha);
		printf("Nombre: %s \n", raiz->datos->nombre);
	}
	return 0;
}

Arbol *buscar(Arbol *raiz, int codigo)
{
	if(!raiz)
		return NULL;
	if(raiz->datos->id == codigo)
		return raiz;
	if(raiz->datos->id > codigo)
		return buscar(raiz->izquierda, codigo);
	return buscar(raiz->derecha, codigo);		
}

Arbol **mas_a_la_derecha(Arbol **raiz)
{
	if(!*raiz)
		return NULL;
	if(!(*raiz)->derecha)
		return raiz;
	return mas_a_la_derecha(&(*raiz)->derecha);		
}

int cantidad(Arbol *raiz)
{
	if(!raiz)
		return 0;
	return 1 + cantidad(raiz->izquierda) + cantidad(raiz->derecha);	
}

int max(int derecha, int izquierda)
{
	if(izquierda > derecha)
		return izquierda;
	return derecha;	
}

int altura(Arbol *raiz)
{
	if(!raiz)
		return 0;
	return 1 + max(altura(raiz->izquierda), altura(raiz->derecha));	
}