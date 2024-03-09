

public class Quest {
    private int ID;
    private String nome;
    private String descricao;
    
    public Quest(int ID, String nome, String descricao){
        this.ID = ID;
        this.nome = nome;
        this.descricao = descricao;
    }
    
    public int getID(){
        return this.ID;
    }

    public String getNome() {
        return nome;
    }

    public String getDescricao() {
        return descricao;
    }
    
    public void printQuest(){
        System.out.println("Quest{");
        System.out.println("\tID = '" + this.getID() + "'");
        System.out.println("\tname = '" + this.getNome() + "'");
        System.out.println("\tdescription = '" + this.getDescricao() + "'");
        System.out.println("}");
    }
}
