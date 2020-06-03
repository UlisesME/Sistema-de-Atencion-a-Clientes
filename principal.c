/********************************************************************
* iCoffee.exe - Ejecutable para sistema de administración de una    *
*               cafetería                                           *
*                                                                   *
* principal.c - Maneja los argumentos de la línea de comandos y los *
*               inicios de sesión del administrador y los usuarios  *
*                                                                   *
* Autor: Ulises Magaña                                              *
*                                                                   *
* Propósito: Aplicación de los fundamentos de programación en un    *
*            sistema real                                           *
*                                                                   *
* Uso: Correr el programa con el makefile.                          *
*      Argumentos aceptados: [-ls], [-t], [-usuario].               *
*      Ej: ./iCoffee.exe (Entra al módulo de administración)        *
*          ./iCoffee.exe -t (Despliega todos los tickets)           *
*                                                                   *
* Archivos: registroUsuarios.bin, datosAdmin.txt, tickets.txt       *
*                                                                   *
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tipos.h"

// MENÚS DE LOS CUATRO MÓDULOS DEL SISTEMA. ENCONTRADOS EN 'menus.c'
extern void mostrarMenuAdministrador();
extern void mostrarMenuMesero();
extern void mostrarMenuBarista();
extern void mostrarMenuCocinero();

// FUNCIONES DE INICIO DE SESIÓN Y OPCIONES A DESPLEGAR DEPENDIENDO DE LOS ARGUMENTOS DE LA LINEA DE COMANDOS
void crearAdministrador();
void ingresarAdministrador();
void ingresarUsuario();
void ingresarModulo();
void cerrarSesion(int id);
void desplegarUsuarios();
void desplegarTickets();


int main(int argc, char **argv) {
    // SI SE EJECUTA SOLAMENTE './iCoffee.exe'
    if(argc == 1) {
        ingresarAdministrador();
    }
    //

    // SE VERIFICA LA OPCION A DESPLEGAR AL TENER DOS ARGUMENTOS EN LA LINEA DE COMANDOS
    if(argc == 2) { 
        if(strcmp(argv[1], "-usuario") == 0) {
            system("clear");
            ingresarUsuario();
        }
        else if(strcmp(argv[1], "-ls") == 0) {
            printf("Lista de usuarios\n\n");
            desplegarUsuarios();
        }
        else if(strcmp(argv[1], "-t") == 0) {
            printf("Tickets\n\n");
            desplegarTickets();
        }  
        else {
            printf("No existe dicho argumento. Saliendo del sistema...\n");
            system("sleep 1");
            system("clear");
        }
    }
    //

    else {
        printf("Saliendo del sistema...\n");
        system("sleep 1");
        system("clear");
    }
    return(0);
}

void crearAdministrador() {
    char user[50];
    char password[50];
    FILE *archivoAdmin;

    printf("Ingresar nombre de administrador: ");
    scanf(" %[^\n]", user);
    if(strlen(user)>=50) {
        printf("El nombre del usuario debe ser menor a 50 caracteres\n");
        exit(-1);
    }

    printf("Ingresar contraseña de administrador: ");
    scanf(" %[^\n]", password);
    if(strlen(user)>=50) {
        printf("La contraseña del usuario debe ser menor a 50 caracteres\n");
        exit(-1);
    }

    // SE GUARDA EL NOMBRE DE USUARIO Y CONTRASEÑA EN 'datosAdmin.txt'
    archivoAdmin = fopen("datosAdmin.txt","w");
    if(archivoAdmin == NULL) {
        printf("Error al crear el archivo. Saliendo del sistema...");
        system("sleep 1");
        exit(-1);
    }
    fprintf(archivoAdmin, "%s\n", user);
    fprintf(archivoAdmin, "%s\n", password);
    fclose(archivoAdmin);
    //
}

void ingresarAdministrador() {
    char usuario[50], user[50];
    char contrasena[50], password[50];
    FILE *archivoAdmin;
   
    archivoAdmin = fopen("datosAdmin.txt", "r");

    //SE CREA UN ADMINISTRADOR EN CASO DE QUE NO EXISTA
    if(archivoAdmin == NULL) {
        crearAdministrador();
    }
    //

    // SE LEE EL ARCHIVO PARA OBTENER EL USUARIO Y LA CONTRASEÑA
    fscanf(archivoAdmin, " %[^\n]", user);
    fscanf(archivoAdmin, " %[^\n]", password);
    fclose(archivoAdmin);
    //

    printf("Ingresar nombre del administrador: ");
    scanf(" %[^\n]", usuario);
    printf("Ingresar contraseña: ");
    scanf(" %[^\n]", contrasena);

    // SE COMPARAN LOS DATOS DEL ARCHIVO LEIDO CON LOS DATOS INGRESADOS
    if(strcmp(usuario, user) == 0 && strcmp(contrasena, password) == 0) {
        printf("Ingresando al menú de administrador... \n");
        system("sleep 1");
        system("clear");
        mostrarMenuAdministrador();
        exit(0);
    }
    else {
        printf("El nombre del usuario o la contraseña son incorrectos\n");
        system("sleep 1");
        system("clear");
        ingresarAdministrador();
    }
    //
}

void ingresarUsuario() {
    int id, tipoUsuario;
    int contador = 0;  // Cuenta si hay un mismo tipo de usuario dentro del sistema 
    char nombreUsuario[50];
    USUARIOS *nodo;
    FILE *archUsuarios;
    
    archUsuarios = fopen("registroUsuarios.bin", "rb");
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

    printf("Ingresa tu ID de usuario: ");
    scanf(" %d", &id);
    printf("Ingresa tu nombre: ");
    scanf(" %[^\n]", nombreUsuario);
    printf("Ingresa tu tipo de usuario (1-Mesero, 2-Barista, 3-Cocinero): ");
    scanf(" %d", &tipoUsuario);

    // SE VERIFICA QUE SI HAY UN MISMO TIPO DE USUARIO DENTRO (ESTATUS 1) DEL SISTEMA
    while(!feof(archUsuarios)) {
        fread(nodo, sizeof(USUARIOS), 1, archUsuarios);
        if(feof(archUsuarios)) {
            break;
        }
        if(tipoUsuario == nodo->tipoUsuario) {
            if(id != nodo->idUsuario && nodo->estatus == true) {
                contador++;
            }
        }
    }
    //

    if(contador > 0) {
        printf("\nYa hay un mismo tipo de usuario trabajando en el momento. Vuelve mas tarde.\n");
        free(nodo);
        fclose(archUsuarios);
        system("sleep 1.5");
        system("clear");
        exit(0);
    }

    free(nodo);
    fclose(archUsuarios);

    ingresarModulo(id, nombreUsuario, tipoUsuario);
}

void ingresarModulo(int id, char nombreUsuario[], int tipoUsuario) {
    int flag;
    int pos;
    USUARIOS *nodo;
    FILE *archUsuarios;

    archUsuarios = fopen("registroUsuarios.bin", "rb+");
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

    // SE INGRESA AL MÓDULO CORRESPONDIENTE DEL USUARIO 
    while(!feof(archUsuarios)) {
        fread(nodo, sizeof(USUARIOS), 1, archUsuarios);
        if(feof(archUsuarios)) {
            break;
        }
        if(nodo->idUsuario == id && strcmp(nodo->nombre, nombreUsuario) == 0) { 
            flag = 1;
            nodo->estatus = true;
            pos = ftell(archUsuarios)-sizeof(USUARIOS); 
            fseek(archUsuarios, pos, SEEK_SET);
            fwrite(nodo, sizeof(USUARIOS), 1, archUsuarios);
            free(nodo);
            fclose(archUsuarios);

            if(tipoUsuario == 1) {
                system("clear");
                mostrarMenuMesero(id);
            }
            else if(tipoUsuario == 2) {
                system("clear");
                mostrarMenuBarista(id);
            }
            else if(tipoUsuario == 3) {
                system("clear");
                mostrarMenuCocinero(id);
            }
        }
    }
    //

    // SI LOS DATOS DEL USUARIO SON INCORRECTOS
    if(flag != 1) {
        printf("\nNo se encontraron coincidencias\n");
        free(nodo);
        system("sleep 1");
        system("clear");
        ingresarUsuario();
    }
}

void cerrarSesion(int id) {
    int pos;
    USUARIOS *nodo;
    FILE *archUsuarios;

    archUsuarios = fopen("registroUsuarios.bin", "rb+");
    if(archUsuarios == NULL) {
        printf("Error al abrir el archivo. Saliendo del programa...\n");
        exit(-1);
    }
    
    nodo = malloc(sizeof(USUARIOS));
    if(nodo == NULL) {
        printf("No hay espacio en memoria\n");
        exit(-1);
    }

    while(!feof(archUsuarios)) {
        fread(nodo, sizeof(USUARIOS), 1, archUsuarios);
        if(feof(archUsuarios)) {
            break;
        }

        // SE CAMBIA EL ESTATUS DEL USUARIO CORRESPONDIENTE
        if(id == nodo->idUsuario) {
            nodo->estatus = false;
            pos = ftell(archUsuarios)-sizeof(USUARIOS);
            fseek(archUsuarios, pos, SEEK_SET);
            fwrite(nodo, sizeof(USUARIOS), 1, archUsuarios);
            free(nodo);
            fclose(archUsuarios);
            break;
        }
        //
    }

    printf("\nSaliendo del sistema...\n");
    system("sleep 1");
    exit(0);
}

void desplegarUsuarios() {
    USUARIOS *nodo;
    FILE *archUsuarios;
    
    archUsuarios = fopen("registroUsuarios.bin", "rb");
    if(archUsuarios == NULL) {
        printf("No hay usuarios registrados en el sistema\n");
        system("sleep 1");
        system("clear");
    }

    nodo = malloc(sizeof(USUARIOS));
    if(nodo == NULL) {
        printf("No hay espacio en memoria\n");
        exit(-1);
    }

    while(!feof(archUsuarios)) {
        fread(nodo, sizeof(USUARIOS), 1, archUsuarios);
        if(feof(archUsuarios)) {
            break;
        }
        printf("ID: %d\n", nodo->idUsuario);
        printf("Nombre: %s\n\n", nodo->nombre);
    }

    free(nodo);
    fclose(archUsuarios);
}

void desplegarTickets() {
    char linea[1024], ventas[50];
    FILE *archTickets;

    archTickets = fopen("tickets.txt","r");
    if(archTickets == NULL) {
        printf("Error al abrir el archivo. Saliendo del sistema...\n");
        exit(-1);
    }

    while(fgets(ventas, sizeof(linea), archTickets) != NULL) {
        printf("%s", ventas);
    }
    
    fclose(archTickets);
}