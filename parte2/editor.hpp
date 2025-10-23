#ifndef EDITOR_HPP
#define EDITOR_HPP

typedef enum _retorno  {
    OK, 
    ERROR, 
    NO_IMPLEMENTADA
} TipoRet;

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
    Version raizVersiones;  
};

typedef struct {
    char*nombreVersion;
    struct _version* subversiones;
    struct _version* siguienteHermano;

    Linea primera;
    Linea Ultima;
    unsigned int numLineas;
}Version;

typedef struct _archivo* Archivo;
typedef struct _linea* Linea;
typedef struct _version* Version;

Archivo CrearArchivo(char *nombre);

TipoRet BorrarArchivo(Archivo &arch);

// --- Operaciones del editor ---
TipoRet InsertarLinea(Archivo &arch, char * version, char * linea, unsigned int nroLinea);
TipoRet BorrarLinea(Archivo &arch, char * version, unsigned int nroLinea);
TipoRet MostrarTexto(Archivo &arch, char * version);
TipoRet ContarLineas(Archivo &arch, char * version, unsigned int &cantidad);

// ---Operaciones de versiones---
TipoRet CrearVersion(Archivo &arch, char * version);
TipoRet BorrarVersion(Archivo &arch, char * version);
TipoRet MostrarVersiones(Archivo &arch);
TipoRet Iguales(Archivo arch, char * version1, char * version2, bool &iguales);
TipoRet ContarVersiones(Archivo arch, int &cantidad);

#endif // EDITOR_HPP

