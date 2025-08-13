#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

	#define NroEstaciones 4
	#define NroMeses 3

int main() {
	
  char nombreEstacion [NroEstaciones][50];
  float contaminacionOctubre [NroEstaciones];
  float contaminacionNoviembre [NroEstaciones]; 
   float contaminacionDiciembre[NroEstaciones];
   
   //SOLICITAR DATOS
   
   printf(" Ingreso de Datos de Contaminacion  \n");

    for (int i = 0; i < NroEstaciones; i++) {
       
	    printf("\n Ingrese el nombre de la Estacion %d: ", i + 1);
        scanf("%s", nombreEstacion[i]);
printf("\n");
        printf("Ingrese la contaminacion de %s en Octubre : ", nombreEstacion[i]);
        scanf("%f", &contaminacionOctubre[i]);
        
        printf("Ingrese la contaminacion de %s en Noviembre : ", nombreEstacion[i]);
        scanf("%f", &contaminacionNoviembre[i]);

        printf("Ingrese la contaminacion de %s en Diciembre : ", nombreEstacion[i]);
        scanf("%f", &contaminacionDiciembre[i]);
    }
    
    //MOSTRAR INFORMACION
    
    printf("\n Informacion Ingresada \n");
    printf("%-15s %-10s %-10s %-10s\n", "Empresa", "Octubre", "Noviembre", "Diciembre");
   
    for (int i = 0; i < NroEstaciones; i++) {
        printf("%-15s %-10.2f %-10.2f %-10.2f\n",
               nombreEstacion[i],
               contaminacionOctubre[i],
               contaminacionNoviembre[i],
               contaminacionDiciembre[i]);
    }
    //PROMEDIO X ESTACION
  
    printf("\n--- Promedio de Contaminacion por Estacion ---\n");
    printf("\n");
    for (int i = 0; i < NroEstaciones; i++) {
        float promedioEstacion = (contaminacionOctubre[i] + contaminacionNoviembre[i] + contaminacionDiciembre[i]) / NroMeses;
        printf("El promedio de contaminacion para %s es: %.2f \n", nombreEstacion[i], promedioEstacion);
  }
    //PROMEDIO GENERAL
    
     printf("\n Promedio General de Contaminacion por Mes \n");
    printf("\n");
	float sumaOctubre = 0, sumaNoviembre = 0, sumaDiciembre = 0;
  
    for (int i = 0; i < NroEstaciones; i++) {
        sumaOctubre += contaminacionOctubre[i];
        sumaNoviembre += contaminacionNoviembre[i];
        sumaDiciembre += contaminacionDiciembre[i];
    }
   
     printf("El promedio general de contaminacion en Octubre es: %.2f \n", sumaOctubre / NroEstaciones);
     printf("\n");
    printf("El promedio general de contaminacion en Noviembre es: %.2f \n", sumaNoviembre / NroEstaciones);
    printf("\n");
    printf("El promedio general de contaminacion en Diciembre es: %.2f \n", sumaDiciembre / NroEstaciones);
    printf("\n");
   
   
    // 3. Estacion con niveles mas altos y mas bajos de contaminacion
    printf("\n Estacion con Niveles Mas Altos y Mas Bajos \n");

    float maxContaminacion = -1.0; // Inicializar con un valor muy bajo
    float minContaminacion = 999999.0; // Inicializar con un valor muy alto
    char estacionMax[50];
    char estacionMin[50];

    for (int i = 0; i < NroEstaciones; i++) {
        float promedioEstacion = (contaminacionOctubre[i] + contaminacionNoviembre[i] + contaminacionDiciembre[i]); // Suma total para comparar
        if (promedioEstacion > maxContaminacion) {
            maxContaminacion = promedioEstacion;
            strcpy(estacionMax, nombreEstacion[i]);
        }
        if (promedioEstacion < minContaminacion) {
            minContaminacion = promedioEstacion;
            strcpy(estacionMin, nombreEstacion[i]);
        }
    }
    printf("La estacion con los niveles mas altos de contaminacion es: %s\n", estacionMax);
    printf("\n");
    printf("La estacion con los niveles mas bajos de contaminacion  es: %s\n", estacionMin);
	return 0;
	}