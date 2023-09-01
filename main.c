#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "letra.h"
#include "btree.h"
#include "comprimir.h"
#include "descomprimir.h"
#include "io.h"

int main(int argc, char *argv[]) {

  if (argc < 3) {
    printf ("La cantidad de argumentos es menor que la necesaria");
    exit(1);
  }

  char* nombreArchivo = argv[2];

  if      (strcmp(argv[1], "C") == 0) comprimir(nombreArchivo);
  else if (strcmp(argv[1], "D") == 0) descomprimir(nombreArchivo);

  return 0;
}
