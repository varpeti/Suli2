package Matek;

public class Statisztika {
    public int sum(Integer[] a)
    {
        Integer ret = 0;
        for (int i=0;i<a.length;i++) 
        {
            ret += a[i];
        }
        return ret;
    }
}