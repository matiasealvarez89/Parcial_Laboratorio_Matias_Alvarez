#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Controller.h"
#include "pedidoDatos.h"


/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/


int main()
{
	setbuf(stdout, NULL);

	LinkedList* listaPasajeros;
	int opcion;
	int flagCarga;
	int flagCargaArchivo;
	char respusta;

	flagCarga = 0;
	flagCargaArchivo = 0;

	listaPasajeros = ll_newLinkedList();

	do
	{
		printf("\n1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n"
				"2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n"
				"3. Alta de pasajero\n"
				"4. Modificar datos de pasajero\n"
				"5. Baja de pasajero\n"
				"6. Listar pasajeros\n"
				"7. Ordenar pasajeros\n"
				"8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n"
				"9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n"
				"10. Salir\n");

		if(!getNumero(&opcion, "Ingrese la opcion deseada\n", "Ingreso incorrecto\n", 1, 10, 5))
		{
			switch(opcion)
			{
				case 1:
					if(flagCarga == 0 && !controller_loadFromText("data.csv", listaPasajeros))
					{
						flagCarga = 1;
					}else
					{
						printf("No se puede cargar el archivo nuevamente\n");
					}
					break;
				case 2:
					if(flagCarga == 0 && !controller_loadFromBinary("data2.bin", listaPasajeros))
					{
						flagCarga = 1;
					}else
					{
						printf("No se puede cargar el archivo nuevamente\n");
					}
					break;
				case 3:
					if(!controller_addPassenger(listaPasajeros))
					{
						flagCarga = 1;
					}
					break;
				case 4:
					if((flagCarga == 1 || flagCargaArchivo == 1) && !controller_editPassenger(listaPasajeros))
					{
						printf("Se modifico correctamente\n");
					}
					break;
				case 5:
					if((flagCarga == 1 || flagCargaArchivo == 1) && !controller_removePassenger(listaPasajeros))
					{
						printf("Se elimino el pasajero");
					}
					break;
				case 6:
					if(flagCarga == 1 || flagCargaArchivo == 1)
					{
						controller_ListPassenger(listaPasajeros);
					}else
					{
						printf("Todavia no hay datos cargados en la lista\n");
					}
					break;
				case 7:
					if(flagCarga == 1 || flagCargaArchivo == 1)
					{
						controller_sortPassenger(listaPasajeros);
					}else
					{
						printf("Todavia no hay datos cargados en la lista para ordenar\n");
					}
					break;
				case 8:
					if(flagCarga == 1 || flagCargaArchivo == 1)
					{
						controller_saveAsText("data.csv", listaPasajeros);
					}else
					{
						printf("Todavia no hay datos cargados en la lista para Guardar\n");
					}
					break;
				case 9:
					if(flagCarga == 1 || flagCargaArchivo == 1)
					{
						controller_saveAsBinary("data2.bin", listaPasajeros);
					}else
					{
						printf("Todavia no hay datos cargados en la lista para Guardar\n");
					}
					break;
				case 10:
					if(!getRespuestaDosChar(&respusta, "No se olvide de guardar los datos, confirma que desea salir? (S- SI N- NO)\n"
							, "Ingreso Incorrecto\n", 's', 'n', 3))
					{
						if(respusta == 's')
						{
							ll_deleteLinkedList(listaPasajeros);
							printf("Cerrando el programa\n");
						}else
						{
							opcion = 0;
							printf("Volviendo\n");
						}
					}
					break;
			}
		}
	}while(opcion != 10);

    return EXIT_SUCCESS;
}

