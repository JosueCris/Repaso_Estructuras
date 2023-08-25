//  Llenar un arreglo de 3 alumnos, el registro debe contener y en una funcion devolver el alumno con mayor promedio.
#include <stdio.h>

struct registro {
    char nombre[10];
    char apellido[10];
    float promedio;
};

typedef struct registro alumno;

void llenado(alumno datos[], int len);
void impresion(alumno datos[], int len);

int main(int argc, char const *argv[])
{
    alumno alum[3];
    // for(int i=0; i<3; i++){
    //     printf("<<< [%i] >>> \n", i+1);
    //     printf("Ingresa el nombre: ");
    //     scanf("%s", alum[i].nombre);
    //     printf("Ingresa el apellido: ");
    //     scanf("%s", alum[i].apellido);
    //     printf("Ingresa el promedio: ");
    //     scanf("%f", &alum[i].promedio);
    // }
    llenado(alum, 3);
    printf("\n");
    impresion(alum, 3);
    // for(int i=0; i<3; i++)
    // {
    //     printf("<<< Alumno [%i] >>> \n", i+1);
    //     printf("Nombre: %s \n", alum[i].nombre);
    //     printf("Apellido: %s \n", alum[i].apellido);
    //     printf("Promedio: %.1f \n", alum[i].promedio);
    //     printf("--------------------\n");
    // }
    return 0;
}

void llenado(alumno datos[], int len)
{
    for(int i=0; i<len; i++){
        printf("<<< [%i] >>> \n", i+1);
        printf("Ingresa el nombre: ");
        scanf("%s", datos[i].nombre);
        printf("Ingresa el apellido: ");
        scanf("%s", datos[i].apellido);
        printf("Ingresa el promedio: ");
        scanf("%f", &datos[i].promedio);
    }
}

void impresion(alumno datos[], int len)
{
    for(int i=0; i<len; i++)
    {
        printf("<<< Alumno [%i] >>> \n", i+1);
        printf("Nombre: %s \n", datos[i].nombre);
        printf("Apellido: %s \n", datos[i].apellido);
        printf("Promedio: %.1f \n", datos[i].promedio);
        printf("--------------------\n");
    }
}
