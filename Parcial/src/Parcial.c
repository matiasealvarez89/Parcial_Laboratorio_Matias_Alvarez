#include <stdio.h>
#include <stdlib.h>

#include "Censista.h"
#include "pedidoDatos.h"
#include "Zona.h"

#define ELEMENTS 5

#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3


int main(void) {
	setbuf(stdout, NULL);

	Censista arrayCensistas[ELEMENTS];
	Zona arrayZonas[ELEMENTS];
	int respuesta;
	int idIngresadaCensista;
	int idIngresadaZona;
	int flagCargaCensista = 0;
	int flagCargaZona = 0;
	int indexZonaEncontrada = 0;
	int indexCensitaEncontrado = 0;


	if(initCensista(arrayCensistas, ELEMENTS) == 0 && initZona(arrayZonas, ELEMENTS) == 0)
	{
		printf("Inicializando\n");
	}else
	{
		printf("Error\n");
	}

	do
	{
		if(!getNumero(&respuesta, "1)Cargar Censista\n2)Modificar censita\n3)Dar de baja censista\n4)Cargar zona\n5)Asignar zona a censar\n"
				"6)Carga de datos\n7)Mostrar censista\n8)Mostrar zonas\n9)Hardcodeo\n10)Salir\nIngrese la opcion deseada\n", "Ingreso incorrecto.\n", 1, 10, 3))
		{
			switch(respuesta)
			{
				case 1:
					if(!addCensista(arrayCensistas, ELEMENTS))
					{
						flagCargaCensista = 1;
					}else
					{
						printf("No se cargo\n");
					}
					break;
				case 2:
					if(flagCargaCensista == 1 && !getNumero(&idIngresadaCensista, "Ingrese el ID del censita: \n", "Ingreso incorrecto\n", 1000, 2000, 3))
					{
						modificarCensista(arrayCensistas, ELEMENTS, idIngresadaCensista);
					}else
					{
						printf("No se han cargado censitas aun.\n");
					}
					break;
				case 3:
					if(flagCargaCensista == 1 && !getNumero(&idIngresadaCensista, "Ingrese el ID del censita: \n", "Ingreso incorrecto\n", 1000, 2000, 3))
					{
						removeCensista(arrayCensistas, ELEMENTS, idIngresadaCensista);
					}else
					{
						printf("No se han cargado censitas aun.\n");
					}
					break;
				case 4:
					if(!addZona(arrayZonas, ELEMENTS))
					{
						flagCargaZona = 1;
					}else
					{
						printf("No se cargo\n");
					}
					break;
				case 5:
					if(flagCargaCensista == 1 && flagCargaZona == 1 && !getNumero(&idIngresadaZona, "Ingrese el ID de la zona a asignar\n", "Ingreso incorrecto\n", 2000, 3000, 3))
					{
						if(findZona(arrayZonas, ELEMENTS, idIngresadaZona) != -1)
						{
							indexZonaEncontrada = findZona(arrayZonas, ELEMENTS, idIngresadaZona);
							if(!getNumero(&idIngresadaCensista, "Ingrese el ID del censista a asignar\n", "Ingreso incorrecto", 1000, 1999, 3))
							{

								if(findCensista(arrayCensistas, ELEMENTS, idIngresadaCensista) != -1)
								{
									indexCensitaEncontrado = findCensista(arrayCensistas, ELEMENTS, idIngresadaCensista);
									if(arrayCensistas[indexCensitaEncontrado].estado != LIBERADO)
									{
										printf("No se puede asignar censista, porque esta ocupado o fue dado de baja.\n");
									}else
									{
										arrayZonas[indexZonaEncontrada].idCensista = arrayCensistas[indexCensitaEncontrado].idCensista;
									}
								}else
								{
									printf("No se encontro censista con esa ID\n");
								}
							}
						}else
						{
							printf("No se encontro la zona\n");
						}
					}else
					{
						printf("Faltan cargar datos\n");
					}
					break;
				case 6:
					if(flagCargaCensista == 1 && flagCargaZona == 1 && !getNumero(&idIngresadaZona, "Ingrese el ID de la zona a cargar datos\n", "Ingreso incorrecto\n", 2000, 3000, 3))
					{
						if(!cargarDatosZona(arrayZonas, ELEMENTS, idIngresadaZona))
						{
							printf("\n");
						}
					}else
					{
						printf("Faltan cargar datos\n");
					}
					break;
				case 7:
					if(flagCargaCensista == 1 && !printCensistas(arrayCensistas, ELEMENTS))
					{
						printf("\n");
					}else
					{
						printf("No se han cargado censistas aun.\n");
					}
					break;
				case 8:
					if(flagCargaZona != 0 && !printZonas(arrayZonas, ELEMENTS, arrayCensistas))
					{
						printf("\n");
					}else
					{
						printf("No se han cargado zonas aun.\n");
					}
					break;
				case 9:
					hardcodeoCensistas(arrayCensistas, ELEMENTS);
					flagCargaCensista = 1;
					hardcodeoZonas(arrayZonas, ELEMENTS);
					flagCargaZona = 1;
					break;
				case 10:
					printf("Saliendo...\n");
					break;
			}
		}
	}while(respuesta != 10);

	return EXIT_SUCCESS;
}
