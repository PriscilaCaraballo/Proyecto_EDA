// editor_impl.cpp
#include "editor.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

    nuevo->primera = NULL;
    nuevo->ultima = NULL;
    nuevo->numLineas = 0;
    
    
    return nuevo; 
}

TipoRet BorrarArchivo(Archivo &arch) {
    return NO_IMPLEMENTADA;
}

TipoRet InsertarLinea(Archivo arch, char *linea, unsigned int nroLinea) {
    if (arch == NULL)
    {
       return ERROR;
    }
    
    if (nroLinea < 1 || nroLinea > arch->numLineas + 1)
    return ERROR;


    struct _linea* nueva = (struct _linea*) malloc(sizeof(struct _linea)); //NO SE PORQUE MIERDA ES ASI, PERO SINO ME DA ERROR
    if(nueva == NULL) return ERROR;
    nueva->texto = (char*) malloc(strlen(linea) + 1);
    if(nueva->texto == NULL) {
        free(nueva);
        return ERROR;
    }
    strcpy(nueva->texto, linea);
    nueva->siguiente = NULL;
    nueva->anterior = NULL;

     //casos
    //para primera y ultima, si la primera que ponga es la nueva, onda es la primera y la ultima no?
    if (arch->numLineas == 0) {
        arch->primera = arch->ultima = nueva;

    }

    //caso 2, ponele
    //si ya hay uno, y ponele este es el segundo y va adelante, cachai???
    else if (nroLinea == 1) {
    nueva->siguiente = arch->primera;
    arch->primera->anterior = nueva;
    arch->primera = nueva;
    }

    //caso 3, sapeeeeeeeee
    //lo mismo que lo del arriba pero a final
    //qsy es la epotudes que se me ocurre
    else if (nroLinea == arch->numLineas + 1) {
    nueva->anterior = arch->ultima;
    arch->ultima->siguiente = nueva;
    arch->ultima = nueva;
    }

    //caso 4
    //y..en el medio
    else {
    struct _linea* actual = arch->primera;
    for (unsigned int i = 1; i < nroLinea - 1; i++) {
        actual = actual->siguiente;
    }

    //parece un pasapalabtra pero el python tutor dice que esta flama
    nueva->siguiente = actual->siguiente;
    nueva->anterior = actual;
    actual->siguiente->anterior = nueva;
    actual->siguiente = nueva;
    }

    arch->numLineas++;
    return OK;

}

TipoRet BorrarLinea(Archivo arch, unsigned int nroLinea) {
    return NO_IMPLEMENTADA;
}

TipoRet MostrarTexto(Archivo arch) {
    return NO_IMPLEMENTADA;
}

TipoRet ContarLineas(Archivo arch, unsigned int &cantidad) {
    return NO_IMPLEMENTADA;
}
