#ifndef EDITOR_H
#define EDITOR_H

// ==========================================================
// Definiciones de tipos
// ==========================================================

// Tipo de retorno de operaciones
typedef enum _retorno {
    OK, 
    ERROR, 
    NO_IMPLEMENTADA
} TipoRet;

//funciones
//creacion
Archivo CrearArchivo(char * nombre);

TipoRet BorrarArchivo(Archivo &arch);
