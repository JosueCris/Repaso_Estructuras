#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro
{
	char matricula[10];
	char nombre[15];
	char apellido[20];
	float promedio;
}estudiante;

void menu();
int insertar(FILE **file, estudiante datos);
int leer(FILE **file, estudiante datos);
void imprime(estudiante datos);
int consultar(FILE **file, estudiante datos, char *clave);
int actualizar(FILE **file, estudiante datos, char *clave);
int eliminar(FILE **file, estudiante datos, char *clave);


int main(int argc, char const *argv[])
{
	FILE *ptr, *ptr2;
	estudiante info;
	char id[10];
	int opcion;

	do
	{
		menu();
		scanf("%d", &opcion);
		switch(opcion)
		{
			case 1:
				insertar(&ptr, info);
				break;

			case 2:
				leer(&ptr, info);
				break;

			case 3:
				printf("Ingresa la matricula del estudiante: \n> ");
				scanf("%s", &id);
				consultar(&ptr2, info, id);
				break;

			case 0:
				printf("Gracias!!!");
				return 0;	
			default:
				printf("Opcion Invalida :/ \n");	
		}

	}while(opcion != 0);

	return 0;	
}

void menu()
{
	printf("Selecciona una de las opciones: \n");
	printf("\t[1]: Insertar\n\t[2]: Mostrar\n\t[3]: Consultar \n\t[4]: Actualizar\n\t[5]: Eliminar\n\t[0]: Salir\n> ");
}

int insertar(FILE **file, estudiante datos)
{
	if (!(*file = fopen("Archivo.dat", "ab")))
	{
		printf("Error al abrir el archivo!!!\n");
		return 0;
	}
	printf("Ingresa matricula: ");
	scanf("%s", &datos.matricula);
	printf("Ingresa nombre: ");
	scanf("%s", &datos.nombre);
	printf("Ingresa apellido: ");
	scanf("%s", &datos.apellido);
	printf("Ingresa promedio: ");
	scanf("%f", &datos.promedio);
	fwrite(&datos, sizeof(estudiante), 1, *file);
	
	fflush(*file);
	fclose(*file);

	return 1;
}

int leer(FILE **file, estudiante datos)
{
	if (!(*file = fopen("Archivo.dat", "rb")))
	{
		printf("Error al abrir el archivo!!!\n");
		return 0;
	}

	while(fread(&datos, sizeof(estudiante), 1, *file))
		imprime(datos);
	fclose(*file);

	return 1;
}

void imprime(estudiante datos)
{
	printf("Matricula: %s \n", datos.matricula);
	printf("Nombre: %s \n", datos.nombre);
	printf("Apellido: %s \n", datos.apellido);
	printf("Promedio: %.1f \n", datos.promedio);
	printf("-----------------------\n");
}

int consultar(FILE **file, estudiante datos, char *clave)
{
    int existe = 0;
	if (!(*file = fopen("Archivo.dat", "rb")))
	{
		printf("Error al abrir el archivo!!!\n");
		return 0;
	}

	fread(&datos, sizeof(estudiante), 1, *file);
    while(!feof(*file))
    {
        if (strcmp(clave, datos.matricula) == 0)
        {
           imprime(datos);
           existe = 1;
           break;
        }
		fread(&datos, sizeof(estudiante), 1, *file);
    }
    if (existe == 0)
        printf("No existe ese registro :( \n");
    fclose(*file);
}

int actualizar(FILE **file, estudiante datos, char *clave)
{
    int existe = 0;
	if (!(*file = fopen("Archivo.dat", "rb")))
	{
		printf("Error al abrir el archivo!!!\n");
		return 0;
	}

    fread(&datos, sizeof(estudiante), 1, *file);
    while(!feof(*file))
    {
        if (strcmp(clave, datos.matricula) == 0)
        {
			printf("Ingresa promedio: ");
			scanf("%f", &datos.promedio);
           	int pos = ftell(*file)-sizeof(estudiante);
           	fseek(*file, pos, SEEK_SET);
           	fwrite(&datos, sizeof(estudiante), 1, *file);
           	printf("Se modifico el promedio.\n");
           	existe = 1;
           	break;
        }
        fread(&datos, sizeof(estudiante), 1, *file);
    }
    if (existe == 0)
        printf("No existe ese registro\n");
    fclose(*file);
}

int eliminar(FILE **file, estudiante datos, char *clave)
{
    int existe = 0;
	if (!(*file = fopen("Archivo.dat", "rb")))
	{
		printf("Error al abrir el archivo!!!\n");
		return 0;
	}

    FILE *aux;
    if (!(aux = fopen("Temporal.dat", "ab")))
	{
		printf("Error al abrir el archivo!!!\n");
		return 0;
	}

    fread(&datos, sizeof(estudiante), 1, *file);
    while(!feof(*file))
    {
        if (strcmp(clave, datos.matricula) == 0)
        {
           printf("Registro eliminado \n");
           existe = 1;
        }else
            fwrite(&datos, sizeof(estudiante), 1, aux);
        fread(&datos, sizeof(estudiante), 1, *file);
    }
    if (existe == 0)
        printf("No existe este registro \n");
    fclose(aux);
    fclose(*file);
    
    remove("Archivo.dat");
    rename("Nuevo.dat", "Archivo.dat");
}