#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "letra.h"

Letra crear_letra(int frecuencia) {
  Letra letra;
  letra.frecuencia = frecuencia;
  letra.caracter = 00;
  return letra;
}

Letra* crear_tabla(){
  Letra* tabla = malloc(sizeof(Letra) * 256);
  for (int i = 0; i < 256; i++){
    tabla[i].caracter = i;
    tabla[i].frecuencia = 0;
  }
  return tabla;
}

Letra* definir_frecuencias(const char* buf, Letra* tabla, int len) {
  for(int i = 0; i < len; i++){
    unsigned char c = buf[i];
    tabla[c].frecuencia += 1;
  }
  return tabla;
}

Letra* merge(Letra *arreglo1, int len1, Letra *arreglo2, int len2) {
	Letra *tablaOrdenada = malloc((len1 + len2) * sizeof tablaOrdenada[0]);
	int i = 0, j = 0, k = 0;
	while (i < len1 && j < len2) {
		if (arreglo1[i].frecuencia < arreglo2[j].frecuencia) {
			tablaOrdenada[k] = arreglo1[i];
			i++;
			k++;
		} else {
			tablaOrdenada[k] = arreglo2[j];
			j++;
			k++;
		}
	}
	while (i < len1) {
		tablaOrdenada[k] = arreglo1[i];
		i++;
		k++;
	}
	while (j < len2) {
		tablaOrdenada[k] = arreglo2[j];
		j++;
		k++;
	}
	return tablaOrdenada;
}

Letra* mergesort(Letra *tabla, int n) {
	if (n < 2) {
		Letra *tablaOrdenada1 = malloc(n * sizeof tablaOrdenada1[0]);
		tablaOrdenada1[0] = tabla[0];
		return tablaOrdenada1;
	}
	int m = n / 2;
	Letra *arreglo1 = mergesort(tabla, m);
	Letra *arreglo2 = mergesort(tabla + m, n - m);
	Letra *tablaOrdenada = merge(arreglo1, m, arreglo2, n - m);
	free(arreglo1);
	free(arreglo2);
	return tablaOrdenada;
}
