package vp.leagueOfHeroes;

import java.util.*;

public class Equipments 
{
    private static final String[] items = { // Túl sok gond van az enummal :D
        "magic wand",
        "null talisman",
        "wraith band",
        "bracer",
        "soul ring",
        "phase boots",
        "power treads",
        "oblivion staff",
        "pers",
        "hand of midas",
        "travel boots",
        "moon shard",
        "ring of basilius",
        "headdress",
        "buckler",
        "urn of shadows",
        "tranquil boots",
        "ring of aquila",
        "medallion of courage",
        "arcane boots",
        "ancient janggo",
        "vladmir",
        "mekansm",
        "spirit vessel",
        "pipe",
        "guardian greaves",
        "glimmer cape",
        "veil of discord",
        "aether lens",
        "force staff",
        "necronomicon",
        "solar crest",
        "dagon",
        "cyclone",
        "rod of atos",
        "orchid",
        "ultimate scepter",
        "nullifier",
        "refresher",
        "sheepstick",
        "octarine core",
        "hood of defiance",
        "vanguard",
        "blade mail",
        "soul booster",
        "crimson guard",
        "combo breaker",
        "black king bar",
        "lotus orb",
        "shivas guard",
        "hurricane pike",
        "sphere",
        "bloodstone",
        "manta",
        "heart",
        "assault",
        "lesser crit",
        "armlet",
        "meteor hammer",
        "invis sword",
        "basher",
        "bfury",
        "monkey king bar",
        "ethereal blade",
        "radiance",
        "greater crit",
        "butterfly",
        "silver edge",
        "rapier",
        "abyssal blade",
        "bloodthorn",
        "dragon lance",
        "sange",
        "yasha",
        "trident",
        "mask of madness",
        "helm of the dominator",
        "echo sabre",
        "maelstrom",
        "diffusal blade",
        "heavens halberd",
        "desolator",
        "sange and yasha",
        "skadi",
        "satanic",
        "mjollnir",
        "energy booster",
        "vitality booster",
        "point booster",
        "platemail",
        "talisman of evasion",
        "hyperstone",
        "ultimate orb",
        "demon edge",
        "mystic staff",
        "reaver",
        "eagle",
        "relic"
    };
    private ArrayList<Boolean> onJurney = new ArrayList<Boolean>(); //False = elérhető
    private Object syn = new Object();

    public Equipments()
    {
        for (int i=0;i<items.length;i++) 
        {
            onJurney.add(new Boolean(false));   
        }
    }

    private static int getID(String name)
    {
        for (int i=0;i<items.length;i++) if ( Objects.equals(items[i],name) ) {return i;}
        return -1;
    }

    static Random rand = new Random();
    public static String getRandom()
    {
        return items[rand.nextInt(items.length)];
    }

    public synchronized String get(ArrayList<String> name) //Csak akkor adja ki ha mind bent van, hogy ne alakulhasson ki deadlock.
    {
        synchronized (syn) // nem lehet kérni ha épp beadnak valamit
        {
            int[] lock = new int[name.size()];
            for (int i=0;i<name.size();i++) 
            {
                int id = getID(name.get(i));
                if (onJurney.get(id)) return new String(name.get(i)); // Nincs raktáron
                lock[i]=id;  
            }
            //Mindegyik a raktáron van, akkor lefoglalja:
            for (int i=0;i<lock.length;i++) onJurney.set(lock[i],new Boolean(true));
            return new String("ok");
        }
    }

    public synchronized void putBack(ArrayList<String> name)
    {
        synchronized (syn) // nem lehet beadni ha épp kér valaki
        {
            for (int i=0;i<name.size();i++) 
            {
                int id = getID(name.get(i));
                onJurney.set(id,new Boolean(false)); // Visszarakja
            }
        }
    }
}