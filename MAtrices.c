#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
  int matrizAleatoria [3][3];
  int matrizDecreciente [3][3];
  for (int i=0;i<=2;i++) {
  	for (int j=0; j<=2;j++) {
  		matrizAleatoria[i][j]= rand() %10 +20;
	  }
  }
  //MOSTRAR MATRIZ ORIGINAL
  
   printf("\n Matriz ordenada \n");
   printf("\n");
    
    for(int i = 0; i <= 2; i ++)
    {
        for(int j = 0; j <= 2; j ++)
        {
            printf("%d\t", matrizAleatoria[i][j]);
        }

        printf("\n");
    }
    int filas=3, columnas=3;
   int tamanioTotal = 9; // En este caso, 3 * 3 = 9
    int tempArray[tamanioTotal];
    int k = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tempArray[k++] = matrizDecreciente[i][j];
            
			}
			}
    //METODO BURBUJA
      
      
      for(int i=0;i<filas-1;i++){
      	for(int j=0; j<filas-i-1;j++){
      		if(matrizAleatoria[i][0]>matrizAleatoria[j+1][0]){
      			//
      			for(int k=0;k<columnas;k++){
      				int temp=matrizAleatoria[j][k];
      				matrizAleatoria[j][k]=matrizAleatoria[j+1][k];
      				matrizAleatoria[j+1][k]=temp;
				  }
			  }
		  }
	  }
	  
	  //MOSTRAR MATRIZ ORDENADA
	  
	    printf("\nMatriz ordenada por primer elemento:\n");
	    printf("\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d \t ", matrizAleatoria[i][j]);
        }
        printf("\n");
    }

	return 0;
}