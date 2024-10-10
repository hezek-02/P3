/*
  Módulo de implementación de `sistema'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/sistema.h"

nat min(nat s,nat x){//* min(xi,rj)
	if (s < x)
		return s;
	else
		return x;
}
nat max(nat s,nat x){//* min(xi,rj)
	if (s > x)
		return s;
	else
		return x;
}

matriz_t max_datos_procesados(nat n, nat* datos, nat* rendimiento) {
	matriz_t OPT = crear_matriz(n+1, n+1);
	for (nat j = 1; j <= n; j++){
		OPT[n][j]= min(datos[n],rendimiento[j]);
	}

	for (nat i = n-1; i >= 1; i--){
		for (nat j = i; j >= 1; j--){
			OPT[i][j]=max(min(datos[i],rendimiento[j])+OPT[i+1][j+1],OPT[i+1][1]);
		}
	}
	
	return OPT;
}

Lista planificacion_optima(nat n, matriz_t OPT) {
	Lista reinicios = crear_lista();
	nat i=1;
	nat j=1;
	while (i<=n-1){
		if (OPT[i][j]==OPT[i+1][1]){
			insertar_al_final(i,reinicios);
			j=1;//?se reinicia j se reseta
		}else{
			j++;//?j no se resetea
		}
		i++;
	}
	return reinicios;
}

