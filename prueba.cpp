// editor_impl.cpp
#include "editor.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Archivo CrearArchivo(char *nombre) {
    Archivo arch = (Archivo) malloc (sizeof(struct _archivo));
    if (arch == NULL)
    {
        return NULL;
    }
    
    arch->nombre = (char*) malloc (strlen (nombre) + 1);
    if (arch->nombre == NULL)
    {
        free(arch);
        return NULL;
    }
    
    strcpy(arch->nombre, nombre);
    arch->numLineas = 0;
    arch->primera = arch->ultima = NULL;

    return arch;
}

TipoRet InsertarLinea(Archivo arch, char *linea, unsigned int nroLinea) {
    //validacion 
    if (nroLinea < 1 || arch == NULL)
    {
        return ERROR;
    }
    
    
    Linea nuevaLinea = (Linea) malloc(sizeof (struct _linea));
        if (nuevaLinea == NULL)
        {
            return ERROR; // or another appropriate TipoRet value
        }
    
        nuevaLinea->texto = (char*) malloc(strlen(linea) + 1);
        if (nuevaLinea->texto == NULL) {
            free(nuevaLinea);
            return ERROR;
        }
        strcpy(nuevaLinea->texto, linea);
    //caso 1
    //es la primera
    if (arch->numLineas == 0 && nroLinea == 1)
    {
        nuevaLinea->anterior = nuevaLinea->siguiente = NULL;
        arch->primera = arch->ultima = nuevaLinea;
    } else if (arch->numLineas == 1 && nroLinea == 1 )
    {
        nuevaLinea->anterior = nuevaLinea->siguiente = NULL;
        arch->primera = arch->ultima = nuevaLinea;
    } else if(nroLinea == ) {

    }
    
    

    //caso 2
    //agregar al principio 

    //caso 3
    //agregar al final

    //caso 4
    //agregar en el medio
}
