#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Passenger.h"
#include "pedidoDatos.h"

#define LIBRE 1
#define OCUPADO 0
#define ELEMENTS 5

/*int main(void) {
	setbuf(stdout, NULL);

	Passenger arrayPasengers[ELEMENTS];
	int primerPosicionLibre;
	int posicionSeleccionada;
	int respuesta;
	int idParaBaja;
	int flagCarga = 0;

	if(!initPassenger(arrayPasengers, ELEMENTS))
	{
		printf("Se inicializo el programa\n");
	}else
	{
		printf("No hay arrayPasengers reservada"); // preguntar sobre estos mensajes
	}

	do{
		printf("*****************************MENU PRINCIPAL*****************************\n");
		printf("1. ALTAS \n");
		printf("2. MODIFICAR: \n");
		printf("3. BAJA: \n");
		printf("4. INFORMAR: \n");
		printf("5. HARDCODEO: \n");
		printf("6. SALIR: \n");
		if(!getNumero(&respuesta, "Eliga la opcion deseada: \n", "Ingreso incorrecto \n", 1, 6, 3)){
			switch(respuesta){
				case 1:
					primerPosicionLibre = primerEspacioLibre(arrayPasengers, ELEMENTS);
					if(primerPosicionLibre != -1)
					{
						addPassenger(arrayPasengers, ELEMENTS, arrayPasengers[primerPosicionLibre].id, arrayPasengers[primerPosicionLibre].name,
								arrayPasengers[primerPosicionLibre].lastName, arrayPasengers[primerPosicionLibre].price,
								arrayPasengers[primerPosicionLibre].typePassenger, arrayPasengers[primerPosicionLibre].flyCode, primerPosicionLibre);
						flagCarga = 1;
					}else
					{

						printf("No se encontro espacio para almacenar un nuevo ingreso \n\n");
					}
					printPassengers(arrayPasengers, ELEMENTS);
					break;
				case 2:
					if(flagCarga == 1)
					{
						if(!getNumero(&respuesta, "Ingrese el ID del pasajero a modificar: \n", "Numero no valido\n" , 1000, 2000, 3))
						{
							if(findPassenger(arrayPasengers, ELEMENTS, respuesta) == -1)
							{
								printf("No se encontro un pasajero con esa ID\n\n");
							}
							else
							{
								posicionSeleccionada = findPassenger(arrayPasengers, ELEMENTS, respuesta);
								printf("\nId\t\tApellido\tNombre\t\tPrecio\t\tFlycode\t\tTipo de Pasajero\tStatus Flight\n");
								printUnPassenger(arrayPasengers[posicionSeleccionada]);
								printf("\n");
								do
								{
									if(!getNumero(&respuesta, "1) Nombre\n2) Apellido\n3) Precio\n4) FlyCode\n"
											"5) Tipo de Pasajero\n6) Volver\nIngrese el campo que desea modificar: ",
											"Ingreso Incorrecto\n", 1, 6, 3))
									{
										switch(respuesta)
										{
											case 1:
												getPalabra(arrayPasengers[posicionSeleccionada].name, "Ingrese el nombre del pasajero: \n", "Nombre no valido\n", 2, 49, 3);
												break;
											case 2:
												getPalabra(arrayPasengers[posicionSeleccionada].lastName, "Ingrese el apellido del pasajero: \n", "Nombre no valido\n", 2, 49, 3);
												break;
											case 3:
												getFloat(&arrayPasengers[posicionSeleccionada].price, "Ingrese el precio del pasaje: \n", "Ingreso Incorrecto\n", 1, 500000, 3);
												break;
											case 4:
												getPalabra(arrayPasengers[posicionSeleccionada].flyCode, "Ingrese el codigo de vuelo: \n" , "Ingreso Incorrecto\n", 1, 9, 3);
												break;
											case 5:
												getNumero(&arrayPasengers[posicionSeleccionada].typePassenger, "Ingrese el tipo de pasajero (1- PRIMERA CLASE, 2- SUPERIOR, 3- COMUN): \n", "Ingreso Incorrecto\n", 1, 3, 3);
												break;
											case 6:
												printf("Volviendo al menu princpal\n");
												break;
										}
									}
								}while(respuesta != 6);
							}
							respuesta = 0;
						}
					}else
					{
						printf("Aun no se realizo ninguna carga\n");
					}
					break;
				case 3:
					if(flagCarga == 1)
					{
						if(!getNumero(&respuesta, "Ingrese el ID del pasajero a dar de baja: \n", "Numero no valido\n" , 1000, 2000, 3))
								{
									if(findPassenger(arrayPasengers, ELEMENTS, respuesta) == -1)
									{
										printf("No se encontro un pasajero con esa ID\n\n");
									}
									else
									{
										idParaBaja = respuesta;
										posicionSeleccionada = findPassenger(arrayPasengers, ELEMENTS, respuesta);
										printf("\nId\t\tApellido\tNombre\t\tPrecio\t\tFlycode\t\tTipo de Pasajero\tStatus Flight\n");
										printUnPassenger(arrayPasengers[posicionSeleccionada]);
										if(!getNumero(&respuesta, "Desea confirmar la baja del pasajero(1-SI 2-NO): \n",
													"Ingreso Incorrecto\n", 1, 2, 3))
										{
											switch(respuesta)
											{
												case 1:
													if(!removePassenger(arrayPasengers, ELEMENTS, idParaBaja))
													{
														printf("Se ha dado de baja correctamente\n");
													}
													break;
												case 2:
													printf("No se dio de baja\n");
													break;										}
										}
									}
								}
					}else
					{
						printf("Aun no se realizo ninguna carga\n");
					}
						break;
				case 4:
					if(flagCarga == 1)
					{
						printPassengers(arrayPasengers, ELEMENTS);
						do{
							if(!getNumero(&respuesta, "1) arrayPasengersr Alfabeticamente\n2) Promedio de precios\n3) arrayPasengersr por codigo de vuelo\n4) Volver al menu principal\n"
														"Seleccione el tipo de informe: \n", "Numero no valido\n" , 1, 4, 3))
								switch(respuesta)
								{
									case 1:
										sortPassenger(arrayPasengers, ELEMENTS, 1);
										printPassengers(arrayPasengers, ELEMENTS);
										respuesta = 0;
										break;
									case 2:
										promedioPasajes(arrayPasengers, ELEMENTS);
										break;
									case 3:
										sortPassengersByCode(arrayPasengers, ELEMENTS, 1);
										printPassengersStatus(arrayPasengers, ELEMENTS);
										break;
									case 4:
										printf("Volviendo al menu principal\n");
										break;
								}
							}while(respuesta != 4);
					}else
					{
						printf("Aun no se realizo ninguna carga\n");
					}
					break;
				case 5:
					flagCarga = 1;
					arrayPasengers[0].id = 1000;
					strcpy(arrayPasengers[0].name,"Juan");
					strcpy(arrayPasengers[0].lastName,"Gomez");
					arrayPasengers[0].price = 59850.25;
					strcpy(arrayPasengers[0].flyCode,"AAX");
					arrayPasengers[0].typePassenger = 1;
					arrayPasengers[0].isEmpty = 0;
					arrayPasengers[0].statusFlight = 1;
					arrayPasengers[1].id = 1001;
					strcpy(arrayPasengers[1].name,"Camila");
					strcpy(arrayPasengers[1].lastName,"Martin");
					arrayPasengers[1].price = 25200.65;
					strcpy(arrayPasengers[1].flyCode,"AAC");
					arrayPasengers[1].typePassenger = 2;
					arrayPasengers[1].isEmpty = 0;
					arrayPasengers[1].statusFlight = 1;
					arrayPasengers[2].id = 1002;
					strcpy(arrayPasengers[2].name,"Roberto");
					strcpy(arrayPasengers[2].lastName,"Alvarez");
					arrayPasengers[2].price = 62500.25;
					strcpy(arrayPasengers[2].flyCode,"BSQ");
					arrayPasengers[2].typePassenger = 2;
					arrayPasengers[2].isEmpty = 0;
					arrayPasengers[2].statusFlight = 3;
					arrayPasengers[3].id = 1003;
					strcpy(arrayPasengers[3].name,"Candela");
					strcpy(arrayPasengers[3].lastName,"Gimenez");
					arrayPasengers[3].price = 25200.65;
					strcpy(arrayPasengers[3].flyCode,"GSR");
					arrayPasengers[3].typePassenger = 3;
					arrayPasengers[3].isEmpty = 0;
					arrayPasengers[3].statusFlight = 2;
					arrayPasengers[4].id = 1004;
					strcpy(arrayPasengers[4].name,"Lucas");
					strcpy(arrayPasengers[4].lastName,"Alvarez");
					arrayPasengers[4].price = 45213.78;
					strcpy(arrayPasengers[4].flyCode,"GSR");
					arrayPasengers[4].typePassenger = 1;
					arrayPasengers[4].isEmpty = 0;
					arrayPasengers[4].statusFlight = 1;
					break;
				case 6:
					printf("Ha salido con exito...");
					break;

			}
		}

	}while(respuesta != 6);



	return EXIT_SUCCESS;
}
*/
