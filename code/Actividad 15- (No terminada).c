#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 1000

typedef struct
{
	char nombres[Max][100];
	int cant;
}TData;

TData arreglo;
char nuevoName[100];

int volver, seleccion, v, l;

	/* Accion CargarArreglo */
void CargarArreglo(TData *nom);

	/* Funcion Vacia */
int Vacia(TData nom);

	/* Funcion llena */
int Llena(TData nom);

	/* Accion CargarNuevoNombre */
void CargarNuevoNombre(TData *nom, char* nuevoNomb);

	/* Accion SuprimirNombre */
void SuprimirNombre(TData *nom);

	/* Accion Mostrar */
void Mostrar(TData nom);


//Inicio del algoritmo
int main()
{
	volver = 0;
	while(volver == 0){

		printf("Que quieres hacer? \n [1]Cargar Nuevo Arreglo. \n [2]Cargar Nuevo Nombre. \n [3] Suprimir el primer Nombre. \n [4] Mostrar lo que contiene el arreglo \n\n *INGRESA AQUI EL NUMERO:");
		scanf("%d", &seleccion);
		while(seleccion < 1 || seleccion > 4 ){
			printf("No existe ninguna operacion con ese numero.");
			printf("Que quieres hacer? \n [1]Cargar Nuevo Arreglo. \n [2]Cargar Nuevo Nombre. \n [3] Suprimir el primer Nombre. \n [4] Mostrar lo que contiene el arreglo \n *INGRESA AQUI EL NUMERO: ");
			scanf("%d", &seleccion);
		}

		if (seleccion == 1) 
		{
			CargarArreglo(&arreglo);
			printf("Arreglo cargado con Exito\n\n");
		} else {
			if (seleccion == 2)
			{
				printf("Esta operacion no esta disponible en este momento\n\n");
			} else {
				if (seleccion == 3)
				{
					v = Vacia(arreglo);

					if (v != 1)
					{
						SuprimirNombre(&arreglo);
					} else{
						printf("No se puede suprimir ningun nombre, porque el arreglo esta vacio \n\n");
					}
					
				} else {
					v = Vacia(arreglo);
					if (v != 1)
					{
						Mostrar(arreglo);
					}else{
						printf("No se puede mostrar el arreglo, porque esta vacio \n\n");
					}
					
				}
			}
		}

		printf("Ingresa [0] si quieres volver al menu. Si quieres terminar ingresa cualquier numero: ");
		scanf("%d", &volver);
	};

	system("pause");
	return 0;
}

//Fin


void CargarArreglo(TData *nom){
	//Lexico Local
	int j;
	//Inicio de la accion
	printf("Ingresa la cantidad de nombres: ");
	scanf("%d", &nom->cant);

	while(nom->cant < 0 || nom->cant > 1000){

		printf("La cantidad de nombres tiene que estar entre 0 y 1000, porfavor ingrese nuevamente la cantidad: ");
		scanf("%d", &nom->cant);

	};

	j = 1; //Esta variable la utilizo para que el usuario sepa cual es el numero del nombre que va ingresar
	for (int i = 0; i < nom->cant; ++i)
	{
		printf("Ingresa el (%d) nombre: ", j);
		scanf("%s", nom->nombres[i]);
		j = ++j;
	}

}

int Vacia(TData nom){
	//Inicio De La Funcion
	if (nom.cant == 0)
	{
		return(1);
	} else {
		return(0);
	}
}


int Llena(TData nom){
	//Inicio De La Funcion
	if (nom.cant == 1000)
	{
		return(1);
	} else {
		return(0);
	}
}

/*
void CargarNuevoNombre(TData *nom){
	//Lexico local
	char nuevoNombre[100]
	//Inicio de la funcion
	if (Llena(*nom) == 1)
	{
		printf("No es posible insertar el nuevo nombre ya que el arreglo está lleno \n");
	} else{
		printf("Ingresa el nombre que quieres insertar ");
		scanf("%s", nuevoNombre);
		nom->cant = nom->cant+1;

		strcpy(nom->nombres[caca], nuevoNomb);
		printf("Nuevo nombre insertado con exito\n");
	}

}
*/

void SuprimirNombre(TData *nom){
	//Inicio de la accion
	nom->cant = nom->cant - 1;
	strcpy(nom->nombres[0], nom->nombres[nom->cant]); 
}


void Mostrar(TData nom){
	//Lexico Local
	int j;
	//Inicio de la accion

	j = 1; //Esta variable la utilizo para que el usuario sepa cual es el numero del nombre que se va a mostrar
	for (int i = 0; i < nom.cant; ++i)
	{
		printf("El nombre (%d) es: %s \n", j, nom.nombres[i]);
		j = ++j;
	}

}