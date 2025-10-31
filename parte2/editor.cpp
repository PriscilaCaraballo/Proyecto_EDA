#include "editor.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static Archivo archivo_actual = NULL;

void mostrar_ayuda() {
  printf("\n=== MENÚ DE COMANDOS DEL MANEJADOR DE VERSIONES ===\n");
  printf("Comandos disponibles:\n");
  printf("  crear <nombre>                    - Crear un nuevo archivo\n");
  printf("  crear_version <version>           - Crear una nueva versión (alias: cv)\n");
  printf("  mostrar_versiones                 - Mostrar todas las versiones (alias: mv)\n");
  printf("  insertar <version> <linea> <pos>  - Insertar línea en versión (alias: i)\n");
  printf("  borrar_linea <version> <pos>      - Borrar línea en versión (alias: b)\n");
  printf("  mostrar_texto <version>           - Mostrar texto de versión (alias: m)\n");
  printf("  comparar <version1> <version2>    - Comparar dos versiones (alias: c)\n");
  printf("  contar_versiones                  - Contar total de versiones\n");
  printf("  borrar_version <version>          - Borrar una versión específica (alias: bv)\n");
  printf("  borrar_archivo                    - Borrar el archivo actual\n");
  printf("  ayuda                             - Mostrar esta ayuda (alias: h)\n");
  printf("  salir                             - Salir del programa (alias: q)\n");
  printf("\nEjemplos:\n");
  printf("  crear curriculum.txt\n");
  printf("  cv 1\n");
  printf("  cv 2\n");
  printf("  i 1 \"Nombre: Juan Pérez\" 1\n");
  printf("  i 2 \"Dirección: Rivera 1234\" 1\n");
  printf("  m 1\n");
  printf("  c 1 2\n");
  printf("  mv\n");
  printf("  contar_versiones\n");
  printf("\nPara pruebas automatizadas:\n");
  printf("  ./menu_editor < archivo_comandos.txt\n");
  printf("  echo 'comando' | ./menu_editor\n");
  printf("====================================================\n\n");
}

void procesar_crear(char *args) {
  if (archivo_actual != NULL) {
    printf("ERROR: Ya existe un archivo abierto. Use 'borrar_archivo' primero.\n");
    return;
  }

  char *nombre = strtok(args, " \t");
  if (nombre == NULL) {
    printf("ERROR: Debe especificar un nombre de archivo.\n");
    return;
  }

  archivo_actual = CrearArchivo(nombre);
  if (archivo_actual != NULL) {
    printf("Archivo '%s' creado exitosamente.\n", nombre);
  } else {
    printf("ERROR: No se pudo crear el archivo.\n");
  }
}

void procesar_crear_version(char *args) {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  char *version = strtok(args, " \t");
  if (version == NULL) {
    printf("ERROR: Debe especificar una versión.\n");
    return;
  }

  TipoRet resultado = CrearVersion(archivo_actual, version);
  if (resultado == OK) {
    printf("Versión '%s' creada exitosamente.\n", version);
  } else if (resultado == ERROR) {
    printf("ERROR: No se pudo crear la versión.\n");
  } else {
    printf("ERROR: Función CrearVersion no implementada.\n");
  }
}

void procesar_mostrar_versiones() {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  TipoRet resultado = MostrarVersiones(archivo_actual);
  if (resultado != OK) {
    printf("ERROR: No se pudieron mostrar las versiones.\n");
  }
}

void procesar_insertar(char *args) {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  char *version = strtok(args, " \t");
  char *linea_completa = strtok(NULL, "");

  if (version == NULL || linea_completa == NULL) {
    printf("ERROR: Debe especificar versión y línea.\n");
    return;
  }

  char *linea = strtok(linea_completa, " \t");
  char *pos_str = strtok(NULL, " \t");

  if (linea == NULL || pos_str == NULL) {
    printf("ERROR: Debe especificar línea y posición.\n");
    return;
  }

  unsigned int pos = atoi(pos_str);
  TipoRet resultado = InsertarLinea(archivo_actual, version, linea, pos);

  if (resultado == OK) {
    printf("Línea insertada exitosamente.\n");
  } else if (resultado == ERROR) {
    printf("ERROR: No se pudo insertar la línea.\n");
  } else {
    printf("ERROR: Función InsertarLinea no implementada.\n");
  }
}

void procesar_borrar_linea(char *args) {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  char *version = strtok(args, " \t");
  char *pos_str = strtok(NULL, " \t");

  if (version == NULL || pos_str == NULL) {
    printf("ERROR: Debe especificar versión y posición.\n");
    return;
  }

  unsigned int pos = atoi(pos_str);
  TipoRet resultado = BorrarLinea(archivo_actual, version, pos);

  if (resultado == OK) {
    printf("Línea borrada exitosamente.\n");
  } else if (resultado == ERROR) {
    printf("ERROR: No se pudo borrar la línea.\n");
  } else {
    printf("ERROR: Función BorrarLinea no implementada.\n");
  }
}

void procesar_mostrar_texto(char *args) {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  char *version = strtok(args, " \t");
  if (version == NULL) {
    printf("ERROR: Debe especificar una versión.\n");
    return;
  }

  TipoRet resultado = MostrarTexto(archivo_actual, version);
  if (resultado != OK) {
    printf("ERROR: No se pudo mostrar el texto.\n");
  }
}

void procesar_comparar(char *args) {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  char *version1 = strtok(args, " \t");
  char *version2 = strtok(NULL, " \t");

  if (version1 == NULL || version2 == NULL) {
    printf("ERROR: Debe especificar dos versiones.\n");
    return;
  }

  bool iguales;
  TipoRet resultado = Iguales(archivo_actual, version1, version2, iguales);

  if (resultado == OK) {
    printf("Las versiones %s y %s son %s\n", version1, version2, iguales ? "iguales" : "diferentes");
  } else if (resultado == ERROR) {
    printf("ERROR: No se pudieron comparar las versiones.\n");
  } else {
    printf("ERROR: Función Iguales no implementada.\n");
  }
}

void procesar_contar_versiones() {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  int cantidad;
  TipoRet resultado = ContarVersiones(archivo_actual, cantidad);

  if (resultado == OK) {
    printf("Total de versiones: %d\n", cantidad);
  } else if (resultado == ERROR) {
    printf("ERROR: No se pudo contar las versiones.\n");
  } else {
    printf("ERROR: Función ContarVersiones no implementada.\n");
  }
}

void procesar_borrar_version(char *args) {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  char *version = strtok(args, " \t");
  if (version == NULL) {
    printf("ERROR: Debe especificar una versión.\n");
    return;
  }

  TipoRet resultado = BorrarVersion(archivo_actual, version);
  if (resultado == OK) {
    printf("Versión borrada exitosamente.\n");
  } else if (resultado == ERROR) {
    printf("ERROR: No se pudo borrar la versión.\n");
  } else {
    printf("ERROR: Función BorrarVersion no implementada.\n");
  }
}

void procesar_borrar_archivo() {
  if (archivo_actual == NULL) {
    printf("ERROR: No hay archivo abierto.\n");
    return;
  }

  TipoRet resultado = BorrarArchivo(archivo_actual);
  if (resultado == OK) {
    printf("Archivo borrado exitosamente.\n");
    archivo_actual = NULL;
  } else {
    printf("ERROR: No se pudo borrar el archivo.\n");
  }
}

void procesar_comando(char *linea) {
  char comando[256];
  int i = 0;
  while (linea[i] != '\0' && linea[i] != ' ' && i < 255) {
    comando[i] = linea[i];
    if (comando[i] == ' ')
      break;
    comando[i] = tolower(comando[i]);
    i++;
  }
  comando[i] = '\0';

  static char empty[] = "";
  char *args = strchr(linea, ' ');
  if (args != NULL) {
    args++;
  } else {
    args = empty;
  }

  if (strncmp(comando, "crear_version", 13) == 0) {
    procesar_crear_version(args);
  } else if (strncmp(comando, "cv", 2) == 0) {
    procesar_crear_version(args);
  } else if (strncmp(comando, "crear", 5) == 0) {
    procesar_crear(args);
  } else if (strncmp(comando, "mostrar_versiones", 17) == 0) {
    procesar_mostrar_versiones();
  } else if (strncmp(comando, "mv", 2) == 0) {
    procesar_mostrar_versiones();
  } else if (strncmp(comando, "insertar", 8) == 0 ||
             strncmp(comando, "i", 1) == 0) {
    procesar_insertar(args);
  } else if (strncmp(comando, "borrar_version", 14) == 0) {
    procesar_borrar_version(args);
  } else if (strncmp(comando, "bv", 2) == 0) {
    procesar_borrar_version(args);
  } else if (strncmp(comando, "borrar_linea", 12) == 0 ||
             strncmp(comando, "b", 1) == 0) {
    procesar_borrar_linea(args);
  } else if (strncmp(comando, "mostrar_texto", 13) == 0 ||
             strncmp(comando, "m", 1) == 0) {
    procesar_mostrar_texto(args);
  } else if (strncmp(comando, "contar_versiones", 16) == 0) {
    procesar_contar_versiones();
  } else if (strncmp(comando, "comparar", 8) == 0 ||
             strncmp(comando, "c", 1) == 0) {
    procesar_comparar(args);
  } else if (strncmp(comando, "borrar_archivo", 14) == 0) {
    procesar_borrar_archivo();
  } else if (strncmp(comando, "ayuda", 5) == 0 ||
             strncmp(comando, "help", 4) == 0 ||
             strncmp(comando, "h", 1) == 0) {
    mostrar_ayuda();
  } else if (strncmp(comando, "salir", 5) == 0 ||
             strncmp(comando, "exit", 4) == 0 ||
             strncmp(comando, "quit", 4) == 0 ||
             strncmp(comando, "q", 1) == 0) {
    if (archivo_actual != NULL) {
      BorrarArchivo(archivo_actual);
    }
    exit(0);
  } else {
    printf("ERROR: Comando desconocido '%s'. Use 'ayuda' para ver comandos disponibles.\n", comando);
  }
}

int main(void) {
  printf("=== MANEJADOR DE VERSIONES ===\n");
  printf("Escriba 'ayuda' para ver los comandos disponibles.\n\n");

  char linea[1024];
  while (fgets(linea, sizeof(linea), stdin)) {
    linea[strcspn(linea, "\r\n")] = 0;
    if (strlen(linea) > 0) {
      procesar_comando(linea);
    }
  }

  return 0;
}
