#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FORA_DO_GRAFO 56
#define ARESTAS_LIGADAS 55
#define ARESTA_INVALIDA 57

typedef struct adjacente{
    int info;
    struct adjacente *prox;
}ADJACENTE;

typedef struct vertice{
    int info;
    int grau_adjacente;
    int grau_saida;
    int grau_entrada;
    ADJACENTE *meu_adjacente;
    struct vertice *adjacente; //vetor de adjacentes ao vertice atual
}VERTICE;

typedef struct aresta{
    float peso;
    VERTICE *destino;
    VERTICE *origem;
}ARESTA;

typedef struct grafo{
    int qtd_arestas;
    int qtd_vertices; //quantidade de vertices ao criar o grafo
    ARESTA *arestas;
}TIPO_GRAFO;
typedef TIPO_GRAFO* GRAFO;


void set_tamanho_grafo(GRAFO grafo, int tamanho){
    grafo->arestas = (ARESTA*)calloc(tamanho, sizeof(struct aresta)); 
}

VERTICE *new_vertice(){
    static int qtd = 0;
    VERTICE *vertice = (VERTICE*)malloc(sizeof(VERTICE));
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
    
    //grafo->arestas = (ARESTA*)calloc(qtd_vertices, sizeof(struct aresta)); //array de aresta
    //grafo->arestas = (int**)malloc(qtd_vertices*sizeof(int*)); // aloca um array para ser os vertices
  
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

void  main(){
    GRAFO grafo = new_grafo(3); // o inteiro define quantas aresta poderemos ter
    
    VERTICE *vert0 = new_vertice();
    VERTICE *vert1 = new_vertice();
    VERTICE *vert2 = new_vertice();
    
    ligar_vertices(grafo, vert0, vert1, 1, 9.7, true);
    
    ligar_vertices(grafo, vert0, vert2, 2, 1.7, true);
    
  
    mostrar_todos_adjacentes(vert0);
    

}




