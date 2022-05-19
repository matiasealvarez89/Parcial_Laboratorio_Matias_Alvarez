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


void informeA(Censista* listCensista, Zona* listZona, int len)
{

	int indexZona;

	if(listCensista != NULL && listZona != NULL && len > 0)
	{
		printf("\nId\t\tEstado\t\tApellido\tNombre\t\tFecha de Nacimiento\t\tEdad\t\tDomicilio\t\n");
		for(int i = 0; i < len; i++)
		{
			if(listCensista[i].estado == 1)
			{
				indexZona= findZonaPorIdCensista(listZona, len, listCensista[i].idCensista);
				if(listZona[indexZona].estado == 1)
				{
					printUnCensista(listCensista[i]);
				}

			}
		}
	}


}

void informeC(Zona* list, int len)
{
	int localidadMaximo;
	int acumuladorUno = 0;
	int acumuladorDos = 0;
	int acumuladortres = 0;
	int acumuladorCuatro = 0;
	int acumuladorCinco = 0;
	char textoLocalidad[20];

	if(list != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			switch(list[i].localidad)
			{
				case 1:
					acumuladorUno += list[i].cantidadAusentes;
					break;
				case 2:
					acumuladorDos += list[i].cantidadAusentes;
					break;
				case 3:
					acumuladortres += list[i].cantidadAusentes;
					break;
				case 4:
					acumuladorCuatro += list[i].cantidadAusentes;
					break;
				case 5:
					acumuladorCinco += list[i].cantidadAusentes;
					break;
			}
		}

		if(acumuladorUno > acumuladorDos && acumuladorUno > acumuladortres && acumuladorUno > acumuladorCuatro && acumuladorUno > acumuladorCinco)
		{
			localidadMaximo = 1;
		}

		if(acumuladorDos > acumuladorUno && acumuladorDos > acumuladortres && acumuladorDos > acumuladorCuatro && acumuladorDos > acumuladorCinco)
		{
			localidadMaximo = 2;
		}

		if(acumuladortres > acumuladorUno && acumuladortres > acumuladorDos && acumuladortres > acumuladorCuatro && acumuladortres > acumuladorCinco)
		{
			localidadMaximo = 3;
		}

		if(acumuladorCuatro > acumuladorUno && acumuladorCuatro > acumuladorDos && acumuladorCuatro > acumuladortres && acumuladorCuatro > acumuladorCinco)
		{
			localidadMaximo = 4;
		}

		if(acumuladorCinco > acumuladorUno && acumuladorCinco > acumuladorDos && acumuladorCinco > acumuladortres && acumuladorCinco > acumuladorCuatro)
		{
			localidadMaximo = 5;
		}

		switch(localidadMaximo)
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

		printf("La localidad con mayor cantidad de ausentes es %s\n\n", textoLocalidad);

	}
}

void informeD(Censista* listCensista, Zona* listZona, int len)
{
	int maximo = 0;
	int idCensistaMaximo;


	if(listCensista != NULL && listZona != NULL && len > 0)
	{
		for(int i = 0; i < len; i++)
		{
			if(listZona[i].cantidadCensados + listZona[i].cantidadCensadosDigital > maximo)
			{
				maximo = listZona[i].cantidadCensados + listZona[i].cantidadCensadosDigital;
				idCensistaMaximo = listZona[i].idCensista;
			}
		}
		printf("El censista cuya zona fue la mas censada es el ID: %d\n\n", idCensistaMaximo);
	}
}


void informeB(Censista* list, int len)
{
	int retorno = -1;
	int i;
	Censista aux;
	int estaOrdenado;

	if (list != NULL && len > 0)
	{

		do {
			estaOrdenado = 1;
			len--;
			for (i = 0; i < len; i++)
			{
				if (list[i].isEmpty == OCUPADO && strcmp(list[i].apellido,list[i + 1].apellido) == 1)
				{
					aux = list[i];
					list[i] = list[i + 1];
					list[i + 1] = aux;
					estaOrdenado = 0;
				}

			}
		}while(estaOrdenado == 0);

		printCensistas(list, len);
	}
}


