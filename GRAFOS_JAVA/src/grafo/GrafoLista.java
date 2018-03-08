package grafo;

import java.util.LinkedList;

public class GrafoLista{

	private int qtdVertice;
    private int qtdArestas;

    private LinkedList<TuplaAresta> listaDeVizinhos[];
	
	public int getQtdVertice() {
		return qtdVertice;
	}

	public int getQtdArestas() {
		return qtdArestas;
	}
	
	public LinkedList<TuplaAresta>[] getVizinhos() {
		return this.listaDeVizinhos;
	}

	@SuppressWarnings("unchecked")
	public GrafoLista(int tamanho){
        this.qtdVertice = tamanho;
        this.qtdArestas = 0;

        this.listaDeVizinhos = new LinkedList[tamanho];

        for(int c=0; c < qtdVertice; c++){
            this.listaDeVizinhos[c] = new LinkedList<>();
        }
    }    
	
	public boolean checkAresta(int origem, int destino) {
				
		for(TuplaAresta vizinho: this.listaDeVizinhos[origem]) {
			if(vizinho.getInfo() == destino) {
				return true;
			}
		}		
		return false;
	}

    public void addAresta(int origem, int destino, double peso, boolean digrafo){
        
    	this.qtdArestas = this.qtdArestas + 1;
    	    	
        this.listaDeVizinhos[origem].add( new TuplaAresta(destino, peso) );
        if( !digrafo ){
            this.listaDeVizinhos[destino].add( new TuplaAresta(origem, peso) );
        }

    }
    
    public int grauDoVertice(Integer vertice) {
    	
    	return this.listaDeVizinhos[vertice].size();
    	
    }
   
    public void print(){
        
        for(int c=0; c<this.qtdVertice; c++){        	
            System.out.printf("Vizinhos de (%d) = [", c);
            for (TuplaAresta vizinho : this.listaDeVizinhos[c]) {
                System.out.print(" ("+vizinho.getInfo() + "|"+ vizinho.getPeso() +") ");
            }
            System.out.println("]");
        }        
    }

    private void gbp(int  vertice, boolean visitados[]) {
    	
    	visitados[vertice] = true;
    	System.out.print(vertice + " ");
    	
    	for(TuplaAresta c: this.listaDeVizinhos[vertice]) {
    		if( !visitados[c.getInfo()] ) {
    			gbp(c.getInfo(), visitados);
    		}
    	}
    	
    }
    public void buscaEmProfundidade(int vertice) {
    	boolean visitados[] = new boolean[this.qtdVertice];
    	
    	this.gbp(vertice, visitados);
    	
    }
    
    public void buscarEmLargura(int vertice) {
    	int vert;
    	boolean visitados[] = new boolean[this.qtdVertice]; 
    	
    	LinkedList<Integer> filaDeVertices = new LinkedList<>();
    	
    	visitados[vertice] = true;
    	filaDeVertices.push(vertice);
    	
    	while( !filaDeVertices.isEmpty() ) {
    		vert = filaDeVertices.pop();
    		System.out.print(vert+" ");
    		
    		for(TuplaAresta c : this.listaDeVizinhos[vert]) {
    			if(!visitados[c.getInfo()]) {
    				visitados[c.getInfo()] = true;
    				filaDeVertices.push(c.getInfo());
    			}
    		}
    	}    	
    }
    
    public GrafoMatriz intoMatriz(GrafoLista lista) {
	    GrafoMatriz matriz = new GrafoMatriz(4);
	    LinkedList<TuplaAresta>[] linked = lista.getVizinhos();	    
	    for(int c=0; c<lista.getQtdVertice(); c++) {
	    	for(int k=0; k<linked[c].size(); k++) {
	    		TuplaAresta tupla = linked[c].get(k);	    	
	    		matriz.addAresta(c, tupla.getInfo(), tupla.getPeso(), false);
	    	}
	    }
	    return matriz;
	}


}



