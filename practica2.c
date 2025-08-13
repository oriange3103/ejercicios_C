#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxMascotas 100

struct mascota {
    char especie[50];
    char raza[50];
    char nombre[50];
    int edad;
    char vacunas[10][10];
};

// --- Declaración de prototipos de funciones ---

void buscar(struct mascota *mascotas, int total_mascotas);
int agregar_mascota(struct mascota *mascotas, int total_mascotas, int max_mascotas);
void imprimir_mascotas(struct mascota *mascotas, int total_mascotas);
void editar_mascota(struct mascota *mascotas, int total_mascotas);

int main() {
    int opcion;
    int cantMascotas = 0;
    struct mascota animales[maxMascotas];
    
    // --- Bucle del menú ---
    do {
        printf("\n\n");
        printf("\n----INICIO----\n");
        printf("1. Agregar mascota\n");
        printf("2. Buscar mascota\n");
        printf("3. Imprimir registro\n");
        printf("4. Editar registro\n");
        printf("5. Salir\n");
        printf("\n\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                cantMascotas = agregar_mascota(animales, cantMascotas, maxMascotas);
                break;
            case 2:
                buscar(animales, cantMascotas);
                break;
            case 3:
                imprimir_mascotas(animales, cantMascotas);
                break;
            case 4:
                editar_mascota(animales, cantMascotas);
                break; // <-- Se agregó el 'break' aquí
            case 5:
                printf("\n Regrese pronto\n");		
                break;
            default:
                printf("Opcion no valida, intente de nuevo\n");
                break;			
        }
    } while (opcion != 5); // <-- La condición es 'opcion != 5' para salir

    return 0;
}

// --- Definición de funciones ---
int agregar_mascota(struct mascota *mascotas, int total_mascotas, int max_mascotas) {
    if (total_mascotas >= max_mascotas) {
        printf("No se pueden agregar más mascotas. El límite es %d.\n", max_mascotas);
        return total_mascotas;
    }
    
    int i = total_mascotas;
    printf("\n--- Agregar nueva mascota ---\n");
    printf("Ingrese la especie: \n");
    scanf(" %[^\n]s", mascotas[i].especie);
    printf("Ingrese la raza: \n");
    scanf(" %[^\n]s", mascotas[i].raza);
    printf("Ingrese el nombre: \n");
    scanf(" %[^\n]s", mascotas[i].nombre);
    printf("Ingrese la edad: \n");
    scanf("%d", &mascotas[i].edad);
    printf("Ingrese las vacunas: \n");
    scanf(" %[^\n]s", mascotas[i].vacunas);

    return total_mascotas + 1;
}

void buscar(struct mascota *mascotas, int total_mascotas){
    char busqueda [50];
    int busquedaEdad;
    int encontrado=0;
    
    printf("\n Ingrese el dato a buscar (especie, raza, nombre, edad, vacunas)\n");
    scanf(" %[^\n]s",busqueda);
    
    busquedaEdad = atoi(busqueda);
    
    printf("\n Resultados de la busqueda \n");
    
    for(int i=0; i<total_mascotas; i++){
        if (strcmp(busqueda, mascotas[i].especie) == 0 ||
            strcmp(busqueda, mascotas[i].raza) == 0 ||
            strcmp(busqueda, mascotas[i].nombre) == 0 ||
            busquedaEdad == mascotas[i].edad) {
            
            printf("----------------------------------\n");
            printf("Especie: %s\n", mascotas[i].especie);
            printf("Raza: %s\n", mascotas[i].raza);
            printf("Nombre: %s\n", mascotas[i].nombre);
            printf("Edad: %d\n", mascotas[i].edad);
            printf("----------------------------------\n");
            
            encontrado = 1;
        }
    }
    
    if (encontrado == 0) {
        printf("No se encontraron resultados para '%s'.\n", busqueda);
    }
}

void imprimir_mascotas(struct mascota *mascotas, int total_mascotas) {
    if (total_mascotas == 0) {
        printf("\nNo hay mascotas registradas.\n");
        return;
    }
    
    printf("\n--- DATOS DE LAS MASCOTAS ---\n");
    printf(" --------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-15s | %-5s\n", "ESPECIE", "RAZA", "NOMBRE", "EDAD");
    printf(" --------------------------------------------------------------------\n");
    for (int i = 0; i < total_mascotas; i++) {
        printf("| %-15s | %-15s | %-15s | %-5d\n", mascotas[i].especie, mascotas[i].raza, mascotas[i].nombre, mascotas[i].edad);
    }
    printf(" --------------------------------------------------------------------\n");
}


void editar_mascota(struct mascota *mascotas, int total_mascotas) {
    char nombre_a_buscar[50];
    int encontrado = 0;

    if (total_mascotas == 0) {
        printf("\n No hay mascotas registradas para editar.\n");
        return;
    }

    printf("\n--- Editar Mascota ---\n");
    printf("Ingrese el nombre de la mascota a editar: ");
    scanf(" %[^\n]s", nombre_a_buscar);

    for (int i = 0; i < total_mascotas; i++) {
        if (strcmp(nombre_a_buscar, mascotas[i].nombre) == 0) {
            printf("\n Mascota encontrada. Ingrese los nuevos datos:\n");
            
            printf("Nueva especie (%s): ", mascotas[i].especie);
            scanf(" %[^\n]s", mascotas[i].especie);
            
            printf("Nueva raza (%s): ", mascotas[i].raza);
            scanf(" %[^\n]s", mascotas[i].raza);
            
            printf("Nuevo nombre (%s): ", mascotas[i].nombre);
            scanf(" %[^\n]s", mascotas[i].nombre);
            
            printf("Nueva edad (%d): ", mascotas[i].edad);
            scanf("%d", &mascotas[i].edad);
            
            printf("Nuevas vacunas (%s): ", mascotas[i].vacunas);
            scanf(" %[^\n]s", mascotas[i].vacunas);

            printf("\n Datos de la mascota actualizados con exito \n");
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("\n No se encontro una mascota con el nombre '%s'.\n", nombre_a_buscar);
    }
}