import java.util.*;

import Weapon.L1.L2.*;

public class Main
{
    public static void main(String[] args) 
    {
        Bayonett b = new Bayonett();
        System.out.println(b.name()+":");
        System.out.println("swing: "+b.swing());
        System.out.println("attack: "+b.attack()+"\n");

        Rifle r = new Rifle();
        System.out.println(r.name()+":");
        System.out.println("shoot: "+r.shoot());
        System.out.println("attack: "+r.attack()+"\n");

        BayonettRifle br = new BayonettRifle();

        System.out.println(br.name()+":");
        System.out.println("swing: "+br.swing());
        System.out.println("shoot: "+br.shoot());
        System.out.println("attack: "+br.attack()+"\n");

        try{System.in.read();}catch(Exception e){} //TODO: remove
    }
}