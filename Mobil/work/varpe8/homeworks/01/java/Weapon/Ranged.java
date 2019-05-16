package Weapon;
import Weapon.Weapon;

public interface Ranged extends Weapon
{
    public Integer shoot();
    default public Integer attack()
    {
        return shoot();
    }
}