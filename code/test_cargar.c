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

int main() {
int n; 
   FILE *fptr;
    TPersona test;
      if ((fptr = fopen("personas.dat","r")) == NULL){
       printf("Error! opening file");
   }
   while(fscanf(fptr) != NULL) {    
    fread(&test, sizeof(TPersona), 1, fptr); 
    printf("nombre: %s\t dni: %d\tedad: %d\n borrado: %d \n", test.nombre, test.dni, test.edad, test.borrado);
   }
	fclose(fptr);
}


