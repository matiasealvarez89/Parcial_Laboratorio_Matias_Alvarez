#ifndef ZONA_H_
#define ZONA_H_

typedef struct
{
	int idZona;
	int isEmpty;
	int calles[4];
	int localidad;
	int idCensista;
	int cantidadCensados;
	int cantidadCensadosDigital;
	int cantidadAusentes;
	int estado;
}Zona;

#endif /* ZONA_H_ */
