#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int sumaFila(int [3][2],int ,int ); //PROTOTIPO DE LA FUNCION
int sumaColumna(int [3][2],int ,int );
int main() {
	
	int matriz [3][2];
	
	//fila 0
	matriz[0][0]=5;
	matriz[0][1]=8;
	
	//fila 1
	matriz[1][0]=7;
	matriz[1][1]=20;
	
	//fila 2
	matriz[2][0]=30;
	matriz[2][1]=25;
	
	int resultado= sumaFila(matriz,2,2);
	printf("La suma de los valores de la fila 2 es: %d",resultado);
	printf("\n _______________________________________________________\n");
	int resultado2= sumaColumna(matriz,2,3);
    printf("\n La suma de los valores de la columna 0 es: %d",resultado2);
	
	return 0;
}
int sumaFila(int matriz[3][2],int numFila,int cantColumnas) //FUNCION SUMA
{
        int sumatoria= 0; 	
          for(int j=0;j< cantColumnas;j++){
          	sumatoria= sumatoria + matriz[numFila][j];
		  }
		  return sumatoria;
}

int sumaColumna(int matriz[3][2],int numColumna,int cantFilas) //FUNCION SUMA
{
        int sumatoria= 0; 	
          for(int i=0;i< cantFilas;i++){
          	sumatoria= sumatoria + matriz[i][numColumna];
		  }
		  return sumatoria;
}