package vp.io;

import java.io.*;

public class BuffWriter {
    static public void addNewLine(Writer writer,String line,int indent) throws IOException
    {
        while (indent>0) {line="\t"+line; indent--;}
        BufferedWriter bufferedWriter = new BufferedWriter(writer);
        bufferedWriter.write(line, 0, line.length());
        bufferedWriter.newLine();
        bufferedWriter.flush();
    }
}