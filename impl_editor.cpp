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
    nueva->siguiente = arch->primera; //nueva apunta a la primera
    arch->primera->anterior = nueva; //la primera apunta a la nueva
    arch->primera = nueva; //ahora la primera es la nueva
    }

    //flow si tenemos A y B y queremos poner C adelante de A
    // A <-> B
    //B es arch->primera->siguiente 
    //C es nueva
    // C <-> A <-> B

    // A->siguiente = B
    // B->anterior = A
    // arch->primera = A
    // arch->ultima = B

    //caso 3, sapeeeeeeeee
    //lo mismo que lo del arriba pero a final
    //qsy es la epotudes que se me ocurre
    else if (nroLinea == arch->numLineas + 1) {
    nueva->anterior = arch->ultima;
    arch->ultima->siguiente = nueva;
    arch->ultima = nueva;
    }
    //lo mismp que arriba pero al final


    //caso 4
    //y..en el medio
    else {
    struct _linea* actual = arch->primera;
    for (unsigned int i = 1; i < nroLinea - 1; i++) { //me muevo hasta la linea anterior a la que quiero insertar
        actual = actual->siguiente; 
    }

    //parece un pasapalabtra pero el python tutor dice que esta flama
    nueva->siguiente = actual->siguiente;
    nueva->anterior = actual;
    actual->siguiente->anterior = nueva; //la linea que estaba despues de actual ahora apunta a nueva
    actual->siguiente = nueva;
    }

    arch->numLineas++;
    return OK;

}

//tenemos un segmentation fault
//solucionado, faltaba el else if
TipoRet BorrarLinea(Archivo arch, unsigned int nroLinea) {
    //caso
    // Archivo vacío == error
    if (arch == NULL) {
        return ERROR;
    }
    // nroLinea inválido == error
    if (arch->numLineas == 0 || nroLinea < 1 || nroLinea > arch->numLineas) {
        return ERROR;
    }

    struct _linea* actual = arch->primera;
   
    for (unsigned int i = 1; i < nroLinea; i++) {
        actual = actual->siguiente;
    }
    // Borrar la primera línea
    if(actual == arch->primera) { 
        arch->primera = actual->siguiente;
        if(arch->primera != NULL) {
            arch->primera->anterior = NULL;
        } else {
            arch->ultima = NULL; // Si era la única línea, actualizar última también
        }
    } else if (actual == arch->ultima)
    {
        arch->ultima = actual->anterior;
 
        //error aqui
        if(arch->ultima != NULL) {
            arch->ultima->siguiente = NULL;
        } else {
            arch->primera = NULL; // Si era la única línea, actualizar primera también
        }
        

    } else { // Borrar una línea del medio
        //metele que yo tengo A <-> B <-> C
        //quiero borrar B
        //actual es B
        // A es actual->anterior
        // C es actual->siguiente


        //ta ponele hasta ahi, to quiero A <-> C
        //osea, A->siguiente = C y C->anterior = A
        actual->anterior->siguiente = actual->siguiente; // A->siguiente = C. "El siguiente del anterior "
        actual->siguiente->anterior = actual->anterior; // C->anterior = A. "El anterior del siguiente "
    }
    free(actual->texto);
    free(actual);
    arch->numLineas--;
    return OK;
}

TipoRet MostrarTexto(Archivo arch) {
    if(arch == NULL) return ERROR;

    if(arch->numLineas == 0) {
        printf("El archivo está vacío.\n");
        return OK;
    }
    //mostrar el nombre del archivo antes de las lineas (el porfe lo pone asi)
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


//=============================
//    Hay que mejorar esto
//=============================
TipoRet ContarLineas(Archivo arch, unsigned int &cantidad) {
   if(arch == NULL) return ERROR;

    if(arch->numLineas == 0) {
        printf("Hay 0 cantidad de lineas.\n");
        return OK;
    }

    struct _linea* actual = arch->primera;
    unsigned int numeroLinea = 1; 
    while(actual != NULL) {
        printf("%u: %s\n", numeroLinea, actual->texto);
        actual = actual->siguiente;
        numeroLinea++;
    }
    return OK;
}


//resumen a 6/10 
//falta borrar linea y borrar archivo
//cree CrearArchivo e InsertarLinea, MostrarTexto y ContarLineas
//me falta borrar linea y borrar archivo

//resumen a 7/10
//hice borrar linea
//me falta borrar archivo

//=============================
//     main temporal
//=============================

//7-10 
//hice test basico, tengo error de: formato, por que estoy usando espacios en vez de :
//esperado: 
// 1: Nombre: Juan Pérez
// 2: Dirección: Rivera 1234
// 3: Teléfono: 6111111
// mio
//    1 Nombre: Juan Pérez
//    2 Dirección: Rivera 1234
//    3 Teléfono: 6111111

