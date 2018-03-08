#ifndef CABECALHOS
#define CABECALHOS

void set_tamanho_grafo(GRAFO grafo, int tamanho);
VERTICE *new_vertice();
GRAFO new_grafo( int tamanho);
void ligar_vertices(GRAFO grafo, VERTICE *origem, VERTICE *destino, int aresta, float peso, bool digrafo );
void mostrar_todos_adjacentes(VERTICE *vertice);


#endif