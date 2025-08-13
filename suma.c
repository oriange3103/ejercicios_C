#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int filas=3;
	int columnas=3;
	int matriz[3][3]= {
	{3,8,6},
	{1,4,5},
	{9,3,10},
	};
	
	//VARIABLE SUMA
	 int sumaDiagonalPrincipal=0;
	 
	//RECORRER MATRIZ
	
	for(int i=0;i<filas;i++){
		sumaDiagonalPrincipal+=matriz[i][i];
	}
	printf("La suma de la diagonal principal es: %d",sumaDiagonalPrincipal);
	return 0;
}