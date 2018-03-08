import grafo.GrafoLista;
import grafo.GrafoMatriz;


public class Main {
	
	public static void main(String[] args) {
	    GrafoLista lista = new GrafoLista(4);		
	    lista.addAresta(0, 1, 3.6, true);
	    lista.addAresta(1, 2, 5.7, false);
	    lista.addAresta(0, 3, 3.2, true);
	    lista.addAresta(0, 2, 1.5, false);
	    lista.addAresta(3, 1, 1.9, false);
	
	    lista.print();
	    
	    System.out.println();
	    
	    GrafoMatriz matriz = lista.intoMatriz(lista);
	    
	    matriz.print();
	    
	    System.out.println();
	    
	    GrafoLista grafo = matriz.intoLista(matriz);
	    
	    grafo.print();
	   
	}
}