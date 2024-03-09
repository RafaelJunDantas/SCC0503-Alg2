import java.util.Objects;

public class Vertex
{
    private Quest quest;

    public Quest getQuest() {
        return quest;
    }
    
    public String getName() {
        return this.getQuest().getNome();
    }
    
    public int getID(){
        return this.getQuest().getID();
    }
    
    public String getDescricao(){
        return this.getQuest().getDescricao();
    }

    public Vertex(Quest quest) {
        this.quest = quest;
    }
    
    public void printVertex(){
        this.getQuest().printQuest();
    }

    @Override
    public String toString()
    {
        return """
               \nQuest{
               \tID= '""" + this.getID() + "'\n" + "\tname = '" + this.getName() + "'\n"
                + "\tdescription = '" + this.getDescricao() + "'\n" + "}";
    }
}
