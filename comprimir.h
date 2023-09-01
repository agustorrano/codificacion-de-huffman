#ifndef __COMPRIMIR_H_
#define __COMPRIMIR_H_
#include "btree.h"

/*
 * obtener_codigos_caracteres : BTree, char**, char*, int -> void
 * La función recibe el árbol Huffman, un arreglo de strings (va a representar la lista 
 * que va a contener los códigos de las hojas), un string (donde se va a guardar cada código 
 * para luego insertarlo en la lista) y un entero (va a representar la longitud del código).
 * Los códigos se obtendrán según el camino que hay que seguir para llegar desde la raíz
 * hasta los caracteres. Uno por uno, estos códigos se irán guardando en un arreglo, en la 
 * posición que representa al caracter que está siendo codificado. Por ejemplo, el código de
 * la 'a' estará en la posición 97 del arreglo. 
 */
void obtener_codigos_caracteres(BTree arbol, char** arrCodigos, char* codigoBinario, int len);

/*
 * codigos_caracteres : BTree -> char**
 * Comienza definiendo la variable "largo", la cual es la longitud máxima que puede tener un código ya
 * que es la posición donde más abajo se puede encontrar una hoja (le sumamos 1 por el carácter '\0').
 * Luego, aloca memoria para la cantidad de códigos, y para cada código. Notemos que en algunos casos
 * va a tener memoria de más, teniendo en cuenta el largo del string. pero despúes en la función 
 * obtener_codigos_caracteres creamos la variable temp que tiene la cantidad justa y liberamos la que
 * primero definimos.
 * Con la función obtener_codigos_caracteres, recorre el árbol para generar los códigos y finalmente
 * retorna el array con todos los códigos de las hojas.
 */
char** codigos_caracteres(BTree arbol);

/*
 * obtener_codigo_arbol : BTree, char*, char*, int*, int* -> void
 * La función codifica la forma del árbol, guardando dicha codificaión en un arreglo. Si el 
 * nodo en el que estamos posicionados es una hoja, agrega un '1', en caso contrario un '0',
 * luego codificamos primero el subárbol izquierdo y después el derecho. A su vez, cada vez
 * que encuentra una hoja, guarda su valor en otro arreglo. Al terminar la recursión, tendremos
 * un arreglo con el codigo de la forma del arbol, y otro con los caracteres que lo componen.
 */
void obtener_codigo_arbol(BTree arbol, char* codigoBinarioArbol, char* arregloCaracteres, int* pos1, int* pos2);

/*
 * codificar_arbol : BTree -> char*
 * La función crea las variables necesarias para definir la longitud de los arreglos que le pasaremos
 * a obtener_codigo_arbol. Luego de llamar a dicha función, copia el arreglo de caracteres al final
 * del array del codigo binario del arbol, y retorna este mismo.
 */
char* codificar_arbol (BTree arbol);

/*
 * codificar_archivo : char*, int, char** -> char*
 * Crea una variable char* que va a guardar la información del archivo codificada. Para hacer 
 * esto, itera sobre el path con un for, y para cada caracter busca su codigo binario en el
 * arrCodigos y lo agrega al array codigoBinarioArchivo. Cuando copió el codigo de todos los 
 * caracteres del path, finaliza el bucle y retorna el codigo formado.
 */
char* codificar_archivo(char* path, int len, char** arrCodigos);

/*
 * modificar_nombre: char*, char* -> char*
 * Crea y devuelve una nueva variable que será el primer argumento concatenado con el segundo.
 */
char* modificar_nombre(char* nombreOriginal, char* agregar);

/*
 * comprimir : char* -> void
 * Es la función principal de nuestro compresor. Primero, crea una tabla que es un array de 
 * 256 estructuras Letra, las completa con un caracter y su frecuencia correspondiente. Luego,
 * ordena la tabla con mergesort poniendo al principio las letras con menor frecuencia. 
 * El segundo paso es crear el arbol huffman. Nuestra implementación utiliza una estructura
 * enlazada que tiene tanto punteros al siguiente nodo, como a su izquierda y derecha. Cuando
 * definimos la lista, todos los punteros a izquierda y derecha serán NULL.
 * Luego, con la función crear_arbol_huff, esta lista pasará a tener forma de arbol, y todos 
 * sus punteros next serán NULL.
 * El siguiente paso es la codificación. Guardamos en una variable doble puntero el código binario
 * de cada caracter, en otra el codigo de la forma del arbol huff, y en una última los caracteres de
 * las hojas.
 * Por último, creamos los dos archivos que devuelve el compresor. El codigo binario del archivo 
 * lo implosionamos y lo escribimos en el .Hf . En el archivo .Tree, quedará el arbol huffman
 * que después será necesario para la descompresión.
 * Finalmente, liberamos memoria utilizada.
 */
void comprimir(char* nombreArchivo);

#endif
