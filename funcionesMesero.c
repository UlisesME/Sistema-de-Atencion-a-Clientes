/********************************************************************
* funcionesMesero.c - Funciones para la captura y envío de comandas *
*                     con uso de listas dinámicas y                 *
*                     manejo de información mediante archivos       *
*                                                                   *
* Autor: Ulises Magaña                                              *
*                                                                   *
* Archivos: tickets.txt, pedidosBebidas.bin, pedidosAlimentos.bin   *
*                                                                   *
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tipos.h"

#define AMERICANO 35
#define CAPUCHINO 50
#define EXPRESS 40
#define TORTA 60
#define BAGEL 55
#define ENSALADA 40

// MENU MESERO. ENCONTRADO EN 'menus.c'
extern void mostrarMenuMesero();

void capturarComanda(); // Muestra menú de captura y manda las comandas al barista y cocinero
void facturar(BEBIDAS *inicio, ALIMENTOS *start, int mesa, float total);

void capturarBebida(BEBIDAS **inicio, BEBIDAS **aux, char bebidas[]);
void mandarBebidas(BEBIDAS *inicio, FILE *archTickets, FILE *archBebidasBin);
void liberarBebidas(BEBIDAS *inicio);

void capturarAlimento(ALIMENTOS **start, ALIMENTOS **temp, char alimentos[]);
void mandarAlimentos(ALIMENTOS *start, FILE *archTickets, FILE *archAlimentosBin);
void liberarAlimentos(ALIMENTOS *start);

void capturarComanda() {
    BEBIDAS *inicio, *aux;
    ALIMENTOS *start, *temp;
    int mesa;
    char opcion;
    float total = 0; 
    
    inicio = NULL;
    start = NULL;

    system("clear");
    printf("\t\t\t\tRegistrar Pedido\n\n");
    printf("Seleccione la mesa que está atendiendo: ");
    scanf(" %d", &mesa);
    if(mesa >= 1 && mesa <= 5) {
        do {
            system("clear");
            printf("\t\t\t\tMENU\n\n");
            printf("[A]mericano $35\n");
            printf("[C]apuchino $50\n");
            printf("[X]press $40\n");
            printf("[T]orta $60\n");
            printf("[B]agel $55\n");
            printf("[E]nsalada $40\n\n");
            printf("[M]andar comanda terminada\n");
            printf("[S]alir sin capturar\n\n");
            printf("Capture alimento/bebida--> ");
            scanf(" %c", &opcion);

            if(opcion == 'a' || opcion == 'A') {
                total += AMERICANO;
                capturarBebida(&inicio, &aux, "Americano");
                printf("\nSe ha agregado la bebida con éxito\n");
                system("sleep 1");
                system("clear");
            }
            else if(opcion == 'c' || opcion == 'C') {
                total += CAPUCHINO;
                capturarBebida(&inicio, &aux, "Capuchino");
                printf("\nSe ha agregado la bebida con éxito\n");
                system("sleep 1");
                system("clear");
            }
            else if(opcion == 'x' || opcion == 'X') {
                total += EXPRESS;
                capturarBebida(&inicio, &aux, "Express");
                printf("\nSe ha agregado la bebida con éxito\n");
                system("sleep 1");
                system("clear");
            }
            else if(opcion == 't' || opcion == 'T') {
                total += TORTA;
                capturarAlimento(&start, &temp, "Torta");
                printf("\nSe ha agregado el alimento con éxito\n");
                system("sleep 1");
                system("clear");
            }
            else if(opcion == 'b' || opcion == 'B') {
                total += BAGEL;
                capturarAlimento(&start, &temp, "Bagel");
                printf("\nSe ha agregado el alimento con éxito\n");
                system("sleep 1");
                system("clear");
            }
            else if(opcion == 'e' || opcion == 'E') {
                total += ENSALADA;
                capturarAlimento(&start, &temp, "Ensalada");
                printf("\nSe ha agregado el alimento con éxito\n");
                system("sleep 1");
                system("clear");
            }
            else if(opcion == 's' || opcion == 'S') {
                // SE LIBERAN LOS PEDIDOS CAPTURADOS EN CASO DE QUERER SALIR
                if(total > 0) {
                    liberarAlimentos(start);
                    liberarBebidas(inicio);
                    system("sleep 1");
                    system("clear");
                    mostrarMenuMesero();
                }
                //
                else {
                    system("sleep 1");
                    system("clear");
                    mostrarMenuMesero();
                }
            }
            else if(opcion == 'm' || opcion == 'M') {
                if(total == 0) {
                    printf("No se han registrado comandas\n");
                    system("sleep 1");
                    system("clear");
                    capturarComanda();
                }
                else {
                    facturar(inicio, start, mesa, total);
                }
            }
            else {
                printf("\nOpcion no válida\n");
                system("sleep 1");
                system("clear");
                capturarComanda();
            }
        }while(opcion != 's' || opcion != 'S');
    }
    else {
        printf("Dicha mesa no existe\n");
        system("sleep 1");
        system("clear");
        capturarComanda();
    }
}

void facturar(BEBIDAS *inicio, ALIMENTOS *start, int mesa, float total) {
    int numTicket = 1;
    char opcion;
    char linea[1024], numArchTicket[20];
    FILE *archTickets, *archBebidasBin, *archAlimentosBin;

    printf("\n[F]acturar\t\t[C]ancelar\n\nSelecciona una opcion--> ");
    scanf(" %c", &opcion);
    
    if(opcion == 'f' || opcion == 'F'){
        archTickets = fopen("tickets.txt","a+");
        if(archTickets == NULL) {
            printf("Error al abrir el archivo. Saliendo del sistema...\n");
            exit(-1);
        }

        // SE OBTIENE EL NUMERO DEL TICKET DE COMPRA
        while(fgets(numArchTicket, sizeof(linea), archTickets) != NULL){
            numTicket++;
        }
        //
        
        sprintf(numArchTicket, "%d", numTicket);
        strcat(numArchTicket, ".txt"); // Se concatena el numero de ticket 
        fprintf(archTickets, "%s\tVenta Total: $%.2f\n", numArchTicket, total);
        fclose(archTickets);

        // EN ESTE ARCHIVO SE ESCRIBEN LAS CAPTURAS DE ALIMENTOS Y BEBIDAS
        archTickets = fopen(numArchTicket, "w");
        if(archTickets == NULL) {
            printf("Error al abrir el archivo. Saliendo del sistema...\n");
            exit(-1);
        }
        //

        // SOLO SE ESCRIBEN LAS BEBIDAS CAPTURADAS
        archBebidasBin = fopen("pedidosBebidas.bin", "wb");
        if(archBebidasBin == NULL) {
            printf("Error al abrir el archivo. Saliendo del sistema...\n");
            exit(-1);
        }
        //

        // SOLO SE ESCRIBEN LOS ALIMENTOS CAPTURADOS
        archAlimentosBin = fopen("pedidosAlimentos.bin", "wb");
        if(archAlimentosBin == NULL) {
            printf("Error al abrir el archivo. Saliendo del sistema...\n");
            exit(-1);
        }
        //

        //SE IMPRIME EL NUMERO DE TICKET Y LA MESA PARA IMPRIMIRLOS EN bebidasServidas.txt y alimentosServidos.txt
        fprintf(archTickets, "%s \tMesa: %d\t\n\n", numArchTicket, mesa);
        
        mandarBebidas(inicio, archTickets, archBebidasBin);
        mandarAlimentos(start, archTickets, archAlimentosBin);
        fclose(archBebidasBin);
        fclose(archAlimentosBin);
        fclose(archTickets);

        liberarBebidas(inicio);
        liberarAlimentos(start);
        system("clear");
        mostrarMenuMesero();
    }
    else if(opcion == 'c' || opcion == 'C') {
        liberarBebidas(inicio);
        liberarAlimentos(start);
        system("clear");
        mostrarMenuMesero();
    }
    else {
        printf("Opcion no válida\n");
        system("sleep 1");
        system("clear");
        facturar(inicio, start, mesa, total);
    }
}

void capturarAlimento(ALIMENTOS **start, ALIMENTOS **temp, char alimentos[]) {
    ALIMENTOS *node;

    node = malloc(sizeof(ALIMENTOS));
    if(node == NULL) {
        printf("No hay espacio suficiente de memoria\n");
        exit(-1);
    }

    strcpy(node->alimento, alimentos); // Se asigna al elemento de la estructura el alimento capturado

    // SE CREA LA LISTA DE ALIMENTOS CAPTURADOS
    if(*start == NULL) {
        *start = node;
    }
    else {
        (*temp)->next = node;
    }
    node->next = NULL;
    *temp = node;
    //
}

void capturarBebida(BEBIDAS **inicio, BEBIDAS **aux, char bebidas[]) {
    BEBIDAS *nodo;
    
    nodo = malloc(sizeof(BEBIDAS));
    if(nodo == NULL) {
        printf("No hay espacio suficiente de memoria\n");
        exit(-1);
    }

    strcpy(nodo->bebida, bebidas); // Se asigna al elemento de la estructura la bebida capturada

    // SE CREA LA LISTA DE BEBIDAS CAPTURADAS
    if(*inicio == NULL) {
        *inicio = nodo;
    }
    else {
        (*aux)->sig = nodo;
    }
    nodo->sig = NULL;
    *aux = nodo;
    //
}

void mandarBebidas(BEBIDAS *inicio, FILE *archTickets, FILE *archBebidasBin) {
    BEBIDAS *nodo;
    nodo = inicio; // Se apunta al inicio de la lista

    // SE RECORRE LA LISTA PARA GUARDAR E IMPRIMIR LAS BEBIDAS CAPTURADAS
    while(nodo != NULL) {
        fwrite(nodo, sizeof(BEBIDAS), 1, archBebidasBin); 
        fprintf(archTickets, "%s\n", nodo->bebida); 
        nodo = nodo->sig;
    }
    //
}

void mandarAlimentos(ALIMENTOS *start, FILE *archTickets, FILE *archAlimentosBin) {
    ALIMENTOS *node;
    node = start; // Se apunta al inicio de la lista

    // SE RECORRE LA LISTA PARA GUARDAR E IMPRIMIR LOS ALIMENTOS CAPTURADOS
    while(node != NULL) {
        fwrite(node, sizeof(ALIMENTOS), 1, archAlimentosBin);
        fprintf(archTickets, "%s\n", node->alimento);
        node = node->next;
    }
    //
}

void liberarBebidas(BEBIDAS *inicio) {
    BEBIDAS *nodo;
    nodo = inicio;

    // SE VA LIBERANDO LA LISTA FIFO DE BEBIDAS
    while(nodo != NULL) {
        inicio = inicio->sig;
        free(nodo);
        nodo = inicio;
    }
    //
}

void liberarAlimentos(ALIMENTOS *start) {
    ALIMENTOS *node;
    node = start;

    // SE VA LIBERANDO LA LISTA FIFO DE BEBIDAS
    while(node != NULL) {
        start = start->next;
        free(node);
        node = start;
    }
    //
}