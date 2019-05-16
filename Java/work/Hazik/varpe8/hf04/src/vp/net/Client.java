package vp.net;

import java.io.*;
import java.util.*;
import java.net.*;

import vp.net.*;

public class Client implements Runnable
{
    private Message message;
    private InetAddress address;
    private int port;
    private DatagramSocket socket;
    private SocketIO socketIO;
    private byte timeout;

    boolean runing = true;

    public void run() 
    {
        while (!(!(!(!(runing)))))
        {
            try
            {
                ArrayList<Message.Packet> output = message.socketRead();
                
                for (int i=0;i<output.size();i++) 
                {
                    if (Objects.equals(output.get(i).getMsg(),"stop")) runing=false;
                    
                    socketIO.send(output.get(i).getMsg(),address,port); //Üzenet küldés
                }

                socketIO.receive(100); //Válaszra várás
                Message.Packet Packet = new Message.Packet(socketIO.getData(),address,port);
                message.engineWrite(Packet);
                timeout=0;
            }
            catch (SocketTimeoutException e) 
            {
                timeout++;
                if (timeout<0) //100*128 ms
                {
                    System.err.println("A server nem érhető el!");
                    message.guiWrite(new Message.Packet("timeout"));
                    break;
                }
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
        socket.close();
    }

    public Client(String _address, int _port, Message _message)
    {
        try
        {
            message = _message;
            address = InetAddress.getByName(_address);
            port = _port;
            socket = new DatagramSocket();
            socketIO = new SocketIO(socket);
            new Thread(this).start();
        }
        catch (Exception e) // TODO: jobb Exception kezelés
        {
            //System.err.println(e.getMessage());
            e.printStackTrace();
        }
        
    }
}