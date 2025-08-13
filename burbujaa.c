#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int vector[10]={10,9,8,7,6,5,4,3,2,1};
	int aux;
	
	for(int i=0; i< 10; i++){
		for( int j=0; j<10;j++){
			if(vector[j]> vector[j+1]){
				aux= vector [j+1];
				vector[j+1]= vector[j];
				vector[j]=aux;
			}
		}
	}
	
	
	for (int i=0;i< 10; i++){
		printf("%d\t", vector[i]);
	}
	return 0;
}