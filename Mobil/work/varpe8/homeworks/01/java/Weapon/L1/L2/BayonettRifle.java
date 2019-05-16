package Weapon.L1.L2;
import Weapon.L1.*;

public class BayonettRifle implements Gun, Sword
{
    public String name()
    {
        return new String("BayonettRifle");
    }

    public Integer swing() 
    {
        return new Integer(11);
    }

    public Integer shoot() 
    {
        return new Integer(12);
    }

	// How to use the implementationn of superclass? (interface)
	
    public Integer attack()
    {
        return swing() + shoot();
    }
}