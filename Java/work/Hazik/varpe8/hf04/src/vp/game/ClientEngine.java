package vp.game;

import java.util.*;

import vp.net.*;
import vp.game.*;

public class ClientEngine implements Runnable
{
    private Message message;

    private Server server;
    private ServerEngine serverEngine;

    private void handle(Message.Packet input)
    {
        System.out.println("LOG.Client."+name+".handle: "+input.getMsg());

        ArrayList<String> cmd = Message.split(input.getMsg(),"\\s");

        if (Objects.equals(cmd.get(0),"pong"))
        {
            if (Objects.equals(cmd.get(1),"wait4players"))
            {
                message.guiWrite(new Message.Packet(cmd.get(1)+" "+cmd.get(2)+" "+cmd.get(3))); //wait4players max cur
            }
            else if (Objects.equals(cmd.get(1),"game"))
            {
                message.guiWrite(new Message.Packet(input.getMsg())); // x. játékos
            }
        }
        else if (Objects.equals(cmd.get(0),"startclient"))
        {
            Client client = new Client(cmd.get(1),Integer.parseInt(cmd.get(2)),message);
        }
        else if (Objects.equals(cmd.get(0),"startserver"))
        {
            Message server_message = new Message();
            try
            {
                int port = Integer.parseInt(cmd.get(6));
                if (port<1 || port>65535) throw new Exception("port");

                server = new Server(Integer.parseInt(cmd.get(6)),server_message);
                
                serverEngine = new ServerEngine(server_message,
                    Integer.parseInt(cmd.get(1)),
                    Integer.parseInt(cmd.get(2)),
                    Integer.parseInt(cmd.get(3)),
                    Integer.parseInt(cmd.get(4)),
                    Integer.parseInt(cmd.get(5))
                );

                message.engineWrite(new Message.Packet("startclient"
                + " " + "localhost"
                + " " + port
                ));
                System.out.println(cmd.get(5));
            }
            catch (Exception e)
            {
                //Ha valami rossz leállítunk mindent
                try
                {
                    server.stop();
                    serverEngine.stop();
                }
                catch (Exception e2) 
                {    
                }
                message.guiWrite(new Message.Packet("error setServerInvaildInput "+e.getMessage())); 
            }
            
        }
        /*else if (Objects.equals(cmd.get(0),"stopserver"))
        {
            server.stop();
            serverEngine.stop();
        }*/
        else if (Objects.equals(cmd.get(0),"setname"))
        {
            name = cmd.get(1);
            message.socketWrite(new Message.Packet("hello my name is "+name));
        }
        else if (Objects.equals(cmd.get(0),"error"))
        {
           message.guiWrite(new Message.Packet(input.getMsg())); //Az egészet tovább küldi a GUInak.
        }
            
    }

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<Message.Packet> input = message.engineRead();

                for (int i=0;i<input.size();i++)
                {
                    handle(input.get(i));
                }

                message.socketWrite(new Message.Packet("ping "+name)); // Pulzáló életjel a szervernek

                Thread.sleep(1000); // Másodpercenként dolgozza fel, küld fel adatot, pulzál.
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
    }
    
    public ClientEngine(Message _message)
    {
        message = _message;
        message.socketWrite(new Message.Packet(new String("ping nil")));
        new Thread(this).start();
    }

    String name = new String("nil");
}