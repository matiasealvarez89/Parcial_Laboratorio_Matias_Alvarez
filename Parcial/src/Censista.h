#ifndef CENSISTA_H_
#define CENSISTA_H_

typedef struct
{
	int dia;
	int mes;
	int anio;
}fecha;

typedef struct
{
	char nombreCalle[50];
	int altura;
	int piso;
	int departamento;
}direccion;

typedef struct
{
	int idCensista;
	int isEmpty;
	int estado;
	char nombre[50];
	char apellido[50];
	fecha fechaDeNacimiento;
	int edad;
	direccion domicilio;
}Censista;

int initCensista(Censista* list, int len);
int primerEspacioLibre(Censista* list, int len);
int addCensista(Censista* list, int len);
int printCensistas(Censista* list, int len);
void printUnCensista(Censista unCensista);
int modificarCensista(Censista* list, int len, int id);
int findCensista(Censista* list, int len, int id);
int removeCensista(Censista* list, int len, int id);
int hardcodeoCensistas(Censista* list, int len);

#endif /* CENSISTA_H_ */
