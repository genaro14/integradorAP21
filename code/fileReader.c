/*
UNIVERSIDAD NACIONAL DE RÍO CUARTO
FACULTAD DE CS EXACTAS, FCO-QCAS Y NATURALES - DEPTO DE COMPUTACIÓN
INTRODUCCIÓN A LA ALGORÍTMICA Y PROGRAMACIÓN
Año: 2021
** PROYECTO FINAL **
ALUMNOS
BUCHIERI GIOVANNI 
GIACHERO GABRIEL
PENNONE GENARO
*/

#include <stdio.h>
#include <stdlib.h>

#define Max 1000
typedef char TElem[100];

typedef struct {
    char nombre[30];
    int dni;
    int edad;
    int borrado;
} TPersona;



int main() {
int n; 
   FILE *fptr;
    TPersona test;
      if ((fptr = fopen("personas.dat","rb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

    // attempt to read the next line and store 
    // the value in the "number" variable 
   for(n = 1; n < 10; ++n) {    
    fread(&test, sizeof(TPersona), 1, fptr); 
    printf("nombre: %s\t dni: %d\tedad: %d\n", test.nombre, test.dni, test.edad);
   }
    

 }
