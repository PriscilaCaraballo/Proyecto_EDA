#ifndef EDITOR_HPP
#define EDITOR_HPP


// Definiciones de tipos

// Tipo de retorno de operaciones
typedef enum _retorno  {
    OK, 
    ERROR, 
    NO_IMPLEMENTADA
} TipoRet;

// struct
struct _linea {
    char *texto;
    struct _linea *siguiente;
    struct _linea *anterior;
};

struct _archivo {
    char *nombre;
    struct _linea *primera;
    struct _linea *ultima;
    unsigned int numLineas;  
};

//estructuras
// typedef  enum _retorno TipoRet;
typedef struct _archivo* Archivo;


//funciones
//creacion y destruccion
Archivo CrearArchivo(char *nombre);

TipoRet BorrarArchivo(Archivo &arch);

// --- Operaciones del editor ---
TipoRet InsertarLinea(Archivo arch, char *linea, unsigned int nroLinea);
TipoRet BorrarLinea(Archivo arch, unsigned int nroLinea);
TipoRet MostrarTexto(Archivo arch);
TipoRet ContarLineas(Archivo arch, unsigned int &cantidad);

#endif // EDITOR_HPP



//posible estructura para los struct de lista dobemente enlazada


//Version 2 de structs ------------

// typedef struct Linea{
//     int numero;
//     char *contenido;
//     struct _Linea *sigiente;
//     struct _Linea *anterior;
//};Linea

//typedef struct Archivo{
//    char *nombre
//    int totlalines;
//    Linea *primera;
//    Linea *ultima;
//};Archivo