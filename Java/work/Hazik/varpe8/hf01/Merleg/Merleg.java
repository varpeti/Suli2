package Merleg;

import java.util.*;


public class Merleg {
    private ArrayList<Integer> sulyok = new ArrayList<Integer>(); //Sulyokat tárolja

    public int[] sulyokraValt(int N)
    {

        int table[] = new int[N+1]; // Részeredmények és a megoldás
        int useds[] = new int[N+1]; // Ebből szedem majd ki a felhasznált súlyokat

        Arrays.fill(table,Integer.MAX_VALUE-1);
        Arrays.fill(useds,-1);
        table[0] = 0;

        for(int i=0; i < sulyok.size(); i++)
            for(int j=sulyok.get(i); j <= N; j++)
                if (table[j-sulyok.get(i)]+1 < table[j]) 
                {
                    table[j] = 1+table[j-sulyok.get(i)];
                    useds[j] = i;
                }

        int ret[] = new int[sulyok.size()+1]; //Felhasznált súlyok
        Arrays.fill(ret, 0);

        if (useds[useds.length - 1] == -1) return ret; //Nincs megoldás

        //Felhasznált súlyok kiszedése
        int i = useds.length-1;
        while (i > 0)
        {
            ret[useds[i]]++;
            i = i - sulyok.get(useds[i]);
        }

        ret[ret.length-1]=table[N]; //Megoldás a tábla végén    

        return ret;
    }

    public Merleg(Integer[] _sulyok)
    {
        this.sulyok.addAll(Arrays.asList(_sulyok)); // arrayból arraylistet csinál.
        Collections.sort(this.sulyok);
        //System.out.println(this + " " + sulyok);
    }
}