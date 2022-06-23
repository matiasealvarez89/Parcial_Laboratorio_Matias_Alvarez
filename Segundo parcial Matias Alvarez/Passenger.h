#ifndef PASSENGER_H_
#define PASSENGER_H_

#include "LinkedList.h"

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	int tipoPasajero;
	char codigoVuelo[8];
	int flightStatus;

}Passenger;

void Passenger_initArray(Passenger** arrayPassenger, int len);

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nombreStr, char* apellidoStr, char* precioStr, char* tipoPasajeroStr, char* codigoVueloStr, char* flightStatusStr);

int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setFlightStatus(Passenger* this, int flightStatus);
int Passenger_getFlightStatus(Passenger* this, int* flightStatus);

int Passenger_setAll(Passenger* this, int id, char* nombre, char* apellido, float precio, int tipoPasajero, char* codigoVuelo, int flightStatus);
int Passenger_getAll(Passenger* this, int* id, char* nombre, char* apellido, float* precio, int* tipoPasajero, char* codigoVuelo, int* flightStatus);
void Passenger_delete(Passenger* this);
int Passenger_compareByApellido(void* pasajeroUno, void* pasajeroDos);
int Passenger_compareByPrecio(void* pasajeroUno, void* pasajeroDos);
int Passenger_compareById(void* pasajeroUno, void* pasajeroDos);

void Passenger_printUnPassenger(Passenger* this);

Passenger* Passenger_addPassenger(int idNuevoPassenger);
int Passenger_edit(Passenger* pPasajeroAEditar);
int Passenger_findById(LinkedList* pArrayaPasajero, int id);


#endif /* PASSENGER_H_ */
