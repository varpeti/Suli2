import java.util.*;

import Singleton.Singleton;

public class Main
{
    public static void main(String[] args) 
    {
        Singleton obj = Singleton.getInstance();
        obj.method();
        Singleton obj2 = Singleton.getInstance();
        obj2.method();

        try{System.in.read();}catch(Exception e){} //TODO: remove
    }
}