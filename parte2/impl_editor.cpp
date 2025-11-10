// editor_impl.cpp
#include "editor.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <cstring>

#ifndef _WIN32
#include <unistd.h>
#endif


// ============================================================
//  0. Operaciones principales sobre archivos
// ============================================================

Archivo CrearArchivo(char *nombre) {
    Archivo nuevo = (Archivo) malloc(sizeof(struct _archivo));
    if (!nuevo) return NULL;
    nuevo->nombre = (char *) malloc(strlen(nombre) + 1);
    if (!nuevo->nombre)
    {
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->nombre, nombre);
    nuevo->raizVersiones = NULL;
    return nuevo;
}

TipoRet BorrarArchivo(Archivo &arch) {
    if (!arch) return ERROR;

    LiberarVersiones(arch->raizVersiones);
    free(arch->nombre);
    free(arch);
    arch = NULL;
    return OK;
}

// ============================================================
//  1. Operaciones principales sobre versiones
// ============================================================
// no esta copiando lineas del padre a la nueva version
TipoRet CrearVersion(Archivo &arch, char *version) {
    if (!arch || !version) return ERROR;

    // Si no hay raíz, crearla
    if (arch->raizVersiones == NULL) {
        arch->raizVersiones = CrearNodo(version);
        if (!arch->raizVersiones)
            return ERROR;   
        
        return OK;
    }

    // Verificar que no exista
    if (BuscarVersion(arch->raizVersiones, version))
        return ERROR;

    // Buscar el padre (parte antes del último punto)
    char *ultimoPunto = strrchr(version, '.');
    Version padre = NULL;
    if (ultimoPunto) {
        char padreStr[50];
        strncpy(padreStr, version, ultimoPunto - version);
        padreStr[ultimoPunto - version] = '\0';
        padre = BuscarVersion(arch->raizVersiones, padreStr);
    }
    
    // Si no tiene punto, se agrega como hermano de la raíz
    Version nuevo = CrearNodo(version);
    if (!nuevo) return ERROR;

    if (!padre) {
        Version aux = arch->raizVersiones;
        while (aux->siguienteHermano)
            aux = aux->siguienteHermano;
        aux->siguienteHermano = nuevo;
        return OK;
    }

    return CrearVersionRec(arch->raizVersiones, padre->nombreVersion, nuevo);
}

TipoRet CrearVersionRec(Version actual, const char *version, Version nuevo) {
    if (!actual) return ERROR;

    // Si encontramos el padre directo
    if (strcmp(actual->nombreVersion, version) == 0) {
        // Agregar como subversión
        if (!actual->subversiones) {
            actual->subversiones = nuevo;
        } else {
            Version aux = actual->subversiones;
            while (aux->siguienteHermano)
                aux = aux->siguienteHermano;
            aux->siguienteHermano = nuevo;
        }
        return OK;
    }

    // Buscar recursivamente en hijos y hermanos
    if (CrearVersionRec(actual->subversiones, version, nuevo) == OK)
        return OK;
    return CrearVersionRec(actual->siguienteHermano, version, nuevo);
}

TipoRet BorrarVersion(Archivo &arch, char *version) {
    if (arch == NULL || arch->raizVersiones == NULL || version == NULL)
        return ERROR;

    //  Caso especial: borrar la raíz
    if (strcmp(arch->raizVersiones->nombreVersion, version) == 0) {
        LiberarVersiones(arch->raizVersiones);
        arch->raizVersiones = NULL;
        return OK;
    }

    //  Caso general: buscar recursivamente dentro del árbol
    int borrado = BorrarVersionRec(arch->raizVersiones, version);
    if (!borrado)
        return ERROR;
    return OK;
}

TipoRet MostrarVersiones(Archivo arch) {
    if (arch == NULL || arch->raizVersiones == NULL) return ERROR;

    printf("%s\n\n", arch->nombre);
    MostrarVersionesRec(arch->raizVersiones);

    return OK;
}

TipoRet Iguales(Archivo arch, char * version1, char * version2, bool &iguales) {
    if(arch ==NULL ) return ERROR;
    if (version1 ==  NULL || version2 == NULL) return ERROR;

    Version ver1 = BuscarVersion(arch->raizVersiones, version1);
    Version ver2 = BuscarVersion(arch->raizVersiones, version2);

    if (ver1 == NULL || ver2 == NULL) return ERROR;
    if (ver1->numLineas != ver2->numLineas) {
        iguales = false;
        return OK;
    }
    if ((ver1->numLineas == 0) && (ver2->numLineas == 0)) {
    iguales = true;
    return OK;
    }
    Linea linea1 = ver1->primera;
    Linea linea2 = ver2->primera;  
    while (linea1 != NULL && linea2 != NULL) {
        if (strcmp(linea1->texto, linea2->texto) != 0) {
            iguales = false;
            return OK;
        }
        linea1 = linea1->siguiente;
        linea2 = linea2->siguiente;
    }
    iguales = true;
    return OK;
}

TipoRet ContarVersiones(Archivo arch, int &cantidad) {
    if (!arch || !arch->raizVersiones) return ERROR;
    cantidad = ContarVersionesRec(arch->raizVersiones);
    return OK;
}

// ============================================================
// 2. Operaciones principales del editor de texto
// ============================================================

TipoRet InsertarLineaRec(Linea actual, unsigned int pos, unsigned int nroLinea, Linea nueva) {
    if (!actual) return ERROR;

    // Caso base: llegamos al nodo anterior al punto de inserción
    if (pos == nroLinea - 1) {
        nueva->siguiente = actual->siguiente;
        nueva->anterior = actual;

        if (actual->siguiente)
            actual->siguiente->anterior = nueva;

        actual->siguiente = nueva;
        return OK;
    }

    // Paso recursivo: avanzar al siguiente nodo
    return InsertarLineaRec(actual->siguiente, pos + 1, nroLinea, nueva);
}

//permite insertar en versiones con sub 
TipoRet InsertarLinea(Archivo &arch, char *version, char *linea, unsigned int nroLinea) {
    if (!arch || !version || !linea) return ERROR;

    Version v = BuscarVersion(arch->raizVersiones, version);
    if (!v) return ERROR;

    if(v->subversiones != NULL) return ERROR;
    

    if (nroLinea < 1 || nroLinea > v->numLineas + 1)
        return ERROR;

    // Crear la nueva línea
    Linea nueva = (Linea) malloc(sizeof(struct _linea));
    if (!nueva) return ERROR;

    nueva->texto = (char *) malloc(strlen(linea) + 1);
    if (!nueva->texto) {
        free(nueva);
        return ERROR;
    }
    strcpy(nueva->texto, linea);
    nueva->siguiente = nueva->anterior = NULL;

    //  Caso 1: lista vacía
    if (v->numLineas == 0) {
        v->primera = v->ultima = nueva;
    }
    //  Caso 2: insertar al principio
    else if (nroLinea == 1) {
        nueva->siguiente = v->primera;
        v->primera->anterior = nueva;
        v->primera = nueva;
    }
    //  Caso 3: insertar al final
    else if (nroLinea == v->numLineas + 1) {
        nueva->anterior = v->ultima;
        v->ultima->siguiente = nueva;
        v->ultima = nueva;
    }
    //  Caso 4: insertar en el medio (recursivo)
    else {
        if (InsertarLineaRec(v->primera, 1, nroLinea, nueva) == ERROR) {
            free(nueva->texto);
            free(nueva);
            return ERROR;
        }
    }

    v->numLineas++;
    return OK;
}

// warning: no usa char *version
// no uso la version especifica, siempre me paro en la raiz 
TipoRet BorrarLinea(Archivo &arch, char *version, unsigned int nroLinea) {
    if (!arch || !version || nroLinea < 1) return ERROR;

    Version v = BuscarVersion(arch->raizVersiones, version);
    if (!v || !v->primera) return ERROR;

    if (nroLinea > v->numLineas) return ERROR;

    Linea actual = v->primera;

  /// primer linea 
    if (nroLinea == 1) {
        v->primera = actual->siguiente;
        
        if (v->primera)
            v->primera->anterior = NULL;
        else
            v->ultima = NULL;
        free(actual->texto);
        free(actual);
    }
    
    else {
        for (unsigned int i = 1; i < nroLinea && actual; i++)
            actual = actual->siguiente;

        if (!actual) return ERROR;

        if (actual->anterior)
            actual->anterior->siguiente = actual->siguiente;

        if (actual->siguiente)
            actual->siguiente->anterior = actual->anterior;
        else
            v->ultima = actual->anterior;

        free(actual->texto);
        free(actual);
    }

    v->numLineas--;
    return OK;
}

TipoRet MostrarTexto(Archivo arch, char *version) {
    if (!arch || !version) return ERROR;

    Version v = BuscarVersion(arch->raizVersiones, version);
    if (!v) return ERROR;

    printf("%s\n\n", arch->nombre);
    if (!v->primera) {
        printf("No contiene líneas\n");
        return OK;
    }

    struct _linea* actual = v->primera;
    unsigned int numeroLinea = 1;
    while (actual) {
        printf("\t%u %s\n", numeroLinea, actual->texto);
        actual = actual->siguiente;
        numeroLinea++;
    }

    return OK;
}

// warning: no usa char *version
// no uso la version especifica, siempre me paro en la raiz
TipoRet ContarLineas(Archivo arch, char * version, unsigned int &cantidad) {
   if(arch == NULL) return ERROR;

   if(arch->raizVersiones->numLineas == 0) {
        cantidad = 0;
        return OK;
    }    
    cantidad = arch->raizVersiones->numLineas;
    return OK;
}


// ===========================================================
//  3. Funciones auxiliares generales
// ===========================================================
Version CrearNodo(const char *nombre) {
    Version v = (Version) malloc(sizeof(struct _version));
    if (!v) return NULL;

    v->nombreVersion = (char *) malloc(strlen(nombre) + 1);
    if (!v->nombreVersion) {
        free(v);
        return NULL;
    }

    strcpy(v->nombreVersion, nombre);
    v->subversiones = v->siguienteHermano = NULL;
    v->primera = v->ultima = NULL;
    v->numLineas = 0;
    return v;
}

Version BuscarVersion(Version raiz, const char *nombre) { 
    if (raiz == NULL) return NULL;
    if (strcmp(raiz->nombreVersion, nombre) == 0)
        return raiz;
    Version encontrada = BuscarVersion(raiz->subversiones, nombre);
    if (encontrada != NULL)
        return encontrada;
    return BuscarVersion(raiz->siguienteHermano, nombre);
}

void LiberarLineasRecursivo (Linea l){
    if(!l) return;
    LiberarLineasRecursivo(l->siguiente); 
    free(l->texto);
    free(l);
}

void LiberarVersiones(Version v) {
    if (!v) return;

    LiberarVersiones(v->subversiones);
    LiberarVersiones(v->siguienteHermano);
    LiberarLineasRecursivo(v->primera);
    free(v->nombreVersion);
    free(v);
}

void MostrarVersionesRec(Version v) {
    if (v == NULL) return;

    printf("%s\n", v->nombreVersion);
    MostrarVersionesRec(v->subversiones);
    MostrarVersionesRec(v->siguienteHermano);
}

int ContarVersionesRec(Version v) {
    if (!v) return 0;
    return 1 + ContarVersionesRec(v->subversiones) + ContarVersionesRec(v->siguienteHermano);
}

//no estoy borrando los hermanos, solo subversiones
// tenog que arreglar eso
int BorrarVersionRec(Version versionActual, const char *nombre) {
    if (versionActual == NULL)
        return 0;

    Version sub = versionActual->subversiones;
//  Caso 1: la primera subversión es la que queremos borrar
    if (sub != NULL && strcmp(sub->nombreVersion, nombre) == 0) {
        versionActual->subversiones = sub->siguienteHermano;
        LiberarVersiones(sub);
        return 1;
    } 

    //  Caso 2: la siguiente subversión (hermano) es la que queremos borrar
    if (versionActual->siguienteHermano != NULL && strcmp(versionActual->siguienteHermano->nombreVersion, nombre) == 0) {
        Version aBorrar = versionActual->siguienteHermano;
        versionActual->siguienteHermano = aBorrar->siguienteHermano;
        LiberarVersiones(aBorrar);
        return 1;
    }

    //  Caso 3: buscar recursivamente en subversiones y hermanos
    if (BorrarVersionRec(versionActual->subversiones, nombre))
        return 1;

    if (BorrarVersionRec(versionActual->siguienteHermano, nombre))
        return 1;

    return 0;
}

