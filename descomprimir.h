#ifndef __DESCOMPRIMIR_H_
#define __DESCOMPRIMIR_H_
#include "btree.h"

/* 
 * eliminar_caracteres_finales: char*, int n -> char*
 * Recibe un string, crea una copia, y le elimina los últimos n caracteres.
 * Devuelve dicha copia.
 */
char* eliminar_caracteres_finales(char* cadenaOriginal, int n);

/*
 * parsear_arbol: char*, int* -> BTree
 * Recibe el codigo de 0's y 1's en el que está codificada la forma del arbol, 
 * y un puntero a entero (que comienza siendo 0), con el que se recorrerá el 
 * codigoBinario. Recrea el arbol teniendo en cuenta que si lee un 1 es una hoja
 * y un 0 es un nodo.
 */
BTree parsear_arbol(char* codigoForma, int* p);

/*
 * completar_arbol: char*, BTree, int* -> void
 * Recibe el codigo de 256 caracteres ordenado según su aparición en el arbol,
 * un puntero a entero (que comienza siendo 0), con el que se recorrerá el codigo,
 * y el arbol ya creado pero sin Letras en sus nodos. 
 * Hace un recorrido en orden consumiendo caracteres del codigo y guardándolos en 
 * las hojas.
 */
void completar_arbol(char* codigoCaracteres, BTree arbol, int* p);

/*
 * decodificar_simbolo: BTree, char*, int* -> char
 * Recibe un arbol, pregunta si es una hoja, y de ser verdadero, la Letra del nodo
 * es el caracter q buscabamos. Por otro lado, si no es una hoja, evalúa la función
 * en su hijo izquierdo o derecho, dependiendo de si el bit que lee de la cadena 
 * Explosionada es un 0 o un 1. El proceso lo realiza hasta llegar a la hoja y devolver
 * el caracter encontrado.
 */
char decodificar_simbolo(BTree arbol, char* cadenaExplosionada, int* p);

/*
 * decodificar_archivo: BTree, char* -> char*
 * Crea un array donde se guardará el texto decodificado. Define una variable x, la cual le 
 * pasaremos como puntero a la función decodificar_simbolo, que aumentará en razón a la 
 * cantidad de bits que lee decodificar_simbolo para encontrar el caracter. Además, utilizamos
 * una variable i, que aumenta en 1, cada vez que se decodifica un caracter, es decir, cada vez
 * que iteramos en el bucle while.
 * Dicho bucle seguirá llamando a decodificar_simbolo (y haciendo reallocs cuando sea necesario),
 * hasta que haya decodificado y escrito en la variable texto, la cantidad de caracteres esperados.
 */
char* decodificar_archivo(BTree arbol, char* cadenaExplosionada, int* lenTexto);

/*
 * descomprimir: char* -> void
 * Es la función principal de nuestro descompresor. Primero, se ocupa de generar los nombres de los 
 * archivos que va a leer y/o escribir. Luego, lee el archivo que contiene el texto comprimido, lo
 * explosiona, y lo guarda en la variable textoExplosionado. Lee también el archivo con la forma y 
 * los caracteres de nuestro arbol huffman y lo guarda en las variables codigoForma y codigoCaracteres.
 * Después de hacer esto, comienza la decodificación.
 * LLama a la función parsear_arbol para recrear la forma del mismo, y luego guarda las Letras en las
 * hojas con la función completar_arbol. Por último, genera el texto decodificado, utilizando el arbol
 * y la cadena explosionada, y escribe dicho texto, en un archivo .dec .
 * Finalmente, libera la memoria utilizada.
 */
void descomprimir(char* nombreArchivo);

#endif