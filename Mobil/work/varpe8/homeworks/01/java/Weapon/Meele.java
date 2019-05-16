package Weapon;
import Weapon.Weapon;

public interface Meele extends Weapon
{
    public Integer swing();
    default public Integer attack()
    {
        return swing();
    }
}