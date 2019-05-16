package Singleton;

public class Singleton 
{
    private static Singleton instance = new Singleton();

    private Singleton()
    {
        System.out.println("Hello World! I'm a singleton!");
    }

    public static Singleton getInstance()
    {
        return instance;
    }

    public void method()
    {
        System.out.println(this.hashCode());
    }
}