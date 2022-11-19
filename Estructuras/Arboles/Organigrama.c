#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct persona
{
	int id;
	char nombre[20];
	char apellido[20];
	char puesto[20];
};

struct organigrama
{
	struct persona *dato;
	struct organigrama *hijos;
	struct organigrama *hermanos;
};

typedef struct persona Empleado;
typedef struct organigrama Arbol;

void menu();
Empleado *llenar_registro(Empleado **emp);

Arbol *crear_nodo(Empleado *emp);
int add(Arbol **raiz, Empleado *emp);
int add_children(Arbol **raiz, Empleado *emp);
int imprime(Arbol *raiz);
Arbol *dfs(Arbol *raiz, int codigo);
Arbol *bfs(Arbol *raiz, int codigo);
int cant_nodos(Arbol *raiz);
int cant_hijos(Arbol *raiz, int codigo);

int main(int argc, char const *argv[])
{
	Arbol *arbol_gral = NULL;
	Empleado *info = NULL;
	int option, codigo;

	do
	{
		menu();
		scanf("%d", &option);

		switch(option)
		{
			case 1:
				printf("Ingresa los datos del empleado: \n");
				add(&arbol_gral, llenar_registro(&info));
				printf("\n");
				break;

			case 2:
				printf("\nEmpleados registrados:\n");
				imprime(arbol_gral);
				printf("\n\n");
				break;					

			
			case 3: 
				printf("Ingresa el codigo del empleado a buscar: ");
				scanf("%d", &codigo);
				
				Arbol *item = bfs(arbol_gral, codigo);
				if (item)
					printf("Encontrado:\n\tNombre: %s\n\tApellido: %s\n\tPuesto: %s\n\n", item->dato->nombre, item->dato->apellido, item->dato->puesto);
				else
					printf("No Existe!!! \n\n");
				break;
				
/*
			case 4:
				printf("Ingresa el codigo del empleado a eliminar: ");
				scanf("%d", &codigo);
				if (deleteL(&list, codigo) == 1)
					printf("Deleted \n\n");
				else
					printf("No delete!!!\n\n");
				break;
*/
			case 5:
				printf("Numero de nodos: %d\n\n", cant_nodos(arbol_gral));
				break;
/*
			case 6:
				printf("Ingresa el codigo del empleado a buscar: ");
				scanf("%d", &codigo);
				printf("Numero de hijos: %d\n\n", cant_hijos(arbol_gral, codigo));
*/				break;	

			case 0:
				printf("\nAdios Baboso :P \n\n");
				return 0;
				break;	

			default:
				printf("\nPrueba otra vez!!! \n\n");
				break;	
		}
	}while(option != 0);

	return 0;
}

void menu()
{
	printf("Select your option to choose from the general tree: \n\t");
	printf("[1]: Insertar\n\t[2]: Recorrer\n\t[3]: Buscar\n\t[4]: Eliminar\n\t[5]: Cant. Nodos\n\t[6]: Cant. Hijos\n\t[0]: Salir\n> ");
}

Empleado *llenar_registro(Empleado **emp)
{
	*emp = (Empleado *) malloc(sizeof(Empleado));
	if(!emp)
		return NULL;
	printf("Ingresa el id: ");
	scanf("%d", &(*emp)->id);
	printf("Ingresa el nombre: ");
	scanf("%s", &(*emp)->nombre);
	printf("Ingresa el apellido: ");
	scanf("%s", &(*emp)->apellido);
	printf("Ingresa el puesto: ");
	scanf("%s", &(*emp)->puesto);

	return *emp;
}

Arbol *crear_nodo(Empleado *emp)
{
	Arbol *nuevo = (Arbol *) malloc(sizeof(Arbol));
	if(!nuevo)
		return NULL;
	nuevo->dato = (Empleado *) malloc(sizeof(Empleado));
	if(!nuevo->dato)
	{
		free(nuevo);
		return NULL;
	}
	nuevo->dato = emp;
	nuevo->hijos = NULL;
	nuevo->hermanos = NULL;

	return nuevo;
}

int add(Arbol **raiz, Empleado *emp)
{
	int codigo;
	if(!*raiz)
	{
		if(*raiz = crear_nodo(emp))
			return 1;
		return 0;	
	}
	printf("Ingrese el codigo del padre: ");
	scanf("%d", &codigo);
	Arbol *padre = dfs(*raiz, codigo);
	if (!padre)
	{
		printf("Error :( \n");
		return 1;
	}
	return add_children(&padre->hijos, emp);
}

int add_children(Arbol **raiz, Empleado *emp)
{
	if(!*raiz)
	{
		if(*raiz = crear_nodo(emp))
			return 1;
		return 0;	
	}
	return add_children(&(*raiz)->hermanos, emp);
}

int imprime(Arbol *raiz)
{
	if(!raiz)
		return 0;
	printf("%s -> ", raiz->dato->puesto);
	imprime(raiz->hermanos);
    printf("\n | \n V \n");
	imprime(raiz->hijos);

	return 1;
}

Arbol *dfs(Arbol *raiz, int codigo)
{
	if(!raiz)
		return NULL;
	if(codigo == raiz->dato->id)
		return raiz;
	Arbol *aux = dfs(raiz->hijos, codigo);
	if (!aux)
        aux = dfs(raiz->hermanos, codigo);
    return aux;	
}

Arbol *bfs(Arbol *raiz, int codigo)
{
	if(!raiz)
		return NULL;
	if(codigo == raiz->dato->id)
		return raiz;
	Arbol *aux = bfs(raiz->hermanos, codigo);
	if(!aux)	
		aux = bfs(raiz->hijos, codigo);
	return aux;	
}

int cant_nodos(Arbol *raiz)
{
	if(!raiz)
		return 0;
	return 1 + cant_nodos(raiz->hermanos) + cant_nodos(raiz->hijos);	
}

/*
int cant_hijos(Arbol *raiz, int codigo)
{
	if(!raiz->hijos)
		return 0;
	if(codigo == raiz->dato->id)
	{
		Arbol *aux = raiz->hermanos;
		if(!aux)	
			return 0;
		aux = raiz->hijos;
		return 1 + cant_hijos(aux->hermanos, codigo);	
	}	
}
*/