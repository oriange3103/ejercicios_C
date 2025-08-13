#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
	
	
menu();

	return 0;
}

int menu(){
	int a,b;
	int respuesta;
	
	printf("\n 1. Sumar \n");
	printf("\n 2. Restar \n");
	printf("\n 3. Multiplicar \n");
	printf("\n 4. Dividir \n");
	printf("\n 5. Potenciar \n");
	printf("\n 6. Raiz \n");
	printf("\n 7. Valor absoluto \n");
	
	printf("\n Ingrese respuesta \n");
	scanf("%d", &respuesta);
	
	printf("\n Ingrese valor 1 \n");
	scanf("%d", &a);
	printf("\n Ingrese valor 2 \n");
	scanf("%d", &b);	
	
	switch (respuesta){
		case 1:
			printf("Resultado: %d", sumar(a,b));
			break;
		case 2:
			printf("Resultado: %d", restar(a,b));
			break;
		case 3:
			printf("Resultado: %d", multiplicar(a,b));
			break;
		case 4:
			printf("Resultado: %d", dividir(a,b));
			break;
		case 5:
			printf("Resultado: %d", radicar(a));
			break;
		case 6:
			printf("Resultado: %d", potenciar(a,b));
			break;
		case 7:
			printf("Resultado: %d", valorAbs(a));	
			break;
		default:
		  printf("Saliendo");																	
	}
	return 0;
}

int sumar (int a, int b){
	return a+b;
}

int restar (int a, int b){
	return a-b;
}

int multiplicar (int a, int b){
	return a*b;
}

int dividir (int a, int b){
	return a / b;
}

int radicar (int a){
	return sqrt (a);
}

int potenciar (int a, int b){
	return pow (a,b);
}

int valorAbs (int a){
	return abs (a);
}