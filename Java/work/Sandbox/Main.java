import Matek.Statisztika;
import Matek.Komplex;
import java.util.Vector;
import java.util.Arrays;

public class Main
{
    public static void main(String[] args) 
    {
        Statisztika s = new Statisztika();
        Vector<Integer> v = new Vector<Integer>();
        v.add(2);
        v.add(3);
        System.out.println(s.sum(v.toArray(new Integer[v.size()])));

        Vector< Vector<Integer> > m = new Vector< Vector<Integer> >();
        while(true);
    }
}