#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Max 1000
typedef char TElem[100];

typedef struct 
{
	char nombre[30];
	int dni;
	int edad; //(1..80)
	int borrado; 
}TPersona;

typedef struct 
{
	char nombre[30];
	int dni;
	int edad; //(1..80)
}TPers;

//typedef TArreglo TPers[Max];

typedef struct
{
	TPers info[Max];
	int cant; // (0..Max)
}TData;
/* Accion Mostrar */
/* Accion Cargar desde archivo */
void Cargar(TData *per, FILE *g);

void Mostrar(TData nom);
//----------------------------------------------------------------


void Cargar (TData *per, FILE *g){
	//lexico local
	TPersona aux;
	int i=0;
	//inicio de la accion
	if ((g = fopen("personas.dat","rb")) == NULL){
       printf("Error al abrir archivo");
	   exit;
   	}

   	while(fread(&aux, sizeof(TPersona), 1, g) > 0) {    
		printf("nombre: %s\t dni: %d\tedad: %d\t borrado: %d\n", aux.nombre, aux.dni, aux.edad, aux.borrado);
		if (aux.borrado == 0){
    	strcpy ((*per).info[i].nombre, aux.nombre);
		(*per).info[i].edad = aux.edad;
		(*per).info[i].dni = aux.dni;
		++i;
		} 
   }
	per->cant = i;
	printf("cant: %d\n",per->cant);
	fclose(g);
}

void Mostrar(TData per){
	//Inicio de la accion
	for (int i = 0; i < per.cant; i++) {
		printf("Nombre: %s \n", per.info[i].nombre);
		printf("DNI: %d \n", per.info[i].dni);
		printf("Edad: %d \n", per.info[i].edad);
	}
	
}

int main() {
	TData test;
	FILE *h;
	Cargar(&test,h);
	Mostrar(test);
	return 0;
}


