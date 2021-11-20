#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<unistd.h>

int SanityCheck() {	
	char *filename = "personas.dat";
	 if( access( filename, F_OK ) == 0){ 
        printf("%s ,Archivo encontrado \n",filename);   
        return 0;
	}else if( access( filename, F_OK ) == -1) {
		printf("El archivo  %s no existe, no puede continuar \n", filename);
		return 1;
		exit(0);
	} 
} // END SANITY CHECK
void main(){
    SanityCheck();
}