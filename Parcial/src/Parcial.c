#include <stdio.h>
#include <stdlib.h>

#include "Censista.h"
#include "pedidoDatos.h"

#define ELEMENTS 5


int main(void) {
	setbuf(stdout, NULL);

	Censista arrayCensistas[ELEMENTS];
	int respuesta;
	int idIngresada;

	if(initCensista(arrayCensistas, ELEMENTS) == 0)
	{
		printf("Inicializando\n");
	}else
	{
		printf("Error\n");
	}

	do
	{
		if(!getNumero(&respuesta, "1)Cargar Censista\n2)Modificar censita\n3)Dar de baja censista\n4)Cargar zona\n5)Asignar zona a censar\n"
				"6)Carga de datos\n7)Mostrar censista\n8)Mostrar zonas\n9)Salir\nIngrese la opcion deseada\n", "Ingreso incorrecto.\n", 1, 9, 3))
		{
			switch(respuesta)
			{
				case 1:
					if(addCensista(arrayCensistas, ELEMENTS))
					{
						printf("Se cargo corrrectamente\n");
					}else
					{
						printf("No se cargo\n");
					}
					break;
				case 2:
					if(!getNumero(&idIngresada, "Ingrese el ID del censita: \n", "Ingreso incorrecto\n", 1000, 2000, 3))
					{
						modificarCensista(arrayCensistas, ELEMENTS, idIngresada);
					}
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					printf("Saliendo...\n");
					break;
			}
		}
	}while(respuesta != 9);

	return EXIT_SUCCESS;
}
