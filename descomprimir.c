#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "io.h"
#include "comprimir.h"
#include "descomprimir.h"


char* eliminar_caracteres_finales (char* cadenaOriginal, int n) {
  int a = strlen(cadenaOriginal) - n; //a = len(nombreArchivo)
  char* cadenaCortada = malloc(sizeof(char) * (a + 1));
  int i;
  for (i = 0; i < a; i++) 
    cadenaCortada[i] = cadenaOriginal[i];
  cadenaCortada[i] = '\0';
  return cadenaCortada;
}

BTree parsear_arbol(char* codigoForma, int* p) {
  Letra letra = crear_letra(0); //letra con frecuencia 0
  BTree arbol = btree_crear();
  arbol = btree_unir(letra, NULL, NULL);
  if (codigoForma[*p] == '1'){
    return arbol;
  } else {
    *p += 1;
    arbol->left = parsear_arbol(codigoForma, p);
    *p += 1;
    arbol->right = parsear_arbol(codigoForma, p);
  }
  return arbol;
}

void completar_arbol(char* codigoCaracteres, BTree arbol, int* p) {
  assert(arbol != NULL);
  if (btree_hoja(arbol)) {
    arbol->letra.caracter = codigoCaracteres[*p];
    *p += 1;
    return;
  }
  completar_arbol(codigoCaracteres, arbol->left, p);
  completar_arbol(codigoCaracteres, arbol->right, p);
}

char decodificar_simbolo(BTree arbol, char* cadenaExplosionada, int* p) {
  char caracter;
  if (btree_hoja(arbol)) {
    caracter = arbol->letra.caracter;
    return caracter;
  }
  if (cadenaExplosionada[*p] == '0') {
    *p += 1;
    caracter = decodificar_simbolo(arbol->left, cadenaExplosionada, p);
  } else {
    *p += 1;
    caracter = decodificar_simbolo(arbol->right, cadenaExplosionada, p);
  }
  return caracter;
}

char* decodificar_archivo(BTree arbol, char* cadenaExplosionada, int* lenTexto) {
  int x = 0, sz = 1024;
  char* texto = malloc(sizeof(char) * sz);
  assert(texto != NULL);
  int lenCadenaExp = strlen(cadenaExplosionada);
  int i = 0;
  while(x < lenCadenaExp) { 
    if (i == sz) { 
      sz = sz * 2;
      texto = realloc(texto, sz);
    }
    texto[i] = decodificar_simbolo(arbol, cadenaExplosionada, &x); //aumenta x
    i++;
  }
  texto = realloc(texto, i);
  *lenTexto = i;
  return texto;
}

void descomprimir(char* nombreArchivoHf) {
  //definimos los nombres de archivos
  int lenHf = 0, nlen = 0, lenTree = 0, p = 0;
  char* nombreArchivo = eliminar_caracteres_finales(nombreArchivoHf, 3);
  char* nombreArchivoTree = modificar_nombre(nombreArchivo, ".tree");
  char* nombreArchivoDec = modificar_nombre(nombreArchivo, ".dec");

  //leemos archivos y guardamos la información en variables.
  char* texto = readfile(nombreArchivoHf, &lenHf);
  char* textoExplosionado = explode(texto, lenHf, &nlen);
  char* codigoBinarioArbol = readfile(nombreArchivoTree, &lenTree);
  char* codigoForma = malloc(sizeof(char) * (511 + 1));
  char* codigoCaracteres = malloc(sizeof(char) * (256 + 1));
  memcpy(codigoForma, codigoBinarioArbol, 511);
  memcpy(codigoCaracteres, codigoBinarioArbol + 511, 256);
  
  //decodificamos
  BTree arbol = parsear_arbol(codigoForma, &p);
  p = 0;
  completar_arbol(codigoCaracteres, arbol, &p);
  p = 0;
  char* textoDecodificado = decodificar_archivo(arbol, textoExplosionado, &p);
  writefile(nombreArchivoDec, textoDecodificado, p);

  //liberamos memoria
  free(nombreArchivoTree);
  free(nombreArchivoDec);
  free(texto);
  free(textoExplosionado);
  free(codigoBinarioArbol);
  free(codigoForma);
  free(codigoCaracteres);
  free(textoDecodificado);
  btree_destruir(arbol);
}