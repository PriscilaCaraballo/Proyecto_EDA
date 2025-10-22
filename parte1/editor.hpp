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
};

typedef struct _archivo* Archivo;
typedef struct _linea* Linea;


Archivo CrearArchivo(char *nombre);

TipoRet BorrarArchivo(Archivo &arch);

// --- Operaciones del editor ---
TipoRet InsertarLinea(Archivo arch, char *linea, unsigned int nroLinea);
TipoRet BorrarLinea(Archivo arch, unsigned int nroLinea);
TipoRet MostrarTexto(Archivo arch);
TipoRet ContarLineas(Archivo arch, unsigned int &cantidad);


// Reemplaza el contenido de una línea por un nuevo texto
TipoRet ReemplazarLinea(Archivo arch, unsigned int nroLinea, char *nuevoTexto);

// Busca una palabra y muestra las líneas donde aparece
TipoRet BuscarPalabra(Archivo arch, char *palabra);

// Guarda el contenido del archivo en un archivo de texto externo
TipoRet GuardarArchivo(Archivo arch, char *nombreArchivoDestino);

#endif // EDITOR_HPP

