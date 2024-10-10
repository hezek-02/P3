/* 5413213 */
/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>
#include <grafo.h>
#include <lista_datos.h>
#include <lista.h>
#include "../include/cronologia_consistente.h"

  // Determinar si existe o no una cronología consistente con los datos, 
  // en caso de existir, construirla en cr 

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2){
  Cronologia cr = new evento[2*n]; 
  //?construir grafo dirigido segun las aristas brindadas
  Grafo repGrafo = crear_grafo(2*n,true);
  for (nat i = 1; i <= n; i++){
    agregar_vertice(i, repGrafo);//?vertice nacimiento de i
    agregar_vertice(i+n, repGrafo);//?vertice muerte de i
    agregar_arista(i,i+n,repGrafo); //! arista nacimiento muerte
  }
  nat qty = cantidad(tipo1);
  while(qty>0){
    agregar_arista(primer_dato(tipo1).id1+n,primer_dato(tipo1).id2,repGrafo);//?muerte id1, nacimiento id2
    tipo1=resto_datos(tipo1);
    qty--;
  }
  qty = cantidad(tipo2);
  while(qty>0){
    agregar_arista(primer_dato(tipo2).id1,primer_dato(tipo2).id2+n,repGrafo);
    agregar_arista(primer_dato(tipo2).id2,primer_dato(tipo2).id1+n,repGrafo);
    qty--;
    tipo2=resto_datos(tipo2);
  }
  //?Hallar OT
  Lista ordTop = crear_lista();
  Lista conjInDegZero = crear_lista();
  int * inDeg = new int[2*n+1];//?Arreglo id, grados incidentes

  for (nat i = 1; i <= 2*n; i++){
    nat grade = in_grado(i,repGrafo);
    inDeg[i] = grade;//?grado de entrada vertice i
    if (inDeg[i] == 0)
      insertar_al_final(i,conjInDegZero);//?añadirlo al conjunto de grados de entrada = 0
  }

  nat longOT=0;
  while (!es_vacia_lista(conjInDegZero)){//?recorrer lista con grados de entrada = 0
      insertar_al_final(primero(conjInDegZero),ordTop);//?añadir al OT
      longOT++;
      Lista ady = adyacentes(primero(conjInDegZero),repGrafo);//?adyacentes al nodo
      while (!es_vacia_lista(ady)){//?recorrer nodos adyacentes
        nat nodo = primero(ady);
          inDeg[nodo]--;//?restarle grado incidencia
          if (inDeg[nodo]==0)//?añadirlo al OT
            insertar_al_final(nodo,conjInDegZero);
        remover_al_inicio(ady);
      }
    remover_al_inicio(conjInDegZero);
  }
  delete [] inDeg;
  destruir_grafo(repGrafo);
  destruir_lista(conjInDegZero);

  if(longOT==2*n) { // si existe, retornarla en cr
    for (nat i = 0; i < 2*n; i++){
      nat id = primero(ordTop);
      if (id<=n)//?id nace
        cr[i] = {id,nace};
      else
        cr[i] = {id-n,muere}; 
      remover_al_inicio(ordTop);
    }
    destruir_lista(ordTop);
    return cr;
  } else {// si no existe, liberar la memoria asociada a cr y retornar NULL   
    destruir_lista(ordTop);
    delete[] cr;
    return NULL;
  }

} 
