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
}TPersona

typedef struct 
{
	char nombre[30];
	int dni;
	int edad; //(1..80)
}TPers

typedef TArreglo TPers[Max];


typedef struct
{
	TPers info[Max];
	int cant; // (0..Max)
}TData;

typedef struct
{
	TArreglo info[Max]
	TNodo *next
}TNodo;

TData soporte;
char nuevoName[100];

int volver,seleccion;
bool salir;



/* Accion Vacia */
int Vacia(TData nom);

/* Accion Llena */
int Llena(TData nom);

/* Accion InsertarAlFinal */
int InsertarAlFinal(TData *per)

/* Accion SuprimirNombre */
void SuprimirPersona(TData *nom);

	/* Accion Mostrar */
void Mostrar(TData nom);

/* Accion Menu */
void Menu(void);

//Inicio del algoritmo
int main()
{
	salir = false;
	while(!salir){
		system("cls");
		Menu();
		scanf("%d", &seleccion);

		while(seleccion < 1 || seleccion > 4 ){
			system("cls");
			printf("No existe ninguna operacion con ese numero.");
			Menu();
			scanf("%d", &seleccion);
		}
		if (seleccion == 1)
		{
			CargarNuevoNombre(&listaNombres);
		} else {
			if (seleccion == 2)
			{
				SuprimirPersona(&listaNombres);
			} else {
				if (seleccion == 3)
				{
					Mostrar(listaNombres);
				} else {
						salir =true;
					}
			}
		}

		if (seleccion != 4)
		{
			printf("Si quiere SALIR presione [1], para volver al MENU Presione [Cualquier Otro Numero]");
			scanf("%d", &volver);
			if (volver == 1)
			{
				salir =true;
			}
		}
	};
	return 0;
}
//Fin

void Menu(void) {
	printf("---------------------------------------------------------------------------------- \n");
	printf("Que quieres hacer? \n");
	printf("[1] Cargar Nuevo Nombre. \n");
	printf("[2] Suprimir el primer Nombre. \n");
	printf("[3] Mostrar lo que contiene el arreglo \n");
	printf("[4] Salir \n " );
	printf("*INGRESA AQUI EL NUMERO: ");
}

int Vacia(TData per){
	//Inicio De La Funcion
	if (per.cant == 0)
	{
		return(1);
	} else {
		return(0);
	}
}

int Llena(TData per){
	//Inicio De La Funcion
	if (per.cant == 1000) {
		return(1);
	} else {
		return(0);
	}
}

int InsertarAlFinal(TData *per) {
	//Lexico local
	TPers persona;
	char msg[100];
	char nuevoNombre[100];
	char cleanBuffer[2];
	//Inicio de la funcion
		if (Llena(*per) ) {
			printf("No es posible insertar el nuevo nombre ya que el arreglo esta lleno \n");
		} else {
			printf("Ingresa el nombre que quieres insertar: ");
			//scanf("%s", nuevoNombre); // Validar entrada de nombres, Cambiar por get
			fgets(cleanBuffer,sizeof cleanBuffer,stdin);// Limpia Buffer
			fgets(nuevoNombre,50,stdin);
			nom->cant = nom->cant+1;
			strcpy((*per).nombres[(*per).cant-1], nuevoNombre);
			printf("El nombre: *%s*", ((*per).nombres[(*per).cant-1]));
			printf("Fue insertado con exito\n");
		}
}

void SuprimirPersona(TData *per) {
	//Inicio de la accion
	if (Vacia(*per->info))
		{ 
			printf("No se puede suprimir ningun nombre, porque el arreglo esta vacio \n");
		} else {
			strcpy(per->nombres[0], nom->nombres[nom->cant]);
			per->cant = per->cant - 1;
			printf("Información suprimida con éxito \n" );
		}
}

void Mostrar(TData per){
	//Inicio de la accion
	for (int i = 0; i < per.cant; ++i)
	{
		printf("Nombre: %s \n", per.info[i].nombre);
		printf("DNI: %s \n", per.info[i].dni);
		printf("Edad: %s \n", per.info[i].edad);
	}
	
}
