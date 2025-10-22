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
    if(arch == NULL){
        return ERROR;
    }

    Linea actual = arch->primera;
    while(actual !=NULL){
        Linea siguiente = actual->siguiente;

        if(actual->texto !=NULL){
            free(actual->texto);
        }

        free(actual);
        actual = siguiente;
    }

    if(arch->nombre !=NULL){
        free(arch->nombre);
    }

    free(arch);
    arch = NULL;
    return OK;

}

TipoRet InsertarLinea(Archivo arch, char *linea, unsigned int nroLinea) {
    if (arch == NULL)
    {
       return ERROR;
    }
    
    if (nroLinea < 1 || nroLinea > arch->numLineas + 1)
    return ERROR;


    struct _linea* nueva = (struct _linea*) malloc(sizeof(struct _linea)); 
    if(nueva == NULL) return ERROR;
    nueva->texto = (char*) malloc(strlen(linea) + 1);
    if(nueva->texto == NULL) {
        free(nueva);
        return ERROR;
    }
    strcpy(nueva->texto, linea);
    nueva->siguiente = NULL;
    nueva->anterior = NULL;

     
    if (arch->numLineas == 0) {
        arch->primera = arch->ultima = nueva;

    }

    
    else if (nroLinea == 1) {
    nueva->siguiente = arch->primera; 
    arch->primera->anterior = nueva; 
    arch->primera = nueva; 
    }

    
    else if (nroLinea == arch->numLineas + 1) {
    nueva->anterior = arch->ultima;
    arch->ultima->siguiente = nueva;
    arch->ultima = nueva;
    }
    
    else {
    struct _linea* actual = arch->primera;
    for (unsigned int i = 1; i < nroLinea - 1; i++) { 
        actual = actual->siguiente; 
    }

    nueva->siguiente = actual->siguiente;
    nueva->anterior = actual;
    actual->siguiente->anterior = nueva; 
    actual->siguiente = nueva;
    }

    arch->numLineas++;
    return OK;

}


TipoRet BorrarLinea(Archivo arch, unsigned int nroLinea) {
    
    if (arch == NULL) {
        return ERROR;
    }
    
    if (arch->numLineas == 0 || nroLinea < 1 || nroLinea > arch->numLineas) {
        return ERROR;
    }

    struct _linea* actual = arch->primera;
   
    for (unsigned int i = 1; i < nroLinea; i++) {
        actual = actual->siguiente;
    }
    
    if(actual == arch->primera) { 
        arch->primera = actual->siguiente;
        if(arch->primera != NULL) {
            arch->primera->anterior = NULL;
        } else {
            arch->ultima = NULL; 
        }
    } else if (actual == arch->ultima)
    {
        arch->ultima = actual->anterior;
 
        if(arch->ultima != NULL) {
            arch->ultima->siguiente = NULL;
        } else {
            arch->primera = NULL; 
        }
        

    } else { 
        actual->anterior->siguiente = actual->siguiente; 
        actual->siguiente->anterior = actual->anterior; 
    }
    free(actual->texto);
    free(actual);
    arch->numLineas--;
    return OK;
}

TipoRet MostrarTexto(Archivo arch) {
    if(arch == NULL) return ERROR;

    if(arch->numLineas == 0) {
        printf("%s\n\nNo contiene líneas\n", arch->nombre);
        return OK;
    }
    
    printf("%s\n\n", arch->nombre);


    struct _linea* actual = arch->primera;
    unsigned int numeroLinea = 1; 
    while(actual != NULL) {
        
        
        printf("    %u %s\n", numeroLinea, actual->texto);
        actual = actual->siguiente;
        numeroLinea++;
        
    }
    return OK;
}


TipoRet ContarLineas(Archivo arch, unsigned int &cantidad) {
   if(arch == NULL) return ERROR;

    if(arch->numLineas == 0) {
        cantidad = 0;
        return OK;
    }

    cantidad = arch->numLineas;
    return OK;
}

