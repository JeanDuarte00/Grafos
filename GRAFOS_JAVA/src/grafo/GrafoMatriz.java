package grafo;

import java.util.LinkedList;

public class GrafoMatriz{
	private int qtdVertices;
	private int qtdArestas;
	
	private TuplaAresta listaDeVizinhos[][];
	
		
	public GrafoMatriz(int tamanho){
		this.qtdVertices = tamanho;
		this.qtdArestas = 0;
		
		this.listaDeVizinhos = new TuplaAresta[tamanho][tamanho];
	}
	
	public TuplaAresta[][] getVizinhos() {
		return this.listaDeVizinhos;
	}
 	
	public int getQtdVertice() {
		return qtdVertices;
	}

	public int getQtdArestas() {
		return qtdArestas;
	}
	
	public double getPeso(int origem, int destino) {
		return this.listaDeVizinhos[origem][destino].getPeso();
	}
	
	public double getInfo(int origem, int destino) {
		return this.listaDeVizinhos[origem][destino].getInfo();
	}
	
	public boolean checkAresta(int origem, int destino) {
		for(int c=0; c<this.qtdVertices; c++) {
			if(this.listaDeVizinhos[origem][destino].getInfo() == 1) {
				return true;
			}
		}
		return false;
	}

	
	public void addAresta(int origem, int destino,  double peso, boolean digrafo) {
		this.qtdArestas = this.qtdArestas + 1;
		this.listaDeVizinhos[origem][destino] = new TuplaAresta(1, peso);
	}

	
	public int grauDoVertice(int vertice) {
		int qtd =0;
		for(int c=0; c<this.qtdVertices; c++) {
			if(this.listaDeVizinhos[vertice][c].getInfo() == 1) {
				++qtd;
			}
		}
		
		return qtd;
	}

	
	public void print() {
		for(int c=0; c<this.qtdVertices; c++) {
			for(int k=0; k<this.qtdVertices; k++) {				
				if(this.listaDeVizinhos[c][k] == null) {
					this.listaDeVizinhos[c][k] = new TuplaAresta(0,0.0);
				}
			}
		}
		
		System.out.print("      ");
		for(int l=0; l<this.qtdVertices; l++) {
			System.out.print(" {  "+l+"  } ");
		}System.out.println("\n");
		
		for(int c=0; c<this.qtdVertices; c++) {
			System.out.print("{"+c+"}  ");
			System.out.print("|");
			for(int k=0; k<this.qtdVertices; k++) {				
					System.out.print(" ("+ this.listaDeVizinhos[c][k].getInfo() + "|" + this.listaDeVizinhos[c][k].getPeso() + ") ");				
			}
			System.out.println("|");
			
		}
		
	}


	public GrafoLista intoLista(GrafoMatriz matriz) {
		boolean digrafo;
		GrafoLista lista = new GrafoLista( matriz.getQtdVertice() );
		LinkedList<TuplaAresta>[] linked = lista.getVizinhos();
		TuplaAresta tuplas[][] = matriz.getVizinhos();
		
		for(int c=0; c<matriz.getQtdVertice(); c++) {
			for(int k=0; k<matriz.getQtdVertice(); k++) {
				if(tuplas[c][k].getInfo() == 1) {
					linked[c].add( new TuplaAresta(c,k) );
					
					//se dupla ligação -(c,k) == (k,c) - retorna true
					digrafo = ( lista.checkAresta(c, k) && lista.checkAresta(k, c) );
					lista.addAresta(c, k, tuplas[c][k].getPeso(), !digrafo);
				}
			}
		}
		return lista;
	}
	
	
	public void buscarEmLargura(int vertice) {
		// TODO Auto-generated method stub
		
	}


	
	public int grauDoVertice(Integer vertice) {
		// TODO Auto-generated method stub
		return 0;
	}


	
	public void buscaEmProfundidade(int vertice) {
		// TODO Auto-generated method stub
		
	}

	
	

}
