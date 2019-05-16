package Weapon.L1;
import Weapon.Meele;

public interface Sword extends Meele 
{
    default public Integer swing()
    {
        return new Integer(13);
    }    
}