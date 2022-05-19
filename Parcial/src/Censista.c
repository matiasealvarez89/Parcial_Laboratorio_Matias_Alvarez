#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Censista.h"
#include "pedidoDatos.h"

#define LIBRE 1
#define OCUPADO 0

#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3


static int idIncremental = 1000;
static int censista_obtenerID();
static int censista_obtenerID()
{
	return idIncremental++;
}

/// @brief funcion para inicializar el array de pasajeros
///
/// @param list array donde se guaran los pasajeros
/// @param len largo del array
/// @return (-1) error (0) si incializo correctamente
int initCensista(Censista* list, int len)
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


int addCensista(Censista* list, int len)
{
	int retorno = -1;
	int index;

	index = primerEspacioLibre(list, len);

	if(list != NULL && len > 0)
	{
		if(!getPalabra(list[index].nombre, "Ingrese el nombre del censista: \n", "Nombre no valido\n", 2, 49, 3)
			&& !getPalabra(list[index].apellido, "Ingrese el apellido del pasajero: \n", "Apellido no valido\n", 2, 49, 3)
			&& !getNumero(&list[index].fechaDeNacimiento.dia, "Ingrese el dia de la fecha de nacimiento: \n", "Ingreso incorrecto\n", 1, 31, 3)
			&& !getNumero(&list[index].fechaDeNacimiento.mes, "Ingrese el mes de la fecha de nacimiento: \n", "Ingreso incorrecto\n", 1, 12, 3)
			&& !getNumero(&list[index].fechaDeNacimiento.anio, "Ingrese el año de la fecha de nacimiento: \n", "Ingreso incorrecto\n", 1930, 2004, 3)
			&& !getPalabra(list[index].domicilio.nombreCalle, "Ingrese la calle del domicilio: \n" , "Ingreso Incorrecto\n", 1, 20, 3)
			&& !getNumero(&list[index].domicilio.altura, "Ingrese la altura del domicilio (0 si no aplica): \n", "Ingreso Incorrecto\n", 1, 10000, 3)
			&& !getNumero(&list[index].domicilio.piso, "Ingrese el piso del domicilio (0 si no aplica): \n", "Ingreso Incorrecto\n", 1, 100, 3)
			&& !getNumero(&list[index].domicilio.departamento, "Ingrese el departamento del domicilio (0 si no aplica): \n", "Ingreso Incorrecto\n", 1, 100, 3))
		{
			list[index].edad = 2022 - list[index].fechaDeNacimiento.anio;
			list[index].isEmpty = OCUPADO;
			list[index].estado = LIBERADO;
			list[index].idCensista = censista_obtenerID();
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
int primerEspacioLibre(Censista* list, int len)
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

void printUnCensista(Censista unCensista)
{

	char textoEstado[10];

	switch(unCensista.estado)
	{
		case 1:
			strcpy(textoEstado, "ACTIVO");
			break;
		case 2:
			strcpy(textoEstado, "INACTIVO");
			break;
		case 3:
			strcpy(textoEstado, "LIBERADO");
			break;
	}

	if(unCensista.isEmpty == OCUPADO)
	{
		printf("%d\t\t", unCensista.idCensista);
		printf("%s\t", textoEstado);
		printf("%s\t\t", unCensista.apellido);
		printf("%s\t\t", unCensista.nombre);
		printf("%d/%d/%d\t\t\t", unCensista.fechaDeNacimiento.dia,unCensista.fechaDeNacimiento.mes,unCensista.fechaDeNacimiento.anio);
		printf("%d\t\t", unCensista.edad);
		printf("%s %d %d %d\t\n", unCensista.domicilio.nombreCalle, unCensista.domicilio.altura, unCensista.domicilio.piso, unCensista.domicilio.departamento);
	}
}

/// @brief funcion para mostrar el listado de pasajeros
///
/// @param list array de pasajeros
/// @param len largo del array
/// @return (-1) error (0) si pudo imprimir correctamente
int printCensistas(Censista* list, int len)
{
	int retorno = -1;

	if(list != NULL && len >0)
	{
		printf("\nId\t\tEstado\t\tApellido\tNombre\t\tFecha de Nacimiento\t\tEdad\t\tDomicilio\t\n");
		for(int i = 0; i < len; i++)
		{
			if(list[i].isEmpty == OCUPADO)
			{
				printUnCensista(list[i]);
			}
		}
		retorno = 0;
		printf("\n");
	}
	return retorno;
}

int modificarCensista(Censista* list, int len, int id)
{
	int retorno = -1;
	int index;
	int respuesta;
	int respuestaFecha;
	int respuestaDomicilio;

	if(list != NULL && len > 0)
	{
		index = findCensista(list, len, id);
		if(index != -1)
		{
			printf("\nId\t\tEstado\t\tApellido\tNombre\t\tFecha de Nacimiento\t\tEdad\t\tDomicilio\t\n");
			printUnCensista(list[index]);
			printf("\n");
			do
			{
				if(!getNumero(&respuesta, "1)Nombre\n2)Apellido\n3)Fecha de nacimiento\n4)Domicilio\n5)Volver\nSeleccione el campo a "
						"modificar\n", "Ingreso incorrecto\n", 1, 5, 3))
				{
					switch(respuesta)
					{
					case 1:
						getPalabra(list[index].nombre, "Ingrese el nombre del censista: \n", "Nombre no valido\n", 2, 49, 3);
						break;
					case 2:
						getPalabra(list[index].apellido, "Ingrese el apellido del pasajero: \n", "Apellido no valido\n", 2, 49, 3);
						break;
					case 3:
						do
						{
							if(!getNumero(&respuestaFecha, "1)Dia\n2)Mes\n3)Año\n4)Volver\nSeleccione el campo a modificar: \n",
									"Ingreso incorrecto\n", 1, 4, 3))
							{
								switch(respuestaFecha)
								{
									case 1:
										getNumero(&list[index].fechaDeNacimiento.dia, "Ingrese el dia de la fecha de nacimiento: \n", "Ingreso incorrecto\n", 1, 31, 3);
										break;
									case 2:
										getNumero(&list[index].fechaDeNacimiento.mes, "Ingrese el mes de la fecha de nacimiento: \n", "Ingreso incorrecto\n", 1, 12, 3);
										break;
									case 3:
										getNumero(&list[index].fechaDeNacimiento.anio, "Ingrese el año de la fecha de nacimiento: \n", "Ingreso incorrecto\n", 1930, 2004, 3);
										break;
									case 4:
										printf("Volviendo\n");
										break;
								}
							}
						}while(respuestaFecha !=4);
						break;
					case 4:
						do
						{
							if(!getNumero(&respuestaDomicilio, "1)Calle\n2)Altura\n3)Piso\n4)Departamento\n"
									"5)Volver\nSeleccione el campo amodificar: \n", "Ingreso incorrecto\n", 1, 5, 3))
							{
								switch(respuestaDomicilio)
								{
									case 1:
										getPalabra(list[index].domicilio.nombreCalle, "Ingrese la calle del domicilio: \n" , "Ingreso Incorrecto\n", 1, 20, 3);
										break;
									case 2:
										getNumero(&list[index].domicilio.altura, "Ingrese la altura del domicilio (0 si no aplica): \n", "Ingreso Incorrecto\n", 1, 10000, 3);
										break;
									case 3:
										getNumero(&list[index].domicilio.piso, "Ingrese el piso del domicilio (0 si no aplica): \n", "Ingreso Incorrecto\n", 1, 100, 3);
										break;
									case 4:
										getNumero(&list[index].domicilio.departamento, "Ingrese el departamento del domicilio (0 si no aplica): \n", "Ingreso Incorrecto\n", 1, 100, 3);
										break;
									case 5:
										printf("Volviendo\n");
										break;
								}
							}
						}while(respuestaDomicilio !=5);
						break;
					case 5:
						printf("Volviendo al menu principal\n");
						break;
					}
				}
			}while(respuesta !=5);
		}
	}
	return retorno;
}

/// @brief funcion para encontrar un censista buscandolo por id
///
/// @param list array de censista
/// @param len largo del array
/// @param id id por el cual se busca el censista
/// @return (-1) si no se encontro el censista, sino retorna la posicion del array
int findCensista(Censista* list, int len, int id)
{
	int retorno = -1;

			if(list != NULL && len > 0 && id > 0)
			{
				for(int i = 0; i < len; i++)
				{
					if(list[i].isEmpty == OCUPADO && list[i].idCensista == id)
					{
						retorno = i;
						break;
					}
				}
			}

			if(retorno == -1)
			{
				printf("No se encontro al censista\n");
			}
		return retorno;
}

/// @brief funcion para borrar un pasajero del array
///
/// @param list array de pasajeros
/// @param len largo del array
/// @param id id por el cual se busca el pasajero
/// @return (-1) si no lo encontro (0) si lo borro correctamente
int removeCensista(Censista* list, int len, int id)
{
	int retorno = -1;
	int index;
	char respuesta;

			if(list != NULL && len > 0 && id > 0)
			{
				index = findCensista(list, len, id);
				if(index != -1)
				{
					if(list[index].estado != ACTIVO)
					{
						printf("\nId\t\tEstado\t\tApellido\tNombre\t\tFecha de Nacimiento\t\tEdad\t\tDomicilio\t\n");
						printUnCensista(list[index]);
						if(!getRespuestaDosChar(&respuesta, "Confirma la baja del censista (s/n): \n", "Ingreso invalido\n", 's', 'n', 3))
						{
							switch(respuesta)
							{
								case 's':
									list[index].estado = INACTIVO;
									retorno = 0;
									printf("Se cambio el estado a INACTIVO, volviendo al menu principal\n");
									break;
								case 'n':
									printf("Volviendo al menu principal\n");
									retorno = 0;
									break;
							}
						}

					}
				}else
				{
					if(list[index].estado == ACTIVO)
					{
						printf("No se puede dar de baja porque el censista se encuentra ACTIVO");
						retorno = 0;
					}
				}
			}

	return retorno;
}

int hardcodeoCensistas(Censista* list, int len)
{
	int retorno = -1;
	Censista aux[5] = {{1000, OCUPADO, ACTIVO, "Matias", "Alvarez", {6,12,1989}, 32, {"Chacabuco", 340, 2, 15}},
						{1001, OCUPADO,ACTIVO, "Juan", "Ramirez" ,{18, 3, 1999}, 23, {"Sarmiennto", 23, 0, 0}},
						{1002, OCUPADO, ACTIVO, "Damian", "Estevez", {11,5,2000}, 22, {"Defensa", 1900, 4, 25}},
						{1003, OCUPADO, ACTIVO, "Rocio", "Arias", {27, 11, 2001}, 21, {"Maipu", 401, 0, 0}},
						{1004, OCUPADO, LIBERADO, "Julian", "Benitez", {7, 5 , 2002}, 20, {"Alsina", 250, 2 ,9}}};

	list[0] = aux[0];
	list[1] = aux[1];
	list[2] = aux[2];
	list[3] = aux[3];
	list[4] = aux[4];

	//list = aux


	return retorno;
}
