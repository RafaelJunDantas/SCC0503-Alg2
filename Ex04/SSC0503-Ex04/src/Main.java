import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        
        Scanner scan = new Scanner(System.in);
        
        //System.out.print("Numero de vertices: ");
        int numberOfVertex = scan.nextInt();
        //System.out.println("Quantidade de vertices: " + numberOfVertex);
        
        scan.nextLine();     //le o \n 
        
        List<Vertex> vertices = new ArrayList<>();
        
        for(int i = 0; i < numberOfVertex; i++){
            //System.out.print("Nome da quest " + i + ": ");
            String nome = scan.nextLine();
            //System.out.println("Nome lido: " + nome);
            
            //System.out.print("Descricao da quest " + i + ": ");
            String descricao = scan.nextLine();
            //System.out.println("Descricao lida: " + descricao);
            
            Quest q = new Quest(i, nome, descricao);
            //q.printQuest();
            
            vertices.add(new Vertex(q));
        }
        
        AbstractGraph graph = new GraphMatrix(vertices);
        
        //System.out.print("Numero de arestas: ");
        int numberOfEdge = scan.nextInt();
        //System.out.println("Quantidade de arestas: " + numberOfEdge);
        
        scan.nextLine();     //le o \n
        
        for(int i = 0; i < numberOfEdge; i++){
            //System.out.print("ID do vertice de origem e destino: ");
            int origem = scan.nextInt();
            int destino = scan.nextInt();
            //System.out.println("Vertice de origem: " + origem + " <-> Vertice de destino: " + destino);
            
            graph.addEdge(vertices.get(origem), vertices.get(destino), 1);
            
            scan.nextLine();     //le o \n
        }
        
        //System.out.print("Vertice inicial da travessia: ");
        int start = scan.nextInt();
        //System.out.println("Vertice inicial: " + start);
        
        TraversalStrategy traversalStrategy = new BuscaProfundidade(graph);
        traversalStrategy.traverseGraph(graph.getVertices().get(start));
        //traversalStrategy.printDistances();
        //traversalStrategy.printPath();
        //traversalStrategy.printVisitTree(start);
        
        scan.close();
    }
    
}
