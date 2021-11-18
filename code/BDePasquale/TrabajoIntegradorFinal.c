#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define NMax 1000

//registro con nombre, dni y edad
typedef struct{
	char nombre[50];
	int dni;
	int edad;
}TElem;
//registro del arreglo con la cantidad de personas y sus datos
typedef struct {
	TElem n[NMax]; 	
	int cant;
}TData;
//registro de la lista con el puntero al siguiente y sus datos
typedef struct TDoblete{
	TElem info;
	struct TDoblete *next;
}TData2;

//acciones y funciones
bool Vacia(TData *dat);
bool Llena(TData *dat);
void NombreNuevo(TData *dat);
void SuprimirNombre(TData *dat);
void Mostrar(TData dat);
void AgregarDesdeArchivo(TData *dat);
void GuardarYSalir(TData dat);
TData2* MostrarMenores(TData dat,int j,TData2 ** s);
void BuscarporDNI(TData dat);
char Mayoresalprimero(TData dat);
int Edadmayor(TData dat,int j,int *m);


int main(){
TData datos;
TData2 * sec,* aux;
int respuesta,i,mayor;
AgregarDesdeArchivo(&datos);

		printf("--MENU--\n");
		printf("1:Ingresar una persona nueva\n");
		printf("2:Suprimir la primer persona del arreglo\n");
		printf("3:Mostrar personas cargadas en el arreglo\n");
		printf("4:Mostrar personas menores de edad\n");
		printf("5:Buscar persona por DNI\n");
		printf("6:Personas mayores a la primera\n");
		printf("7:Mostrar persona con mayor edad\n");
		printf("8:Guardar y salir\n");

do{

		printf("Elija una opción: ");
		scanf("%i",&respuesta);
		if (respuesta==1){
			NombreNuevo(&datos);
		}
		else{
			if (respuesta==2){
				SuprimirNombre(&datos);
			}
			else{
				if (respuesta==3){
					Mostrar(datos);
				}
				else{
					if (respuesta==4){
						i=0;
						aux=malloc(sizeof(TData2));
						aux->next=NULL;
						sec=aux;
						MostrarMenores(datos,i,&sec);
					}
					else{
						if(respuesta==5){
							BuscarporDNI(datos);
						}
						else{
							if(respuesta==6){
								Mayoresalprimero(datos);
							}
							else{
								if(respuesta==7){
									i=0;
									mayor=1;
									Edadmayor(datos,i,&mayor);
								}
								else{
									if(respuesta==8){
										GuardarYSalir(datos);
									}
									else{
										printf("Ingrese una opción valida\n");
									}
								}
							}
						}
					}
				}
			}
		}
	} while (!(respuesta==8));

return 0;
}

//determina si el arreglo esta vacio.
bool Vacia(TData *dat){
	if ((*dat).cant==0){
		return true;
	}
	else{
		return false;
	}

}

//determina si el arreglo esta lleno.
bool Llena(TData *dat){
	if ((*dat).cant==NMax){
		return true;
	}
	else{
		return false;
	}

}

//Inserta una nueva persona al final del arreglo.
void NombreNuevo(TData *dat){
	int i;
	if (Llena(dat)){
		printf("Ya tienes 1000 personas cargados,no puedes agregar mas\n");
		
	}
	else{
		(*dat).cant=(*dat).cant + 1;
		i=(*dat).cant;
		printf("Ingrese los datos de la nueva persona: \n");
		printf("Nombre: ");
		while ((getchar()) != '\n');
		fgets(dat->n[i].nombre,50,stdin);
		printf("DNI: ");
		scanf("%i",&dat->n[i].dni);
		printf("Edad: ");
		scanf("%i",&dat->n[i].edad);
	}
}

//Suprime la primer persona del arreglo.
void SuprimirNombre(TData *dat){
	int i=0;
	if (Vacia(dat)){
		printf("No puedes suprimir ninguna persona,ya que no tienes ninguna cargada\n");
		
	}
	else{
		while(i<(*dat).cant){
			i++;
			(*dat).n[i]=(*dat).n[i+1];
		}
		(*dat).cant=(*dat).cant - 1;
	}
}

//Muestra todos las personas del arreglo.
void Mostrar(TData dat){
	int i=0;
	if (Vacia(&dat)){
		printf("No tienes ninguna persona cargada en el arreglo\n");
	}else{
		printf("Esta es la cantidad de personas en el arreglo: %i\n",dat.cant);
		printf("Estos son las personas cargadas: \n");
		while(i<dat.cant){
			i++;
			printf("---------------------------------\n");
			printf("Nombre: %s\n",dat.n[i].nombre);
			printf("DNI: %i\n",dat.n[i].dni);
			printf("Edad: %i\n",dat.n[i].edad);
			printf("---------------------------------\n");
			printf("\n");
		}
	}
}

//Agrega personas al arreglo desde un archivo,solo las que en su campo borrado tengan 0
void AgregarDesdeArchivo(TData *dat){
	typedef struct{
		char nombre[30];
		int dni;
		int edad;
		int borrado;
	}TPersona;
	FILE* f;
	TPersona aux;
	int i=0;
	f=fopen("personas.dat","rb");
	if(f){
		while (fread(&aux,sizeof(TPersona),1,f)!=0){
			if (aux.borrado==0){
				i++;
				strcpy(dat->n[i].nombre,aux.nombre);
				dat->n[i].dni=aux.dni;
				dat->n[i].edad=aux.edad;
			}
			printf("nombre: %s\t dni: %d\tedad: %d\n", aux.nombre, aux.dni, aux.edad);
		}
	}else{
		printf("No se encontro el archivo con el nombre 'personas.dat'\n");
	}
	fclose(f);
	dat->cant=i;
}

//Guarda las personas que estan en el arreglo en un archivo llamado "personas.dat"(borra el archivo anterior y hace uno nuevo)
void GuardarYSalir(TData dat){
	typedef struct{
		char nombre[50];
		int dni;
		int edad;
		int borrado;
	}TPersona;
	FILE* s;
	TPersona aux;
	int i=0;
	remove("personas.dat");
	s=fopen("personas.dat","wb");
	while(i<dat.cant){
		i++;
		strcpy(aux.nombre,dat.n[i].nombre);
		aux.dni=dat.n[i].dni;
		aux.edad=dat.n[i].edad;
		printf("Borrar a %s(0 para no y 1 para si): ",aux.nombre);
		scanf("%i",&aux.borrado);
		fwrite(&aux,sizeof(aux),1,s);
	}
	fclose(s);
}

//Crea una LSE(Lista Simplemente Encadenada) con las personas menores a 18,y los muestra
TData2* MostrarMenores(TData dat,int j,TData2 ** s){
	TData2 *nuevo,*aux;
	if(dat.cant==0){
		printf("No hay personas cargadas en el arreglo\n");
	}else{
		if(j>=0 && j<dat.cant){
			j++;
			if (dat.n[j].edad<18){
				nuevo=malloc(sizeof(TData2));
				nuevo->info=dat.n[j];
				nuevo->next=(*s)->next;
				(*s)->next=nuevo;
			}
			MostrarMenores(dat,j,s);
		}else{
			aux=*s;
			if(aux->next==NULL){
				printf("No hay personas menores de edad\n");
			}
			while(aux->next!=NULL){
				aux=(*aux).next;
				printf("--------------------------\n");
				printf("Nombre: %s\n",aux->info.nombre);
				printf("DNI: %i\n",aux->info.dni);
				printf("Edad: %i\n",aux->info.edad);
				printf("--------------------------\n");
			}
		}
	}
}

//El usuario ingresa un DNI, si hay una persona con ese DNI,muestra sus datos
void BuscarporDNI(TData dat){
	int i,j;
	TElem aux;
	int dni;
	int m,sup,inf;
	if (Vacia(&dat)){
		printf("El arreglo esta vacio\n");
	}else{
		i=2;
		while (i<=dat.cant){
			aux=dat.n[i];
			j=i-1;
			while(j>0 && dat.n[j].dni>aux.dni){
				dat.n[j+1]=dat.n[j];
				j--;
			}
			dat.n[j+1]=aux;
			i++;
		}
		printf("Ingrese el DNI a buscar: ");
		scanf("%i",&dni);
		if(dni<dat.n[1].dni || dni>dat.n[dat.cant].dni){
			printf("No existe ninguna persona con ese DNI\n");
		}else{
			inf=1;
			sup=dat.cant;
			while (inf<sup){
				m=(inf+sup)/2;
				if (dni>dat.n[m].dni){
					inf=m+1;
				}else{
					sup=m;
				}
			}
			if (dat.n[inf].dni==dni){
				printf("---------------------------------\n");
				printf("Nombre: %s\n",dat.n[inf].nombre);
				printf("DNI: %i\n",dat.n[inf].dni);
				printf("Edad: %i\n",dat.n[inf].edad);
				printf("---------------------------------\n");
			}else{
				printf("No existe ninguna persona con ese DNI\n");
			}
		}
	}
}

//Te informa si hay o no 3 o mas personas mayores a la primera en el arreglo
char Mayoresalprimero(TData dat){
	int mayorespri=0,i=0,primero;
	if (Vacia(&dat)){
		printf("El arreglo esta vacio\n");
	}else{
		i++;
		primero=dat.n[i].edad;
		while (i<=dat.cant){
			i++;
			if (primero<dat.n[i].edad){
				mayorespri++;
			}
		}
		if (mayorespri>=3){
			printf("Hay tres o mas personas mayores a la primera\n");
		}else{
			printf("No hay mas de 3 personas mayores a la primera\n");
		}
	}
}

//Te muestra los datos de la persona con mayor edad en el arreglo
int Edadmayor(TData dat,int j,int *m){
	if (Vacia(&dat)){
		printf("El arreglo esta vacio\n");
	}else{
		if(dat.cant>0 && j==dat.cant){
			printf("---------------------------------\n");
			printf("Nombre: %s\n",dat.n[*m].nombre);
			printf("DNI: %i\n",dat.n[*m].dni);
			printf("Edad: %i\n",dat.n[*m].edad);
			printf("---------------------------------\n");
			printf("\n");
		}else{
			if(j<dat.cant){
				j++;
				if(dat.n[j].edad>dat.n[*m].edad){
					*m=j;
				}
				Edadmayor(dat,j,m);
			}
		}
	}
}