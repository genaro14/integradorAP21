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
}TPersona;

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
FILE *g;
FILE *f;

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

/* Accion Cargar desde archivo */
void Cargar(TData *per, FILE g);

/* Acción Guardar en el archivo */
void Guardar (TData *per, FILE f);

/* Acción CargaALista, modulo de la funcon ListaMenores*/
void CargarALista (TData per,int i/*(0...max)*/,TNodo *aux);

/* Accion Opciones */
void opciones(void);
void Swap();
//Inicio del algoritmo
int main()
{
	salir = false;
	while(!salir){
		system("cls");
		opciones();
		scanf("%d", &seleccion);

		while(seleccion < 1 || seleccion > 4 ){
			system("cls");
			printf("No existe ninguna operacion con ese numero.");
			opciones();
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

void opciones(void) {
	printf("MENU DE OPCIONES \n");
	printf("------------------\n");
	printf("[1] Insetar al final \n");
	printf("[2] Suprimir el primero \n");
	printf("[3] Mostrar todos \n");
	printf("[4] Mostrar Menores \n");
	printf("[5] Buscar por DNI \n");
	printf("[6] Mayores Al Primero \n");
	printf("[7] Edad Mayor \n");
	printf("[0] Salir y Guardar \n " );
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

void Cargar (TData *per, FILE *g){
	//lexico local
	TPersona aux;
	int i=0;
	//inicio de la accion
	if ((g = fopen("personas.dat","rb")) == NULL){
       printf("Error! opening file");
	   break;
   	}

   	while(!feof(g)) {    
    	fread(&aux, sizeof(TPersona), 1, g); 
		if (aux.borrado == 0){
    	strcpy ((*per).info[i].nombre, aux.nombre);
		(*per).info[i].edad = aux.edad;
		(*per).info[i].dni = aux.dni;
		i = i++;
		} //Bug Repite último
   }
	per->cant = i;
	fclose(g);
}

void Guardar(TData per, FILE* f){
	//Lexico Local
	int i = 0;
	TPersona aux;
	//Inicio
	if ((f = fopen("personas.dat","w")) == NULL){
       printf("Error! opening file");
	   break;
   	}

	while(i <= per.cant){

		strcpy(aux.nombre, per.info[i].nombre);
		aux.edad = per.info[i].edad;
		aux.dni = per.info[i].dni;
		aux.borrado = 0;
		fwrite(&aux,sizeof(TPersona),1,f);
		//fflush(stdin); //limpia buffer
		i = i++;
	}

	fclose(f);
}

void CargarALista (TData per,int i,TNodo *aux){
	//lexico local
	TNodo *x;
	//inicio de la accion
	x = (TNodo *) malloc (sizeof(TNodo));
	stcpy((*x).info.nombre, per.info[i].nombre);
	(*x).info.edad = per.info[i].edad;;
	(*x).info.dni = per.info[i].dni;;
	(*x).next = aux;
	aux = x;
}	

// hacer swap

/* ORDENAMIENTO BURBUJA POR DNI*/
void OrdBurbuja(TData *per){
	//Lexico Local
	int i, j, term;

	//Inicio
	i = (*pers).cant - 1;
	term = 1;
	while(i > 0 && term!= 0){
		j = 0;
		term = 0;
		while(j < i) {
			if ((*pers).info[j].dni > (*pers).info[j+1].dni)
			{
				Swap(j, j+, &(*per));
				term = ++term;
			}
			j = ++j;

		}
		i = i - 1;
	}
}