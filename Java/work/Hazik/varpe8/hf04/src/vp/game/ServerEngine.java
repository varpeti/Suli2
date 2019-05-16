package vp.game;

import java.util.*;
import java.net.*;

import vp.net.*;

public class ServerEngine implements Runnable
{
    private Message message;
    boolean runing = true;

    //Broadcasthoz tárolja az eddigi clienseket
    private ArrayList<InetAddress> clientAddresses = new ArrayList<>();
    private ArrayList<Integer>     clientPorts     = new ArrayList<>();
    private HashMap<String,String> existingClients = new HashMap<>();

    // pong-al folyamatosan streamelt message
    private String status = "wait4players 2 0";

    // Játék változók, metódusok
    static public class Game
    {
        static public int players = 2; //Ne nyomjon "error gameisfull"-t
        static public int ship2   = 0;
        static public int ship3   = 0;
        static public int ship4   = 0;
        static public int ship5   = 0;
        static public int round   = 0;
        static public int size    = 0;
        static public ArrayList<ArrayList<String>> table = new ArrayList<>();

        static private boolean addShipX(int x, int y, int len,String type)
        {
            if (!(x+len<size && y<size)) return false; //Out of index
            for (int i=0;i<len;i++) 
            {
                if (!Objects.equals(table.get(x+i).get(y),"water")) return false; // Collide
            }
            for (int i=0;i<len;i++) 
            {
                table.get(x+i).set(y,type);
            }
            return true;
        }

        static private boolean addShipY(int x, int y, int len,String type)
        {
            if (!(y+len<size && x<size)) return false; //Out of index
            for (int i=0;i<len;i++) 
            {
                if (!Objects.equals(table.get(x).get(y+i),"water")) return false; // Collide
            }
            for (int i=0;i<len;i++) 
            {
                table.get(x).set(y+i,type);
            }
            return true;
        }

        static public boolean generate() throws Exception
        {
            //Init
            for (int x=0;x<size;x++) 
            {
                ArrayList<String> s = new ArrayList<>();
                for (int y=0;y<size;y++) 
                {
                    s.add("water");
                }
                table.add(s);
            }

            //TODO: Hajók "random" elhelyezése
            int x = 0;
            int y = 0;
            for (int i=0;i<Game.players;i++) 
            {
                String clientID = ""+i;
                for (int i5=0;i5<ship5;i5++) 
                {
                    while(true)
                    {
                        if ( addShipX(x,y,5,clientID+" 1") ) break;
                        if ( addShipY(x,y,5,clientID+" 1") ) break;
                        x++;if(x==Game.size){y++; x=0;}if(y==Game.size)throw new Exception("ships inc");
                    }
                }
                for (int i4=0;i4<ship4;i4++) 
                {
                    while(true)
                    {
                        if ( addShipX(x,y,4,clientID+" 1") ) break;
                        if ( addShipY(x,y,4,clientID+" 1") ) break;
                        x++;if(x==Game.size){y++; x=0;}if(y==Game.size)throw new Exception("ships inc");
                    }
                }
                for (int i3=0;i3<ship3;i3++) 
                {
                    while(true)
                    {
                        if ( addShipX(x,y,3,clientID+" 1") ) break;
                        if ( addShipY(x,y,3,clientID+" 1") ) break;
                        x++;if(x==Game.size){y++; x=0;}if(y==Game.size)throw new Exception("ships inc");
                    }
                }
                for (int i2=0;i2<ship2;i2++) 
                {
                    while(true)
                    {
                        if ( addShipX(x,y,2,clientID+" 1") ) break;
                        if ( addShipY(x,y,2,clientID+" 1") ) break;
                        x++;if(x==Game.size){y++; x=0;}if(y==Game.size)throw new Exception("ships inc");
                    }
                }
            }

            return true;
        }
    }

    private boolean clientinfo(Message.Packet input)
    {
        // Ha elsőször csatlakozik hozzáadjuk //TODO: lecsatlakozottak, régóta nem válaszolók kivétele a listáról.

        String clientID = input.getAddress().toString() + "," + input.getPort();
        if (!existingClients.containsKey(clientID)) 
        {

            if (Game.players<=clientAddresses.size())
            {
                message.socketWrite(new Message.Packet("error gameisfull",input.getAddress(),input.getPort()));
                return false; // Ha megvan az összes játékos.
            }

            existingClients.put(clientID,"anon");
            clientAddresses.add(input.getAddress());
            clientPorts.add(input.getPort());
        }
        return true;
    }
    private void broadcast(String msg)
    {
        for (int j=0; j < clientAddresses.size(); j++) //Broadcast
        {
            message.socketWrite(new Message.Packet(msg,clientAddresses.get(j),clientPorts.get(j)) ); 
        }
    }
    private void broadcast(String msg,int repeate)
    {
        for (int j=0; j < clientAddresses.size(); j++) //Broadcast
        {
            message.socketWrite(new Message.Packet(msg,clientAddresses.get(j),clientPorts.get(j),repeate) ); 
        }
    }

    private void handle(Message.Packet input)
    {
        System.out.println("LOG.Server.handle: "+input.getMsg());

        ArrayList<String> cmd = Message.split(input.getMsg(),"\\s");

        if (Objects.equals(cmd.get(0),"ping"))
        {
            existingClients.put(input.getAddress().toString() + "," + input.getPort(),cmd.get(1)); //Névfrissítés

            ArrayList<String> statusf = Message.split(status,"\\s");
            if (Objects.equals(statusf.get(0),"wait4players"))
            {
                if (Game.players==clientAddresses.size()) 
                {
                    Game.round = 0;
                    status = "game -1 nil";
                }
                else
                {
                    status = "wait4players "+Game.players+" "+clientAddresses.size();
                }

            }
            else if (Objects.equals(statusf.get(0),"game"))
            {
                String clientID = clientAddresses.get(Game.round).toString() + "," + clientPorts.get(Game.round);
                    status = "game"
                        //Size
                        + " " + Game.size
                        //Name                   
                        + " " + existingClients.get(clientID);

                for (int pID=0;pID<Game.players;pID++) //TODO: csak a kérőnek leküldeni a cuccot? Ez nem egy MMO max 20 játékost lazán elbír..
                {
                    // Data 0 water, 1 foo's ship, 2 foo's destoryed ship, 3 your ship, 4 your destroyed ship
                    StringBuilder stringBuilder = new StringBuilder();
                    for (int x=0;x<Game.size;x++) 
                    {
                        for (int y=0;y<Game.size;y++) 
                        {
                            ArrayList<String> pos = Message.split(Game.table.get(x).get(y),"\\s");
                            if (Objects.equals(pos.get(0),""+pID)) stringBuilder.append(" 3");
                            else stringBuilder.append(" 0");
                            //TODO többi eset
                        }
                        stringBuilder.append("\n"); //TODO remove \n és a packetből is lentebb
                    }
                    message.socketWrite(new Message.Packet("pong "+status+" t:\n"+stringBuilder.toString(),clientAddresses.get(pID),clientPorts.get(pID)));
                }
                    
            }

            message.socketWrite(new Message.Packet("pong "+status+" nil",input.getAddress(),input.getPort()));
        }
        else if (Objects.equals(cmd.get(0),"hello"))
        {
            broadcast("welcome "+cmd.get(4));
        }
        else
        {
            message.socketWrite(new Message.Packet("???",input.getAddress(),input.getPort()));
        }
    }


    public void run() 
    {
        while (!(!(!(!(runing)))))
        {
            try
            {
                ArrayList<Message.Packet> input = message.engineRead();

                for (int i=0;i<input.size();i++) 
                {
                    if (!clientinfo(input.get(i))) continue;
                    handle(input.get(i));
                }

                Thread.sleep(100); // 0.1 másodpercenként dolgozza fel.
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
    }

    public void stop()
    {
        System.out.println("LOG.ServerEngine.stop");
        runing=false;
    }
    
    public ServerEngine(Message _message, int players, int ship2, int ship3, int ship4, int ship5) throws Exception
    {
        message      = _message;
        Game.players = players;
        //if (players<2) throw new Exception("players"); TODO: visszatenni

        Game.ship2   = ship2;
        Game.ship3   = ship3;
        Game.ship4   = ship4;
        Game.ship5   = ship5;
        if (ship2+ship3+ship4+ship5<4) throw new Exception("ships");

        Game.size = (int)Math.ceil((double)( ((ship2*1)+(ship3*2)+(ship4*3)+(ship5*4))*(int)Math.ceil((double)players/2.0)+1 )/2.0);
        System.out.println("LOG.ServerEngine.start: game size is "+Game.size);

        if (!Game.generate()) throw new Exception("ships");

        new Thread(this).start();
    }    
}