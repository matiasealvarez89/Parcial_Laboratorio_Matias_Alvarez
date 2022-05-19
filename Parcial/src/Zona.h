#ifndef ZONA_H_
#define ZONA_H_

#include "Censista.h"

typedef struct
{
	int idZona;
	int isEmpty;
	char calles[4][20];
	int localidad;
	int idCensista;
	int cantidadCensados;
	int cantidadCensadosDigital;
	int cantidadAusentes;
	int estado;
}Zona;

int primerEspacioLibreZona(Zona* list, int len);
int addZona(Zona* list, int len);
int initZona(Zona* list, int len);
int printZonas(Zona* list, int len,  Censista* listCensistas);
void printUnaZona(Zona unaZona, Censista* listCensistas, int len);
int findZona(Zona* list, int len, int id);
int cargarDatosZona(Zona* list, int len, int id);

#endif /* ZONA_H_ */
