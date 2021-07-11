// Trabajo integrador Algo y prog 2021
//Max = 1000 ∈ Z
// TNombres= arreglo[1.. Max] de Cadena
// TData = < nombres ∈ TNombres, cant ∈ (0..Max) >
//arreglo ∈ TData
//nuevoNombre ∈ Cadena

#include <stdio.h>
#define Max 1000
int Telem; // (1..10)
typedef struct {
                  String a[Max]; // Tnumer
                  int cant;   // cantidad de notas a ser cargadas
               } TData;
TData misNotas;
float promedio;
void cargarNotas( TData *carga )
{
  int aux;
  printf("Cuantas notas va a cargar? \n");
	scanf("%d",&aux);
  printf("Ingrese las notas \n");
  for (int i = 0; i < aux; i++)
	{
    printf("nota %d: ", i+1);
    scanf("%d",&carga->a[i] );
    while ((*carga).a[i] < 0 || (*carga).a[i] > 10)
    {//validar ent
      printf("Las notas estan comprendidas entre 0 y 10. Reingrese \n");
      scanf("%d",&carga->a[i] );
    }
  }
  (*carga).cant = aux;
}

void promedioNotas( TData not, float *prom )
{
	for (int i = 0; i < not.cant; i++)
	{
		*prom = *prom + not.a[i];
	}
	*prom = *prom / not.cant;
}

void main()
{
  cargarNotas(&misNotas);
  promedioNotas(misNotas, &promedio);
  printf("El promedio de las notas es: %f \n", promedio);
}
