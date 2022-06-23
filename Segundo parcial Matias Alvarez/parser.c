#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno;
	Passenger* nuevoPassenger;
	char id[50];
	char nombre[50];
	char apellido[50];
	char precio[50];
	char tipoPasajero[50];
	char codigoVuelo[50];
	char flightStatus[50];

	retorno = -1;

	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, apellido, precio, codigoVuelo, tipoPasajero, flightStatus);
		while(!feof(pFile))
		{
			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, apellido, precio,
					tipoPasajero, codigoVuelo, flightStatus) == 7)
			{


				nuevoPassenger = Passenger_newParametros(id, nombre, apellido, precio, codigoVuelo, tipoPasajero, flightStatus);

				if(nuevoPassenger != NULL)
				{
					if(ll_add(pArrayListPassenger, nuevoPassenger) != -1)
					{
					retorno = 0;
					}
				}else
				{
					Passenger_delete(nuevoPassenger);
				}
			}
		}
	}


	return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno;
	Passenger* pPasajero;

	retorno = -1;

	if(pFile != NULL && pArrayListPassenger)
	{
		while(!feof(pFile))
		{
			pPasajero = Passenger_new();
			if(pPasajero != NULL && fread(pPasajero, sizeof(Passenger), 1, pFile) == 1)
			{
				if(ll_add(pArrayListPassenger, pPasajero) != -1)
				{
					retorno = 0;
				}else
				{
					Passenger_delete(pPasajero);
				}
			}
		}
	}

    return retorno;
}
