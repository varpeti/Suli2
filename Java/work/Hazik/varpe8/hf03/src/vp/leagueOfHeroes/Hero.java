package vp.leagueOfHeroes;

import  vp.leagueOfHeroes.*;

import java.util.*;

public class Hero implements Runnable 
{
    private String name = new String();
    private String league = new String();
    private Quests quests;
    private Equipments equipments = new Equipments();
    private int repu = 0;

    public void run() 
    {
        int questid = -1;
        String itemsok = new String("");
        ArrayList<String> items = new ArrayList<String>();
        while (!quests.isOver()) //30 másodperc után van még hős aki küldetésen van. Mivel hogy 30. másodpercben is jön ki 2 quest ezért ha valaki végig tudja vinni, végigviheti. De ha nem elég híres, vagy nincs bent a felszerelés akkor haza megy. 
        {
            //Tábla
            if (questid==-1) {
                questid = quests.getQuest(repu); // A bátor hős átnézi a küldetéseket.
                if (questid==-1) {try{Thread.sleep(150);}catch(Exception e){}; System.out.println(name+" nem talált megfelelő küldetést!\n"); continue;} // Ha nincs megfelelő vár legalább 0.15 másodpercet
                
                System.out.println(name+" elfogadta a "+questid+". küldetést!\n");
            }
           
            //Felszerelés
            if ( !Objects.equals(itemsok,"ok") ) {
                items = quests.getItemList(questid); // Lekéri a szükséges felszerelések listáját.
                itemsok = equipments.get(items); // Kikéri a felszerelést.
                if ( !Objects.equals(itemsok,"ok") ) {try{Thread.sleep(300);}catch(Exception e){}; System.out.println(name+" várakozik a szükséges felszerelésre! Mivel elvitték a(z) "+itemsok+"-t\n"); continue;} // Ha nincs bent az összes ami kell vár legalább 0.3 másodpercet
                
                System.out.println(name+" megszerezte az összes kelléket a harchoz!\n");
            }

            //Harc
            {   
                try{Thread.sleep(quests.getQuestTime(questid));}catch(Exception e){}; // A véres küzdelem.
                repu+=quests.getQuestRepu(questid,league); // Hírnév jutalom.
                System.out.println(name+" "+league+"-ból/ből végzett a csatával! A hírneve "+repu+"-ig emelkedett! Megtisztíja és vissza adja a felszerelést!\n");
                equipments.putBack(items); // Becsületesen, megtisztítva vissza adja a felszerelést.
            }

            // Újra nézi a táblát.
            questid=-1; itemsok = new String("");
        }
        Leagues.fin(name);
        System.out.println(name+" végzett mára és haza ment pihenni.\n");
    }

    public Hero(String _name,String _league, Quests _quests, Equipments _equipments)
    {
        name = _name;
        league = _league;
        quests = _quests;
        equipments = _equipments;
        repu = 0;
        new Thread(this).start();
    }

    public synchronized String getName()
    {
        return name;
    }
}