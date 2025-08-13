#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


#define NUM_PACIENTES 50

typedef struct {
	int id;
	int frecuenciaCardiaca;
	int presionArterial;
	int saturacionOxigeno;
} paciente;

void actualizarPaciente(paciente *p);
paciente* buscarCriticos(paciente *lista, int tamano, int *total);

int main() {
	
	paciente pacientes[NUM_PACIENTES]; 
	
	srand(time(NULL));
	
	for(int i = 0; i < NUM_PACIENTES; i ++) {
		pacientes[i].id = i + 1; 
		actualizarPaciente(&pacientes[i]);
	}
	
	printf("-----MONITOREO DE UCI-----\n");
	
	
	for (int simulacion = 1; simulacion <= 3; simulacion++) {
		printf("\nActualizacion %d\n", simulacion);
		
		for (int i = 0; i < NUM_PACIENTES; i++) {
			actualizarPaciente(&pacientes[i]);
		}
		
		int criticosEncontrados = 0;
		
		paciente* listaCriticos = buscarCriticos(pacientes, NUM_PACIENTES, &criticosEncontrados);
		
		if (criticosEncontrados > 0) {
			printf("\n--- ALERTA: %d pacientes criticos ---\n", criticosEncontrados);
			for (int i = 0; i < criticosEncontrados; i++) {
				printf("  -> Paciente ID %d: FC %d, PA %d, SatO2 %d%%\n",
				listaCriticos[i].id,
				listaCriticos[i].frecuenciaCardiaca,
				listaCriticos[i].presionArterial,
				listaCriticos[i].saturacionOxigeno);
			}
			free(listaCriticos);
		} else {
			printf("No hay pacientes criticos en este momento.\n");
		}
	} 
	
	return 0;
}

