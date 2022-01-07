/*Una tienda de muebles necesita guardar todo su inventario con las características de sus bienes así como el precio
de compra y de venta y la cantidad con que cuentan de cada equipo en almacén.

Cada vez que un vendedor realiza una venta de un bien, esta venta se registra, permitiendo hacer la consultas de:
- Las ventas totales.
- El margen de ganancia por las ventas.
- El ranking del vendedor con mas ventas.

Realizar un programa en C con el que se pueda llevar esto a cabo.
El programa debe hacer uso de archivos en formato binario uno para vendedores y uno para ventas.
Adjuntar el(los) archivos de código fuente.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct muebles
{
	int idmueble;
	char nombre[15];
	float pcompra;
	float pventa;
	int cantalmacen;
}muebles;

typedef struct vendedor
{
	int idvendedor;
	char nombre[15];
	char apellido[30];
	int ventasdia;
}vendedor;

typedef struct ventas_muebles
{
	int idventa;
	char nombreproducto[15];
	int vendido;
	float pventamuebles;
	float pago;
	float cambio;
	char nombrevendedor[15];
}ventas_muebles;

int registrar_muebles(FILE **fp1); // Ingreso datos del mueble
int consultar_muebles(FILE **fp1); // Imprimo datos de los muebles
int registrar_empleados(FILE **fp2); // Ingreso datos del empleado
int consultar_empleados(FILE **fp2); // Imprimo datos de los empleados
int hacer_compra(FILE **fp1, FILE **fp2, FILE **fp3);
int consultar_ventas(FILE **fp3);

//int consulta_ganancias();

int main(int argc, char const *argv[])
{
	int i, seleccion, op1, op2, numMuebles, numEmpleados ,numCompra;
	FILE *p1, *p2, *p3;
	
	do{
		printf("Buen dia estimado(a) usuario\nPor favor seleccione la opcion que desea realizar:\n--------------------------------------------------\n");
	
	printf("Que desea hacer ahora:\n\t[1]: Registrar Muebles\n\t[2]: Mostrar Muebles\n\t[3]: Registrar Empleados\n\t[4]: Mostrar Empleados\n\t[5]: Realizar Compra\n\t[6]: Mostrar Compras\n\t[7]: Salir\n\n[]: > ");
	scanf("%d", &op1);
	printf("\n");
	switch(op1){
		case 1:
		registrar_muebles(&p1);
		break;

		case 2:
		consultar_muebles(&p1);
		break;

		case 3:
		registrar_empleados(&p2);
		break;

		case 4:
		consultar_empleados(&p2);
		break;

		case 5:
		hacer_compra(&p1, &p2, &p3);
		break;

		case 6:
		break;

		case 7:
		printf("Gracias vuelva pronto :v \n\n");
		return 0;

		default:
		printf("Vuelve a Intentarlo \n\n");
		break;
	}
} while(op1!=1 || op1!=2 || op1!=3 || op1!=4 || op1!=5 || op1!=6|| op1!=7);
	

	return 0;
}

int registrar_muebles(FILE **fp1)
{
	int i;
	muebles info;
	if(!(*fp1=fopen("Almacen.bin", "ab"))){
		printf("Error al abrir o crear el archivo");
		return 0;
	}
	printf("Ingresa los datos de tus muebles: \n");
	printf("\nID Mueble: ");
	scanf("%d", &info.idmueble);
	printf("Nombre: ");
	scanf("%s", info.nombre);
	printf("Precio Compra: $");
	scanf("%f", &info.pcompra);
	printf("Precio Venta: $");
	scanf("%f", &info.pventa);
	printf("Cantidad Disponible: ");
	scanf("%d", &info.cantalmacen);

	fwrite(&info, sizeof(struct muebles), 1, *fp1);
	if(fwrite != 0){
		printf("Datos guardados correctamente!\n");
	}else{
		printf("Error al guardar datos\n");
	}

	system("cls");

	fclose(*fp1);
	return 0;
}

int registrar_empleados(FILE **fp2)
{
	int i;
	vendedor persona;
	if(!(*fp2=fopen("Empleados.bin", "ab"))){
		printf("Error al abrir o crear el archivo");
		return 0;
	}
	printf("Inserta datos del empleado \n");
	printf("\nID: ");
	scanf("%d", &persona.idvendedor);
	printf("Nombre: ");
	scanf(" %[^\n]", persona.nombre);
	printf("Apellidos: ");
	scanf(" %[^\n]", persona.apellido);
	printf("Ventas de Hoy: %d \n", persona.ventasdia=0);
	
	fwrite(&persona, sizeof(struct vendedor), 1, *fp2);
	if(fwrite != 0){
		printf("Datos guardados correctamente!\n");
	}else{
		printf("Error al guardar datos\n");
	}
	system("cls");

	fclose(*fp2);
	return 0;
}

int hacer_compra(FILE **fp1, FILE **fp2, FILE **fp3)
{
	int i, ganancia=0;
	muebles info;
	vendedor persona;
	ventas_muebles vender;
	if(!(*fp3=fopen("Ventas.bin", "ab"))){
		printf("Error al abrir o crear el archivo");
		return 0;
	}
	printf("ID Venta: ");
	scanf("%d", &vender.idventa);
	printf("Nombre Producto: ");
	scanf("%s", vender.nombreproducto);
	printf("Cantidad a Comprar: ");
	scanf("%d", &vender.vendido);
	printf("Costo: $");
	scanf("%f", &vender.pventamuebles);
	printf("Pago: $");
	scanf("%f", &vender.pago);
	printf("Cambio: $%.2f \n", ((vender.pago-(vender.vendido*vender.pventamuebles))));
	printf("Vendedor: ");
	scanf(" %[^\n]", vender.nombrevendedor);

	fwrite(&vender, sizeof(struct ventas_muebles), 1, *fp3);
	if(fwrite != 0){
		printf("Datos guardados correctamente!\n");
	}else{
		printf("Error al guardar datos\n");
	}
	
	if(!(*fp1=fopen("Almacen.bin", "ab+"))){
		printf("Error al abrir o crear el archivo");
		return 0;
	}
	rewind(*fp1);
	while(fread(&info, sizeof(struct muebles), 1, *fp1)){
		
		printf("\nID Mueble: %d \n", info.idmueble);
		printf("Nombre: %s \n", info.nombre);
		printf("Precio Compra: $%.2f \n", info.pcompra);
		printf("Precio Venta: $%.2f \n", info.pventa);
		printf("Cantidad Disponible: %d \n", (info.cantalmacen-vender.vendido));
		printf("----------------------------------------\n");
	}

	if(!(*fp2=fopen("Empleados.bin", "ab+"))){
		printf("Error al abrir o crear el archivo");
		return 0;
	}
	rewind(*fp2);
	while(fread(&persona, sizeof(struct vendedor), 1, *fp2)){
		
		printf("ID: %d \n", persona.idvendedor);
		printf("Nombre: %s \n", persona.nombre);
		printf("Apellidos: %s \n", persona.apellido);
		printf("Ventas de Hoy: %d \n", (persona.ventasdia+vender.vendido));
		printf("----------------------------------------\n");
	}
	printf("Ganancias: $%.2f \n\n", ((info.pventa-info.pcompra)*(vender.vendido)));

	fclose(*fp2);
	fclose(*fp1);
	fclose(*fp3);

	return 0;
}

int consultar_muebles(FILE **fp1)
{
	int i;
	muebles info;
    if(!(*fp1=fopen("Almacen.bin", "rb+"))){
    	printf("\nNo hay muebles en el almacen \n\n");
      	return 0;
    }
    printf("\nMuebles Registrados\n");
    while(fread(&info, sizeof(struct muebles), 1, *fp1)){
    	printf("\nID Mueble: %d \n", info.idmueble);
		printf("Nombre: %s \n", info.nombre);
		printf("Precio Compra: $%.2f \n", info.pcompra);
		printf("Precio Venta: $%.2f \n", info.pventa);
		printf("Cantidad Disponible: %d \n", info.cantalmacen);
		printf("----------------------------------------\n");

    }
    fclose (*fp1);
	
	return 0;
}

int consultar_empleados(FILE **fp2)
{
	int i, codigoEmp;
	vendedor persona;
    if(!(*fp2=fopen("Empleados.bin", "rb"))){
    	printf("\nNo hay empleados registrados \n\n");
      	return 0;
    }

    printf("Ingresa el codigo del empleado a consultar: \n");
    scanf("%d", &codigoEmp);
    
    	while(fread(&persona, sizeof(struct vendedor), 1, *fp2)){
    		if(codigoEmp == persona.idvendedor){
    			printf("ID: %d \n", persona.idvendedor);
				printf("Nombre: %s \n", persona.nombre);
				printf("Apellidos: %s \n", persona.apellido);
				printf("Ventas de Hoy: %d \n", persona.ventasdia);
				printf("----------------------------------------\n");
			} else{
				printf("\nEmpleado inexistente: \n\n");
			}

}
    
    fclose (*fp2);
	
	return 0;
}