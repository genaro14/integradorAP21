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
#include <unistd.h>
#if defined(_WIN32) || defined (_WIN64)
   #include <windows.h> 
   #define VENTANAS 1
# elif __unix__ 
	#define VENTANAS 0
#endif
#define P_archivo "personas.dat" // Archivo Original
//#define P_archivo "../files/ArchivoVacio/personas.dat" // Archivo Vacio
//#define P_archivo "../files/MayoresDeMismaEdad/personas.dat" // Mayores de Misma Edad
//#define P_archivo "../files/TodosBorradosLogicos/personas.dat" // Todos Borrados Logicos
//#define P_archivo "../files/tresMayoresAlPrimero/personas.dat" // Tres Mayores al primero



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

TData soporte;		//arreglo pasado como parametro en el menu
FILE *g; 			//nombre interno que se le dará al archivo Personas.dat en la carga al arreglo

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

/* Acción CargaALista, modulo de la funcion ListaMenores*/
void CargarALista (TData per,int i/*(0...max)*/,TNodo **aux);

/* Funcion Recursiva que crea una lista con los menores de Edad*/
TNodo* ListaMenores(TData per, int cant, TNodo *lis);

/* Accion que muestra la lista creada con la funcion "ListaMenores" */
void MostrarMenores(TNodo *lis);

/* Accion Intercambiar (utilizada en "OrdenarDni") */ 
void Swap(int x, int y, TData *per);

/* Accion Ordenar El Arreglo Por DNI */
void OrdenarDNI (TData *per);

/* Accion Busqueda Dicotomica de DNI*/
void BusquedaDNI(TData per, int dni);

/* Funcion indica si hay 3 personas mayores a la primera */
int mayoresQueElPrimero(TData per);


/* Funcion Recurviva indica la persona mayor del arreglo */
TPers edadMayor(TData per, int cant, TPers aux);

/* Accion Opciones */
void opciones(void);

/* Menu  */
void Menu(TData personas);

/* SANITY CHECK */
int SanityCheck();

/* Funcion de pausa independiente del SO*/
void pausa();

//Inicio
int main() {	
	if(SanityCheck()){
		Cargar(&soporte,g);
		Menu(soporte);
	} else{
		exit(1);
	}
	return 0;
}
//Fin

//Parte del Inciso M
/* Accion Que Muestra las Opciones del Menu */
void opciones(void) {
	printf("\t\tMENU de Opciones\n");
   	printf("\t\t----------------\n\n");
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

//Inciso A
/* Funcion Informa Si EL Arreglo esta Vacio */
int Vacia(TData per){
	//Inicio De La Funcion
	if (per.cant == 0)
	{
		return(1);
	} else {
		return(0);
	}
}

//Inciso B
/* Funcion Informa Si EL Arreglo esta Lleno */
int Llena(TData per){
	//Inicio De La Funcion
	if (per.cant == Max) {
		return(1);
	} else {
		return(0);
	}
}

//Inciso C
/* Accion Agrega Informacion de una Persona Al Final Del Arreglo */
int InsertarAlFinal(TData *per) {
	//Lexico local
	TPers persona;
	char cleanBuffer[2];
	//Inicio de la funcion
		if (Llena(*per) ) {
			printf("No es posible insertar el nuevo nombre ya que el arreglo esta lleno \n\n");
		} else {
			printf("Ingresa el nombre que quieres insertar: ");
			fgets(cleanBuffer,sizeof cleanBuffer,stdin);// Limpia Buffer
			fgets(persona.nombre,30,stdin);
			int size = strlen(persona.nombre); //Total size of string persona.nombre
			persona.nombre[size-1] = '\0'; // Replace '\n' for '\0', line Ending
			printf("Ingresa la edad: ");
			scanf("%d", &persona.edad);
			while(persona.edad < 1 || persona.edad > 80){
				printf("Vuelve a Ingresar la edad: ");
				scanf("%d", &persona.edad);
			}
			printf("Ingresa El DNI: ");
			scanf("%d", &persona.dni);
			(*per).cant = (*per).cant+1;
			(*per).info[(*per).cant-1] = persona;
			//strcpy((*per).info[(*per).cant-1].nombre, persona.nombre);
			//(*per).info[(*per).cant-1].edad = persona.edad;
			//(*per).info[(*per).cant-1].dni = persona.dni;
			printf("La Persona Fue insertado con Exito\n\n");
		}
}

//Inciso D
/* Accion Suprime Primera Persona Del Arreglo */
void SuprimirPersona(TData *per) {
	//Inicio de la accion
	if (Vacia(*per))
		{ 
			printf("No se puede suprimir ningun nombre, porque el arreglo esta vacio \n\n");
		} else {
			if ((*per).cant > 1)
			{
			
				strcpy(per->info[0].nombre, per->info[per->cant-1].nombre);
				per->info[0].dni = per->info[per->cant-1].dni;
				per->info[0].edad = per->info[per->cant-1].edad;
				per->cant = per->cant - 1;
				printf("Informacion suprimida con Exito.\n\n" );
			} else {
				per->cant = per->cant - 1;			//Si per.cant = 1 se quedara en 0
			}
		}
}

//Inciso E
/* Accion Mostrar El Arreglo */
void Mostrar(TData per){
	int i;
	//Inicio de la accion
	// TEST & DEBUG// 
	printf("Cantidad de cargados: %d \n\n",per.cant);
	for (int i = 0; i < per.cant; ++i)
	{
		printf("Nombre: %s \n", per.info[i].nombre);
		printf("DNI: %d \n", per.info[i].dni);
		printf("Edad: %d \n\n", per.info[i].edad);
	}	
}

//Inciso G
/* Accion Cargar Arreglo */
void Cargar (TData *per, FILE *g){
	//lexico local
	TPersona aux;
	int i=0;
	//inicio de la accion
	if ((g = fopen(P_archivo,"rb")) == NULL){
       printf("Archivo vacío");
	   exit;
   	}

   	while((fread(&aux, sizeof(TPersona), 1, g) > 0) && i<Max) {    
		// TEST & DEBUG 
		//printf("nombre: %s\t dni: %d\tedad: %d\t borrado: %d\n", aux.nombre, aux.dni, aux.edad, aux.borrado);
		if (aux.borrado == 0){
    	strcpy ((*per).info[i].nombre, aux.nombre);
		(*per).info[i].edad = aux.edad;
		(*per).info[i].dni = aux.dni;
		++i;
		} 
   }
	per->cant = i;
	// TEST & DEBUG //printf("cant: %d\n",per->cant);
	fclose(g);
}


//Inciso H
/* Accion Guardar Arreglo en el Archivo */
void Guardar(TData per, FILE* f){
	//Lexico Local
	int i = 0;
	TPersona aux;
	//Inicio
	if ((f = fopen(P_archivo,"w")) == NULL){
       printf("Error! opening file");
	   exit;
   	}
	//TEST & DEBUG //
	printf("cant: %d \n", per.cant);
	while(i < per.cant){
		strcpy(aux.nombre, per.info[i].nombre);
		aux.edad = per.info[i].edad;
		aux.dni = per.info[i].dni;
		aux.borrado = 0;
		fwrite(&aux,sizeof(TPersona),1,f);
		//fflush(stdin); //limpia buffer
		//TEST & DEBUG //
		printf("i: %d \n", i);
		i++;
	}
	fclose(f);
}

/* Accion Que Permite la carga de la informacion de los menores a la cabeza de la lista*/
void CargarALista (TData per,int i,TNodo **aux){
	//lexico local
	TNodo *x;
	//inicio de la accion
	x = (TNodo *) malloc (sizeof(TNodo));
	strcpy(x->info->nombre, per.info[i].nombre);
	x->info->edad = per.info[i].edad;;
	x->info->dni = per.info[i].dni;;
	x->next = (*aux);
	(*aux) = x;
}

//Inciso I
/* Funcion recursiva que crea una lista con la informacion de los menores de edad*/
TNodo* ListaMenores(TData per, int cant, TNodo *lis){
	//Inicio	
	if (cant == 0)			//caso base
	{
		return(lis);
	} else {
		if (cant > 0)		//etapa inductiva
		{
			if (per.info[cant-1].edad < 18)
			{
				CargarALista(per, cant-1, &lis);
				return(ListaMenores(per,cant-1, lis));
			} else {
				return(ListaMenores(per,cant-1, lis));
			}
		}
	}

}


/* Accion que informa por pantalla la lista formada por los menores de edad*/
void MostrarMenores(TNodo *lis){
	//Lexico Local
	//Inicio
	if (lis == NULL)
	{
		printf("No existen menores de edad en la lista. \n\n");
	}else{
		if (lis != NULL)
		{
			printf("Lista de los menores de Edad: \n\n");
			while(lis != NULL){
				printf("\t* Nombre: %s\n",(*lis).info->nombre);   //printf("%s\n",lis->info->nombre);
				printf("\t* Edad: %d\n",(*lis).info->edad); 	 //printf("%d\n",lis->info->edad);
				printf("\t* DNI: %d\n\n\n",(*lis).info->dni);     //printf("%d\n",lis->info->dni);
				lis = lis->next;

			};
		}
	}
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

//Inciso J
/* ORDENAMIENTO BURBUJA POR DNI*/
void OrdenarDNI (TData *per){
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

/* Busqueda Dicotomica de un DNI */ 
void BusquedaDNI(TData per, int dni){
	//Lexico Local
	int k, inf, sup;
	//Inicio
	if (dni < per.info[0].dni || dni > per.info[per.cant-1].dni)
	{
		printf("No existe ninguna persona con ese DNI.\n\n");
	}else{
		if (per.info[0].dni <= dni && dni <= per.info[per.cant-1].dni)
		{
			inf = 0;
			sup = per.cant-1;
			while(inf < sup){
				k = (inf+sup)/2;
				if (dni > per.info[k].dni)
				{
					inf = k+1;
				} else {
					if (dni <= per.info[k].dni)
					{
						sup = k;
					}
				}
			};
			if (per.info[inf].dni == dni)
			{
				printf("\n\n Se ha encontrado la persona con ese DNI:\n\n");
				printf("\t* Nombre: %s\n",per.info[inf].nombre);
				printf("\t* Edad: %d\n",per.info[inf].edad);
				printf("\t* DNI: %d\n",per.info[inf].dni);
			} else {

				printf("No se ha encontrado a la persona con ese DNI.\n\n");
			}
		}
	}
}

//INCISO K
/* Funcion que informa si existen al menos 3 personas mayores que el primero */
int mayoresQueElPrimero(TData per){
	//Lexico Local
	int i, cantMayor, edad, pri;
	//Inicio
	i = 0;
	cantMayor = 0;
	pri = per.info[i].edad;
	i = ++i;
	while(i<per.cant && cantMayor<3){
		if (per.info[i].edad > pri)
		{
			cantMayor = cantMayor+1;
		}
		i = ++i;
	}
	if (i<per.cant)
	{
		return(1);
	} else {
		if (i = per.cant)
		{
			if (cantMayor < 3)
			{
				return(0);
			} else {
				return(1);
			}
		}
	}

}


//Inciso L
TPers edadMayor(TData per, int cant, TPers aux){
	//Inicio
	if (cant == 0)				//caso base
	{
		return(aux);
	} else {
		if (cant > 0)			//Etapa Inductiva
		{
			if (aux.edad < per.info[cant].edad)
			{
				strcpy(aux.nombre, per.info[cant].nombre);
				aux.dni = per.info[cant].dni;
				aux.edad = per.info[cant].edad;
			}
			return(edadMayor(per,cant-1,aux));
		}
	}
}

//Inciso M
void Menu(TData personas){
	//Lexico
	char msg[150];			//variable que utilizaremos para informar mensajes
	int selec;				//Variable utilizada para la selección de opciones
	TNodo *listaM;			//variable que utilizada para lista de menores de edad
	bool term;				//variable utilizada para salir del ciclo
	int dni;				//variable utilizada para la entrada del DNI a buscar
	TPers mostrarPersona;	//variable utilizada para mostrar la información de la persona mayor
	FILE *f;				//nombre interno que se le dará al archivo Personas.dat
	int cantMayores;
	int salir;
	//Inicio
	term = false; 
	while(!term){
		
		opciones();
		scanf("%d", &selec);
		while(selec < 0 || selec > 7 ){
			system("clear||cls");
			printf("No existe ninguna operacion con ese numero. \n");
			opciones();
			scanf("%d", &selec);
		}
		if (selec == 1)
		{
			system("clear||cls");
			// TEST & DEBUG //
			printf("Has Seleccionado *Insertar Al Final* \n\n");		
			InsertarAlFinal(&personas);
			pausa();
			system("clear||cls");
		} 
		else if (selec == 2)
			{
			system("clear||cls");
			// TEST & DEBUG //
			printf("Has Seleccionado *Suprimir el Primero* \n\n");		
			SuprimirPersona(&personas);
			pausa();
			system("clear||cls");
			} 
		else if (selec == 3)
			{	
				system("clear||cls");
				// TEST & DEBUG //
				if (!Vacia(personas)){
					Mostrar(personas);
				} else {
					printf("No se puede Mostrar nada ya que El Arreglo Esta Vacio");
				}
				pausa();
				system("clear||cls");
			} 
		else if (selec == 4)
			{
				system("clear||cls");
				// TEST & DEBUG //
				printf("Has Seleccionado *Mostrar Menores* \n\n");	
				if (!Vacia(personas)) 
				{
					listaM = NULL;
					listaM = ListaMenores(personas, personas.cant, listaM);
					MostrarMenores(listaM);
				} else 
				{
					strcpy(msg, "El Arreglo esta vacio \n");
					printf("%s", msg);
				}
				pausa();
				system("clear||cls");
			}
		else if (selec == 5)
		{
			system("clear||cls");
				//OrdenarDNI(personas);
				// TEST & DEBUG //
				printf("Has Seleccionado *Busqueda Por DNI* \n\n");
			if (!Vacia(personas)) 
			{	
				printf("Ingresa el DNI de la Persona: ");
				OrdenarDNI(&personas);
				scanf("%d",&dni);	
				BusquedaDNI(personas, dni);
			} else 
			{
				strcpy(msg, "El Arreglo esta vacio \n");
				printf("%s", msg);
			}
			pausa();
			system("clear||cls");
		}
		else if (selec == 6)
		{ 
			system("clear||cls");
			// TEST & DEBUG //
			printf("Has seleccionado *Mayores Al Primero* \n\n");
			if (!Vacia(personas)) 
			{
				cantMayores = mayoresQueElPrimero(personas);
				// TEST & DEBUG //
				if (cantMayores == 1){
					strcpy(msg,"Si existen 3 personas mayores al primer individuo del arreglo" );
				}else {
					strcpy(msg,"NO Existen 3 personas mayores al primer individuo del arreglo");
				}
				printf("%s \n\n",msg);

			} else 
			{
				strcpy(msg, "El Arreglo esta vacio \n");
				printf("%s", msg);
			}
			pausa();
			system("clear||cls");
		}
		else if (selec == 7)
		{
			system("clear||cls");
			// TEST & DEBUG //
			printf("EdadMayor \n");
			if (!Vacia(personas)) 
			{
				// TEST & DEBUG //
				mostrarPersona = edadMayor(personas,personas.cant-1,personas.info[0]);
				printf("Has Seleccionado *Edad Mayor* \n\n");
				printf("Nombre: %s\n", mostrarPersona.nombre);
				printf("dni %d\n", mostrarPersona.dni);
				printf("edad %d\n", mostrarPersona.edad);
			} else 
			{
				strcpy(msg, "El Arreglo esta vacio \n");
				printf("%s", msg);
			}
			pausa();
			system("clear||cls");
		}
		else if (selec == 0)
		{
			system("clear||cls");
			// TEST & DEBUG //
			if (!Vacia(personas)) 
			{
			Guardar(personas,g);
			term = true;
			} else 
			{
				strcpy(msg, "El Arreglo esta vacio, seguro que quiere guardar?\n Presiona [1] Si [2] No\n\n Opcion: ");
				printf("%s", msg);
				scanf("%d", &salir);
				while(salir != 1 && salir != 2){
					strcpy(msg, "La Opcion No es VALIDA!\n\nEl Arreglo esta vacio, seguro que quiere guardar?\n Presiona [1] Si [2] No\n\n Opcion: ");
					printf("%s", msg);
					scanf("%d", &salir);
				}
				system("clear||cls");
				if (salir == 1)
				{
					Guardar(personas,g);
					term = true;
				}

			}
		}
		
		// else if (selec > 7 || selec < 0)
		// {
		// 	printf("Si quiere SALIR presione [1], para volver al MENU Presione [Cualquier Otro Numero]");
		// 	scanf("%d", &volver);
		// 	if (volver == 1)
		// 	{
		// 		term  =true;
		// 	}
		// }
	};
	
}

int SanityCheck() {	

	char *filename = P_archivo;
	 if( access( filename, F_OK ) == 0){  
        return 1;
	}else if( access( filename, F_OK ) == -1) {
		printf("El archivo  %s no existe, no puede continuar \n", filename);
		pausa();
		return 0;
	} 
} // END SANITY CHECK


void pausa(){
	if(VENTANAS	) {
		system("pause");
	}
	else {
		while ( getchar() != '\n');
		while ( getchar() != '\n');
	}
}
