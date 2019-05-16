package hu.ppke.itk.java.second.io;

import java.io.*;

/**
 * Első feladat: billzetről olvasás, fájlba írás, fájlból olvasás
 * 
 * @author zelgala
 * 
 */
public class ReadWrite {

    /**
     * Beolvas egy sort a billentyűzetről és visszatér vele egy egyszerű
     * String-ként!
     * 
     * @return str 
     *          ezt olvasta be
     * @throws IOExcetion
     */
    public static String readFromKeyboard() throws IOException {
        BufferedReader br = new BufferedReader( new InputStreamReader(System.in) );
        return br.readLine();
    }

    /**
     * A writeToFile egy Stringet ír ki egy fájlba Figyelni kell rá ha nem
     * zárjuk le a fájlt a kiírás nem történik meg!
     * 
     * @param data
     *          mit írjon ki
     * @param destination
     *          ide írja ki
     * @throws IOExcetion
     */
    public static void writeToFile(String data, String destination) throws IOException {
        PrintWriter file = new PrintWriter(new FileWriter(destination));
        file.println(data);
        file.close();
    }

    /**
     * A readFromFile() egy fájlból olvas ki egy sort és visszatér vele 
     * egy egyszerű String-ként!
     * 
     * @param source
     *          melyik fájlból
     * @return str 
     *          ezt olvasta be
     * @throws IOExcetion
     */
    public static String readFromFile(String source) throws IOException {
        String str = "";
        BufferedReader br = new BufferedReader(new FileReader(source));
        str = br.readLine();
        br.close();
        return str;
    }

    /**
     * A keyboardToFile a billentyűzetről beolvasott sort írja ki egy fájlba
     * Figyelni kell rá, ha nem zárjuk le a fájlt, a kiírás nem történik meg!
     * 
     * @param destination
     *          ide írja ki
     * @throws IOException
     */
    public static void keyboardToFile(String destination) throws IOException {
        writeToFile(readFromKeyboard(), destination);
    }

    /**
     * Ebben a main függvényben hívódnak meg a fvek, amiket meg kell írni NE
     * MÓDOSÍTSD!!!
     * 
     * @param args
     */
    public static void main(String[] args) {
        String str;
        String sourceFile = "source.txt";
        String destinationFile1 = "result1.txt";
        String destinationFile2 = "result2.txt";
        try {
            System.out
                    .println("Reading from the keyboard (readFromKeyboard method):");
            str = readFromKeyboard();
            System.out.println("You wrote this:" + str);

            System.out.println("Write the result into the result1.txt:" + str);
            writeToFile(str, destinationFile1);

            String beolvasott = readFromFile(sourceFile);
            System.out.println("Reading from the source file: " + beolvasott);

            System.out
                    .println("Reading from the keyboard and writing into file at the same time:");
            keyboardToFile(destinationFile2);
            System.out.println("You wrote this into the result2.txt: "
                    + readFromFile(destinationFile2));
        } catch (IOException e) {
            System.out.println("It was an Exception!");
        }
        while(true);
    }
}
