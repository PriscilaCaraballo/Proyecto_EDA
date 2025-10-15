// editor_impl.cpp
#include "editor.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Archivo CrearArchivo(char *nombre) {
    Archivo arch = (Archivo)  malloc (sizeof(struct _archivo));
    if (arch == NULL)
    {
        return NULL;
    }
    
    arch->nombre = (char *) malloc (strlen (nombre) + 1);
    if (arch->nombre == NULL)
    {
        free(arch);
        return NULL;
    }
    
    strcpy(arch->nombre, nombre);
    arch->primera = arch->ultima = NULL;
    arch->numLineas = 0;

    return arch;
}

TipoRet BorrarArchivo(Archivo &arch) {
    if (arch == NULL)
    {
        return ERROR;
    }
    
    Linea actual = arch->primera;
    while (actual != NULL)
    {
        Linea siguiente = actual->siguiente;
        if (actual->texto != NULL)
        {
            free(actual->texto);
        }
        
        free(actual);
        actual = siguiente;
    }
    
    if (arch->nombre != NULL)
    {
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

    if (nroLinea < 1 || nroLinea > arch->numLineas+1)
    {
        return ERROR;
    }
    
    //crear la linea
    struct _linea* lin = (struct _linea*) malloc(sizeof(struct _linea));
    if (lin == NULL)
    {
       return ERROR;
    }
    
    lin->texto = (char *) malloc(strlen (linea) + 1);
    if (lin->texto == NULL)
    {
        free(lin);
        return ERROR;
    }
    
    strcpy(lin->texto, linea);
    lin->anterior = lin->siguiente = NULL;
    //caso 1
    //es la primera
    if (arch->numLineas == 0)
    {
        arch->primera = arch->ultima = lin;

        //caso 2, al principio
    } else if (nroLinea == 1 && arch->numLineas > 0)
    {
        lin->siguiente = arch->primera;
        arch->primera->anterior = lin;
        arch->primera = lin;

        //caso 3,  al final 
    } else if (nroLinea == arch->numLineas + 1)
    {
        lin->anterior = arch->ultima;
        arch->ultima->siguiente = lin;
        arch->ultima = lin;
        //caso 4, en el medio
    } else {
        struct _linea*  actual = arch->primera;
        for (unsigned int i = 1; i < nroLinea - 1 ;i++)
        {
            actual = actual->siguiente;
        }
        lin->siguiente = actual->siguiente;
        lin->anterior = actual;
        actual->siguiente->anterior = lin; //la linea que estaba despues de actual ahora apunta a nueva
        actual->siguiente = lin;
        
    }
    
    arch->numLineas++;
    return OK;
}

TipoRet BorrarLinea(Archivo arch, unsigned int nroLinea) {
    if (arch == NULL)
    {
        return ERROR;
    }
    
    if (nroLinea > arch->numLineas || nroLinea < 0 || arch->numLineas == 0)
    {
        return ERROR;
    }
    
    struct _linea* actual = arch->primera;
    for (unsigned int i = 0; i < nroLinea; i++)
    {
         actual = actual->siguiente;
       
    }

    if (actual == arch->primera)
    {
        arch->primera = actual->siguiente;
        if (arch->primera != NULL)
        {
            arch->primera->anterior = NULL;
        } else {
            arch->ultima = NULL;
        }
        
    } else if (actual == arch->ultima)
    {
        arch->ultima = actual->anterior;
        if (arch->ultima != NULL)
        {
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
    if (arch == NULL)
    {
       return ERROR;
    }

    if (arch->numLineas == 0)
    {
        printf("No hay ningunaa linea");
        return OK;
    }
    
    printf("%s \n\n ", arch->nombre);
    struct _linea *actual = arch->primera;
    unsigned int numeroLinea = 1;
    while (actual != NULL)
    {
        printf("    %u %s \n", numeroLinea, actual->texto);
        actual = actual->siguiente;
        numeroLinea++;
    }

    return OK;
    
}


