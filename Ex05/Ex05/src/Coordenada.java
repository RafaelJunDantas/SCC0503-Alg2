
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Rafael
 */
public class Coordenada {
    
    private int x;
    private int y;
    
    public Coordenada(int x, int y){
        this.x = x;
        this.y = y;
    }
    
    public int getX(){
        return this.x;
    }
    
    public int getY(){
        return this.y;
    }
    
    public boolean compareTo(Coordenada posicao2){
        return this.x == posicao2.getX() && this.y == posicao2.getY();
    }
    
    public float distanceTo(Coordenada posicao2){
        float xDiff = this.x - posicao2.getX();
        float yDiff = this.y - posicao2.getY();
        
        return (float) sqrt(pow(xDiff, 2) + pow(yDiff, 2));
    }
}
