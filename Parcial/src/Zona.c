#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Zona.h"
#include "pedidoDatos.h"
#include "Censista.h"

#define LIBRE 1
#define OCUPADO 0

#define PENDIENTE 1
#define FINALIZADO 2

#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3

//char localidades[5][20] = {"Avellaneda", "Lomas de Zamora", "Lanus", "Banfield", "Wilde"};

static int idIncremental = 2000;
static int zona_obtenerID();
static int zona_obtenerID()
{
	return idIncremental++;
}

/// @brief funcion para inicializar el array de pasajeros
///
/// @param list array donde se guaran los pasajeros
/// @param len largo del array
/// @return (-1) error (0) si incializo correctamente
int initZona(Zona* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL)
	{
		if(len >= 0)
		{
			for(i = 0; i < len; i++)
			{
				//Inicializo Estructura - LIBRE 0 - OCUPADO 1
				list[i].isEmpty = LIBRE;
			}
		}
		retorno = 0;
	}
	return retorno;
}

int addZona(Zona* list, int len)
{
	int retorno = -1;
	int index;

	index = primerEspacioLibreZona(list, len);

	if(list != NULL && len > 0)
	{
		if(!getNumero(&list[index].localidad, "Ingrese la localidad (1- Avellaneda, 2- Lomas de Zamora, 3- Lanus Este 4- Banfield, 5- Lavallol)\n", "Ingreso incorrecto\n", 1, 5, 3)
				&& !getPalabra(list[index].calles[0], "Ingrese el nombre de la primer manzana\n", "Ingreso incorrecto\n", 1, 20, 3)
				&& !getPalabra(list[index].calles[1], "Ingrese el nombre de la segunda manzana\n", "Ingreso incorrecto\n", 1, 20, 3)
				&& !getPalabra(list[index].calles[2], "Ingrese el nombre de la tercer manzana\n", "Ingreso incorrecto\n", 1, 20, 3)
				&& !getPalabra(list[index].calles[3], "Ingrese el nombre de la cuarta manzana\n", "Ingreso incorrecto\n", 1, 20, 3))
		{
			list[index].estado = PENDIENTE;
			list[index].isEmpty = OCUPADO;
			list[index].idZona = zona_obtenerID();
			list[index].idCensista = 0;
			list[index].cantidadCensados = 0;
			list[index].cantidadAusentes = 0;
			list[index].cantidadCensadosDigital = 0;
			retorno = 0;

			printf("Guardado\n");
		}else
		{
			printf("No se guardo\n");
		}
	}

	return retorno;
}

/// @brief funcion para encontrar la primr posicion libre del array
///
/// @param list array de censistas
/// @param len largo del array
/// @return (-1) error (i) posicion libre
int primerEspacioLibreZona(Zona* list, int len)
{
	int retorno = -1;

		if(list != NULL && len > 0)
		{
			for(int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == LIBRE)
				{
					retorno = i;
					break;
				}
			}
		}
	return retorno;
}

void printUnaZona(Zona unaZona, Censista* listCensistas, int len)
{

	char textoEstado[10];
	char textoLocalidad[20];
	int indexCensista;

	switch(unaZona.estado)
	{
		case 1:
			strcpy(textoEstado, "PENDIENTE");
			break;
		case 2:
			strcpy(textoEstado, "FINALIZADO");
			break;
	}

	switch(unaZona.localidad)
	{
		case 1:
			strcpy(textoLocalidad, "Avellaneda");
			break;
		case 2:
			strcpy(textoLocalidad, "Lomas de Zamora");
			break;
		case 3:
			strcpy(textoLocalidad, "Lanus Este");
			break;
		case 4:
			strcpy(textoLocalidad, "Banfield");
			break;
		case 5:
			strcpy(textoLocalidad, "Lavallol");
			break;
	}

	if(unaZona.isEmpty == OCUPADO)
	{
		printf("%d\t", unaZona.idZona);
		printf("%s\t", textoEstado);
		if(unaZona.idCensista == 0)
		{
			printf("Sin asignar\t");
		}else
		{
			printf("%d\t\t", unaZona.idCensista);
			indexCensista = findCensista(listCensistas, len, unaZona.idCensista);
		}
		if(unaZona.idCensista == 0)
		{
			printf("Sin asignar\t");
		}else
		{
			printf("%s\t\t", listCensistas[indexCensista].apellido);
		}
		if(unaZona.idCensista == 0)
		{
			printf("Sin asignar\t");
		}else
		{

			printf("%s\t\t", listCensistas[indexCensista].nombre);
		}
		printf("%s\t", textoLocalidad);
		printf("%s\t", unaZona.calles[0]);
		printf("%s\t", unaZona.calles[1]);
		printf("%s\t", unaZona.calles[2]);
		printf("%s\t", unaZona.calles[3]);
		printf("%d\t\t\t", unaZona.cantidadCensados);
		printf("%d\t\t\t", unaZona.cantidadCensadosDigital);
		printf("%d\t\t\n", unaZona.cantidadAusentes);
	}
}

/// @brief funcion para mostrar el listado de pasajeros
///
/// @param list array de pasajeros
/// @param len largo del array
/// @return (-1) error (0) si pudo imprimir correctamente
int printZonas(Zona* list, int len, Censista* listCensistas)
{
	int retorno = -1;

	if(list != NULL && len >0)
	{
		printf("\nId\tEstado\t\tCensista\tNombre\t\tApellido\tLocalidad\tCalle1\tCalle2\tCalle3\tCalle4\tCantidad censados\tCantidad digital\tCantidad Ausentes\n");
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == OCUPADO)
			{
				printUnaZona(list[i], listCensistas, len);
			}
		}
		retorno = 0;
		printf("\n");
	}
	return retorno;
}

/// @brief funcion para encontrar un zona buscandolo por id
///
/// @param list array de zona
/// @param len largo del array
/// @param id id por el cual se busca el censista
/// @return (-1) si no se encontro el censista, sino retorna la posicion del array
int findZona(Zona* list, int len, int id)
{
	int retorno = -1;

			if(list != NULL && len > 0 && id > 0)
			{
				for(int i = 0; i < len; i++)
				{
					if(list[i].isEmpty == OCUPADO && list[i].idZona == id)
					{
						retorno = i;
						break;
					}
				}
			}

			if(retorno == -1)
			{
				printf("No se encontro la zona\n");
			}
		return retorno;
}

int cargarDatosZona(Zona* list, int len, int id)
{
	int retorno = -1;
	int index;

	index = findZona(list, len, id);

	if(index != -1)
	{
		if(!getNumero(&list[index].cantidadCensados, "Ingrese la cantidad de censados\n", "Ingreso incorrecto\n", 0, 10000, 3)
				&& !getNumero(&list[index].cantidadCensadosDigital, "Ingrese la cantidad de personas que hicieron el censo digital\n", "Ingreso incorrecto\n", 0, 10000, 3)
				&& ! getNumero(&list[index].cantidadAusentes, "Ingrese la cantidad de ausentes\n", "Ingreso incorrecto\n", 0, 10000, 3))
		{
			printf("Se guardaron los datos correctamente\n");
		}else
		{
			printf("No se guardaron datos\n");
		}
	}else
	{
		printf("No se encontro la zona\n");
	}

	return retorno;
}

int hardcodeoZonas(Zona* list, int len)
{
	int retorno = -1;
	Zona aux[5] = {{2000, 0, {"AAB","AXA","JFR","JSE"}, 1, 1001 , 0, 0, 0,1},
						{2001, 0,{"KLR","ERT","FGR","JFW"}, 5, 0, 0, 0, 0, 1},
						{2002, 0, {"DFC", "ERX","ACD","WSZ"}, 2, 1000, 15000, 12300, 5230,2},
						{2003, 0, {"BCD", "DSJ", "CDA", "CAZ"}, 5, 1003, 12350, 12500, 3268,2},
						{2004, 0, {"HER", "XVS", "AZX", "AZE" }, 3, 1003, 13520, 1654, 3856, 2}};

	list[0] = aux[0];
	list[1] = aux[1];
	list[2] = aux[2];
	list[3] = aux[3];
	list[4] = aux[4];

	//list = aux


	return retorno;
}
