package GoldenAK47;

public class GoldenAK47 
{
    // Mivel a class betöltődésekor jön létre, thread safe marad, a lazy ("csak ha használjuk") implementációval szemben
    private static GoldenAK47 instance = new GoldenAK47();

    private GoldenAK47()
    {
        System.out.println("Hello World! I'm the Only, and the One GoldenAK47!");
    }

    public static GoldenAK47 getInstance()
    {
        return instance;
    }

    public void shoot()
    {
        System.out.println(this.hashCode() + " is shooting.");
    }
}