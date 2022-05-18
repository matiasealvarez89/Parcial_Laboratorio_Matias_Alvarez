#ifndef PASSENGER_H_
#define PASSENGER_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flyCode[10];
	int typePassenger;
	int isEmpty;
	int statusFlight;

}Passenger;

int initPassenger(Passenger* list, int len);
void printUnPassenger(Passenger unPassenger);
int addPassenger(Passenger* list, int len, int id, char name[], char lastName[], float price,int typePassenger, char flyCode[],int indexint);
int	findPassenger(Passenger* list, int len, int id);
int removePassenger(Passenger* list, int len, int id);
int sortPassenger(Passenger* list, int lista, int order);
int printPassengers(Passenger* list, int len);
int sortPassengersByCode(Passenger* list, int len, int order);
int primerEspacioLibre(Passenger* list, int len);
int promedioPasajes(Passenger* list, int len);
int printPassengersStatus(Passenger* list, int len);

#endif /* PASSENGER_H_ */
