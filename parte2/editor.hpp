#ifndef EDITOR_HPP
#define EDITOR_HPP

typedef enum _retorno  {
    OK, 
    ERROR, 
    NO_IMPLEMENTADA
} TipoRet;

typedef struct _archivo* Archivo;
typedef struct _linea* Linea;
typedef struct _version* Version;
struct _linea {
    char *texto;
    struct _linea *siguiente;
    struct _linea *anterior;
    
};

struct _archivo {
    char *nombre;
    Version raizVersiones;  
};

struct _version {
    char* nombreVersion;
    struct _version* subversiones; 
    struct _version* siguienteHermano;
    struct _linea *primera;
    struct _linea *ultima;
    unsigned int numLineas;
};


Archivo CrearArchivo(char *nombre);
TipoRet BorrarArchivo(Archivo &arch);


// ============================================================
//  1. Operaciones principales sobre versiones
// ============================================================

TipoRet CrearVersion(Archivo &arch, char *version);
//arreglar para poner padre
TipoRet CrearVersionRec(Version actual,  const char* version, Version nuevo);
TipoRet BorrarVersion(Archivo &arch, char *version);
TipoRet MostrarVersiones(Archivo arch);
TipoRet Iguales(Archivo arch, char *version1, char *version2, bool &iguales);
TipoRet ContarVersiones(Archivo arch, int &cantidad);

// ============================================================
//  2. Operaciones principales del editor de texto
// ============================================================

TipoRet InsertarLineaRec(Linea actual, unsigned int pos, unsigned int nroLinea, Linea nueva);
TipoRet InsertarLinea(Archivo &arch, char *version, char *linea, unsigned int nroLinea);
TipoRet BorrarLinea(Archivo &arch, char *version, unsigned int nroLinea);
TipoRet MostrarTexto(Archivo arch, char *version);
TipoRet ContarLineas(Archivo arch, char *version, unsigned int &cantidad);

// ============================================================
//  3. Funciones auxiliares generales
// ============================================================
// crear raiz de versiones
Version CrearNodo(const char *nombre);

// Búsqueda y liberación de estructuras
Version BuscarVersion(Version raiz, const char *nombre);
void LiberarLineasRecursivo(Linea l);
void LiberarVersiones(Version v);

// Impresión y conteo recursivo de versiones
void MostrarVersionesRec(Version v);
int ContarVersionesRec(Version v);

//borrar version recursivo
int BorrarVersionRec(Version versionActual, const char *nombre);

#endif // EDITOR_HPP
 