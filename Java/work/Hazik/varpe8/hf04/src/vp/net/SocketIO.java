package vp.net;

import java.net.*;
import java.io.*;

public class SocketIO 
{
    private DatagramSocket socket;
    private byte[] inputB = new byte[1024];
    private DatagramPacket inputPacket;

    public SocketIO(DatagramSocket _socket)
    {
        socket = _socket;
    }

    //Egy IP:port szerverre küld egy Stringet
    public void send(String data, InetAddress address, int port) throws IOException
    {
        byte[] outputB = new byte[1024]; 
        outputB = data.getBytes();
        DatagramPacket outputPacket = new DatagramPacket(outputB, outputB.length, address, port);
        socket.send(outputPacket);
    }

    //Visszaküld a kliensnek egy Stringet, elötte kell egy socketIO.receive() !!!
    public void send(String data) throws IOException, NullPointerException
    {
        byte[] outputB = new byte[1024]; 
        outputB = data.getBytes();
        DatagramPacket outputPacket = new DatagramPacket(outputB, outputB.length, getAddress(), getPort()); // NullPointerException
        socket.send(outputPacket);
    }

    //Kérésre, válaszra vár, bármeddig (ajánlott: server)
    public void receive() throws IOException, SocketTimeoutException
    {
        socket.setSoTimeout(0);
        inputB = new byte[1024];
        inputPacket = new DatagramPacket(inputB, inputB.length);
        socket.receive(inputPacket);
    }

    //Kérésre, válaszra vár, adott ideig. (ajánlott: cliens)
    public void receive(int timeout) throws IOException, SocketTimeoutException
    {
        socket.setSoTimeout(timeout);
        inputB = new byte[1024];
        inputPacket = new DatagramPacket(inputB, inputB.length);
        socket.receive(inputPacket);
    }

    // A socketIO.receive() által kapott adatok getterei, elötte kell a socketIO.receive() !!!

    public InetAddress getAddress() throws NullPointerException
    {
        return inputPacket.getAddress();
    }

    public int getPort() throws NullPointerException
    {
        return inputPacket.getPort();
    }

    public String getData() throws NullPointerException
    {
        return new String (inputB,0,inputPacket.getLength());
    }
}