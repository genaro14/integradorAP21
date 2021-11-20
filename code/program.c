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
#include<unistd.h>

#define Max 1000
typedef char TElem[100];

typedef struct {
	char nombre[30];
	int dni;
	int edad; //(1..80)
	int borrado; 
}TPersona;

typedef struct {
	char nombre[30];
	int dni;
	int edad; //(1..80)
}TPers;

typedef struct {
	TPers info[Max];
	int cant; // (0..Max)
}TData;

typedef struct nodo {
	 TPers info[Max];
	struct nodo *next;
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
int InsertarAlFinal(TData *per);

/* Accion SuprimirNombre */
void SuprimirPersona(TData *nom);

/* Accion Mostrar */
void Mostrar(TData nom);

/* Accion Cargar desde archivo */
void Cargar(TData *per, FILE *g);

/* Acción Guardar en el archivo */
void Guardar (TData per, FILE *f);

/* Acción CargaALista, modulo de la funcon ListaMenores*/
void CargarALista (TData per,int i/*(0...max)*/,TNodo *aux);

/* Accion Opciones */
void opciones(void);

// Intercambio de var
void Swap(int x, int y, TData *per);

//SANITY CHECK
int SanityCheck() ;
//MENU
int Menu(void);


int main() {	
	if(SanityCheck()){
		Cargar(&soporte,g);
		Menu();
	} else{
		exit(1);
	}
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
			(*per).cant = (*per).cant+1;
			strcpy((*per).info[(*per).cant-1].nombre, nuevoNombre);
			printf("El nombre: *%s*", ((*per).info[(*per).cant-1].nombre));
			printf("Fue insertado con exito\n");
		}
}

void SuprimirPersona(TData *per) {
	//Inicio de la accion
	if (Vacia(soporte))
		{ 
			printf("No se puede suprimir ningun nombre, porque el arreglo esta vacio \n");
		} else { //falta cant=1
			strcpy(per->info[0].nombre, per->info[per->cant-1].nombre);
			per->info[0].dni = per->info[per->cant-1].dni;
			per->info[0].edad = per->info[per->cant-1].edad;
			per->cant = per->cant - 1;
			printf("Información suprimida con éxito \n" );
		}
}

void Mostrar(TData per){
	//Inicio de la accion
	// TEST & DEBUG// 
	printf("cant: %d \n",per.cant);
	for (int i = 0; i < per.cant; ++i)
	{
		printf("Nombre: %s \n", per.info[i].nombre);
		printf("DNI: %d \n", per.info[i].dni);
		printf("Edad: %d \n", per.info[i].edad);
	}
	
}

void Cargar (TData *per, FILE *g){
	//lexico local
	TPersona aux;
	int i=0;
	//inicio de la accion
	if ((g = fopen("personas.dat","rb")) == NULL){
       printf("Archivo vacío");
	   exit;
   	}

   	while(fread(&aux, sizeof(TPersona), 1, g) > 0) {    
		// DEBUG & TEST //printf("nombre: %s\t dni: %d\tedad: %d\t borrado: %d\n", aux.nombre, aux.dni, aux.edad, aux.borrado);
		if (aux.borrado == 0){
    	strcpy ((*per).info[i].nombre, aux.nombre);
		(*per).info[i].edad = aux.edad;
		(*per).info[i].dni = aux.dni;
		++i;
		} 
   }
	per->cant = i;
	// DEBUG & TEST //printf("cant: %d\n",per->cant);
	fclose(g);
}

void Guardar(TData per, FILE* f){
	//Lexico Local
	int i = 0;
	TPersona aux;
	//Inicio
	if ((f = fopen("personas.dat","w")) == NULL){
       printf("Error! opening file");
	   exit;
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
	stpcpy(x->info->nombre, per.info[i].nombre);
	x->info->edad = per.info[i].edad;;
	x->info->dni = per.info[i].dni;;
	x->next = aux;
	aux = x;
}	


void Swap(int x, int y, TData *per){
TPers temp;
temp = per->info[x];
per->info[x] = per->info[y];
per->info[y] = temp;
// strcpy(temp.nombre, per->info[x]->nombre);
// temp.edad = per->info[x]->edad;
// temp.dni = per->info[x]->dni;

}
/* ORDENAMIENTO BURBUJA POR DNI*/
void OrdBurbuja(TData *per){
	//Lexico Local
	int i, j, term;

	//Inicio
	i = (*per).cant - 1;
	term = 1;
	while(i > 0 && term!= 0){
		j = 0;
		term = 0;
		while(j < i) {
			if ((*per).info[j].dni > (*per).info[j+1].dni)
			{
				Swap(j, j+1, per);
				term = ++term;
			}
			j = ++j;

		}
		i = i - 1;
	}
}
int Menu(void){
	salir = false;
	while(!salir){
		system("clear||cls");
		opciones();
		scanf("%d", &seleccion);

		while(seleccion < 1 || seleccion > 4 ){
			system("clear||cls");
			printf("No existe ninguna operacion con ese numero.");
			opciones();
			scanf("%d", &seleccion);
		}
		if (seleccion == 1)
		{
			InsertarAlFinal(&soporte);
		} else {
			if (seleccion == 2)
			{
				SuprimirPersona(&soporte);
			} else {
				if (seleccion == 3)
				{
					Mostrar(soporte);
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
}
int SanityCheck() {	
	char *filename = "personas.dat";
	 if( access( filename, F_OK ) == 0){ 
        printf("%s ,Archivo encontrado \n",filename);   
        return 1;
	}else if( access( filename, F_OK ) == -1) {
		printf("El archivo  %s no existe, no puede continuar \n", filename);
		return 0;
	} 
} // END SANITY CHECK