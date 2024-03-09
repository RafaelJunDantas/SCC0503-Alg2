
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        
        Scanner scan = new Scanner(System.in);
        
        int numberOfNodes = scan.nextInt();
        
        scan.nextLine();
        
        ArrayList<Vertex> vertexList = new ArrayList();
        
        for(int i = 0; i < numberOfNodes; i++){
            String line = scan.nextLine();
            var lineSplitted = line.split(",");
            int x = Integer.parseInt(lineSplitted[0]);
            int y = Integer.parseInt(lineSplitted[1]);
            //System.out.println(x + " " + y);
            
            Coordenada posicao = new Coordenada(x,y);
            
            vertexList.add(new Vertex(i, posicao));
        }
        
        AbstractGraph graph = new GraphMatrix(vertexList);
        
        int numberOfEdges = scan.nextInt();
        
        scan.nextLine();
        
        for(int i = 0; i < numberOfEdges; i++){
            String line = scan.nextLine();
            //System.out.println("--> " + line);
            var lineSplitted = line.split(":");
            //System.out.println("--> " + input[0] + " " + input[1]);
            var pos1 = lineSplitted[0].split(",");
            var pos2 = lineSplitted[1].split(",");
            int x1 = Integer.parseInt(pos1[0]);
            int y1 = Integer.parseInt(pos1[1]);
            int x2 = Integer.parseInt(pos2[0]);
            int y2 = Integer.parseInt(pos2[1]);
            //System.out.println(x1 + " " + y1 + " " + x2 + " " + y2);
            
            Coordenada posicao1 = new Coordenada(x1,y1);
            Coordenada posicao2 = new Coordenada(x2,y2);
            //System.out.println(posicao1.distanceTo(posicao2));
            
            Vertex origem = null;
            Vertex destino = null;
            
            for(int j = 0; j < vertexList.size(); j++){
                if(vertexList.get(j).getCoordenada().compareTo(posicao1)){
                    origem = vertexList.get(j);
                    //System.out.println(origem.getName());
                }
                if(vertexList.get(j).getCoordenada().compareTo(posicao2)){
                    destino = vertexList.get(j);
                    //System.out.println(destino.getName());
                }
            }
            
            graph.addEdge(origem, destino, posicao1.distanceTo(posicao2));
        }
        
        System.out.println();
        
        TraversalStrategy traverseStrategy = new FloydWarshallTraversal(graph);
        traverseStrategy.traverseGraph(vertexList.get(0));
        
        scan.close();
    }
}
