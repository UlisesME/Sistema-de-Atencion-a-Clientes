/********************************************************************
* menus.c - Muestra los menús de los tipos de usuario y llama a sus *
*           respectivas funciones                                   *
*                                                                   *
* Autor: Ulises Magaña                                              *
*                                                                   *
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tipos.h"

// FUNCION DE SALIDA DEL SISTEMA PARA MESERO, BARISTA Y COCINERO. ENCONTRADO EN 'principal.c'
extern void cerrarSesion(int id);

// FUNCIONES DEL ADMINISTRADOR. ENCONTRADOS EN 'funcionesAdmin.c'
extern void darAltaUsuario();
extern void darBajaUsuario();
extern void mostrarInformeUsuarios();
extern void mostrarBebidasAlimentos();
extern void mostrarHistoricoVentas();

// FUNCION DE MESERO. ENCONTRADO EN 'funcionesMesero.c'
extern void capturarComanda();

// FUNCIONES DE BARISTA Y COCINERO. ENCONTRADOS EN 'funcionesBaristaCocinero'
extern void cargarBebidas(BEBIDAS **inicio, BEBIDAS **aux, int *flag);
extern void mostrarBebidaEnLista(BEBIDAS *inicio);
extern void liberarBebidaEnLista(BEBIDAS **inicio, int *flag);
extern void cargarAlimentos(ALIMENTOS **start, ALIMENTOS **temp, int *flag);
extern void mostrarAlimentoEnLista(ALIMENTOS *start);
extern void liberarAlimentoEnLista(ALIMENTOS **start, int *flag);

// MENUS
void mostrarMenuAdministrador();
void mostrarMenuMesero(int id);
void mostrarMenuBarista(int id);
void mostrarMenuCocinero(int id);
void mostrarMenuAyuda();

void mostrarMenuAdministrador() {
    char opcion;
    
    printf("\t\t\t\tMENU ADMINISTRADOR\n");
    printf("\n1- Dar de alta usuario");
    printf("\n2- Dar de baja usuario");
    printf("\n3- Informe de usuarios");
    printf("\n4- Mostrar lista de bebidas/alimentos preparados");
    printf("\n5- Mostrar historico de ventas");
    printf("\n6- Ayuda");
    printf("\n7- Salir del sistema");
    printf("\n\nSelecciona una opcion--> ");
    scanf(" %c", &opcion);
    if(opcion == '1') {
        system("clear");
        darAltaUsuario();
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }
    else if(opcion == '2') {
        system("clear");
        darBajaUsuario();
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }
    else if(opcion == '3') {
        system("clear");
        mostrarInformeUsuarios();
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }
    else if(opcion == '4') {
        system("clear");
        mostrarBebidasAlimentos();
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }
    else if(opcion == '5') {
        system("clear");
        mostrarHistoricoVentas();
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }
    else if(opcion == '6') {
        system("clear");
        mostrarMenuAyuda();
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }
    else if(opcion == '7') {
        printf("\nSaliendo del sistema...\n");
        system("sleep 1");
        exit(0);
    }
    else{
        printf("Opción no válida\n");
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
    }
}

void mostrarMenuMesero(int id) {
    char opcion;

    do {
        printf("\t\t\t\tMENU MESERO\n");
        printf("\n1- Capturar comanda"); 
        printf("\n2- Salir del sistema");
        printf("\n\nSelecciona una opcion--> ");
        scanf(" %c", &opcion);
        if(opcion == '1') {
            capturarComanda();
        }
        else if(opcion == '2') {
            cerrarSesion(id);
        }
        else{
            printf("Opción no válida\n");
            system("sleep 1");
            system("clear");
        }
    }while(opcion != '1' || opcion != '2');

}

void mostrarMenuBarista(int id) {
    int flag = 0;
    char opcion;
    BEBIDAS *inicio, *aux;
    
    inicio = NULL;
    cargarBebidas(&inicio, &aux, &flag);

    do {
        printf("\t\t\t\tMENU BARISTA\n");
        printf("\n1- Mostrar bebida en lista");
        printf("\n2- Liberar bebida");
        printf("\n3- Salir del sistema");
        printf("\n\nSelecciona una opcion--> ");
        scanf(" %c", &opcion);

        if(opcion == '1') {
            mostrarBebidaEnLista(inicio);
            system("sleep 1.5");
            system("clear");
        }
        else if(opcion == '2') {
            liberarBebidaEnLista(&inicio, &flag);
            system("sleep 1.5");
            system("clear");
        }
        else if(opcion == '3') {
            if(flag == 0) {
                printf("No puedes salir del sistema hasta liberar todas las bebidas\n");
                system("sleep 1");
                system("clear");
            }
            else {
                cerrarSesion(id);
            }
        }
        else{
            printf("Opción no válida\n");
            system("sleep 1");
            system("clear");
        }
    }while(opcion != '1' || opcion != '2' || opcion != '3');
}

void mostrarMenuCocinero(int id) {
    int flag = 0;
    char opcion;
    ALIMENTOS *start, *temp;

    start = NULL;
    cargarAlimentos(&start, &temp, &flag);

    do {
        printf("\t\t\t\tMENU COCINERO\n");
        printf("\n1- Mostrar alimento en lista");
        printf("\n2- Liberar alimento");
        printf("\n3- Salir del sistema");
        printf("\n\nSelecciona una opcion--> ");
        scanf(" %c", &opcion);

        if(opcion == '1') {
            mostrarAlimentoEnLista(start);
            system("sleep 1.5");
            system("clear");
        }
        else if(opcion == '2') {
            liberarAlimentoEnLista(&start, &flag);
            system("sleep 1.5");
            system("clear");
        }
        else if(opcion == '3') {
            if(flag == 0) {
                printf("No puedes salir del sistema hasta liberar todas las bebidas\n");
                system("sleep 1");
                system("clear");
            }
            else {
                cerrarSesion(id);
            }
        }
        else{
            printf("Opción no válida\n");
            system("sleep 1");
            system("clear");
        }
    }while(opcion != '1' || opcion != '2' || opcion != '3');
}

void mostrarMenuAyuda() {
    printf("\t\t\t\t\t\t\tGuia de uso\n\n");
    printf("Menu: Para poder escoger una opcion dentro del menu debe ingresar el numero donde se encuentra la instruccion.\n\n");
    printf("Administrador: Se inicia sesion via password y se despliega en pantalla su respectivo menu de usuario.\n\n");
    printf("Mesero/Barista/Cocinero: Se inicia sesion al ser registrado por el administrador y se despliega en pantalla su respectivo menu de usuario.\n");
    printf("\nMesero/Barista/Cocinero: Al salir del sistema se da de baja al usuario.\n");
    printf("\nBarista/Cocinero: Solamente se puede salir del sistema cuando se hayan liberado las bebidas o los alimentos.\n");
    printf("\n\n\t\t\t\t\t\tFormas de ejecutar el programa\n\nPrimera forma de ejecucion: $./iCoffee.exe (En este caso el programa inicia mostrando los nombres de los desarrolladores del sistema y se dirige al modo administrador).\n");
    printf("Segunda forma de ejecucion: $./iCoffee.exe -usuario (Entrar como modo usuario al sistema).\n");
    printf("Tercera forma de ejecucion: $./iCoffee.exe -ls (Despliega en pantalla el listado de todos los usuarios dados de alta).\n");
    printf("Cuarta forma de ejecucion: $./iCoffee.exe -t (Despliega en pantalla todos los tickets de venta realizados).\n");
    printf("\n\nPresione enter para continuar");
    __fpurge(stdin);
    getchar(); 
}