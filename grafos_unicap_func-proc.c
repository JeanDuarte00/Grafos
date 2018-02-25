#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafos_unicap_retornos.h"
#include "grafos_unicap_structs.h"
#include "grafos_unicap_cabecalhos.h"



void set_tamanho_grafo(GRAFO grafo, int tamanho){
    grafo->arestas = (ARESTA*)calloc(tamanho, sizeof(struct aresta)); 
}

VERTICE *new_vertice(){
    static int qtd = 0;
    VERTICE *vertice = (VERTICE*)malloc(1*sizeof(VERTICE));
    vertice->info = qtd;
    vertice->grau_adjacente = 0;
    vertice->grau_entrada = 0;
    vertice->grau_saida = 0;
    vertice->adjacente = NULL;
    qtd = qtd + 1;
    return vertice;
}


GRAFO new_grafo( int tamanho){//grau_adjacente é a quantidade de adjacente que pode ter, o grau do vertice X
    
    GRAFO grafo = (GRAFO)malloc(sizeof(TIPO_GRAFO));
    grafo->qtd_arestas = 0;//inicia com ZERO, quando for criando as ligações de aresta vai incrementando
    grafo->qtd_vertices = 0;
    set_tamanho_grafo(grafo, tamanho);// N aresta possiveis criadas
    
    return grafo;
}

void info_aresta(GRAFO grafo, int aresta){
    puts(" ");
    printf("EXTREMOS DA ARESTA [%d] = (%d , %d)\n",aresta,grafo->arestas[aresta].origem->info, grafo->arestas[aresta].destino->info);
    printf("PESO DA ARESTA: %.3f\n", grafo->arestas[aresta].peso);
    
}



void ligar_vertices(GRAFO grafo, VERTICE *origem, VERTICE *destino, int aresta, float peso, bool digrafo ){
    
    //inserir  na lista de ambos
  
    VERTICE *vertice = origem;
    
    while( vertice->adjacente != NULL){
        vertice = vertice->adjacente;
    }
    vertice->adjacente = destino;
    
    
    if(!digrafo){
        vertice = destino;
        while( vertice->adjacente != NULL){
            vertice = vertice->adjacente;
        }
        vertice->adjacente = origem;
    }
    
    grafo->arestas[aresta].origem = origem;
    grafo->arestas[aresta].destino = destino;
    grafo->arestas[aresta].peso = peso;
}

void mostrar_todos_adjacentes(VERTICE *vertice){
    
    if(vertice->adjacente == NULL){
        puts("SEM ADJACENTES");
        return;
    }
    
    
    VERTICE *aux = vertice;
    
    
    printf("ADJACENTES DE (%d) = [", vertice->info);
    while(aux->adjacente != NULL){
        printf("%d, ", aux->adjacente->info);
        aux = aux->adjacente;
        
    }
    printf("]\n");
}
