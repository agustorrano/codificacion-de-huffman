#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "comprimir.h"
#include "io.h"

void obtener_codigos_caracteres(BTree arbol, char** arrCodigos, char* codigoBinario, int len) {
  if (!btree_vacio(arbol)) {
    if (btree_hoja(arbol)) {
      unsigned char c = arbol->letra.caracter;
      codigoBinario[len] = '\0';
      char *temp = malloc(sizeof(char) * (len+1));
      assert(temp != NULL);
      strcpy(temp, codigoBinario);
      arrCodigos[c] = temp;
    }
    codigoBinario[len] = '0';
    obtener_codigos_caracteres(arbol->left, arrCodigos, codigoBinario, len + 1);
    codigoBinario[len] = '1';
    obtener_codigos_caracteres(arbol->right, arrCodigos, codigoBinario, len + 1);
  }
}

char** codigos_caracteres(BTree arbol) {
  int largo = btree_altura(arbol) + 1;
  char** arrCodigos = malloc(sizeof(char*) * 256);
  char* codigoBinario = malloc(sizeof(char) * largo); 
  obtener_codigos_caracteres(arbol, arrCodigos, codigoBinario, 0); // 
  free(codigoBinario);
  return arrCodigos;
}

void obtener_codigo_arbol(BTree arbol, char* codigoBinarioArbol, char* arregloCaracteres, int* pos1, int* pos2) {
    if (btree_hoja(arbol)) {
      codigoBinarioArbol[*pos1] = '1';
      arregloCaracteres[*pos2] = arbol->letra.caracter;
      *pos2 +=1;
    }
    else {
      codigoBinarioArbol[*pos1] = '0';
      *pos1 +=1;
      obtener_codigo_arbol(arbol->left, codigoBinarioArbol, arregloCaracteres, pos1, pos2);
      *pos1 +=1;
      obtener_codigo_arbol(arbol->right, codigoBinarioArbol, arregloCaracteres, pos1, pos2);
    }
}

char* codificar_arbol (BTree arbol) {
    int cantNodos = btree_nnodos(arbol);
    int cantHojas = 256;
    char* codigoBinarioArbol = malloc(sizeof(char) * (cantNodos + cantHojas));
    char* arregloCaracteres = malloc(sizeof(char) * cantHojas);
    int x = 0, y = 0;
    int *p = &x, *q = &y;
    obtener_codigo_arbol(arbol, codigoBinarioArbol, arregloCaracteres, p, q);
    for (int i = 0; i < 256; i++) {
      codigoBinarioArbol[cantNodos + i] = arregloCaracteres[i];
    }

    free(arregloCaracteres);
    return codigoBinarioArbol;
}

char* codificar_archivo(char* path, int len, char** arrCodigos) {
  int sz = 1024;
  char* codigoBinarioArchivo = malloc(sizeof(char) * sz);
  int j = 0; //variable utilizada para realloc
  for (int i = 0; i < len; i++) {
    unsigned char c = path[i];
    char* a = arrCodigos[c];
    int lenA = strlen(a);
    j += lenA; //j va a ser finalmente la long de codigoBinarioArchivo

    if (j >= sz) {
      sz = sz*2;
      codigoBinarioArchivo = realloc(codigoBinarioArchivo, sz);
    }

    memcpy(codigoBinarioArchivo + j - lenA, a, lenA);
  }
  codigoBinarioArchivo[j] = 0;
  codigoBinarioArchivo = realloc (codigoBinarioArchivo, (j + 1));
  return codigoBinarioArchivo;
}

char* modificar_nombre(char* nombreOriginal, char* agregar) {
  char* nombreArchivo = malloc(sizeof(char) * (strlen(agregar) + strlen(nombreOriginal) + 1));
  strcpy(nombreArchivo, nombreOriginal);
  nombreArchivo = strcat(nombreArchivo, agregar);
  return nombreArchivo;
}

void comprimir(char* nombreArchivo) {
  //creacion de arbol huffman
  Letra* tabla;
  tabla = crear_tabla();
  int len;
  char* path = readfile(nombreArchivo, &len);
  tabla = definir_frecuencias(path, tabla, len);
  Letra* tablaOrdenada; 
  tablaOrdenada = mergesort(tabla, 256);
  BTree arbol = btree_crear();
  arbol = crear_lista(arbol, tabla, 256);
  arbol = crear_arbol_huff(arbol);

  //codificacion:
  char **arrCodigos = codigos_caracteres(arbol);
  char* codigoBinarioArbol = codificar_arbol(arbol);
  char* codigoBinarioArchivo = codificar_archivo(path, len, arrCodigos);
  
  int lenArchivoCod = strlen(codigoBinarioArchivo);
  int nlen;
  
  char* codigoImplosionado = implode(codigoBinarioArchivo, lenArchivoCod, &nlen);
  char* nombreArchivoHf = modificar_nombre(nombreArchivo, ".hf");
  char* nombreArchivoTree = modificar_nombre(nombreArchivo, ".tree");
  writefile(nombreArchivoHf, codigoImplosionado, nlen);
  writefile(nombreArchivoTree, codigoBinarioArbol, (256 + 511));

  //liberación de memoria
  free(nombreArchivoHf);
  free(nombreArchivoTree);
  free(codigoImplosionado);
  free(codigoBinarioArchivo);
  free(codigoBinarioArbol);
  for (int i = 0; i < 256; i++)
    free(arrCodigos[i]);
  free(arrCodigos);
  btree_destruir(arbol);
  free(path);
  free(tablaOrdenada);
  free(tabla);
}
