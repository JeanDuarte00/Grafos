
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
typedef TIPO_GRAFO *GRAFO;