#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include "poker.h"

#define COLOR_ROJO     "\x1b[31m"
#define COLOR_NEGRO    "\x1b[90m"
#define COLOR_RESET    "\x1b[0m"

typedef struct {
    char valor[3];
    char palo[5];
    int valorNumerico;
    int esEspecial;
} Carta;

#define MAX_CARTAS 15

typedef struct {
    int id;
    Carta mano[MAX_CARTAS];
    int cantidad;
    int puntos;
    int eliminado;
    int tieneEspecial;
    Carta cartaEspecial;
    int plantado;
} Jugador;

typedef struct {
    char nombre[50];
    int puntos;
} PuntuacionJugador;

// Ranking en memoria
#define MAX_RANKING_MEMORIA 100
PuntuacionJugador rankingMemoria[MAX_RANKING_MEMORIA];
int totalRanking = 0;

//  Funciones de utilidad
int leerNumero(const char *mensaje) {
    int entrada;
    printf("%s", mensaje);
    while (scanf("%d", &entrada) != 1) {
        printf("Entrada inválida. Intenta de nuevo: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return entrada;
}

//  Funciones de cartas
void inicializarBaraja(Carta baraja[], int *volumen) {
    char *valores[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    char *especiales[] = {"J", "Q", "K"};
    char *palos[] = {"♥", "♦", "♣", "♠",}; 
    int index = 0;

    for (int s = 0; s < 4; s++) {
        for (int v = 0; v < 10; v++) {
            strcpy(baraja[index].valor, valores[v]);
            strcpy(baraja[index].palo, palos[s]);
            baraja[index].valorNumerico = (v == 0) ? 1 : v + 1;
            baraja[index].esEspecial = 0;
            index++;
        }
        for (int e = 0; e < 3; e++) {
            strcpy(baraja[index].valor, especiales[e]);
            strcpy(baraja[index].palo, palos[s]);
            baraja[index].valorNumerico = 10;
            baraja[index].esEspecial = 1;
            index++;
        }
    }

    *volumen = index;
}

void barajarBaraja(Carta baraja[], int volumen) {
    srand(time(NULL));
    for (int i = 0; i < volumen; i++) {
        int j = rand() % volumen;
        Carta temp = baraja[i];
        baraja[i] = baraja[j];
        baraja[j] = temp;
    }
}

// Funciones de jugador
void inicializarJugador(Jugador *j, int id) {
    j->id = id;
    j->cantidad = 0;
    j->puntos = 0;
    j->eliminado = 0;
    j->tieneEspecial = 0;
    j->plantado = 0;
}

void agregarCarta(Jugador *j, Carta c) {
    if (j->cantidad < MAX_CARTAS) {
        j->mano[j->cantidad++] = c;
        if (c.esEspecial) {
            j->tieneEspecial = 1;
            j->cartaEspecial = c;
        }
    }
}

int calcularPuntos(Jugador *j) {
    int total = 0, ases = 0;
    for (int i = 0; i < j->cantidad; i++) {
        if (strcmp(j->mano[i].valor, "A") == 0) {
            ases++;
            total += 11;
        } else {
            total += j->mano[i].valorNumerico;
        }
    }
    while (total > 21 && ases > 0) {
        total -= 10;
        ases--;
    }
    j->puntos = total;
    return total;
}

void mostrarMano(Jugador *j) {
    printf("Jugador %d - Mano (Puntos: %d):\n%s", j->id, j->puntos, COLOR_RESET);
    for (int i = 0; i < j->cantidad; i++) {
        const char* color = (strcmp(j->mano[i].palo, "♥") == 0 || strcmp(j->mano[i].palo, "♦") == 0) ? COLOR_ROJO : COLOR_NEGRO;
        printCard(j->mano[i].palo, j->mano[i].valor, color);
    }
    printf("\n");
}

//  Reparto inicial
void repartirCartas(Jugador jugadores[], int n, Carta baraja[], int *indice) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            agregarCarta(&jugadores[j], baraja[(*indice)++]);
            calcularPuntos(&jugadores[j]);
            const char* color = (strcmp(jugadores[j].mano[jugadores[j].cantidad - 1].palo, "♥") == 0 || strcmp(jugadores[j].mano[jugadores[j].cantidad - 1].palo, "♦") == 0) ? COLOR_ROJO : COLOR_NEGRO;
            printCard(jugadores[j].mano[jugadores[j].cantidad - 1].palo, jugadores[j].mano[jugadores[j].cantidad - 1].valor, color);
        }
    }
}

//  Verifica si alguien ganó con 21
int verificarGanador(Jugador jugadores[], int n) {
    for (int i = 0; i < n; i++) {
        if (!jugadores[i].eliminado && jugadores[i].puntos == 21) {
            return jugadores[i].id;
        }
    }
    return -1;
}

//  Ranking en memoria
int compararRanking(const void* a, const void* b) {
    return ((PuntuacionJugador*)b)->puntos - ((PuntuacionJugador*)a)->puntos;
}

void guardarRankingEnMemoria(PuntuacionJugador jugador) {
    if (totalRanking < MAX_RANKING_MEMORIA) {
        rankingMemoria[totalRanking++] = jugador;
    }
}

void mostrarRankingEnMemoria() {
    if (totalRanking == 0) {
        printf("No hay partidas registradas aún.\n");
        return;
    }

    qsort(rankingMemoria, totalRanking, sizeof(PuntuacionJugador), compararRanking);

    printf("\n--- Ranking de esta sesión ---\n");
    for (int i = 0; i < totalRanking; i++) {
        printf("%d. %-20s %d puntos\n", i + 1, rankingMemoria[i].nombre, rankingMemoria[i].puntos);
    }
}

//  Reglas del juego
void mostrarReglas() {
    printf("\n--- Reglas del Juego ---\n");
    printf("Objetivo: Llegar a 21 puntos sin pasarse.\n");
    printf("Jugadores: Mínimo 3, máximo 4.\n");
    printf("Turno: Puedes pedir carta, plantarte o usar carta especial.\n");
    printf("Cartas especiales:\n");
    printf("  - K: Salta turno del siguiente jugador.\n");
    printf("  - Q: Cambia dirección del juego.\n");
    printf("  - J: Penaliza al siguiente jugador con +2 o +4 cartas.\n");
    printf("Puntuación:\n");
    printf("  - Ganar con 21: 100 puntos.\n");
    printf("  - Desempate con carta especial: 50 puntos.\n");
    printf("  - Otros: suma de cartas.\n");
    printf("-------------------------\n");
    getchar();
}

//  Menú principal
void mostrarMenu() {
    printf("%s", COLOR_RESET);
    printf("\n--- Menú Principal ---\n");
    printf("1. Jugar\n");
    printf("2. Ver reglas\n");
    printf("3. Ver ranking\n");
    printf("4. Salir\n");
    printf("----------------------\n");
}

//  Función principal
int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("cls");
    srand(time(NULL));

    int estadoJuego = 1;

    while (estadoJuego) {
        mostrarMenu();
        int opcion = leerNumero("Selecciona una opción: ");

        switch (opcion) {
            case 1: {
                int numJugadores;
                do {
                    numJugadores = leerNumero("Número de jugadores (3-4): ");
                    if (numJugadores < 3 || numJugadores > 4) {
                        printf("Número inválido. Debe ser entre 3 y 4.\n");
                    }
                } while (numJugadores < 3 || numJugadores > 4);

                Jugador jugadores[4];
                for (int i = 0; i < numJugadores; i++) {
                    inicializarJugador(&jugadores[i], i + 1);
                }

                Carta baraja[100];
                int volumenBaraja, indiceBaraja = 0;
                inicializarBaraja(baraja, &volumenBaraja);
                barajarBaraja(baraja, volumenBaraja);
                repartirCartas(jugadores, numJugadores, baraja, &indiceBaraja);

                int ganadorID = -1;
                int activos = numJugadores;
                int turno = 0;
                int direccion = 1;
                int todosPlantados = 0;

                while (ganadorID == -1 && activos > 1 && !todosPlantados) {
                    Jugador *j = &jugadores[turno];

                    if (!j->eliminado && !j->plantado) {
                        printf("\n--- Turno del Jugador %d ---\n", j->id);
                        mostrarMano(j);

                        printf("Opciones:\n1. Pedir carta\n2. Plantarse\n");
                        if (j->tieneEspecial) printf("3. Usar carta especial\n");
                        int eleccion = leerNumero("Elige: ");

                        if (eleccion == 1) {
                            if (indiceBaraja < volumenBaraja) {
                                Carta nueva = baraja[indiceBaraja++];
                                agregarCarta(j, nueva);
                                calcularPuntos(j);
                                const char* color = (strcmp(nueva.palo, "♥") == 0 || strcmp(nueva.palo, "♦") == 0) ? COLOR_ROJO : COLOR_NEGRO;
                                printCard(nueva.palo, nueva.valor, color);
                                if (j->puntos > 21) {
                                    j->eliminado = 1;
                                    activos--;
                                    printf("Jugador %d eliminado por exceder 21.\n", j->id);
                                }
                            } else {
                                printf("No hay más cartas.\n");
                            }
                        } else if (eleccion == 2) {
                            j->plantado = 1;
                            printf("Jugador %d se planta con %d puntos.\n", j->id, j->puntos);
                        } else if (eleccion == 3 && j->tieneEspecial) {
                            printf("Jugador %d usa carta especial %s.\n", j->id, j->cartaEspecial.valor);
                            j->tieneEspecial = 0;
                        } else {
                            printf("Opción inválida.\n");
                        }

                        ganadorID = verificarGanador(jugadores, numJugadores);
                    }

                    int siguiente = turno;
                    int intentos = 0;
                    do {
                        siguiente = (siguiente + direccion + numJugadores) % numJugadores;
                        intentos++;
                    } while ((jugadores[siguiente].eliminado || jugadores[siguiente].plantado) && intentos < numJugadores);
                    turno = siguiente;

                    int plantados = 0;
                    for (int i = 0; i < numJugadores; i++) {
                        if (!jugadores[i].eliminado && jugadores[i].plantado) {
                            plantados++;
                        }
                    }
                    if (plantados == activos) {
                        todosPlantados = 1;
                        printf("Todos los jugadores activos se han plantado.\n");
                    }
                }

                printf("\n--- Fin de la partida ---\n");
                if (ganadorID != -1) {
                    printf("Jugador %d gana con 21 puntos.\n", ganadorID);
                    for (int i = 0; i < numJugadores; i++) {
                        jugadores[i].puntos = (jugadores[i].id == ganadorID) ? 100 : calcularPuntos(&jugadores[i]);
                    }
                } else {
                    printf("Nadie llegó a 21. Se asignan puntos por suma de cartas.\n");
                    for (int i = 0; i < numJugadores; i++) {
                        jugadores[i].puntos = jugadores[i].eliminado ? 0 : calcularPuntos(&jugadores[i]);
                    }
                }

                int maxPuntos = 0;
                int idGanadorRanking = -1;
                for (int i = 0; i < numJugadores; i++) {
                    if (!jugadores[i].eliminado && jugadores[i].puntos > maxPuntos) {
                        maxPuntos = jugadores[i].puntos;
                        idGanadorRanking = i;
                    }
                }

                if (idGanadorRanking != -1) {
                    PuntuacionJugador r;
                    sprintf(r.nombre, "Jugador%d", jugadores[idGanadorRanking].id);
                    r.puntos = jugadores[idGanadorRanking].puntos;
                    guardarRankingEnMemoria(r);
                    printf("Jugador %d guardado en el ranking con %d puntos.\n", jugadores[idGanadorRanking].id, r.puntos);
                }

                for (int i = 0; i < numJugadores; i++) {
                    printf("Jugador %d: %d puntos\n", jugadores[i].id, jugadores[i].puntos);
                }

                int otra = leerNumero("¿Jugar otra vez? (1=Sí, 0=No): ");
                if (!otra) estadoJuego = 0;
                break;
            }

            case 2:
                mostrarReglas();
                break;

            case 3:
                mostrarRankingEnMemoria();
                break;

            case 4:
                estadoJuego = 0;
                printf("Gracias por jugar.\n");
                break;

            default:
                printf("Opción inválida.\n");
                break;
        }
    }

    return 0;
}
                