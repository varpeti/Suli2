import vp.svg.picture.Picture;
import java.io.*;
import java.util.*;

public class Main
{
    static Boolean isHTML = false;
    

    static void showhelp()
    {
        System.out.println("Usage: <this> [parameters] inputfilename outputfilename\n"+
            "    Parameters:\n"+
            "        --help      - show this\n"+
            "        --html      - write the output file in HTML format\n"
        );
    }

    public static void main(String[] args) 
    {
        Picture picture = new Picture();
        try{
            if      (args.length==0) { showhelp(); throw new IOException("Missing arguents!"); }
            else if (args.length==1) { showhelp(); throw new IOException();                    }
            
            for (int i=0;i<args.length;i++) 
            {
                    if      (Objects.equals(args[i],"--help")) showhelp() ;
                    else if (Objects.equals(args[i],"--html")) isHTML=true;
            }

            picture.build(args[args.length-2]);
            picture.write(args[args.length-1],isHTML);

        }catch (Exception e) {
            if (!Objects.equals(e.getMessage(),null)) System.err.println(e.getMessage()); //stderr-re írja ki
        }
        

        try{System.in.read();}catch(Exception e){} //TODO: earse me
    }
}