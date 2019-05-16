import java.util.*;

import GoldenAK47.GoldenAK47;

public class Main
{
    public static void main(String[] args) 
    {
        GoldenAK47 goldenAK47_1 = GoldenAK47.getInstance();
        goldenAK47_1.shoot();

        GoldenAK47 goldenAK47_2 = GoldenAK47.getInstance();
        goldenAK47_2.shoot();

        System.out.println("(goldenAK47_1.hashCode()==goldenAK47_2.hashCode()) is " + (goldenAK47_1.hashCode()==goldenAK47_2.hashCode()) );

        //try{System.in.read();}catch(Exception e){} // TODO remove me
    }
}