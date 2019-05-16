package vp.net;

import java.io.*;
import java.util.*;
import java.net.*;

import vp.net.*;

public class Server implements Runnable
{
    private Message message;
    static private DatagramSocket socket;

    boolean runing = true;

    public class ClientThread implements Runnable
    {
        SocketIO socketIO;
    
        public void run()
        {
            try 
            {
                InetAddress clientAddress = socketIO.getAddress(); //cliens IP cím
                int clientPort = socketIO.getPort(); // cliens Port
                String input = socketIO.getData(); // A string amit küldött

                message.engineWrite(new Message.Packet(input,clientAddress,clientPort) );

                ArrayList<Message.Packet> output = message.socketRead();
                
                for (int i=0;i<output.size();i++) 
                {
                    Message.Packet msgPacket = output.get(i);
                    if (!msgPacket.isAddressed()) continue; //throw new Exception("Message.Packet: Missing client address:port!");
                    socketIO.send(msgPacket.getMsg(),msgPacket.getAddress(),msgPacket.getPort()); //Üzenet küldés
                }
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }

        ClientThread(SocketIO _socketIO)
        {
            socketIO = _socketIO;
        }
    }

    public void run()
    {
        while (!(!(!(!(runing)))))
        {
            try 
            {   
                SocketIO _socketIO = new SocketIO(socket);
                _socketIO.receive(); //Várakozás a requestre

                new Thread(new ClientThread(_socketIO)).start(); //Ha van request, külön szállra rakom ki.
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
                if (false) break;
            }
        }
        socket.close();
    }

    public Server(int port, Message _message) throws Exception
    {
        try
        {
            message = _message;
            socket = new DatagramSocket(port); //Socket foglalás
            new Thread(this).start();
        }
        catch (Exception e)
        {
            throw new Exception("bound");
        }
    }

    public void stop()
    {
        System.out.println("LOG.Server.stop");
        runing=false;
    }
}