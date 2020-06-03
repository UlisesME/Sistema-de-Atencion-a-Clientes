typedef struct usuarios{
    int idUsuario;
    char nombre[50];
    int tipoUsuario;
    bool estatus;
}USUARIOS;

typedef struct bebidas{
    char bebida[50];
    struct bebidas *sig;
}BEBIDAS;

typedef struct alimentos{
    char alimento[50];
    struct alimentos *next;
}ALIMENTOS;
