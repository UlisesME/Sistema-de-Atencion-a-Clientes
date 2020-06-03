/********************************************************************
* funcionesBaristaCocinero.c - Funciones para los módulos de        *
*                              barista y cocinero mediante uso de   *
*                              listas dinámicas y archivos          *
*                                                                   *
* Autor: Ulises Magaña                                              *
*                                                                   *
* Archivos: pedidosBebidas.bin, tickets.txt, bebidasServidas.txt    *
*           pedidosAlimentos.bin, alimentosServidos.txt             *
*                                                                   *
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tipos.h"

void cargarBebidas(BEBIDAS **inicio, BEBIDAS **aux, int *flag);
void mostrarBebidaEnLista(BEBIDAS *inicio);
void liberarBebidaEnLista(BEBIDAS **inicio, int *flag);
void cargarAlimentos(ALIMENTOS **start, ALIMENTOS **temp, int *flag);
void mostrarAlimentoEnLista(ALIMENTOS *start);
void liberarAlimentoEnLista(ALIMENTOS **start, int *flag);

void cargarBebidas(BEBIDAS **inicio, BEBIDAS **aux, int *flag) {
    BEBIDAS *nodo;
    FILE *archBebidasBin;

    // AL HABER LIBERADO TODAS LAS BEBIDAS Y NO TENER UN NUEVO PEDIDO
    archBebidasBin = fopen("pedidosBebidas.bin", "rb");    
    if(archBebidasBin == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    fseek(archBebidasBin, 0, SEEK_END);

    // ARCHIVO VACIO
    if(ftell(archBebidasBin) == 0){
        *flag = 1; // Indica que todas las bebidas han sido liberadas
    }
    //
    else {
        *flag = 0;
    }

    fclose(archBebidasBin);
    //

    archBebidasBin = fopen("pedidosBebidas.bin", "rb");
    if(archBebidasBin == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    // SE CREA LA LISTA DE BEBIDAS QUE TIENE EL ARCHIVO
    while(!feof(archBebidasBin)) {
        nodo = malloc(sizeof(BEBIDAS));
        if(nodo == NULL) {
            printf("No hay espacio suficiente de memoria\n");
            exit(-1);
        }

        fread(nodo, sizeof(BEBIDAS), 1, archBebidasBin);
        if(feof(archBebidasBin)) {
            free(nodo);
            break;
        }

        if(*inicio == NULL) {
            *inicio = nodo;
        }
        else {
            (*aux)->sig = nodo;
        }
        nodo->sig = NULL;
        *aux = nodo;
    }
    //

    fclose(archBebidasBin);
}

void mostrarBebidaEnLista(BEBIDAS *inicio) {
    BEBIDAS *nodo;
    nodo = inicio; // Se apunta al inicio de la lista

    if(inicio != NULL) {
        // SE MUESTRA LA BEBIDA A PREPARAR
        if(nodo != NULL) {
            printf("%s\n", nodo->bebida);
            nodo = nodo->sig;
        }
        //
    }
    else if(nodo == NULL) {
        printf("\nNo hay bebidas en lista\n");
    }
}

void liberarBebidaEnLista(BEBIDAS **inicio, int *flag) {
    int numTicket = 0;
    char linea[1024], numArchTicket[20], formatoTicket[20];
    BEBIDAS *nodo;
    FILE *archTickets, *archivoBebidas, *archBebidasBin;

    // SE OBTIENE EL NUMERO DE TICKET DE COMPRA
    archTickets = fopen("tickets.txt","r");
    if(archTickets == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    while(fgets(numArchTicket, sizeof(linea), archTickets) != NULL){
        numTicket++;
    }
    
    sprintf(numArchTicket, "%d", numTicket);
    strcat(numArchTicket, ".txt");
    fclose(archTickets);
    //

    archTickets = fopen(numArchTicket, "r");
    if(archTickets == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    fgets(formatoTicket, sizeof(linea), archTickets); // Se lee el numero de ticket y el numero de mesa
    formatoTicket[strlen(formatoTicket) - 1] = 0; // Se anula el último caracter '\n'
    fclose(archTickets);

    archivoBebidas = fopen("bebidasServidas.txt", "a");
    if(archivoBebidas == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    nodo = *inicio; // Se apunta al inicio de la lista

    // SE LIBERAN LAS BEBIDAS FIFO Y SE GUARDAN EN UN ARCHIVO
    if(nodo != NULL) {
        *inicio = (*inicio)->sig;
        printf("Se ha entregado: %s\n", nodo->bebida);
        fprintf(archivoBebidas, "%s %s\n", formatoTicket, nodo->bebida);
        free(nodo);
        
        // AL LIBERAR TODAS LAS BEBIDAS
        if(nodo->sig == NULL) {
            *flag = 1;

            // SE DEJA EL ARCHIVO VACIO
            archBebidasBin = fopen("pedidosBebidas.bin", "wb");
            if(archBebidasBin == NULL) {
                printf("Error al abrir el archivo. Saliendo del sistema...\n");
                exit(-1);
            }
            //
            fclose(archBebidasBin);
        }
        //
    }
    //
    else {
        printf("\nSe han preparado todas las bebidas\n");
    }

    fclose(archivoBebidas);
}

void cargarAlimentos(ALIMENTOS **start, ALIMENTOS **temp, int *flag) {
    ALIMENTOS *node;
    FILE *archAlimentosBin;

    // AL HABER LIBERADO TODOS LOS ALIMENTOS Y NO TENER UN NUEVO PEDIDO
    archAlimentosBin = fopen("pedidosAlimentos.bin", "rb");
    if(archAlimentosBin == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    fseek(archAlimentosBin, 0, SEEK_END);

    // ARCHIVO VACIO
    if(ftell(archAlimentosBin) == 0){
        *flag = 1; // Indica que todos los alimentos han sido liberados
    }
    //
    else {
        *flag = 0;
    }

    fclose(archAlimentosBin);
    //

    archAlimentosBin = fopen("pedidosAlimentos.bin", "rb");
    
    if(archAlimentosBin == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    // SE CREA LA LISTA DE ALIMENTOS QUE TIENE EL ARCHIVO
    while(!feof(archAlimentosBin)) {
        node = malloc(sizeof(ALIMENTOS));
        if(node == NULL) {
            printf("No hay espacio suficiente de memoria\n");
            exit(-1);
        }

        fread(node, sizeof(ALIMENTOS), 1, archAlimentosBin);
        if(feof(archAlimentosBin)) {
            free(node);
            break;
        }

        if(*start == NULL) {
            *start = node;
        }
        else {
            (*temp)->next = node;
        }
        node->next = NULL;
        *temp = node;
    }
    //

    fclose(archAlimentosBin);
}

void mostrarAlimentoEnLista(ALIMENTOS *start) {
    ALIMENTOS *node;
    node = start; // Se apunta al inicio de la lista

    if(start != NULL) {
        // SE MUESTRA EL ALIMENTO A PREPARAR
        if(node != NULL) {
            printf("%s\n", node->alimento);
            node = node->next;
        }
        //
    }
    else if(node == NULL) {
        printf("\nNo hay alimentos en lista\n");
    }
}

void liberarAlimentoEnLista(ALIMENTOS **start, int *flag) {
    int numTicket = 0;
    char linea[1024], numArchTicket[20], formatoTicket[20];
    ALIMENTOS *node;
    FILE *archTickets, *archivoAlimentos, *archAlimentosBin;

    // SE OBTIENE EL NUMERO DE TICKET DE COMPRA
    archTickets = fopen("tickets.txt","r");
    if(archTickets == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    while(fgets(numArchTicket, sizeof(linea), archTickets) != NULL){
        numTicket++;
    }
    
    sprintf(numArchTicket, "%d", numTicket);
    strcat(numArchTicket, ".txt");
    fclose(archTickets);
    //

    archTickets = fopen(numArchTicket, "r");
    if(archTickets == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    fgets(formatoTicket, sizeof(linea), archTickets); // Se lee el numero de ticket y el numero de mesa
    formatoTicket[strlen(formatoTicket) - 1] = 0; // Se anula el último caracter '\n'
    fclose(archTickets);

    archivoAlimentos = fopen("alimentosServidos.txt", "a");
    if(archivoAlimentos == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    node = *start; // Se apunta al inicio de la lista
    
    // SE LIBERAN LOS ALIMENTOS FIFO Y SE GUARDAN EN UN ARCHIVO
    if(node != NULL) {
        *start = (*start)->next;
        printf("Se ha entregado: %s\n", node->alimento);
        fprintf(archivoAlimentos, "%s %s\n", formatoTicket, node->alimento);
        free(node);

        // AL LIBERAR TODAS LOS ALIMENTOS
        if(node->next == NULL) {
            *flag = 1;

            // SE DEJA EL ARCHIVO VACIO
            archAlimentosBin = fopen("pedidosAlimentos.bin", "wb");
            if(archAlimentosBin == NULL) {
                printf("Error al abrir el archivo. Saliendo del sistema...\n");
                exit(-1);
            }
            //
            fclose(archAlimentosBin);
        }
        //
    }
    //
    else {
        printf("\nSe han preparado todos los alimentos\n");
    }

    fclose(archivoAlimentos);
}
