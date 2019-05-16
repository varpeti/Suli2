package vp.leagueOfHeroes;

import  vp.leagueOfHeroes.*;

import java.util.*;

public class Leagues 
{

    private static String[] leagues = {"Humans","Orcs","Elves","Undeads"};
    private static ArrayList< ArrayList<Hero> > heroes = new ArrayList< ArrayList<Hero> >();
    private static Integer[] repos = {0,0,0,0};
    private static ArrayList< ArrayList<Boolean> > athome = new ArrayList< ArrayList<Boolean> >(); //Otthon van-e? (végzett mára?)
    private static Scores scores;

    public static void setLeagues(Quests quests,Equipments equipments)
    {
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Luna",leagues[0],quests,equipments));             add(new Hero("Mirana",leagues[0],quests,equipments));      add(new Hero("Kunkka",leagues[0],quests,equipments));       }} );
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Axe",leagues[1],quests,equipments));              add(new Hero("Lion",leagues[1],quests,equipments));        add(new Hero("Troll Warlord",leagues[1],quests,equipments));}} );
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Nature's Prophet",leagues[2],quests,equipments)); add(new Hero("Enchantress",leagues[2],quests,equipments)); add(new Hero("Lone Druid",leagues[2],quests,equipments));   }} );
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Lich",leagues[3],quests,equipments));             add(new Hero("Undying",leagues[3],quests,equipments));     add(new Hero("Necrophos",leagues[3],quests,equipments));    }} );
        
        // Szép jó reggelt! Mindenki munkára! Várnak a sárkányok, a királylányok és a WC pucolás Marinéninél!
        for (int i=0;i<heroes.size();i++)
        {
            ArrayList<Boolean> b = new ArrayList<Boolean>();
            for (int j=0;j<heroes.get(i).size();j++) b.add(false);
            athome.add(b);
        }

        //Scores irodában is (szigorúan a reggeli kávé után) kezdődik a munka
        scores = new Scores(leagues);
    }

    public static synchronized void fin(String name) // Befejezte a küldetést
    {
        for (int i=0;i<heroes.size();i++) 
            for (int j=0;j<heroes.get(i).size();j++)
                if ( Objects.equals(name,heroes.get(i).get(j).getName()) ) athome.get(i).set(j,true); 
    }

    public static synchronized void addRepu(String league, int repu) //*2//
    {
        scores.addRepu(league,repu); // A leagues iroda átadja a Scores alrészlegnek a hírnév növekvényt.
    }

    ////////////////////////////////////////////// Scores alrészleg

    private static class Scores implements Runnable
    {
        private String[] leagues;
        private int[] repus;
    
    
        public void run()
        {
            Boolean b = true;
            int o = 0;
            while(b) //2.5 Másodpercenként nézi hogy vége van e?
            {   
                if (o==4) 
                {
                    StringBuilder announce = new StringBuilder("A Ligák által eddig elért eredények:\n");
                    for (int i=0;i<leagues.length;i++) 
                    {
                        announce.append("\t"+leagues[i]+"\t"+repus[i]+"\n");
                    }
                    System.out.println(announce);
                    o=0;
                } else o++;

                try{Thread.sleep(2500);}catch(Exception e){}; // 10 Másodpercenként (2500*4) kiírja az eredményt 
                
                //Addig megy míg mindenki haza nem indult. | mivel 5 sec egy küldetés (max) ezért (elvileg) nem léphet túl még 1x 10sec-es várakozába.
                b=false;
                outerloop: // I rememeber thooose old days... RIP Turbo Pascal RIP goto
                for (int i=0;i<heroes.size();i++) 
                    for (int j=0;j<heroes.get(i).size();j++)
                        if (!athome.get(i).get(j)) {b=true; break outerloop;}
            }


            System.out.println("A Ligák által elért végső eredények:");
            for (int i=0;i<leagues.length;i++) 
            {
                System.out.println("\t"+leagues[i]+"\t"+repus[i]);   
            }
        }
    
        public Scores(String[] _leagues)
        {
            leagues = _leagues;
            repus = new int[leagues.length];
            
            new Thread(this).start();
        }
    
        public synchronized void addRepu(String league, int repu) //*2//
        {
            for (int i=0;i<leagues.length;i++) 
            {
                if ( Objects.equals(league,leagues[i]) ) repus[i]+=repu;
            }
        }
    }
}

//*2: synchronized blokból hívott függvények, nem kellene synchronized-nek lenni. De biztos ami biztos, ha bele nyúl valaki késöbb a renszerbe ne legyen belőle baj.