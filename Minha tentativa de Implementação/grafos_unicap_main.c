#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafos_unicap_retornos.h"
#include "grafos_unicap_structs.h"



void  main(){
    GRAFO grafo = new_grafo(3); // o inteiro define quantas aresta poderemos ter
    
    VERTICE *vert0 = new_vertice();
    VERTICE *vert1 = new_vertice();
    VERTICE *vert2 = new_vertice();
    
    ligar_vertices(grafo, vert0, vert1, 1, 9.7, true);
    
    ligar_vertices(grafo, vert0, vert2, 2, 1.7, true);
    
  
    mostrar_todos_adjacentes(vert0);
    

}




