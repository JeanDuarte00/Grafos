package grafo;

import java.io.BufferedReader;
import java.io.FileReader;

import java.util.LinkedList;

public class GrafoLista{

	private int qtdVertice;
    private int qtdArestas;

    private String nomeVertice[];
    private LinkedList<TuplaAresta> listaDeVizinhos[];
	
    public String getNomeVertice(int posicao) {
    	return this.nomeVertice[posicao];
    }
    
    public void setNomeVertice(String nome, int posicao) {
    	this.nomeVertice[posicao]  = nome;
    }
    
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

        this.nomeVertice = new String[tamanho];
        this.listaDeVizinhos = new LinkedList[tamanho];

        for(int c=0; c < qtdVertice; c++){
            this.listaDeVizinhos[c] = new LinkedList<>();
        }
    } 
	
	@SuppressWarnings("unchecked")
	public GrafoLista(String args) throws Exception {
		BufferedReader leitor  = new BufferedReader(new FileReader(args));
			
		
		int qtdVertices = leitor.read()-48; //.read retorna o valor em ascii
		
		this.qtdVertice = qtdVertices;
        this.qtdArestas = 0;

        this.nomeVertice = new String[qtdVertices];
        this.listaDeVizinhos = new LinkedList[qtdVertices];

        for(int c=0; c < qtdVertice; c++){
            this.listaDeVizinhos[c] = new LinkedList<>();
        }
		
		for(int c=-1; c<qtdVertices; c++){
			
			String linha = leitor.readLine();				
			String partes[] = linha.split(" ");
			
			
			for(int k=1; k<partes.length; k++){
				this.addAresta( c, Integer.parseInt(partes[k]), 0.0, true);
				this.setNomeVertice(partes[0], c);
			}
		}
		
		leitor.close();
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
        
    	if(origem < 0 || destino < 0) {
    		System.out.printf("Valor de origem(%d) e/ou destino(%d) não pode ser menor do que zero!\n", origem, destino);
    	}else if(origem > this.qtdVertice || destino > this.qtdVertice){
    		System.out.printf("Valor de origem(%d) e/ou destino(%d) não pode ser maior do que a quantidade maxima de vertices!\n", origem, destino);
    	}else {
        	
        	this.qtdArestas = this.qtdArestas + 1;
        	    	
            this.listaDeVizinhos[origem].add( new TuplaAresta(destino, peso) );
            if( !digrafo ){
                this.listaDeVizinhos[destino].add( new TuplaAresta(origem, peso) );
            }

    	}

    }
    
    public int grauDoVertice(Integer vertice) {
    	
    	return this.listaDeVizinhos[vertice].size();
    	
    }
   
    public void print(){
        
        for(int c=0; c<this.qtdVertice; c++){        	
            System.out.printf("Vizinhos de %s(%d)\t= [", this.nomeVertice[c],c);
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



