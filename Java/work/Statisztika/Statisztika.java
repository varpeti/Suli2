package stat;

public class Statisztika {
    public int sum(int[] a)
    {
        int ret = 0;
        for (int i=0;i<a.length;i++) 
        {
            ret += a[i];    
        }
        return ret;
    }

    public static void main(String[] args) 
    {
        Statisztika s = new Statisztika();
        int[] a = {1, 2, 3, 4, 5};
        System.out.println(s.sum(a));
    }
}