import java.util.*;

public class BuscaProfundidade extends TraversalStrategy
{
    public BuscaProfundidade(AbstractGraph graph)
    {
        super(graph);
    }

    @Override
    public void traverseGraph(Vertex source)
    {   
        int sourceIndex = getGraph().getVertices().indexOf(source);
        addToPath(source);
        markVertexAsVisited(sourceIndex);
        setDistanceToVertex(sourceIndex, 0);
        setPredecessorVertexIndex(sourceIndex, -1);
        
        Vertex adjacentVertex = getGraph().getFirstConnectedVertex(source);
        int adjacentVertexIndex = getGraph().getVertices().indexOf(adjacentVertex);
        
        while(adjacentVertex != null){
            adjacentVertexIndex = getGraph().getVertices().indexOf(adjacentVertex);
            if(!hasVertexBeenVisited(adjacentVertexIndex)){
                traverseGraph(adjacentVertex);
            }
            adjacentVertex = getGraph().getNextConnectedVertex(source, adjacentVertex);
        }
        markVertexAsVisited(adjacentVertexIndex);
       
        printPath();
    }

    private void updateTraversalInfoForVertex(int newVertexIndex, int previousVertexIndex)
    {
        var newVertex = getGraph().getVertices().get(newVertexIndex);
        var oldVertex = getGraph().getVertices().get(previousVertexIndex);
        float newDistance = getGraph().getDistance(oldVertex, newVertex);
        float distance = getDistanceToVertex(previousVertexIndex) + newDistance;
        addToPath(newVertex);
        markVertexAsVisited(newVertexIndex);
        setDistanceToVertex(newVertexIndex,  distance);
        setPredecessorVertexIndex(newVertexIndex, previousVertexIndex);
        setSuccessorVertexIndex(previousVertexIndex, newVertexIndex);
    }

}