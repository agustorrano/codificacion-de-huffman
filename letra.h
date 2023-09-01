#ifndef __LETRA_H_
#define __LETRA_H_

/*
 * Definimos un nuevo tipo de dato que llamaremos Letra para poder representar
 * cada carácter del código ASCII. Esta estructura tendrá dos atributos, un dato 
 * de tipo carácter, que será el carácter, y un dato de tipo entero, que será la 
 * frecuencia en la que aparece cada carácter.
 */
typedef struct _Letra{
  char caracter;
  int frecuencia;
} Letra;

/*
 * crear_letra : int -> Letra
 * La función recibe un entero correspondiente a la frecuencia en la que aparece
 * en el archivo el caracter que estamos creando. Crea una estructura tipo Letra
 * a la que le asigna como caracter el NULL (00 en ASCII) y la frecuencia dada.
 */
Letra crear_letra(int frecuencia);

/*
 * crear_tabla : void -> Letra*
 * Crea una tabla con las 256 Letras del codigo ASCII extendido. Asigna los
 * caracteres en la tabla en el orden del codigo ASCII, y a todos ellos les
 * indica una frecuencia igual a 0.
 */
Letra* crear_tabla();

/*
 * definir_frecuencias : const char*, Letra*, int -> Letra*
 * Recibe un buffer con el contenido de un archivo, la longitud del buffer, y la
 * tabla con las Letras. Por cada carácter que lee en el buffer, aumenta en uno 
 * su frecuencia en la tabla.
 */
Letra* definir_frecuencias(const char* buf, Letra* tabla, int len);

/*
 * merge : Letra*, int, Letra*, int -> Letra*
 * Recibe dos arreglos de tipo Letra con la longitud de cada uno y retorna la tabla
 * ordenada de menor a mayor según su frecuencia. Para ello, va a mezclar los dos
 * arreglos en un solo arreglo ordenado.
 */
Letra* merge(Letra *arreglo1, int len1, Letra *arreglo2, int len2);

/*
 * mergesort : Letra*, int -> Letra*
 * Recibe la tabla de Letras y la longitud de la misma y retorna un nuevo arreglo 
 * que será la tabla ordenada. Para esto se utilizará el algoritmo de ordenamiento
 * mergesort. La idea del mismo es, si la longitud del arreglo es 0 o 1, entonces 
 * ya está ordenada, por lo tanto se retorna una compia del mismo, en caso contrario,
 * se divide el arreglo desordenado en dos subarreglos de aproximadamente la mitad del
 * tamaño del original y se ordena cada subarreglo recursivamente aplicando mergesort.
 * Finalmente se obtendrá un nuevo arreglo ordenado.
 */
Letra* mergesort(Letra *tabla, int n);

#endif
