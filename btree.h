#ifndef __BTREE_H_
#define __BTREE_H_
#include "letra.h"

/*
 * Para representar el Árbol Huffman, definimos una estructura _BTNodo,
 * y un nuevo tipo de dato BTree que será _BTNodo*. La información a 
 * almacenar por la estructura será una Letra, y tendrá tres punteros,
 * uno al subárbol izquierdo, otro al subárbol derecho y otro al siguente.
 * Decidimos construir la estrucura de esta forma porque primero la utilizamos
 * para crear una lista simplemente enlazada (es decir, el puntero al subárbol
 * izquierdo y el puntero al subárbol dercho apuntan a NULL) con las Letras 
 * ordenadas de menor a mayor según su frecuencia, y luego crear el árbol huffman 
 * a partir de esa lista enlazada. Por ejemplo, sacamos los primeros dos nodos de 
 * la lista enlazada, creamos un árbol donde el primer nodo es el subárbol izquierdo
 * y el segundo el subárbol derecho, sumamos la frecuencia de ambos nodos
 * para obtener la frecuencia del padre y, finalmente, insertamos al padre en la
 * lista enlazada. Notemos que ahora el subárbol izquierdo, el subárbol derecho, y el
 * nodo siguiente del padre van a estar apuntando a nodos distintos de NULL.
 */
struct _BTNodo {
  Letra letra;
  struct _BTNodo* next;
  struct _BTNodo* left;
  struct _BTNodo* right;
};

typedef struct _BTNodo* BTree;

/*
 * btree_crear : void -> BTree
 * Crea un arbol vacío.
 */
BTree btree_crear();


/*
 * btree_unir : Letra, BTree, BTree -> BTree
 * Crea un nuevo nodo correspondiente a la letra recibida.
 * Los arboles left y right pasarán a ser los subarboles de dicho nodo.
 */
BTree btree_unir(Letra letra, BTree left, BTree right);

/*
 * btree_destruir : BTree -> void
 * Destruye el arbol.
 */
void btree_destruir(BTree nodo);

/*
 * btree_vacio : BTree -> int
 * Devuelve 1 si el arbol es vacío, 0 en caso contrario.
 */
int btree_vacio(BTree arbol);

/*
 * lista_agregar_final : Letra, BTree -> BTree
 * Recibe una letra, crea su nodo y lo agrega al final de la lista enlazada.
 * Si la lista esta vacía, será su unico nodo y simplemente lo retorna.
 */
BTree lista_agregar_final(Letra letra, BTree arbol);

/*
 * crear_lista : BTree, Letra*, int -> BTree
 * Recibe la tabla de Letras, su longitud y una lista.
 * Cada elemento de la tabla (ya ordenada) lo insertará en la lista enlazada.
 */
BTree crear_lista(BTree lista, Letra* tabla, int longitud);


/*
 * eliminar_primero : BTree -> BTree
 * Devuelve la lista sin su primer elemento.
 */
BTree eliminar_primero(BTree lista);

/*
 * insertar_ordenado BTree, BTree -> BTree
 * La función inserta, ordenadamente, un árbol en una lista enlazada según la frecuencia
 * de las Letras que almacenan. Si la lista es vacía, va a retornar el árbol. Si el nodo 
 * siguente es vacío, quiere decir que hay solo un elemento en la lista, por lo tanto, 
 * comparamos las frecuencias de ambos nodos e insertamos el árbol a izquierda o a derecha 
 * según corresponda. Si el árbol es menor al primer nodo de la lista, lo insertamos al 
 * inicio. 
 * Si ninguno de los casos anteriores se cumple, quiere decir que tendremos que insertar 
 * el árbol en el medio o al final de la lista. Para esto iremos iterando sobre la lista
 * hasta encontrar un nodo cuyo siguente sea mayor al árbol, entonces lo insertaremos 
 * a la derecha de dicho nodo.
 */
BTree insertar_ordenado(BTree lista, BTree arbol);

/*
 * crear_arbol_huff : BTree -> BTree
 * Eliminamos los dos primeros elementos de nuestra lista, creamos un arbol con ellos, y
 * lo insertamos nuevamente en la lista. La posición del nuevo arbol en la lista, dependerá
 * de su frecuencia, y así la misma seguirá ordenada.
 * La función seguirá con este procedimiento hasta que la lista se haya convertido en arbol.
 */
BTree crear_arbol_huff(BTree lista);

/*
 * btree_nodos : BTree -> int
 * Calcula y devuelve la cantidad de nodos en el arbol.
 */
int btree_nnodos(BTree arbol);

/*
 * btree_hoja : BTree -> int
 * Devuelve 1 si el nodo es una hoja, 0 en caso contrario, considerando
 * que un nodo es una hoja si su nodo izquierdo y derecho son NULL.
 */
int btree_hoja(BTree arbol);

/*
 * btree_altura : BTree -> int
 * Devuelve la altura de un arbol.
 */
int btree_altura(BTree arbol);

#endif
