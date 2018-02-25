#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FORA_DO_GRAFO 56
#define ARESTAS_LIGADAS 55
#define ARESTA_INVALIDA 57


typedef struct grafo{
    bool tem_peso; //se o grafo é ponderado
    int qtd_vertices; //quantidade de vertices ao criar o grafo
    int grau_max; //numero máximo de arestas para cada vertice
    int *grau; //quantidade atual de vertices
    int **arestas; // primeira posição indica o vertice e os dmais as ligações [vertice][adjacentes]
    float **pesos; // peso das ligações do vertice para os adjacentes [vertice][adjacentes]
}TIPO_GRAFO;
typedef TIPO_GRAFO* GRAFO;

/*
void print_peso_aresta(GRAFO grafo, int origem, int destino){
    printf("PESO DE (%d,%d) = %.2f\n\n", origem, destino, grafo->pesos[origem][grafo->grau[origem]]);
    
    for(int c=0; c<grafo->qtd_vertices; c++){
        for(int k=0; k<grafo->grau_max; k++){
            printf("(%d,%d) = %.1f\n", c,k, grafo->pesos[c][k]);
        }
    }
}
*/

void print_adjacentes(GRAFO grafo, int  vertice){
    int c=0;
    printf("VERTICE[%d] = ADJACENTES [ ", vertice);
    while(c<grafo->grau_max){
        printf("%d | ",grafo->arestas[vertice][c]);
        c++;
    }
    printf(" ]\n\n");
}

void print_grafo_completo(GRAFO grafo){
     
    for(int c=0; c<grafo->qtd_vertices; c++){
        printf("VERTICE[%d] = ADJACENTES [ ", c);
        for(int k=0; k<grafo->grau_max; k++){
            printf("%d | ",grafo->arestas[c][k]);
        }
        printf(" ]\n\n");
    }
}


void print_info_grafo(GRAFO grafo){

    printf("tem_peso: %s\n", grafo->tem_peso == true?"grafo com peso":"grafo sem peso");
    printf("qtd_vertices: %d\n",grafo->qtd_vertices);
    printf("grau_max: %d\n",grafo->grau_max);

    
 }

void free_grafo(GRAFO grafo){
    if(grafo != NULL){
        int c;
        
        for(c=0; c<grafo->qtd_vertices; c++){
            free(grafo->arestas[c]);
        }
        free(grafo->arestas);
        
        if(grafo->tem_peso){
            for(c=0; c<grafo->qtd_vertices; c++){
                free(grafo->pesos[c]);   
            }
            free(grafo->pesos);
        }
        free(grafo->grau);
        free(grafo);
    }
}

GRAFO new_grafo(int qtd_vertices, int grau_max, bool tem_peso){
    
    GRAFO grafo = (GRAFO)malloc(sizeof(TIPO_GRAFO));
    grafo->qtd_vertices = qtd_vertices;
    grafo->grau_max = grau_max;
    grafo->tem_peso = tem_peso;
    
    grafo->grau = (int*)calloc(qtd_vertices, sizeof(int)); //retorna um array do tipo int do tamanho qtd_vertices
    grafo->arestas = (int**)malloc(qtd_vertices*sizeof(int*)); // aloca um array para ser os vertices
    
    for(int c=0; c<qtd_vertices; c++){
        grafo->arestas[c] = (int*)malloc(grau_max*sizeof(int)); // para cada vertice criado, cria-se um array com tamanho max que é o grau do vertice
        
        if(grafo->tem_peso){
            grafo->pesos = (float**)malloc(qtd_vertices*sizeof(float*)); // cria um array para os vertices
            
            for(int k=0; k<qtd_vertices; k++){
                grafo->pesos[k] = (float*)malloc(grau_max*sizeof(float)); // para cada peso do vertice indicado, cria-se um array para ser da aresta [vertice][adjacentes]
            }
        }
        
    }
    
    for(int a=0;a<qtd_vertices;a++){
        for(int b=0;b<grau_max;b++){
            grafo->arestas[a][b] = -1;
        }
    }
    
    return grafo;
    
}

int inserir_aresta(GRAFO grafo, int origem, int destino, float peso, bool nao_ordenado){
    
    if(grafo != NULL){
        if((origem < 0 || origem > grafo->qtd_vertices-1) || (destino < 0 || destino > grafo->qtd_vertices-1)){
            return FORA_DO_GRAFO; //se as vertices escolhidas n�o estivem no grafo, finaliza-se
        }
        
        grafo->arestas[origem][grafo->grau[origem]] = destino;
        
        if(grafo->tem_peso){
            grafo->pesos[origem][grafo->grau[origem]] = peso;
        }else{
            grafo->pesos[origem][grafo->grau[origem]] = -1;    
        }
        
        grafo->grau[origem]++;
        
        if(nao_ordenado){ // se grafo nao ordenado, ent�o dece-se ligar no outro lado da aresta
            inserir_aresta(grafo, destino, origem, peso, false); // passando false na recurs�o evito loop infinito
        }
        return ARESTAS_LIGADAS;
    }
}

int deletar_aresta(GRAFO grafo, int origem, int destino, bool nao_ordenado){
    
    if(grafo != NULL){
        if((origem < 0 || origem > grafo->qtd_vertices-1) || (destino < 0 || destino > grafo->qtd_vertices-1)){
            return FORA_DO_GRAFO; //se as vertices escolhidas n�o estivem no grafo, finaliza-se
        }
        
        int c;
        for(c=0 ; (c<grafo->grau[origem] && grafo->arestas[origem][c]!=destino) ; c++);
            
        if(c == grafo->grau[origem]){
            return ARESTA_INVALIDA;
        }
        
        grafo->grau[origem]--;
        grafo->arestas[origem][c] = grafo->arestas[origem][grafo->grau[origem]];
        
        if(grafo->tem_peso){
            grafo->pesos[origem][c] = grafo->pesos[origem][grafo->grau[origem]];
        }
        
        if(nao_ordenado){
            deletar_aresta(grafo, destino, origem, false);
        }
    }
}

void main(){
    
    GRAFO meu_grafo = new_grafo(3, 3, true);
    
    print_info_grafo(meu_grafo);
    
    inserir_aresta(meu_grafo, 1, 2, 0.8, true);//o boolean indica se é ordenado ou nao
    
    inserir_aresta(meu_grafo,0, 2, 0.3, true);//o boolean indica se é ordenado ou nao

    
    print_grafo_completo(meu_grafo);

    free_grafo(meu_grafo);
}



