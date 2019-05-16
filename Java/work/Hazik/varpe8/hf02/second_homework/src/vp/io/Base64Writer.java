package vp.io;

import java.io.*;
import java.util.*;

public class Base64Writer extends java.io.Writer
{
    private StringBuilder buffer = new StringBuilder();

    public Base64Writer() throws IOException 
    {
        super();
    }

    @Override
    public void write(char[] cbuf, int off, int len) throws IOException 
    {
        String ss = new String(cbuf, off, len);
        buffer.append(ss);
    }

    public String toString()
    {
        return Base64.getEncoder().encodeToString(buffer.toString().getBytes());
    }

    @Override
    public void close() throws IOException
    {
        super.write(Base64.getEncoder().encodeToString(buffer.toString().getBytes()));
    }

    @Override
    public void flush() throws IOException{};
}