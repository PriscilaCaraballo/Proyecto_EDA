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

    nuevo->raizVersiones = NULL;
    return nuevo;
}

TipoRet BorrarArchivo(Archivo &arch) {
    if(arch == NULL){
        return ERROR;
    }

    
    Linea actual = arch->raizVersiones->primera;
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

TipoRet InsertarLinea(Archivo &arch, char * version, char * linea, unsigned int nroLinea){
    
    if (arch == NULL || nroLinea < 1 || nroLinea > arch->raizVersiones->numLineas + 1 || version == NULL || linea == NULL ) return ERROR;
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

    
    if (arch->raizVersiones->numLineas == 0) {
        
        arch->raizVersiones->primera = arch->raizVersiones->ultima = nueva;
    }

    
    else if (nroLinea == 1) {
        
        nueva->siguiente = arch->raizVersiones->primera; 
    arch->raizVersiones->primera->anterior = nueva; 
    arch->raizVersiones->primera = nueva; 
    }

    
    
    else if (nroLinea == arch->raizVersiones->numLineas + 1) {
        nueva->anterior = arch->raizVersiones->ultima;
    arch->raizVersiones->ultima->siguiente = nueva;
    arch->raizVersiones->ultima = nueva;
    }
    
    else {
        
        struct _linea* actual = arch->raizVersiones->primera;
    for (unsigned int i = 1; i < nroLinea - 1; i++) { 
        actual = actual->siguiente; 
    }

    nueva->siguiente = actual->siguiente;
    nueva->anterior = actual;
    actual->siguiente->anterior = nueva; 
    actual->siguiente = nueva;
    }

    
    arch->raizVersiones->numLineas++;
    return OK;

}


TipoRet BorrarLinea(Archivo &arch, char * version, unsigned int nroLinea) {
    
    if (arch == NULL) {
        return ERROR;
    }
    
    
    if (arch->raizVersiones->numLineas == 0 || nroLinea < 1 || nroLinea > arch->raizVersiones->numLineas) {

        return ERROR;
    }

  struct _linea* actual = arch->raizVersiones->primera;

   
    for (unsigned int i = 1; i < nroLinea; i++) {
        actual = actual->siguiente;
    }
    
    
    if(actual == arch->raizVersiones->primera) {

        
        arch->raizVersiones->primera = actual->siguiente;


        
        if(arch->raizVersiones->primera != NULL) {


            
            arch->raizVersiones->primera->anterior = NULL;

        } else {
            
            arch->raizVersiones->ultima = NULL; 
        }
        
    } else if (actual == arch->raizVersiones->ultima)

    {
        
        arch->raizVersiones->ultima = actual->anterior;

        
        if(arch->raizVersiones->ultima != NULL) {

            
            arch->raizVersiones->ultima->siguiente = NULL;
        } else {
            
            arch->raizVersiones->primera = NULL; 
        }
        

    } else { 
        actual->anterior->siguiente = actual->siguiente; 
        actual->siguiente->anterior = actual->anterior; 
    }
    free(actual->texto);
    free(actual);
    
    arch->raizVersiones->numLineas--;

    return OK;
}

TipoRet MostrarTexto(Archivo arch, char * version) {
    if(arch == NULL) return ERROR;

    
    if(arch->raizVersiones->numLineas == 0) {

        printf("%s\n\nNo contiene líneas\n", arch->nombre);
        return OK;
    }
    
    printf("%s\n\n", arch->nombre);


    
    struct _linea* actual = arch->raizVersiones->primera;

    unsigned int numeroLinea = 1; 
    while(actual != NULL) {
        
        
        printf("    %u %s\n", numeroLinea, actual->texto);
        actual = actual->siguiente;
        numeroLinea++;
        
    }
    return OK;
}


TipoRet ContarLineas(Archivo arch, char * version, unsigned int &cantidad) {
   if(arch == NULL) return ERROR;

   
   if(arch->raizVersiones->numLineas == 0) {

        cantidad = 0;
        return OK;
    }

    
    cantidad = arch->raizVersiones->numLineas;
    return OK;
}

TipoRet CrearVersion(Archivo &arch, char * version) {   
    
}

TipoRet BorrarVersion(Archivo &arch, char * version) {
    return NO_IMPLEMENTADA;
}
TipoRet MostrarVersiones(Archivo arch) {
    return NO_IMPLEMENTADA;
}
TipoRet Iguales(Archivo arch, char * version1, char * version2, bool &iguales){
    return NO_IMPLEMENTADA;
}

TipoRet ContarVersiones(Archivo arch, int &cantidad) {
    return NO_IMPLEMENTADA;
}
