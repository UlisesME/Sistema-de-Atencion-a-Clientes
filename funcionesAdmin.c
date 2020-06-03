/********************************************************************
* funcionesAdmin.c - Funciones para el módulo de administrador      *
*                    con manejo de información mediante archivos    *
*                                                                   *
* Autor: Ulises Magaña                                              *
*                                                                   *
* Archivos: registroUsuarios.bin, usuarios.txt,                     *
*           alimentosServidos.txt, bebidasServidas.txt, tickets.txt *
*                                                                   *
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tipos.h"

// MENU ADMINISTRADOR. ENCONTRADO EN 'menus.c'
extern void mostrarMenuAdministrador();

void darAltaUsuario();
void darBajaUsuario();
void mostrarInformeUsuarios();
void mostrarBebidasAlimentos();
void mostrarHistoricoVentas();

void darAltaUsuario() {
    int id = 1;  // DA UN NUEVO ID AL REGISTRAR UN USUARIO
    USUARIOS *nodo;
    FILE *archUsuarios;

    archUsuarios = fopen("registroUsuarios.bin", "ab+");
    if(archUsuarios == NULL) {
        printf("Error al abrir el archivo. Saliendo del programa...\n");
        system("sleep 1");
        system("clear");
        exit(-1);
    }

    nodo = malloc(sizeof(USUARIOS));
    if(nodo == NULL) {
        printf("No hay espacio en memoria\n");
        exit(-1);
    }

    // SE LEE CUANTOS USUARIOS HAY REGISTRADOS
    while(!feof(archUsuarios)) {
        fread(nodo, sizeof(USUARIOS), 1, archUsuarios);
        if(feof(archUsuarios)) {
            break;
        }
        id++;  // SE INCREMENTA HASTA TENER UN NUEVO ID
    }
    //

    nodo->idUsuario = id;
    nodo->estatus = false;
    printf("Ingrese el nombre del usuario: ");
    scanf(" %[^\n]", nodo->nombre);
    printf("Ingrese el tipo de usuario:\n\n1-Mesero\n2-Barista\n3-Cocinero\n\nSeleccione una opción--> ");
    scanf(" %d", &nodo->tipoUsuario);

    fwrite(nodo, sizeof(USUARIOS), 1, archUsuarios); // SE REGISTRA UN NUEVO USUARIO
    free(nodo);
    fclose(archUsuarios);
}

void darBajaUsuario() {
    int id, pos;
    USUARIOS *nodo;
    FILE *archUsuarios;

    archUsuarios = fopen("registroUsuarios.bin", "rb+");
    if(archUsuarios == NULL) {
        printf("No hay usuarios registrados en el sistema\n");
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }

    nodo = malloc(sizeof(USUARIOS));
    if(nodo == NULL) {
        printf("No hay espacio en memoria\n");
        exit(-1);
    }

    printf("Ingrese el ID del usuario a dar de baja: ");
    scanf("%d", &id);

    while(!feof(archUsuarios)) {
        fread(nodo, sizeof(USUARIOS), 1, archUsuarios);
        if(feof(archUsuarios)) {
            break;
        }

        // SE MODIFICA EL ESTATUS DE UN USUARIO REGISTRADO A INACTIVO
        if(nodo->idUsuario == id){
            nodo->estatus = false;
            pos = ftell(archUsuarios)-sizeof(USUARIOS);
            fseek(archUsuarios, pos, SEEK_SET);
            fwrite(nodo, sizeof(USUARIOS), 1, archUsuarios);
        }
        //
    }

    free(nodo);
    fclose(archUsuarios);
}

void mostrarInformeUsuarios() {
    USUARIOS *nodo;
    FILE *archUsuarios;
    FILE *archUsuariosTxt;
    
    archUsuarios = fopen("registroUsuarios.bin", "rb");
    if(archUsuarios == NULL) {
        printf("No hay usuarios registrados en el sistema\n");
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }

    archUsuariosTxt = fopen("usuarios.txt", "w");
    if(archUsuariosTxt == NULL) {
        printf("Error al abrir el archivo. Saliendo del programa...\n");
        system("sleep 1");
        system("clear");
        exit(-1);
    }

    nodo = malloc(sizeof(USUARIOS));
    if(nodo == NULL) {
        printf("No hay espacio en memoria\n");
        exit(-1);
    }

    // MUESTRA LOS DATOS DE USUARIOS REGISTRADOS Y ACTUALIZA EL ARCHIVO 'usuarios.txt'
    while(!feof(archUsuarios)) {
        fread(nodo, sizeof(USUARIOS), 1, archUsuarios);
        if(feof(archUsuarios)) {
            break;
        }
        printf("ID: %d\n", nodo->idUsuario);
        printf("Nombre: %s\n", nodo->nombre);
        printf("Tipo de usuario: %d\n", nodo->tipoUsuario);
        printf("Estatus: %d\n\n", nodo->estatus);

        fprintf(archUsuariosTxt, "ID: %d\n", nodo->idUsuario);
        fprintf(archUsuariosTxt, "Nombre: %s\n", nodo->nombre);
        fprintf(archUsuariosTxt, "Tipo de usuario: %d\n", nodo->tipoUsuario);
        fprintf(archUsuariosTxt, "Estatus: %d\n\n", nodo->estatus);
    }
    //

    fclose(archUsuariosTxt);
    fclose(archUsuarios);

    printf("Presione enter para regresar al menú");
    __fpurge(stdin);
    getchar();
}

void mostrarBebidasAlimentos() {
    char linea[1024], alimentosServidos[50], bebidasServidas[50];
    FILE *archivoAlimentos, *archivoBebidas;

    archivoAlimentos = fopen("alimentosServidos.txt","r");
    if(archivoAlimentos == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    archivoBebidas = fopen("bebidasServidas.txt","r");
    if(archivoBebidas == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    printf("Alimentos Servidos\n\n");
    while(fgets(alimentosServidos, sizeof(linea), archivoAlimentos) != NULL){
        printf("%s", alimentosServidos);
    }

    printf("\n\nBebidas Servidas\n\n");
    while(fgets(bebidasServidas, sizeof(linea), archivoBebidas) != NULL){
        printf("%s", bebidasServidas);
    }
    
    fclose(archivoAlimentos);
    fclose(archivoBebidas);

    printf("\n\nPresione enter para regresar al menú");
    __fpurge(stdin);
    getchar();
}

void mostrarHistoricoVentas() {
    char linea[1024], alimentosServidos[50], bebidasServidas[50], ventas[50];
    FILE *archTickets, *archivoAlimentos, *archivoBebidas;

    archTickets = fopen("tickets.txt","r");
    if(archTickets == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    printf("Ventas realizadas\n\n");
    while(fgets(ventas, sizeof(linea), archTickets) != NULL){
        printf("%s", ventas);
    }
    
    fclose(archTickets);

    printf("\n\nPresione enter para regresar al menú");
    __fpurge(stdin);
    getchar();
}
