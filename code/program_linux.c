#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Max 1000
typedef char TElem[100];
typedef struct {
	TElem nombres[Max];
	int cant;
}TData;

TData listaNombres;
char nuevoName[100];

int volver,seleccion, l;
bool salir;

	/* Accion Menu */
void Menu(void);

/* Accion CargarArreglo */
void CargarArreglo(TData *nom);

/* Accion Vacia */
bool Vacia(TData nom);

/* Accion Llena */
bool Llena(TData nom);

/* Accion Cargar Nuevo Nombre */
void CargarNuevoNombre(TData *nom);

	/* Accion SuprimirNombre */
void SuprimirNombre(TData *nom);

	/* Accion Mostrar */
void Mostrar(TData nom);


//Inicio del algoritmo
int main()
{
	char entrada;
	salir = false;
	while(!salir){
		system("clear");
		Menu();
		scanf("%c", &entrada); // Valida Entrada
		seleccion = atoi(&entrada);
		while(seleccion < 1 || seleccion > 5 ) {
			system("clear");
			printf("No existe ninguna operacion con ese numero.");
			Menu();
			scanf("%c", &entrada);// Valida Entrada
			printf("%c \n", entrada );
			seleccion = atoi(&entrada);
		}
		if (seleccion == 1) {
			CargarArreglo(&listaNombres);
		} else {
			if (seleccion == 2) {
				CargarNuevoNombre(&listaNombres);
			} else {
				if (seleccion == 3) {
					SuprimirNombre(&listaNombres);
				} else if(seleccion == 4) {
						Mostrar(listaNombres);
					}
					else if (seleccion == 5) {
						salir =true;
					}
			}
		}

		if (seleccion != 5)	{
			printf("Si quiere volver al MENU Presione [Cualquier Numero] * Si quiere SALIR presione [1]: ");
			scanf("%d", &volver);
			if (volver == 1) {
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
	printf("[1] Cargar Nuevo Arreglo. \n");
	printf("[2] Cargar Nuevo Nombre. \n");
	printf("[3] Suprimir el primer Nombre. \n");
	printf("[4] Mostrar lo que contiene el arreglo \n");
	printf("[5] Salir \n " );
	printf("*INGRESA AQUI EL NUMERO: ");
}

void CargarArreglo(TData *nom){
	//Lexico Local
	char cleanBuffer[2];
	//Inicio de la accion
	printf("Ingresa la cantidad de nombres: ");
	scanf("%d", &nom->cant);

	while(nom->cant < 0 || nom->cant > 1000){
		printf("La cantidad de nombres tiene que estar entre 0 y 1000, por favor ingrese nuevamente la cantidad: ");
		scanf("%d", &nom->cant);
	};
	fgets(cleanBuffer,sizeof cleanBuffer,stdin);// Limpia Buffer
	for (int i = 0; i < nom->cant; ++i)	{
		printf("Ingresa el (%d) nombre: ", i+1);
		//scanf("%s", nom->nombres[i]); // cambiar por get
		fgets((*nom).nombres[i],50,stdin);
	}
	printf("\n *Arreglo cargado con Exito*\n\n");
}

bool Vacia(TData nom){
	if (nom.cant == 0) {
		return true;
	} else {
		return false;
	}
}

bool Llena(TData nom){
	if (nom.cant == Max) {
		return true;
	} else {
		return false;
	}
}

void CargarNuevoNombre(TData *nom){
	//Lexico local
	char nuevoNombre[100];
	char cleanBuffer[2];
	//Inicio de la funcion
	if (nom->cant != 0) {
		if (Llena(*nom) ) {
			printf("No es posible insertar el nuevo nombre ya que el arreglo esta lleno \n");
		} else{
			printf("Ingresa el nombre que quieres insertar: ");
			//scanf("%s", nuevoNombre); // Validar entrada de nombres, Cambiar por get
			fgets(cleanBuffer,sizeof cleanBuffer,stdin);// Limpia Buffer
			fgets(nuevoNombre,50,stdin);
			nom->cant = nom->cant+1;
			strcpy((*nom).nombres[(*nom).cant-1], nuevoNombre);
			printf("El nombre: *%s*", ((*nom).nombres[(*nom).cant-1]));
			printf("Nuevo nombre insertado con exito\n");
		}
	} else {
		printf("Ingresa el  nombre que quieres insertar: ");
		fgets(cleanBuffer,sizeof cleanBuffer,stdin);// Limpia Buffer
		fgets(nuevoNombre,50,stdin);
		nom->cant = 1;
		strcpy(nom->nombres[nom->cant-1], nuevoNombre);// el arreglo comienza en 0
		printf("Nuevo nombre insertado con exito \n");
	}
}

void SuprimirNombre(TData *nom){
	//Inicio de la accion
	if (!Vacia(*nom)) {
			nom->cant = nom->cant - 1;
			strcpy(nom->nombres[0], nom->nombres[nom->cant]);
			printf("Primer Nombre Borrado \n" );
		} else{
			printf("No se puede suprimir ningun nombre, porque el arreglo esta vacio \n\n");
			}
}

void Mostrar(TData nom){
	//Inicio de la accion
	if ( !Vacia(nom) ) {
		for (int i = 0; i < nom.cant; ++i) {
			printf("El nombre (%d) es: %s \n", i+1, nom.nombres[i]);
		}
	}	else {
		printf("No se puede mostrar el arreglo, porque esta vacio \n");
		}
}
