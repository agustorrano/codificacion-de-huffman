#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "btree.h"

BTree btree_crear() { return NULL; }

BTree btree_unir(Letra letra, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->letra = letra;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  nuevoNodo->next = NULL;
  return nuevoNodo;
}

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

int btree_vacio(BTree arbol) { return arbol == NULL; }

BTree lista_agregar_final(Letra letra, BTree lista) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  nuevoNodo->letra = letra;
  nuevoNodo->next = NULL;
  nuevoNodo->left = NULL;
  nuevoNodo->right = NULL;

  if (btree_vacio(lista)) return nuevoNodo;

  BTree nodo = lista;
  for (; nodo->next != NULL; nodo = nodo->next);
  nodo->next = nuevoNodo;
  return lista;
}

BTree crear_lista(BTree lista, Letra* tabla, int longitud) {
  for (int i = 0; i < longitud; i++){
    lista = lista_agregar_final(tabla[i], lista);
  }
  return lista;
}

BTree eliminar_primero(BTree lista) {
  lista = lista->next;
  return lista;
}

BTree insertar_ordenado(BTree lista, BTree arbol) {
  if (lista == NULL) return arbol; //no tiene elementos
  if (lista->next == NULL){        //tiene un solo elemento
    if (arbol->letra.frecuencia < lista->letra.frecuencia){
      arbol->next = lista;
      return arbol;
    } else {
      lista->next = arbol;
      return lista;
    }
  }
  if (arbol->letra.frecuencia < lista->letra.frecuencia) {
    arbol->next = lista;
    return arbol;
  }
  BTree nodo;
  for(nodo = lista; nodo->next != NULL; nodo = nodo->next) {
    if (nodo->next->letra.frecuencia > arbol->letra.frecuencia) {
      arbol->next = nodo->next;
      nodo->next = arbol;
      return lista;
    }
  }
  nodo->next = arbol;
  return lista;
}

BTree crear_arbol_huff(BTree lista) {
  if (lista->next == NULL) return lista;
  BTree nodo1 = lista;
  lista = eliminar_primero(lista);
  BTree nodo2 = lista;
  lista = eliminar_primero(lista);
  int frecuencia = nodo1->letra.frecuencia + nodo2->letra.frecuencia;
  Letra letra = crear_letra(frecuencia);
  BTree nuevoNodo = btree_unir(letra, nodo1, nodo2);
  lista = insertar_ordenado(lista, nuevoNodo);
  lista = crear_arbol_huff(lista);
  return lista;
}

int btree_nnodos(BTree arbol) {
  int contador = 0;
  if(arbol == NULL) return contador;
  contador += 1;
  contador += btree_nnodos(arbol->left);
  contador += btree_nnodos(arbol->right);
  return contador;
}

int btree_hoja(BTree arbol) {
  if (btree_vacio(arbol)) return 0;
  return btree_vacio(arbol->left) && btree_vacio(arbol->right);
}

int btree_altura(BTree arbol) {
  int contadorD = 0, contadorI = 0;
  if (arbol == NULL) return -1;
  contadorD += btree_altura(arbol->right);
  contadorI += btree_altura(arbol->left);
  if (contadorD > contadorI) return contadorD + 1;
  else return contadorI + 1;
}
