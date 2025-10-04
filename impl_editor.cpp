// editor_impl.cpp
#include "editor.hpp"
#include <cstring>
#include <cstdio>
#include <cstdlib>

Archivo CrearArchivo(char *nombre) {
    return nullptr; //como el null pero en c++
}

TipoRet BorrarArchivo(Archivo &arch) {
    return NO_IMPLEMENTADA;
}

TipoRet InsertarLinea(Archivo arch, char *linea, unsigned int nroLinea) {
    return NO_IMPLEMENTADA;
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
