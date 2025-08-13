#include <stdio.h>
#include <stdlib.h>

 typedef struct  {
 	int intensidadVehicular;
 	float promedioVelocidad;
 	int nivelCongestion;
 	int tiempoEspera;
 } datosTrafico;
 
 void generarDatos (datosTrafico *sensor, int hora);
 void alertarCongestion (datosTrafico *sensor);
 
int main() {
	
	int numLecturas=3;
	  
datosTrafico *lecturasDiarias=(datosTrafico *)malloc(numLecturas *sizeof (datosTrafico));
  
   if (lecturasDiarias== NULL) {
	    printf("No se pudo asignar memoria\n");
		return 1;
   }

		srand(time(NULL));
	  	
	printf("\n MONITOREO Y CONTROL \n");
	  	
	  for (int i=0; i<numLecturas; i++){
	  	  	
	   	 int horaSimulada = (i == 0) ? 8 : (i == 1) ? 16 : 0;
	  	  	 
	   	 printf("\n--- Lectura %d (hora %d:00) ---\n", i + 1, horaSimulada);
	  	  	 
	   	 generarDatos(&lecturasDiarias[i], horaSimulada);
	  	  	 
	    printf("\n Intensidad: %d veh/min\n", lecturasDiarias[i].intensidadVehicular);
        printf("\n Velocidad: %.2f km/h\n", lecturasDiarias[i].promedioVelocidad);
        printf("\n Congestion: %d%%\n", lecturasDiarias[i].nivelCongestion);
        printf("\n Tiempo de espera: %d segundos\n", lecturasDiarias[i].tiempoEspera);
        
      alertarCongestion(&lecturasDiarias[i]);
    	}
	
	free (lecturasDiarias);
	printf("memoria liberada\n");
		
	return 0;
}

void generarDatos(datosTrafico *sensor, int hora) {
    // Generar intensidad y congestion, asegurando que no sean negativos
    sensor->intensidadVehicular = rand() % 101; // Entre 0 y 100
    sensor->nivelCongestion = rand() % 101; // Entre 0 y 100

    // Generar velocidad de forma aleatoria
    sensor->promedioVelocidad = (float)(rand() % 101) / 2.0 + 10.0; // Entre 10 y 60 km/h

    // El tiempo de espera depende de la hora
    if (hora >= 7 && hora <= 9 || hora >= 17 && hora <= 19) { // Horas pico
        // Mayor tiempo de espera en horas pico (entre 60 y 240 segundos)
        sensor->tiempoEspera = rand() % 181 + 60;
    } else { // Fuera de horas pico
        // Menor tiempo de espera (entre 5 y 60 segundos)
        sensor->tiempoEspera = rand() % 56 + 5;
    }
}

void alertarCongestion(datosTrafico *sensor) {
    // Usamos punteros para acceder a los miembros de la estructura
    if (sensor->nivelCongestion > 70 || sensor->tiempoEspera > 120) {
        printf("\n ALERTA Nivel de trafico elevado.\n");
        printf("\n  - Congestion: %d%%\n", sensor->nivelCongestion);
        printf("\n  - Tiempo de espera: %d segundos\n", sensor->tiempoEspera);
    }
}





