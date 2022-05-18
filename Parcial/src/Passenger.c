#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Passenger.h"
#include "pedidoDatos.h"

#define LIBRE 1
#define OCUPADO 0


static int idIncremental = 1000;
static int passenger_obtenerID();
static int passenger_obtenerID()
{
	return idIncremental++;
}
/// @brief funcion para inicializar el array de pasajeros
///
/// @param list array donde se guaran los pasajeros
/// @param len largo del array
/// @return (-1) error (0) si incializo correctamente
int initPassenger(Passenger* list, int len)
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
/// @brief funcion para cargar un pasajero
///
/// @param list array donde se guardan los pasajeros
/// @param len largo del array de pasajeros
/// @param id id del pasajero (no se ingresa)
/// @param name nombre
/// @param lastName apellido
/// @param price precio
/// @param typePassenger tipo de pasajero
/// @param flyCode codigo de vuelo
/// @param index posicion en el array donde se guardan los datos
/// @return (-1) error (0) si se guardo correctamente
int addPassenger(Passenger* list, int len, int id, char name[], char lastName[], float price,
		int typePassenger, char flyCode[],int index)
{
	int retorno = -1;

	if(list != NULL && len > 0)
	{
		if(!getPalabra(list[index].name, "Ingrese el nombre del pasajero: \n", "Nombre no valido\n", 2, 49, 3)
			&& !getPalabra(list[index].lastName, "Ingrese el apellido del pasajero: \n", "Apellido no valido\n", 2, 49, 3)
			&& !getFloat(&list[index].price, "Ingrese el precio del pasaje: \n", "Ingreso Incorrecto\n", 1, 500000, 3)
			&& !getPalabra(list[index].flyCode, "Ingrese el codigo de vuelo: \n" , "Ingreso Incorrecto\n", 1, 9, 3)
			&& !getNumero(&list[index].typePassenger, "Ingrese el tipo de pasajero (1- PRIMERA CLASE, 2- SUPERIOR, 3- COMUN): \n", "Ingreso Incorrecto\n", 1, 3, 3))
		{
			list[index].statusFlight = 1;
			list[index].isEmpty = OCUPADO;
			list[index].id = passenger_obtenerID();

			printf("Guardado\n");
		}else
		{
			printf("No se guardo\n");
		}
	}

	return retorno;
}
/// @brief funcion para encontrar un pasajero buscandolo por id
///
/// @param list array de pasajeros
/// @param len largo del array
/// @param id id por el cual se busca el pasajero
/// @return (-1) si no se encontro el pasajero, sino retorna la posicion del array
int findPassenger(Passenger* list, int len, int id)
{
	int retorno = -1;

			if(list != NULL && len > 0 && id > 0)
			{
				for(int i = 0; i < len; i++)
				{
					if(list[i].isEmpty == OCUPADO && list[i].id == id)
					{
						retorno = i;
						break;
					}
				}
			}

		return retorno;
}
/// @brief funcion para borrar un pasajero del array
///
/// @param list array de pasajeros
/// @param len largo del array
/// @param id id por el cual se busca el pasajero
/// @return (-1) si no lo encontro (0) si lo borro correctamente
int removePassenger(Passenger* list, int len, int id)
{
	int retorno = -1;
	int index;

			if(list != NULL && len > 0 && id > 0)
			{
				index = findPassenger(list, len, id);
				if(index != -1)
				{
					printUnPassenger(list[index]);
					list[index].isEmpty = LIBRE;
					retorno = 0;
				}
			}

	return retorno;
}
/// @brief funcion para ordenar el array en orden alfabetico por el apellido
///
/// @param list array de pasajeros
/// @param len largo del array
/// @param order (1) ascendente (2) descendente
/// @return (-1) error (0) si lo ordeno correctamente
int sortPassenger(Passenger* list, int len, int order)
{
	int retorno = -1;
	int i;
	Passenger aux;
	int estaOrdenado;

	if (list != NULL && len > 0) {
		if(order == 1)
		{
			do {
				estaOrdenado = 1;
				len--;
				for (i = 0; i < len; i++) {
					if (list[i].isEmpty == OCUPADO && strcmp(list[i].lastName,list[i + 1].lastName) == 1){
						aux = list[i];
						list[i] = list[i + 1];
						list[i + 1] = aux;
						estaOrdenado = 0;
					}else
					{
						if(strcmp(list[i].lastName,list[i + 1].lastName) == 0)
						{
							if (list[i].typePassenger > list[i + 1].typePassenger)
							{
							aux = list[i];
							list[i] = list[i + 1];
							list[i + 1] = aux;
							estaOrdenado = 0;
							}
						}
					}
				}
			}while(estaOrdenado == 0);
			retorno = 0;
		}
		else
		{
			do {
				estaOrdenado = 1;
				len--;
				for (i = 0; i < len; i++) {
					if (strcmp(list[i + 1].lastName,list[i].lastName) == 1){
						aux = list[i];
						list[i] = list[i + 1];
						list[i + 1] = aux;
						estaOrdenado = 0;
					}else
					{
						if(strcmp(list[i + 1].lastName,list[i].lastName) == 0)
						{
							if (list[i].typePassenger > list[i + 1].typePassenger)
							{
							aux = list[i];
							list[i] = list[i + 1];
							list[i + 1] = aux;
							estaOrdenado = 0;
							}
						}
					}
				}
			}while(estaOrdenado == 0);
			retorno = 0;
		}

	}

	return retorno;
}
/// @brief funcion para mostrar el listado de pasajeros
///
/// @param list array de pasajeros
/// @param len largo del array
/// @return (-1) error (0) si pudo imprimir correctamente
int printPassengers(Passenger* list, int len)
{
	int retorno = -1;

	if(list != NULL && len >0)
	{
		printf("\nId\t\tApellido\tNombre\t\tPrecio\t\tFlycode\t\tTipo de Pasajero\tStatus Flight\n");
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == OCUPADO)
			{
				printUnPassenger(list[i]);
			}
		}
		retorno = 0;
		printf("\n");
	}
	return retorno;
}
/// @brief funcion para ordenar el array por el codigo de vuelo
///
/// @param list array de pasajeros
/// @param len
/// @param order len largo del array
/// @return (-1) error (0) si pudo imprimir correctamente
int sortPassengersByCode(Passenger* list, int len, int order)
{
	int retorno = -1;
	int i;
	Passenger aux;
	int estaOrdenado;

	if (list != NULL && len > 0) {
		if(order == 1)
		{
			do {
				estaOrdenado = 1;
				len--;
				for (i = 0; i < len; i++) {
					if (list[i].isEmpty == OCUPADO && strcmp(list[i].flyCode,list[i + 1].flyCode) == 1){
						aux = list[i];
						list[i] = list[i + 1];
						list[i + 1] = aux;
						estaOrdenado = 0;
					}
				}
			}while(estaOrdenado == 0);
			retorno = 0;
		}
	}
	return retorno;
}
/// @brief funcion complementaria de printPassengers para imprimir por pantalla un solo pasajero
///
/// @param unPassenger pasajero a imprimir
void printUnPassenger(Passenger unPassenger)
{
	char textoTypePassenger[20];
	char textoStatusFlight[20];

	switch (unPassenger.typePassenger)
	{
		case 1:
			strncpy(textoTypePassenger,"PRIMERA CLASE",20);
			break;
		case 2:
			strncpy(textoTypePassenger,"SUPERIOR",20);
			break;
		case 3:
			strncpy(textoTypePassenger,"COMUN\t",20);
			break;
	}
	switch (unPassenger.statusFlight)
	{
		case 1:
			strncpy(textoStatusFlight,"ACTIVO",20);
			break;
		case 2:
			strncpy(textoStatusFlight,"SUSPENDIDO",20);
			break;
		case 3:
			strncpy(textoStatusFlight,"FINALIZADO",20);
			break;
	}

	if(unPassenger.isEmpty == OCUPADO)
	{
		printf("%d\t\t", unPassenger.id);
		printf("%s\t\t", unPassenger.lastName);
		printf("%s\t\t", unPassenger.name);
		printf("$%.2f\t", unPassenger.price);
		printf("%s\t\t", unPassenger.flyCode);
		printf("%s\t\t", textoTypePassenger);
		printf("%s\t\t\n", textoStatusFlight);

	}
}
/// @brief funcion para encontrar la primr posicion libre del array
///
/// @param list array de pasajeros
/// @param len largo del array
/// @return (-1) error (i) posicion libre
/*int primerEspacioLibre(Passenger* list, int len)
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
*/
/// @brief funcion para informar el promedio de pasajes y mostrarlo por consola
///
/// @param list array de pasajeros
/// @param lenlargo del array
/// @return (-1) error (0) si pudo calcularlo correctamente
int promedioPasajes(Passenger* list, int len)
{
	int retorno = -1;
	int contador = 0;
	int contadorSuperaPromedio = 0;
	float acumulador = 0;
	float promedio;

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == OCUPADO)
			{
				contador++;
				acumulador += list[i].price;
			}
		}

		promedio = acumulador / contador;

		for(int i = 0; i < len; i++)
		{
			if(list[i].price > promedio)
			{
				contadorSuperaPromedio++;
			}
		}
		printf("La suma de los precios es: $%.2f\nEl precio promedio es: $%2.f\n%d Pasajeros superan el precio promedio\n\n", acumulador, promedio, contadorSuperaPromedio);
		retorno = 0;
	}

	return retorno;
}
/// @brief funcion para mostrar pasajeros en caso de que el status del vuelo sea ACTIVO
///
/// @param list array de pasajeros
/// @param len largo del array
/// @return (-1) error (0) si lo pudo mostrar correctamente
int printPassengersStatus(Passenger* list, int len)
{
	int retorno = -1;

		if(list != NULL && len >0)
		{
			printf("\nId\t\tApellido\tNombre\t\tPrecio\t\tFlycode\t\tTipo de Pasajero\tStatus Flight\n");
			for(int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == OCUPADO && list[i].statusFlight == 1)
				{
					printUnPassenger(list[i]);
				}
			}
			retorno = 0;
			printf("\n");
		}
		return retorno;
}
