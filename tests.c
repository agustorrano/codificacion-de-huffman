#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "letra.h"
#include "btree.h"
#include "comprimir.h"
#include "descomprimir.h"

void test_crear_letra() {
  Letra letra1;
  letra1.caracter = 00;
  letra1.frecuencia = 5;
  Letra letra2;
  letra2.caracter = 00;
  letra2.frecuencia = 0;
  Letra letra3 = crear_letra(5);
  Letra letra4 = crear_letra(0);
  assert(letra3.caracter == letra1.caracter);
  assert(letra3.frecuencia == letra1.frecuencia);
  assert(letra4.caracter == letra2.caracter);
  assert(letra4.frecuencia == letra2.frecuencia);
}

void test_crear_tabla() {
  Letra* tabla = crear_tabla();
  assert(tabla[97].caracter == 'a');
  assert(tabla[75].caracter == 'K');
  assert(tabla[46].caracter == '.');
  assert(tabla[50].caracter == '2');
  free(tabla);
}

void test_definir_frecuencias() {
  char* buf = "Arreglo para prueba";
  Letra* tabla = crear_tabla();
  int len = 19;
  tabla = definir_frecuencias(buf, tabla, len);
  assert(tabla[97].frecuencia == 3);
  assert(tabla[114].frecuencia == 4);
  assert(tabla[65].frecuencia == 1);
  assert(tabla[75].frecuencia == 0);
  free(tabla);
}

void test_mergesort() {
  Letra* tabla = malloc(sizeof(Letra) * 5);
  for (int i = 0; i < 5; i++) 
    tabla[i].caracter = (i + 65);
  tabla[0].frecuencia = 6;
  tabla[1].frecuencia = 3;
  tabla[2].frecuencia = 0;
  tabla[3].frecuencia = 5;
  tabla[4].frecuencia = 9;
  Letra* tablaOrdenada = mergesort(tabla, 5);
  assert(tablaOrdenada[0].frecuencia == 0 && tablaOrdenada[0].caracter == 'C');
  assert(tablaOrdenada[1].frecuencia == 3 && tablaOrdenada[1].caracter == 'B');
  assert(tablaOrdenada[2].frecuencia == 5 && tablaOrdenada[2].caracter == 'D');
  assert(tablaOrdenada[3].frecuencia == 6 && tablaOrdenada[3].caracter == 'A');
  assert(tablaOrdenada[4].frecuencia == 9 && tablaOrdenada[4].caracter == 'E');
  free(tabla);
  free(tablaOrdenada);
}

void test_lista_agregar_final() {
  Letra letra1 = crear_letra(1);
  Letra letra2 = crear_letra(2);
  Letra letra3 = crear_letra(3);
  BTree nodo = btree_crear();
  nodo = lista_agregar_final(letra1, nodo);
  nodo = lista_agregar_final(letra2, nodo);
  nodo = lista_agregar_final(letra3, nodo);
  assert(nodo->letra.frecuencia == 1);
  assert(nodo->next->letra.frecuencia == 2);
  assert(nodo->next->next->letra.frecuencia == 3);
  BTree nodoAEliminar;
  while (nodo != NULL) {
    nodoAEliminar = nodo;
    nodo = nodo->next;
    free(nodoAEliminar);
  }
}

void test_crear_lista() {
  BTree lista = btree_crear();
  Letra* tabla = malloc(sizeof(Letra) * 5);
  for (int i = 0; i < 5; i++) 
    tabla[i].caracter = (i + 65);
  tabla[0].frecuencia = 6;
  tabla[1].frecuencia = 3;
  tabla[2].frecuencia = 0;
  tabla[3].frecuencia = 5;
  tabla[4].frecuencia = 9;
  lista = crear_lista(lista, tabla, 5);
  int i = 0;
  for (BTree nodo = lista; nodo != NULL; nodo = nodo->next) {
    assert(nodo->letra.frecuencia == tabla[i].frecuencia);
    assert(nodo->letra.caracter == tabla[i].caracter);
    i++;
  }
  BTree nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->next;
    free(nodoAEliminar);
  }
  free(tabla);
}

void test_eliminar_primero() {
  Letra letra1 = crear_letra(0);
  Letra letra2 = crear_letra(4);
  BTree lista = btree_crear();
  lista = lista_agregar_final(letra1, lista);
  lista = lista_agregar_final(letra2, lista);
  BTree listaEliminado = eliminar_primero(lista);
  assert(listaEliminado->letra.frecuencia == 4);
  BTree nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->next;
    free(nodoAEliminar);
  }
}

void test_insertar_ordenado() {
  Letra letra1 = crear_letra(1);
  Letra letra2 = crear_letra(2);
  Letra letra3 = crear_letra(3);
  BTree lista = btree_crear();
  BTree nodo = btree_crear();
  lista = lista_agregar_final(letra1, lista);
  lista = lista_agregar_final(letra3, lista);
  nodo = lista_agregar_final(letra2, nodo);
  lista = insertar_ordenado(lista, nodo);
  assert(lista->next->letra.frecuencia == 2);
  BTree nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->next;
    free(nodoAEliminar);
  }
}

void test_crear_arbol_huff() {
  Letra letra1, letra2, letra3;
  letra1.caracter = 'a';
  letra1.frecuencia = 0;
  letra2.caracter = 'c';
  letra2.frecuencia = 1;
  letra3.caracter = 'e';
  letra3.frecuencia = 2;
  BTree arbolHuff = btree_crear();
  arbolHuff = lista_agregar_final(letra1, arbolHuff);
  arbolHuff = lista_agregar_final(letra2, arbolHuff);
  arbolHuff = lista_agregar_final(letra3, arbolHuff);
  arbolHuff = crear_arbol_huff(arbolHuff);
  assert(arbolHuff->letra.frecuencia == 3);
  assert(arbolHuff->left->letra.frecuencia == 1);
  btree_destruir(arbolHuff);
}

void test_btree() {
  Letra letra1 = crear_letra(0);
  Letra letra2 = crear_letra(1); 
  Letra letra3 = crear_letra(2); 
  Letra letra4 = crear_letra(3);
  BTree ll = btree_unir(letra1, btree_crear(), btree_crear());
  BTree l = btree_unir(letra2, ll, btree_crear());
  BTree r = btree_unir(letra3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(letra4, l, r);
  int nnodos1 = btree_nnodos(raiz);
  int nnodos2 = btree_nnodos(l);
  assert(nnodos1 == 4);
  assert(nnodos2 == 2);
  assert(btree_hoja(ll));
  assert(!btree_hoja(l));
  assert(btree_altura(raiz) == 2);
  btree_destruir(raiz);
}

void test_codigos_caracteres() {
  Letra letra1, letra2, letra3, letra4, letra5;
  letra1.caracter = 'a';
  letra1.frecuencia = 1;
  letra2 = crear_letra(0);
  letra3.caracter = 'c';
  letra3.frecuencia = 2;
  letra4 = crear_letra(0);
  letra5.caracter = 'e';
  letra5.frecuencia = 0;
  BTree rr = btree_unir(letra5, btree_crear(), btree_crear());
  BTree ll = btree_unir(letra1, btree_crear(), btree_crear());
  BTree l = btree_unir(letra2, ll, rr);
  BTree r = btree_unir(letra3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(letra4, l, r);
  char** arrCodigos = codigos_caracteres(raiz);
  assert(strcmp(arrCodigos[97], "00") == 0);
  assert(strcmp(arrCodigos[101], "01") == 0);
  assert(strcmp(arrCodigos[99], "1") == 0);
  free(arrCodigos[97]);
  free(arrCodigos[101]);
  free(arrCodigos[99]);
  free(arrCodigos);
  btree_destruir(raiz);
}

void test_codificar_arbol() {
  Letra letra1 = crear_letra(0);
  Letra letra2 = crear_letra(0);
  Letra letra3 = crear_letra(0);
  Letra letra4 = crear_letra(0);
  Letra letra5 = crear_letra(0);
  BTree rr = btree_unir(letra5, btree_crear(), btree_crear());
  BTree ll = btree_unir(letra1, btree_crear(), btree_crear());
  BTree l = btree_unir(letra2, ll, rr);
  BTree r = btree_unir(letra3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(letra4, l, r);
  char* codigoArbol = codificar_arbol(raiz);
  assert(strcmp(codigoArbol, "00111") == 0);
  free(codigoArbol);
  btree_destruir(raiz);
}

void test_codificar_archivo() {
  Letra letra1, letra2, letra3, letra4, letra5;
  letra1.caracter = 'a';
  letra1.frecuencia = 1;
  letra2 = crear_letra(0);
  letra3.caracter = 'c';
  letra3.frecuencia = 2;
  letra4 = crear_letra(0);
  letra5.caracter = 'e';
  letra5.frecuencia = 0;
  BTree rr = btree_unir(letra5, btree_crear(), btree_crear());
  BTree ll = btree_unir(letra1, btree_crear(), btree_crear());
  BTree l = btree_unir(letra2, ll, rr);
  BTree r = btree_unir(letra3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(letra4, l, r);
  char** arrCodigos = codigos_caracteres(raiz);
  char* codigoBinario = codificar_archivo("ace", 3, arrCodigos);
  assert(strcmp(codigoBinario, "00101") == 0);
  free(codigoBinario);
  free(arrCodigos[97]);
  free(arrCodigos[101]);
  free(arrCodigos[99]);
  free(arrCodigos);
  btree_destruir(raiz);
}

void test_modificar_nombre() {
  char* nombreArchivo1 = modificar_nombre("f.txt", ".hf");
  char* nombreArchivo2 = modificar_nombre("f.txt", ".tree");
  assert(strcmp(nombreArchivo1, "f.txt.hf") == 0);
  assert(strcmp(nombreArchivo2, "f.txt.tree") == 0);
  free(nombreArchivo1);
  free(nombreArchivo2);
}

void test_eliminar_caracteres_finales() {
  char* nombreArchivo1 = eliminar_caracteres_finales("f.txt.hf", 3);
  char* nombreArchivo2 = eliminar_caracteres_finales("f.txt.tree", 5);
  assert(strcmp(nombreArchivo1, "f.txt") == 0);
  assert(strcmp(nombreArchivo2, "f.txt") == 0);
  free(nombreArchivo1);
  free(nombreArchivo2);
}

void test_decodificar_simbolo() {
  Letra letra1, letra2, letra3, letra4, letra5;
  letra1.caracter = 'a';
  letra1.frecuencia = 1;
  letra2 = crear_letra(0);
  letra3.caracter = 'c';
  letra3.frecuencia = 2;
  letra4 = crear_letra(0);
  letra5.caracter = 'e';
  letra5.frecuencia = 0;
  BTree rr = btree_unir(letra5, btree_crear(), btree_crear());
  BTree ll = btree_unir(letra1, btree_crear(), btree_crear());
  BTree l = btree_unir(letra2, ll, rr);
  BTree r = btree_unir(letra3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(letra4, l, r);
  int p = 0;
  char caracter1 = decodificar_simbolo(raiz, "001", &p);
  char caracter2 = decodificar_simbolo(raiz, "001", &p);
  assert(caracter1 == 'a');
  assert(caracter2 == 'c');
  btree_destruir(raiz);
}

int main() {
  test_crear_letra();
  test_crear_tabla();
  test_definir_frecuencias();
  test_mergesort();
  test_lista_agregar_final();
  test_crear_lista();
  test_eliminar_primero();
  test_insertar_ordenado();
  test_crear_arbol_huff();
  test_btree();
  test_codigos_caracteres();
  test_codificar_arbol();
  test_codificar_archivo();
  test_modificar_nombre();
  test_eliminar_caracteres_finales();
  test_decodificar_simbolo();
  return 0;
}