#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "pedidoDatos.h"
#include "Controller.h"



/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno;
		FILE* pFile;

		retorno = -1;

		if (path != NULL && pArrayListPassenger != NULL) {
			pFile = fopen(path, "r");

			if (pFile != NULL) {
				retorno = parser_PassengerFromText(pFile, pArrayListPassenger);
				fclose(pFile);
			}
		}

	    return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger)
{
    int retorno;
    FILE* pFile;

    retorno = -1;

	if(path != NULL && pArrayListPassenger != NULL)
	{
		pFile = fopen(path, "rb");

		if(pFile != NULL)
		{
			parser_PassengerFromBinary(pFile, pArrayListPassenger);
			retorno = 0;
			fclose(pFile);
		}
	}


	return retorno;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger)
{
    int retorno;
    Passenger* pNuevoPasajero;
    int maxId;

    pNuevoPasajero = NULL;

    maxId = controller_idMax("ultimoId.csv");
    maxId++;

    retorno = -1;

    if(pArrayListPassenger != NULL)
    {
    	pNuevoPasajero = Passenger_addPassenger(maxId);
    	if(pNuevoPasajero != NULL)
    	{
    		retorno = ll_add(pArrayListPassenger, pNuevoPasajero);
    		controller_idMaxGuardar("ultimoId.csv", maxId);
    	}else
    	{
    		Passenger_delete(pNuevoPasajero);
    	}
    }

	return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int retorno;
	Passenger* pPasajeroAEditar;
	int idPasajero;
	int indicePasajero;
	int maxId;


	maxId = controller_idMax("ultimoId.csv");
	maxId++;
	retorno = -1;

	if(pArrayListPassenger != NULL && !ll_isEmpty(pArrayListPassenger))
	{
		if(!getNumero(&idPasajero, "Ingrese el ID del pasajero que desea modificar\n", "No existe ese ID\n", 1, maxId, 3))
		{
			indicePasajero = Passenger_findById(pArrayListPassenger, idPasajero);
			if(indicePasajero != -1)
			{
				pPasajeroAEditar = (Passenger*)ll_get(pArrayListPassenger, indicePasajero);
				if(!Passenger_edit(pPasajeroAEditar))
				{
					retorno = ll_set(pArrayListPassenger, indicePasajero, pPasajeroAEditar);
				}
			}
		}

	}

    return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
    int retorno;
    Passenger* pPasajero;
    int idPasajero;
    int index;
    int maxId;
    char respuesta;

    maxId = controller_idMax("ultimoId.csv");
    maxId++;

    retorno = -1;

    if(pArrayListPassenger != NULL && !ll_isEmpty(pArrayListPassenger))
    {
    	if(!getNumero(&idPasajero, "Ingrese el ID del pasajero que desea Eliminar\n", "No existe ese ID\n", 1, maxId, 3))
    	{
    		index = Passenger_findById(pArrayListPassenger, idPasajero);

    		if(index != -1)
    		{
    			pPasajero = (Passenger*)ll_get(pArrayListPassenger, index);
    			printf("ID 	   Nombre 	Apellido	Precio		CodigoVuelo 	TipoPasajero	FlightStatus\n");
    			Passenger_printUnPassenger(pPasajero);
    			if(!getRespuestaDosChar(&respuesta, "Confirma que desea Elminarlo?(S) SI N) NO)\n", "Ingreso incorrecto\n", 's', 'n', 3))
    			{
    				if(respuesta == 's')
    				{
    					ll_remove(pArrayListPassenger, index);
    					Passenger_delete(pPasajero);
    					retorno = 0;
    				}else if(respuesta == 'n')
    				{
    					printf("No se borro.\n");
    				}
    			}
    		}
    	}
    }

    return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
    int retorno;
    Passenger* auxPassenger;
    int len;

    retorno = -1;

    len = ll_len(pArrayListPassenger);

    if(pArrayListPassenger != NULL && len > 0)
    {
    	if(len > 0)
    	{
    		printf("ID 	   Nombre 	Apellido	Precio		CodigoVuelo 	TipoPasajero	FlightStatus\n");
    		for(int i =0; i < len; i++)
    		{
    			auxPassenger =(Passenger*)ll_get(pArrayListPassenger, i);
    			Passenger_printUnPassenger(auxPassenger);
    		}
    	}
    }

    return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int retorno;
	int opcion;
	int orden;

	printf("1) Por orden alfabatico\n"
			"2) Por Precio\n"
			"3) Por Id\n");

	if(!getNumero(&opcion, "Ingrese la opcion deseada\n", "Ingreso incorrecto\n", 1, 3, 3)
			&& !getNumero(&orden, "1) Orden Descendente\n2) Orden Ascendente\nSeleccione el orden deseado\n"
					, "Ingreso incorrecto\n", 1, 2, 3))
	{
		orden--;
		switch(opcion)
		{
			case 1:
				retorno = ll_sort(pArrayListPassenger, Passenger_compareByApellido , orden);
				break;
			case 2:
				retorno = ll_sort(pArrayListPassenger, Passenger_compareByPrecio , orden);
				break;
			case 3:
				retorno = ll_sort(pArrayListPassenger, Passenger_compareById , orden);
				break;
		}
	}

	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	FILE* pFile;
	int len;
	Passenger* pPasajero;
	int auxId;
	char auxNombre[50];
	char auxApellido[50];
	float auxPrecioFloat;
	char auxCodigoVuelo[50];
	int auxTipoPasajeroint;
	char auxTipoPasajero[50];
	int auxStatusFlightInt;
	char auxStatusFlight[50];

	retorno = -1;
	len = ll_len(pArrayListPassenger);

	if(path != NULL && pArrayListPassenger != NULL)
	{
		pFile = fopen(path, "w");
		if(pFile != NULL)
		{
			fprintf(pFile, "id,name,lastname,price,flycode,typePassenger,statusFlight\n");
			for(int i = 0; i < len; i++)
			{
				pPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
				if(!Passenger_getAll(pPasajero, &auxId, auxNombre, auxApellido, &auxPrecioFloat, &auxTipoPasajeroint,
						auxCodigoVuelo, &auxStatusFlightInt))
				{
					switch(auxTipoPasajeroint)
					{
						case 1:
							strcpy(auxTipoPasajero, "FirstClass");
							break;
						case 2:
							strcpy(auxTipoPasajero,"ExecutiveClass");
							break;
						case 3:
							strcpy(auxTipoPasajero, "EconomyClass");
							break;
					}

					switch(auxStatusFlightInt)
					{
						case 1:
							strcpy(auxStatusFlight, "Aterrizado");
							break;
						case 2:
							strcpy(auxStatusFlight, "En Horario");
							break;
						case 3:
							strcpy(auxStatusFlight, "En Vuelo");
							break;
					}
					fprintf(pFile, "%d,%s,%s,%f,%s,%s,%s\n", auxId,auxNombre, auxApellido, auxPrecioFloat, auxCodigoVuelo, auxTipoPasajero, auxStatusFlight);
				}
			}
			retorno = 0;
			fclose(pFile);
		}
	}

    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
    int retorno;
    int len;
    FILE* pFile;
    Passenger* pPasajero;

    len = ll_len(pArrayListPassenger);
    retorno = -1;

    if(path != NULL && pArrayListPassenger != NULL)
    {
    	pFile = fopen(path, "wb");

    	if(pFile != NULL && len > 0)
    	{
    		for(int i = 0; i < len; i++)
    		{
    			pPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
    			fwrite(pPasajero, sizeof(Passenger), 1, pFile);
    		}
    		fclose(pFile);
    	}
    	retorno = 0;
    }


	return retorno;
}

int controller_idMax(char* path)
{
	int retorno;
	FILE* pFile;
	int idMaximo;

	idMaximo = 0;
	retorno = -1;

	if(path != NULL)
	{
		pFile = fopen("ultimoId.csv", "r");
		fscanf(pFile, "%d", &idMaximo);
		fclose(pFile);
		retorno = idMaximo;
	}


	return retorno;
}

int controller_idMaxGuardar(char* path, int idNuevo)
{
	int retorno;
	FILE* pFile;

	retorno = -1;

	if(path != NULL && idNuevo > 0)
	{
		pFile = fopen("ultimoId.csv", "w");
		fprintf(pFile, "%d", idNuevo);
		fclose(pFile);
		retorno = 0;
	}

	return retorno;
}
