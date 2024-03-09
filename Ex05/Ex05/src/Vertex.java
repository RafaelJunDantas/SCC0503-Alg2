import java.util.Objects;

public class Vertex
{
    private int ID;
    private Coordenada posicao;
    
    
    public Vertex(int ID, Coordenada posicao){
        this.ID = ID;
        this.posicao = posicao;
    }

    public String getName(){
        return String.valueOf(ID);
    }
    
    public Coordenada getCoordenada(){
        return this.posicao;
    }
    
    public void printVertex(){
        System.out.println(posicao.getX() + "," + posicao.getY());
    }

    @Override
    public String toString()
    {
        return String.valueOf(ID);
    }
}
